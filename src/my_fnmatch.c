#include "my_fnmatch.h"

#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

static int  my_strlen(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

// pattern = string with glob / string = without 
int my_fnmatch(const char *pattern, const char *string)
{
    int p_i = 0;
    int s_i = 0;
    
    char c;

    int p_len = my_strlen(pattern);
    int s_len = my_strlen(string);

    while (p_i < p_len || s_i < s_len)
    {
        // p_i > => normal string too long for string
        if (p_i < p_len)
        {
            // test all cases
            c = pattern[p_i];
            switch (c)
            {
            case '?':
                s_i++;
                p_i++;
                continue;
            default:
                if (string[s_i] == c)
                {
                    s_i++;
                    p_i++;
                    continue;
                }
                return 0;
            }
        }
        return 0;
    }
    return 1;
}

