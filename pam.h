#include <security/pam_appl.h>

int check_password();
int converse(int n, const struct pam_message **msg, struct pam_response **resp, void *data);
