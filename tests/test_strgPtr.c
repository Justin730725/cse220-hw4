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
#include <stddef.h>

/* Test(suite_name, test_name) is how Criterion declares one test. */

// strgLen test
Test(strgLen, counts_characters)
{
    cr_assert_eq(strgLen("Stony Brook"), 11);
    cr_assert_eq(strgLen(""), 0);
}

Test(strgLen, null_is_an_error)
{
    cr_assert_eq(strgLen(NULL), -1);
}

Test(strgLen, single_character_and_spaces)
{
    cr_assert_eq(strgLen(" "), 1);
    cr_assert_eq(strgLen("x"), 1);
}

Test(strgLen, alphanumeric_and_punctuation)
{
    cr_assert_eq(strgLen("CSE 220"), 7);
    cr_assert_eq(strgLen("CSE-220!"), 8);
}

Test(strgLen, long_sentence)
{
    cr_assert_eq(strgLen("System Fundamental"), 18);
}

// strgCopy test
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

Test(strgCopy, size_one_writes_only_null_terminator)
{
    char destination[5] = "init";

    strgCopy("abc", destination, 1);
    cr_assert_eq(destination[0], '\0');
}

Test(strgCopy, size_zero_does_nothing)
{
    char destination[10] = "untouched";

    strgCopy("Computer Science", destination, 0);
    cr_assert_str_eq(destination, "untouched");
}

Test(strgCopy, null_pointers_safe)
{
    char destination[10] = "untouched";

    strgCopy(NULL, destination, sizeof destination);
    cr_assert_str_eq(destination, "untouched");

    strgCopy("test", NULL, 10);
}

// strgChangeCase tests
Test(strgChangeCase, skips_letters_next_to_digits)
{
    char s[] = "CSE220";

    strgChangeCase(s);
    cr_assert_str_eq(s, "csE220");
}

Test(strgChangeCase, flips_standard_letters)
{
    char s[] = "Stony Brook";

    strgChangeCase(s);
    cr_assert_str_eq(s, "sTONY bROOK");
}

Test(strgChangeCase, single_letter_and_isolated_digits)
{
    char s1[] = "1";
    strgChangeCase(s1);
    cr_assert_str_eq(s1, "1");

    char s2[] = "x2Y z";
    strgChangeCase(s2);
    cr_assert_str_eq(s2, "x2Y Z");
}

Test(strgChangeCase, boundary_characters_with_no_digit_neighbor)
{
    char s[] = "System Fundamental220";

    strgChangeCase(s);
    cr_assert_str_eq(s, "sYSTEM fUNDAMENTAl220");
}

Test(strgChangeCase, null_pointer_safe)
{
    strgChangeCase(NULL);
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

 


// strgDiff Tests
Test(strgDiff, identical_strings_return_negative_one)
{
    cr_assert_eq(strgDiff("Hello", "Hello"), -1);
    cr_assert_eq(strgDiff("", ""), -1);
}

Test(strgDiff, difference_at_start_and_middle)
{
    cr_assert_eq(strgDiff("CSE-220", "CSE220"), 3);
    cr_assert_eq(strgDiff("CSE220", "SE220"), 0);
}

Test(strgDiff, shorter_string_terminator_index)
{
    cr_assert_eq(strgDiff("abc", "abcd"), 3);
    cr_assert_eq(strgDiff("abcd", "abc"), 3);
}

Test(strgDiff, one_empty_string)
{
    cr_assert_eq(strgDiff("", "a"), 0);
    cr_assert_eq(strgDiff("a", ""), 0);
}

Test(strgDiff, null_pointer_returns_negative_two)
{
    cr_assert_eq(strgDiff("abc", NULL), -2);
    cr_assert_eq(strgDiff(NULL, "abc"), -2);
    cr_assert_eq(strgDiff(NULL, NULL), -2);
}

// strgInterleave Tests
Test(strgInterleave, equal_lengths_interleave)
{
    char d[20];

    strgInterleave("abc", "123", d, sizeof d);
    cr_assert_str_eq(d, "a1b2c3");
}

Test(strgInterleave, unequal_lengths_append_remainder)
{
    char d1[20];
    strgInterleave("abcdef", "123", d1, sizeof d1);
    cr_assert_str_eq(d1, "a1b2c3def");

    char d2[20];
    strgInterleave("1234", "cs", d2, sizeof d2);
    cr_assert_str_eq(d2, "1c2s34");
}

Test(strgInterleave, truncation_stops_cleanly)
{
    char d1[5];
    strgInterleave("abc", "123", d1, sizeof d1);
    cr_assert_str_eq(d1, "a1b2");

    char d2[6];
    strgInterleave("abcdef", "12", d2, sizeof d2);
    cr_assert_str_eq(d2, "a1b2c");
}

Test(strgInterleave, empty_string_inputs)
{
    char d[20];

    strgInterleave("", "123", d, sizeof d);
    cr_assert_str_eq(d, "123");

    strgInterleave("", "", d, sizeof d);
    cr_assert_str_eq(d, "");
}

Test(strgInterleave, null_and_zero_guards)
{
    char d[10] = "untouched";

    strgInterleave(NULL, "123", d, sizeof d);
    cr_assert_str_eq(d, "untouched");

    strgInterleave("abc", NULL, d, sizeof d);
    cr_assert_str_eq(d, "untouched");

    strgInterleave("abc", "123", d, 0);
    cr_assert_str_eq(d, "untouched");

    strgInterleave("abc", "123", NULL, sizeof d);
}

// strgReverseLetters tests
Test(strgReverseLetters, reverses_all_letters)
{
    char s[] = "Hello";

    strgReverseLetters(s);
    cr_assert_str_eq(s, "olleH");
}

Test(strgReverseLetters, punctuation_and_spaces_stay_in_place)
{
    char s1[] = "ab-cd";
    strgReverseLetters(s1);
    cr_assert_str_eq(s1, "dc-ba");

    char s2[] = "Hi, Bob";
    strgReverseLetters(s2);
    cr_assert_str_eq(s2, "bo, BiH");
}

Test(strgReverseLetters, digits_stay_in_place)
{
    char s1[] = "a1b2c";
    strgReverseLetters(s1);
    cr_assert_str_eq(s1, "c1b2a");

    char s2[] = "C3PO";
    strgReverseLetters(s2);
    cr_assert_str_eq(s2, "O3PC");
}

Test(strgReverseLetters, empty_and_no_letters)
{
    char s1[] = "";
    strgReverseLetters(s1);
    cr_assert_str_eq(s1, "");

    char s2[] = "123-456";
    strgReverseLetters(s2);
    cr_assert_str_eq(s2, "123-456");
}

Test(strgReverseLetters, null_pointer_safe)
{
    strgReverseLetters(NULL);
}