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

#if defined(__FreeBSD__)
struct pam_conv pamc = { &openpam_ttyconv, NULL };
#elif defined(__linux__)
struct pam_conv pamc = { &misc_conv, NULL };
#endif
pam_handle_t *pamh = NULL;
int pam_err;
int pam_session_opened = 0;

#define PAM_RETURN_ON_FAILURE if(pam_err != PAM_SUCCESS) return;


char *get_ttyname()
{
    char *tty = ttyname(STDERR_FILENO);
    if(! tty) tty = "tty";
    return tty;
}

void authenticate()
{
    pam_err = pam_start("please", "root", &pamc, &pamh);
    PAM_RETURN_ON_FAILURE;

    pam_err = pam_set_item(pamh, PAM_RUSER, getlogin());
    PAM_RETURN_ON_FAILURE;

    pam_err = pam_set_item(pamh, PAM_TTY, get_ttyname());
    PAM_RETURN_ON_FAILURE;

    pam_err = pam_authenticate(pamh, 0);
    PAM_RETURN_ON_FAILURE;

    if(PAM_NEW_AUTHTOK_REQD == pam_acct_mgmt(pamh, 0)) {
        pam_err = pam_chauthtok(pamh, PAM_CHANGE_EXPIRED_AUTHTOK);
        PAM_RETURN_ON_FAILURE;
    }

    pam_err = pam_setcred(pamh, PAM_ESTABLISH_CRED);
    PAM_RETURN_ON_FAILURE;

    pam_err = pam_open_session(pamh, 0);
    PAM_RETURN_ON_FAILURE;
    pam_session_opened = 1;
}

void finish()
{
    if(pam_session_opened) {
        pam_err = pam_close_session(pamh, 0);
    }

    pam_end(pamh, pam_err);
}

int main(int ac, char **av)
{
    int err;
    av++;

    if(! av[0]) {
        fprintf(stderr, "Nothing to do\n");
        return 0;
    }

    authenticate();

    if(PAM_SUCCESS != pam_err) {
        fprintf(stderr, "Authentication failure\n");
        finish();
        return 1;
    }

    finish();

    if(err = execvp(av[0], av)) {
        fprintf(stderr, "Command '%s' not found\n", av[0]);
        return err;
    }
}
