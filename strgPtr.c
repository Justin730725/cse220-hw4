/*
 * CSE 220 Homework 4, Part 1: string manipulation.
 *
 * Implement the six functions below. You may not use <string.h> or <ctype.h>.
 * <stddef.h> is included for you through strgPtr.h, and you may include
 * <stdio.h> while you debug.
 *
 * Array indexing and pointer arithmetic are both accepted. Pointers are
 * encouraged, since that is what this homework is meant to practice.
 *
 * Remove the (void) lines as you fill each function in. They are only there so
 * the starter kit compiles with -Werror before you have written any code.
 */
#include "strgPtr.h"
#include <stddef.h>

int strgLen(const char *s)
{
    /* TODO: return the number of characters before the terminating '\0'. */
    /* NULL is an error here and returns -1. */
    if (s == NULL) {
        return -1;
    }
    int len = 0;
    while (*s != '\0') {
        len++;
        s++;
    }
    return len;
}

void strgCopy(const char *source, char *destination, size_t size)
{
    /*
     * TODO: copy source into destination, including the '\0'.
     *
     * size is the whole capacity of destination, so at most size - 1
     * characters plus the terminator fit. Copy what fits and terminate.
     * Do nothing at all when a pointer is NULL or size is 0.
     */
    if (size == 0) {
        return;
    }
    if (source == NULL) {
        return;
    }
    if (destination == NULL) {
        return;
    }
    size_t index = 0;
    while (index < size - 1 && *(source + index) != '\0') {
        *(destination + index) = *(source + index);
        index++;
    }
    *(destination + index) = '\0';
}

void strgChangeCase(char *s)
{
    /*
     * TODO: flip the case of each letter, in place.
     *
     * Skip a letter when the character immediately before it or immediately
     * after it is a digit. The first character has no left neighbor and the
     * last character has no right neighbor, so only check the side that
     * exists. Characters that are not letters never change.
     */
     if (s == NULL) {
        return;
     }
     int slen = strgLen(s);

    for (int i = 0; i < slen; i++) {
        // check if its a lowercase or uppercase letter
        int is_upper = (s[i] >= 'A' && s[i] <= 'Z');
        int is_lower = (s[i] >= 'a' && s[i] <= 'z');

        if (!is_upper && !is_lower) {
            continue;
        }

        // Check if either neighbor is a digit
        int left_has_digit = (i > 0 && s[i - 1] >= '0' && s[i - 1] <= '9');
        int right_has_digit = (i < slen - 1 && s[i + 1] >= '0' && s[i + 1] <= '9');

        // Flip only when neither neighbor is a digit
        if (!left_has_digit && !right_has_digit) {
            if (is_upper) {
                s[i] = s[i] + 32;
            } else {
                s[i] = s[i] - 32;
            }
        }
    }
}

int strgDiff(const char *s1, const char *s2)
{
    /*
     * TODO: return the index of the first position where the two strings
     * differ, or -1 when they are identical.
     *
     * When one string ends first, that position is the index of its '\0',
     * so "abc" and "abcd" differ at index 3.
     */
    if (s1 == NULL || s2 == NULL) {
        return -2;
    }
    const char *start = s1;
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2) {
            return (int)(s1 - start);
        }
        s1++;
        s2++;
    }
    if (*s1 != *s2) {
        return (int)(s1 - start);
    }
    return -1;
}

void strgInterleave(const char *s1, const char *s2, char *d, size_t size)
{
    /*
     * TODO: write characters into d, alternating s1, s2, s1, s2, and so on,
     * starting with s1. When one string runs out, copy the rest of the other.
     *
     * size is the whole capacity of d. Stop as soon as size - 1 characters
     * have been written, then terminate. Watch the buffer check between the
     * two writes of a pair: the character from s1 may fit while the one from
     * s2 does not.
     */
    if (s1 == NULL || s2 == NULL || d == NULL || size == 0) {
        return;
    }
    char *start = d;
    while ((size_t)(d - start) < size - 1 && (*s1 != '\0' || *s2 != '\0')) {
        // write from s1 if s1 has not ended and room remains
        if (*s1 != '\0' && (size_t)(d - start) < size - 1) {
            *d = *s1;
            d++;
            s1++;
        }

        // write from s2 if s2 has not ended and room remains
        if (*s2 != '\0' && (size_t)(d - start) < size - 1) {
            *d = *s2;
            d++;
            s2++;
        }
    }

    // add terminating character
    *d = '\0';
}

void strgReverseLetters(char *s)
{
    /*
     * TODO: reverse the order of the letters in s, in place.
     *
     * Every character that is not a letter keeps its original index, so
     * "ab-cd" becomes "dc-ba". Walking one index in from each end and
     * swapping only when both sides are letters is one way to do this.
     */
    if (s == NULL) {
        return;
    }
    char *left = s;
    char *right = s + strgLen(s) - 1;
    while (left < right) {
        int left_is_letter = ((*left >= 'A' && *left <= 'Z') || (*left >= 'a' && *left <= 'z'));
        int right_is_letter = ((*right >= 'A' && *right <= 'Z') || (*right >= 'a' && *right <= 'z'));

        if (!left_is_letter) {
            left++;
        }
        if (!right_is_letter) {
            right--;
        }
        if (right_is_letter && left_is_letter) {
            char temp = *left;
            *left = *right;
            *right = temp;
            left++;
            right--;
        }
    }
}
