/*
source code
*/
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {

    char    *args[] = {"/bin/sh", NULL};
    gid_t   gid; //real group ID
    uid_t   uid; //real user ID
    int     nb;
    (void)argc;

    nb = atoi(argv[1]);
    if (nb == 423) {
        args[0] = strdup("/bin/sh");
        args[1] = 0;
        gid = getegid();
        uid = geteuid();

        setresuid(uid, uid, uid);
        setresgid(gid, gid, gid);

        execv("/bin/sh", args);
    } else {
        fwrite("No !\n", sizeof(char), strlen("No ! \n"), stderr);
    }
    return 0;
}