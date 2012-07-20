#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>
#include "pam.h"

#define GROUPS 100


char *wheel_name()
{
    struct group *gr = getgrgid(0);
    return gr->gr_name;
}

int in_wheel()
{
    gid_t groups[GROUPS];
    int size = getgroups(GROUPS, groups);

    for(int i = 0; i < size; i++) {
        if(groups[i] == 0) return 1;
    }

    return 0;
}

int main(int ac, char **av)
{
    av++;

    if(! av[0]) {
        fprintf(stderr, "Nothing to do\n");
        return 0;
    }

    if(! in_wheel()) {
        fprintf(stderr, "You aren't in `%s` group\n", wheel_name());
        return 1;
    }

    if(0 != getuid() && ! check_password()) {
        fprintf(stderr, "Authenticaton failure\n");
        return 2;
    }

    execvp(av[0], av);
}
