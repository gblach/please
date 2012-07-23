#include <stdio.h>
#include <unistd.h>
#include <security/pam_appl.h>

#if defined(__FreeBSD__)
# include <security/openpam.h>
#elif defined(__linux__)
# include <security/pam_misc.h>
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

#if defined(__FreeBSD__)
    pamc.conv = &openpam_ttyconv;
#elif defined(__linux__)
    pamc.conv = &misc_conv;
#endif
    pamc.appdata_ptr = NULL;

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
