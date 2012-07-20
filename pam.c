#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pam.h"


int check_password()
{
    struct pam_conv pamc;
    pam_handle_t *pamh = NULL;
    int retval;

    pamc.conv = &converse;
    pamc.appdata_ptr = NULL;

    retval = pam_start("please", getlogin(), &pamc, &pamh);
    retval = pam_authenticate(pamh, 0);

    return retval == PAM_SUCCESS;
}

int converse(int n, const struct pam_message **msg, struct pam_response **resp, void *data)
{
    struct pam_response *aresp;
    char buf[PAM_MAX_RESP_SIZE];

    data = data;
    if (n <= 0 || n > PAM_MAX_NUM_MSG) return (PAM_CONV_ERR);
    if ((aresp = calloc(n, sizeof *aresp)) == NULL) return (PAM_BUF_ERR);

    for(int i = 0; i < n; i++)
    {
        aresp[i].resp_retcode = 0;
	aresp[i].resp = NULL;
	
        switch (msg[i]->msg_style)
        {
	    case PAM_PROMPT_ECHO_OFF:
	        aresp[i].resp = strdup(getpass(msg[i]->msg));
		if(aresp[i].resp == NULL) goto fail;
		break;
	    
            case PAM_PROMPT_ECHO_ON:
		fputs(msg[i]->msg, stderr);
		if(fgets(buf, sizeof buf, stdin) == NULL) goto fail;
		aresp[i].resp = strdup(buf);
		if(aresp[i].resp == NULL) goto fail;
		break;
	
            case PAM_ERROR_MSG:
		fputs(msg[i]->msg, stderr);
		if(strlen(msg[i]->msg) > 0 && msg[i]->msg[strlen(msg[i]->msg) - 1] != '\n') fputc('\n', stderr);
		break;
	
            case PAM_TEXT_INFO:
		fputs(msg[i]->msg, stdout);
		if (strlen(msg[i]->msg) > 0 && msg[i]->msg[strlen(msg[i]->msg) - 1] != '\n') fputc('\n', stdout);
		break;
	    
            default:
		goto fail;
	}
    }

    *resp = aresp;
    return (PAM_SUCCESS);

fail:

    for(int i = 0; i < n; ++i) {
        if(aresp[i].resp != NULL) {
            memset(aresp[i].resp, 0, strlen(aresp[i].resp));
            free(aresp[i].resp);
        }
    }

    memset(aresp, 0, n * sizeof *aresp);
    *resp = NULL;
    return (PAM_CONV_ERR);
}
