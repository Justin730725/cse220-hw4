/*
 * CSE 220 Homework 4, Part 1 tests.
 *
 * A few sample tests are given so you can see how Criterion is set up. They
 * fail until you implement the functions, which is expected.
 *
 * You must add your own tests: at least 5 per function, for all six functions
 * in strgPtr.c. Test the edge cases too, not only the examples from the
 * assignment: NULL arguments, empty strings, and buffers that are too small.
 *
 * Build and run these with:   make test
 */
#include <criterion/criterion.h>
#include "strgPtr.h"

/* Test(suite_name, test_name) is how Criterion declares one test. */
Test(strgLen, counts_characters)
{
    cr_assert_eq(strgLen("Stony Brook"), 11);
    cr_assert_eq(strgLen(""), 0);
}

Test(strgLen, null_is_an_error)
{
    cr_assert_eq(strgLen(NULL), -1);
}

Test(strgCopy, copies_a_short_string)
{
    char destination[20];

    strgCopy("Computer Science", destination, sizeof destination);
    cr_assert_str_eq(destination, "Computer Science");
}

Test(strgCopy, stops_when_the_buffer_is_full)
{
    char destination[5];

    strgCopy("Computer Science", destination, sizeof destination);
    cr_assert_str_eq(destination, "Comp");
}

Test(strgChangeCase, skips_letters_next_to_digits)
{
    char s[] = "CSE220";

    strgChangeCase(s);
    cr_assert_str_eq(s, "csE220");
}

/*
 * TODO: add your own tests below.
 *
 * You still need more tests for strgLen, strgCopy and strgChangeCase, and at
 * least 5 tests each for strgDiff, strgInterleave and strgReverseLetters.
 *
 * Useful assertions:
 *   cr_assert_eq(actual, expected)       two values are equal
 *   cr_assert_str_eq(actual, expected)   two strings have the same contents
 *   cr_assert_null(pointer)              the pointer is NULL
 *   cr_assert(condition)                 the condition is true
 */
