#include "my_fnmatch.h"

#include <stdio.h>

int main(void)
{
    int res = my_fnmatch("hell[po] world", "hello world");
    return 0;
}
