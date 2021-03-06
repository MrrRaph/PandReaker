#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <string.h>
#include <sys/time.h>

#include "../includes/breakerFor.h"

int main(int argc, char ** argv) {
    char * password;
    struct timeval t1;
    struct timeval t2;
    char first_char, last_char;
    int cmp;

    if(argc == 1) {
        password = "A$4c";
        first_char = 32;
        last_char = 126;
        /* ---ASCII values---
         * special characters: 	32 to 47
         * numbers: 		48 to 57
         * special characters: 	58 to 64
         * letters uppercase: 	65 to 90
         * special characters: 	91 to 96
         * letters lowercase: 	97 to 122
         * special characters: 	123 to 126
         * */
    } else if(argc == 4) {
        password = argv[1];
        first_char = atoi(argv[2]);
        last_char = atoi(argv[3]);
    } else {
        printf("usage: breaker <password> <first_ch> <last_ch>\n");
        printf("default: breaker A$4c 32 126\n");
        printf("exemple to break the binary password 1101000:\n");
        printf("breaker 1101000 48 49\n");
        exit( 0 );
    }
    char * crypted0 = crypt(password, "salt");
    char * crypted = (char*) malloc(strlen(crypted0) + 1);
    strcpy(crypted, crypted0);

    printf("*running parameters*\n");
    printf(" -password length:\t%lu digits\n", strlen(password));
    printf(" -digits:\t\tfrom -%c- to -%c-\n", first_char, last_char);
    printf(" -crypted to break:\t%s\n", crypted);

    gettimeofday(&t1, NULL);
    cmp = search_all(crypted, (int) strlen(password), first_char, last_char);
    gettimeofday(&t2, NULL);

    double period =(double)((int)(t2.tv_sec-t1.tv_sec))+((double)(t2.tv_usec-t1.tv_usec))/1000000;

    printf("time: %dmin %.3fs \n", (int)((t2.tv_sec-t1.tv_sec))/60, (double)((int)(t2.tv_sec-t1.tv_sec)%60)+((double)(t2.tv_usec-t1.tv_usec))/1000000);
    printf("#tries: %d\n", cmp);
    printf("=> efficiency: %.f tries/s\n", (double)cmp/period);

    return EXIT_SUCCESS;
}
