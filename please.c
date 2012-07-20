#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>

#define GROUPS 100


char* wheel_name()
{
    struct group *gr = getgrgid(0);
    return gr->gr_name;
}

int in_wheel()
{
    int groups[GROUPS];
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

    execvp(av[0], av);
}
