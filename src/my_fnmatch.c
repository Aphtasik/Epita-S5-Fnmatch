#include "my_fnmatch.h"

#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h> //TODO: remove

static int  my_strlen(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

static int handle_hook(const char *pattern, char s_c, int *p_i)
{
    //check if a char btw hooks == s_c
    //if it is incr p_i until ]
    //else no matching
    int is_found = 0;
    while (pattern[*p_i] != ']')
    {
        if (pattern[*p_i] == '\0')
        {
            return is_found;
            *p_i += 1;
        }
        else if (pattern[*p_i])
        {
            is_found = 1;
        }
        *p_i += 1;
    }

    *p_i += 1;

    return is_found;
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
            case '[':
                if (handle_hook(pattern, string[s_i], &p_i))
                {
                    s_i++;
                    continue;
                }
                return 0;
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

