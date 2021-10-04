#include "../src/my_fnmatch.h"

#include <criterion/criterion.h>
#include <fnmatch.h>

Test(basic, empty)
{
    int res = my_fnmatch("", "");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(basic, same_text)
{
    int res = my_fnmatch("hello world", "hello world");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(basic, different_text)
{
    int res = my_fnmatch("hello you", "hello world");
    cr_assert_neq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(basic, interrogation)
{
    int res = my_fnmatch("hell? you", "hello world");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(basic, stars_to_end)
{
    int res = my_fnmatch("hell*", "hello world");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(basic, stars_middle)
{
    int res = my_fnmatch("hell*ld", "hello world");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(basic, stars_start)
{
    int res = my_fnmatch("*world", "hello world");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}
