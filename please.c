/*
 * Copyright (c) 2012-2021 Grzegorz Blach. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <security/pam_appl.h>

#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__)
# include <security/openpam.h>
#elif defined(__linux__)
# include <security/pam_misc.h>
#endif

#define PAM_RETURN_ON_FAILURE if(pam_err != PAM_SUCCESS) goto pam_return;

int authenticate()
{
#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__)
    struct pam_conv pamc = { &openpam_ttyconv, NULL };
#elif defined(__linux__)
    struct pam_conv pamc = { &misc_conv, NULL };
#endif
    pam_handle_t *pamh = NULL;
    int pam_err;
    char *username = getlogin();

    pam_err = pam_start("please", username, &pamc, &pamh);
    PAM_RETURN_ON_FAILURE;

    pam_err = pam_set_item(pamh, PAM_USER, "root");
    PAM_RETURN_ON_FAILURE;

    pam_err = pam_set_item(pamh, PAM_RUSER, username);
    PAM_RETURN_ON_FAILURE;

    pam_err = pam_set_item(pamh, PAM_TTY, ttyname(STDERR_FILENO));
    PAM_RETURN_ON_FAILURE;

    pam_err = pam_authenticate(pamh, 0);
    PAM_RETURN_ON_FAILURE;

    pam_err = pam_acct_mgmt(pamh, 0);
    if(pam_err == PAM_NEW_AUTHTOK_REQD)
        pam_err = pam_chauthtok(pamh, PAM_CHANGE_EXPIRED_AUTHTOK);
    PAM_RETURN_ON_FAILURE;

pam_return:
    openlog("please", 0, LOG_AUTH);
    if(pam_err == PAM_SUCCESS)
        syslog(LOG_NOTICE, "user %s authenticated\n", username);
    else
        syslog(LOG_NOTICE, "%s", pam_strerror(pamh, pam_err));
    closelog();

    pam_end(pamh, pam_err);
    return pam_err == PAM_SUCCESS ? 0 : -1;
}

int main(int ac, char **av)
{
    int err;
    av++;

    if(! av[0]) {
        fprintf(stderr, "Nothing to do\n");
        return 0;
    }

    if((err = authenticate())) {
        fprintf(stderr, "Authentication failure\n");
        return err;
    }

    if((err = setuid(0))) {
        perror(NULL);
        return err;
    }

    if((err = setgid(0))) {
        perror(NULL);
        return err;
    }

    if(!strcmp(av[0], "-")) {
        struct passwd *pwd = getpwuid(0);
        if((err = execl(pwd->pw_shell, pwd->pw_shell, NULL))) {
            perror(NULL);
            return err;
        }
    }

    if((err = execvp(av[0], av))) {
        fprintf(stderr, "Command '%s' not found\n", av[0]);
        return err;
    }
}
