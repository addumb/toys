#include<stdio.h>

main() {
    char *ch = "Heyyyyyyy";
    printf("%s\n", ch);
    int len = 0;
    while (*ch) {
        printf("%s\n", ch);
        ch++;
        len++;
    }
    ch-=len;
    printf("How long?: %d\n", len);
    printf("Still there?: %s\n", ch);
}
