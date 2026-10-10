/*
 * CSE 220 Homework 4, Part 2 tests.
 *
 * A few sample tests are given so you can see how Criterion is set up. They
 * fail until you implement the functions, which is expected.
 *
 * You must add your own tests: at least 5 per function, for both
 * encryptCaesar and decryptCaesar. Test the edge cases too: NULL arguments,
 * an empty message, negative keys, a buffer too small for the message, a
 * missing marker, and text after the marker.
 *
 * Build and run these with:   make test
 */
#include <criterion/criterion.h>
#include "caesar.h"

Test(encryptCaesar, shifts_letters_by_key_plus_index)
{
    char ciphertext[20];

    cr_assert_eq(encryptCaesar("abc", ciphertext, sizeof ciphertext, 2), 3);
    cr_assert_str_eq(ciphertext, "ceg__EOM__");
}

Test(encryptCaesar, shifts_digits_by_key_plus_twice_the_index)
{
    char ciphertext[20];

    cr_assert_eq(encryptCaesar("Cse220", ciphertext, sizeof ciphertext, 1), 6);
    cr_assert_str_eq(ciphertext, "Duh911__EOM__");
}

Test(encryptCaesar, reports_a_buffer_with_no_room_for_the_marker)
{
    char ciphertext[7];

    cr_assert_eq(encryptCaesar("abc", ciphertext, sizeof ciphertext, 2), -1);
}

Test(decryptCaesar, recovers_the_message)
{
    char plaintext[20];

    cr_assert_eq(decryptCaesar("ceg__EOM__", plaintext, sizeof plaintext, 2), 3);
    cr_assert_str_eq(plaintext, "abc");
}

Test(decryptCaesar, reports_a_missing_marker)
{
    char plaintext[20];

    cr_assert_eq(decryptCaesar("ceg", plaintext, sizeof plaintext, 2), -1);
}

/*
 * TODO: add your own tests below.
 *
 * One good habit is a round trip test: encrypt a message, decrypt the result
 * with the same key, and check that you get the original message back.
 *
 * Useful assertions:
 *   cr_assert_eq(actual, expected)       two values are equal
 *   cr_assert_str_eq(actual, expected)   two strings have the same contents
 *   cr_assert(condition)                 the condition is true
 */

 // encryptCaesar tests
 Test(encryptCaesar, null_arguments_return_negative_two)
{
    char ciphertext[20];

    cr_assert_eq(encryptCaesar(NULL, ciphertext, sizeof ciphertext, 2), -2);
    cr_assert_eq(encryptCaesar("abc", NULL, 20, 2), -2);
    cr_assert_eq(encryptCaesar(NULL, NULL, 20, 2), -2);
}

Test(encryptCaesar, empty_plaintext_appends_only_marker)
{
    char ciphertext[20];

    cr_assert_eq(encryptCaesar("", ciphertext, sizeof ciphertext, 5), 0);
    cr_assert_str_eq(ciphertext, "__EOM__");
}

Test(encryptCaesar, negative_key_wraps_correctly)
{
    char ciphertext[20];
    cr_assert_eq(encryptCaesar("a0", ciphertext, sizeof ciphertext, -1), 2);
    cr_assert_str_eq(ciphertext, "z1__EOM__");
}

Test(encryptCaesar, truncates_payload_when_buffer_is_too_small)
{
    char ciphertext[10];
    cr_assert_eq(encryptCaesar("abcdef", ciphertext, sizeof ciphertext, 2), 2);
    cr_assert_str_eq(ciphertext, "ce__EOM__");
}

Test(encryptCaesar, punctuation_and_spaces_remain_unchanged)
{
    char ciphertext[30];
    cr_assert_eq(encryptCaesar("a b!c", ciphertext, sizeof ciphertext, 0), 5);
    cr_assert_str_eq(ciphertext, "a d!g__EOM__");
}

// decryptCaesar tests
Test(decryptCaesar, null_arguments_return_negative_two)
{
    char plaintext[20];

    cr_assert_eq(decryptCaesar(NULL, plaintext, sizeof plaintext, 2), -2);
    cr_assert_eq(decryptCaesar("ceg__EOM__", NULL, 20, 2), -2);
    cr_assert_eq(decryptCaesar(NULL, NULL, 20, 2), -2);
}

Test(decryptCaesar, size_zero_or_one_returns_zero)
{
    char plaintext[5] = "init";

    cr_assert_eq(decryptCaesar("ceg__EOM__", plaintext, 0, 2), 0);
    cr_assert_eq(decryptCaesar("ceg__EOM__", plaintext, 1, 2), 0);
    cr_assert_str_eq(plaintext, "init");
}

Test(decryptCaesar, ignores_text_after_the_marker)
{
    char plaintext[20];

    /* Garbage / trailing data after __EOM__ must be skipped */
    cr_assert_eq(decryptCaesar("ceg__EOM__extra_junk", plaintext, sizeof plaintext, 2), 3);
    cr_assert_str_eq(plaintext, "abc");
}

Test(decryptCaesar, incomplete_marker_fails)
{
    char plaintext[20];

    /* Missing one underscore */
    cr_assert_eq(decryptCaesar("ceg__EOM_", plaintext, sizeof plaintext, 2), -1);
}

Test(decryptCaesar, decrypts_negative_key)
{
    char plaintext[20];

    cr_assert_eq(decryptCaesar("z1__EOM__", plaintext, sizeof plaintext, -1), 2);
    cr_assert_str_eq(plaintext, "a0");
}