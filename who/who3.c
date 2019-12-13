/*who1.c - a first version of the who program
 *       - open, read UTMP file, and show results
 *       - formats time nicely
 *       - buffers input(using utmplib.h)
 */

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "utmplib.h"

#define SHOWHOST            /*include remote machine on output*/

void showtime(long);
void show_info(struct utmp *utbufp);

int main() {
    struct utmp *utbufp, *utmp_next();      

    if((utmp_open(UTMP_FILE) == -1)) {
        perror(UTMP_FILE);           /*UTMP_FILE is in utmp.h*/
        exit(1);
    }

    while((utbufp = utmp_next()) != (struct utmp *)NULL)
        show_info(utbufp);
    utmp_close();
      
    return 0;           /*went ok*/
}

/*
 * show_info()
 * display the contents of the utmp sruct
 * in human readable form
 * displays nothing if record no user name
 */

void show_info(struct utmp *utbufp) {
    if(utbufp->ut_type != USER_PROCESS)     /*users only*/
        return;
    printf("%-8.8s", utbufp->ut_name);      /*the logname*/
    printf(" ");                            /*a space*/
    printf("%-8.8s", utbufp->ut_line);      /*the tty*/
    printf(" ");                            /*a space*/
    showtime(utbufp->ut_time);              /*display time*/
#ifdef SHOWHOST                     
    printf("(%s)", utbufp->ut_host);       /*the host*/
#endif
    printf("\n");                           /*new line*/
}

void showtime(long timeval) {
/*
 *display time in a format fit for human consumption
 *uses ctime to build a string then picks parts out of it
 *Note: %12.12s prints a string 12 chars wide and LIMITS
 *it to 12 chars
 */
    char  *cp;                                /*to hold address of time*/
    cp = ctime(&timeval);                   /*convert time to string*/
                                            /*string looks like*/
                                            /*Mon Feb 4 00:46:40 EST 1991*/
                                            /*0123456789012345.*/
    printf("%12.12s", cp+4);                /*pick 12 chars from pos 4*/
}

