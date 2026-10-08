/*
 * CSE 220 Homework 4, Part 2: position aware Caesar cipher.
 *
 * Do not change this file.
 */
#ifndef CAESAR_H
#define CAESAR_H

#include <stddef.h>

/*
 * Encrypts plaintext into ciphertext, appends __EOM__ and '\0'.
 * Returns the number of characters encrypted, -1 if the marker does not
 * fit in size bytes, or -2 if a pointer is NULL.
 */
int encryptCaesar(const char *plaintext, char *ciphertext, size_t size, int key);

/*
 * Decrypts ciphertext up to its first __EOM__ into plaintext.
 * Returns the number of characters written, 0 if size leaves no room,
 * -1 if the marker is missing, or -2 if a pointer is NULL.
 */
int decryptCaesar(const char *ciphertext, char *plaintext, size_t size, int key);

#endif
