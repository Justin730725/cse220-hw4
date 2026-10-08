/*
 * CSE 220 Homework 4, Part 2: position aware Caesar cipher.
 *
 * Implement the two functions below. You may not use <string.h> or <ctype.h>.
 * You must use your own strgLen from Part 1 whenever you need the length of a
 * string, which is why strgPtr.h is included here.
 *
 * Remove the (void) lines as you fill each function in. They are only there so
 * the starter kit compiles with -Werror before you have written any code.
 */
#include "caesar.h"
#include "strgPtr.h"

/* The end of message marker. It is never encrypted or decrypted. */
#define EOM "__EOM__"
#define EOM_LEN 7

int encryptCaesar(const char *plaintext, char *ciphertext, size_t size, int key)
{
    /*
     * TODO: encrypt plaintext into ciphertext, then append __EOM__ and '\0'.
     *
     * Check the errors in this order and change nothing in ciphertext when
     * you return one:
     *   1. a NULL pointer returns -2
     *   2. a size with no room for the marker and its terminator returns -1
     *
     * The marker plus '\0' needs 8 bytes, so at most size - 8 characters of
     * the payload fit. Encrypt only that many when the message is longer, and
     * return how many you actually wrote.
     *
     * Shifting, where index starts at 0 and counts every character:
     *   letters shift by key + index, within A to Z or a to z
     *   digits shift by key + 2 * index, within 0 to 9
     *   everything else is copied unchanged but still uses up an index
     *
     * Careful with negative keys: in C, -3 % 26 is -3, not 23. Make sure the
     * value you end up with is inside the range before you turn it back into
     * a character.
     */
    (void)plaintext;
    (void)ciphertext;
    (void)size;
    (void)key;
    return 0;
}

int decryptCaesar(const char *ciphertext, char *plaintext, size_t size, int key)
{
    /*
     * TODO: decrypt ciphertext into plaintext, stopping at the marker.
     *
     * Check the errors in this order and change nothing in plaintext when you
     * return one:
     *   1. a NULL pointer returns -2
     *   2. a size of 0 or 1, which leaves no room for any character, returns 0
     *   3. a ciphertext with no complete __EOM__ returns -1
     *
     * Decrypt up to the first complete marker only, and ignore anything after
     * it. All 7 characters must be present and in order, so __EOM_ does not
     * count as a marker.
     *
     * Write at most size - 1 characters and then terminate. Return how many
     * you actually wrote. Decrypting means shifting backward by the same
     * amounts that encryption shifted forward, using the same indexes.
     */
    (void)ciphertext;
    (void)plaintext;
    (void)size;
    (void)key;
    return 0;
}
