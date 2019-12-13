/*filesize.c - prints size of passwd file*/

#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat infobuf;
    if(stat("/usr/include/stdio.h", &infobuf) == -1)
        perror("/usr/include/stdio.h");
    else
        printf("The size of /usr/include/stdio.h is %d\n", infobuf.st_size);
    return 0;
}
