/*
 * CSE 220 Homework 4, Part 1: string manipulation.
 *
 * Do not change this file.
 */
#ifndef STRGPTR_H
#define STRGPTR_H

#include <stddef.h>

/* Returns the length of s, or -1 if s is NULL. */
int strgLen(const char *s);

/* Copies source into destination, which holds size bytes in total. */
void strgCopy(const char *source, char *destination, size_t size);

/* Flips the case of every letter that has no digit next to it. */
void strgChangeCase(char *s);

/* Returns the index of the first difference, -1 if equal, -2 if a pointer is NULL. */
int strgDiff(const char *s1, const char *s2);

/* Interleaves s1 and s2 into d, which holds size bytes in total. */
void strgInterleave(const char *s1, const char *s2, char *d, size_t size);

/* Reverses only the letters in s and leaves everything else in place. */
void strgReverseLetters(char *s);

#endif
