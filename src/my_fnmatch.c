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
static int my_fnmatch_rec(const char *pattern, const char *string, int p_len,
        int s_len, int p_i, int s_i)
{
    char c;

    while (p_i < p_len || s_i < s_len)
    {
        // p_i > => normal string too long for string
        if (p_i < p_len)
        {
            // test all cases
            c = pattern[p_i];
            switch (c)
            {
            case '*':
                while (s_i <= s_len)
                {
                    if (my_fnmatch_rec(pattern, string, p_len, s_len, p_i + 1, s_i) == 1)
                    {
                        return 1;
                    }
                    s_i++;
                }
                break;
            case '?':
                if (s_i < s_len)
                {
                    s_i++;
                    p_i++;
                    continue;
                }
                return 0;
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

int my_fnmatch(const char *pattern, const char *string)
{
    if ((!pattern && string) || (pattern && !string))
    {
        return 0;
    }
    else if (!pattern && !string)
    {
        return 1;
    }

    int p_len = my_strlen(pattern);
    int s_len = my_strlen(string);

    return my_fnmatch_rec(pattern, string, p_len, s_len, 0, 0);
}

