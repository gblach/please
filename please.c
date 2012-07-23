#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <security/pam_appl.h>

#ifdef __FREEBSD__
# include <security/openpam.h>
#endif

#ifndef MAXHOSTNAMELEN
# define MAXHOSTNAMELEN 256
#endif
 

int check_password()
{
    struct pam_conv pamc;
    pam_handle_t *pamh = NULL;
    int retval;
    char hostname[MAXHOSTNAMELEN];
    const char *tty;

#ifdef __FREEBSD__
    pamc = { &openpam_ttyconv, NULL };
#endif

    gethostname(hostname, sizeof(hostname));
    tty = ttyname(STDERR_FILENO);

    pam_start("please", getlogin(), &pamc, &pamh);
    pam_set_item(pamh, PAM_RHOST, hostname);
    pam_set_item(pamh, PAM_RUSER, getlogin());
    pam_set_item(pamh, PAM_TTY, tty);
    retval = pam_authenticate(pamh, 0);

    return retval == PAM_SUCCESS;
}

int main(int ac, char **av)
{
    av++;

    if(! av[0]) {
        fprintf(stderr, "Nothing to do\n");
        return 0;
    }

    if(! check_password()) {
        fprintf(stderr, "Authenticaton failure\n");
        return 2;
    }

    execvp(av[0], av);
}
