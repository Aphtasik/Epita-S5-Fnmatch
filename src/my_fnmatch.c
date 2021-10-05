#include "my_fnmatch.h"

#include <stdlib.h>
#include <stddef.h>

static int  my_strlen(const char *str, int start_i, char end_char)
{
    int len = 0;
    while (str[start_i + len] != end_char)
    {
        len++;
    }
    return len;
}

static int handle_hook(const char *pattern, char s_c, int *p_i)
{
    int neg = 1;
    int is_found = 1;
    *p_i += 1;
    if (pattern[*p_i] == '!')
    {
        neg = 0;
        *p_i += 1;
        if (pattern[*p_i] == s_c)
        {
            is_found = 0;
        }
        *p_i += 1;
    }

    int start = *p_i;
    int hook_len = my_strlen(pattern, start, ']');
    int end = start + hook_len;
    while (pattern[*p_i] != ']')
    {
        if (pattern[*p_i] == s_c)
        {
            is_found = 0;
        }
        else if ((pattern[*p_i] == '-' && (*p_i != end - 1)) || (*p_i != start + 1))
        {
            if (s_c >= pattern[*p_i - 1] && s_c <= pattern[*p_i + 1])
            {
                is_found = 0;
            }
        }
        *p_i += 1;
    }
    *p_i += 1;

    return (is_found && neg) || (!is_found && !neg);
}

static int my_fnmatch_rec(const char *pattern, const char *string, int p_len,
        int s_len, int p_i, int s_i)
{
    char c;

    while (p_i < p_len || s_i < s_len)
    {
        if (p_i < p_len)
        {
            c = pattern[p_i];
            switch (c)
            {
            case '\\':
                 if (s_i < s_len && pattern[p_i + 1] == string[s_i])
                 {
                         s_i++;
                         p_i += 2;
                         continue;
                 }
                 return 1;
            case '[':
                if (handle_hook(pattern, string[s_i], &p_i) == 0)
                {
                    s_i++;
                    continue;
                }
                return 1;
            case '*':
                while (s_i <= s_len)
                {
                    if (my_fnmatch_rec(pattern, string, p_len, s_len, p_i + 1, s_i) == 0)
                    {
                        return 0;
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
                return 1;
            default:
                if (string[s_i] == c)
                {
                    s_i++;
                    p_i++;
                    continue;
                }
                return 1;
            }
        }
        return 1;
    }
    return 0;
}

int my_fnmatch(const char *pattern, const char *string)
{
    if ((!pattern && string) || (pattern && !string))
    {
        return 1;
    }
    else if (!pattern && !string)
    {
        return 0;
    }

    int p_len = my_strlen(pattern, 0, '\0');
    int s_len = my_strlen(string, 0, '\0');

    return my_fnmatch_rec(pattern, string, p_len, s_len, 0, 0);
}

