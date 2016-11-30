/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2016-11-30
*
* 描述: Remove leading and trailing whitespace from string array or character array
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strrtrim(char *s)
{
    if (s) {
        char *t = s;
        while (*t) {
            t++;
        }
        while (--t > s && ((*t >= 9 && *t <= 13) || *t == 32)) ;
        t[1] = '\0';
    }

    return s;
}

char *strltrim(char *s)
{
    if (s) {
        char *t = s;
        while ((*t >= 9 && *t <= 13) || *t == 32) {
            t++;
        }
        if (t > s) {
            char *p = s;
            while( *p++ = *t++ ) ;
        }
    }
    return s;
}

char *strtrim(char *s)
{
    strrtrim(s);
    strltrim(s);

    return s;
}

int main(int argc, char *argv[])
{
    int i;
    char test_buffer[64];
    char *sample_strings[] =
    {
        "nothing to trim",
        "    trim the front",
        "trim the back     ",
        " trim one char front and back ",
        " trim one char front",
        "trim one char back ",
        "                   ",
        " ",
        "a",
        "",
        NULL
    };

    for(i = 0; sample_strings[i] != NULL; ++i)
    {
        strcpy(test_buffer, sample_strings[i]);
        printf("[%s] -> [%s]\n", sample_strings[i], strtrim(test_buffer));
    }

    /* The test prints the following:
    [nothing to trim] -> [nothing to trim]
    [    trim the front] -> [trim the front]
    [trim the back     ] -> [trim the back]
    [ trim one char front and back ] -> [trim one char front and back]
    [ trim one char front] -> [trim one char front]
    [trim one char back ] -> [trim one char back]
    [                   ] -> []
    [ ] -> []
    [a] -> [a]
    [] -> []
    */

    return 0;
}