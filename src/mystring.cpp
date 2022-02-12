#include "../include/mystring.h"

void myStrCat(char *base, char *toAdd)
{
    while (*base)
    {
        base++;
    }

    while (*toAdd)
    {
        *base++ = *toAdd++;
    }
    *base = '\0';
}

int myStrLen(char *base)
{
    int len = 0;

    while (*base)
    {
        base++;
        len++;
    }
    return len;
}

int myStrCmp(char *a, char *b)
{
    // Needs to be finished.
    return 0;
}
