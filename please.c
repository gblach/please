#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <security/pam_appl.h>

#if defined(__FreeBSD__)
# include <sys/param.h>
# include <security/openpam.h>
#elif defined(__linux__)
# include <asm/param.h>
# include <security/pam_misc.h>
#endif
 

char *get_hostname()
{
    char hostname[MAXHOSTNAMELEN];
    gethostname(hostname, sizeof(hostname));
    return strdup(hostname);
}

char *get_ttyname()
{
    char *tty;
    tty = ttyname(STDERR_FILENO);
    if(! tty) tty = "tty";
    return tty;
}

int authenticate()
{
#if defined(__FreeBSD__)
    struct pam_conv pamc = { &openpam_ttyconv, NULL };
#elif defined(__linux__)
    struct pam_conv pamc = { &misc_conv, NULL };
#endif
    pam_handle_t *pamh = NULL;
    int retval;

    pam_start("please", getlogin(), &pamc, &pamh);
    pam_set_item(pamh, PAM_RHOST, get_hostname());
    pam_set_item(pamh, PAM_RUSER, getlogin());
    pam_set_item(pamh, PAM_TTY, get_ttyname());
    retval = pam_authenticate(pamh, 0);
    pam_end(pamh, retval);

    return retval == PAM_SUCCESS;
}

int main(int ac, char **av)
{
    av++;

    if(! av[0]) {
        fprintf(stderr, "Nothing to do\n");
        return 0;
    }

    if(! authenticate()) {
        fprintf(stderr, "Authentication failure\n");
        return 1;
    }

    execvp(av[0], av);
}
