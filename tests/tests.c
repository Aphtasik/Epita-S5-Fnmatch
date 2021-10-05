#include "../src/my_fnmatch.h"

#include <criterion/criterion.h>
#include <fnmatch.h>

Test(basic, empty)
{
    int res = my_fnmatch("", "");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(basic, same_text)
{
    int res = my_fnmatch("hello world", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(basic, different_text)
{
    int res = my_fnmatch("hello youuu", "hello world");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(basic, short_pattern)
{
    int res = my_fnmatch("hello", "hello world");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(basic, short_string)
{
    int res = my_fnmatch("hello world", "hello");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(interrogation, one)
{
    int res = my_fnmatch("hell? world", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(interrogation, multiple)
{
    int res = my_fnmatch("hell? wo???", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(stars, to_end)
{
    int res = my_fnmatch("hel*", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(stars, middle)
{
    int res = my_fnmatch("hell*ld", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(stars, start)
{
    int res = my_fnmatch("*world", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(stars, multiple)
{
    int res = my_fnmatch("h*world", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(cocktail, stars_question)
{
    int res = my_fnmatch("hel*?orld", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(cocktail, stars_question_fail)
{
    int res = my_fnmatch("*?", "");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(set, short_set)
{
    int res = my_fnmatch("hell[po] world", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(set, long_set)
{
    int res = my_fnmatch("hell[pqro azryt] world", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(set, with_specials)
{
    int res = my_fnmatch("hello [i*[?h]orld", "hello ?orld");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(range, classic)
{
    int res = my_fnmatch("hello [a-z]orld", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(range, complexe)
{
    int res = my_fnmatch("hello [A-F0-9a-z]orld", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(range, false_case)
{
    int res = my_fnmatch("hello [A-F0-9]orld", "hello world");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(esc, esc_esc)
{
    int res = my_fnmatch("hello \\*world", "hello *world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(negative, simple_ok)
{
    int res = my_fnmatch("hello [!abcde]orld", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(negative, wrong)
{
    int res = my_fnmatch("hello [!abwde]orld", "hello world");
    cr_assert_eq(res, 1, "GOT: %d, EXPECTED: %d", res, 1);
}

Test(negative, special_first)
{
    int res = my_fnmatch("hello [!]b0de]orld", "hello world");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}

Test(hard_stuff, final_boss)
{
    int res = my_fnmatch("[-a-\\0]bite", "0bite");
    cr_assert_eq(res, 0, "GOT: %d, EXPECTED: %d", res, 0);
}
