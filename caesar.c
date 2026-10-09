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

// mod that always returns a positive value
static int mod(int val, int m)
{
    int r = val % m;
    return (r < 0) ? (r + m) : r;
}

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
    
    // null check
    if (plaintext == NULL || ciphertext == NULL) {
        return -2;
    }
    // buffer cannot fit marker and ending characters
    if (size < 8) {
        return -1;
    }
    // determine the max allowed payload
    int plain_len = strgLen(plaintext);
    int max_payload = (int)size - (EOM_LEN + 1);
    int chars_to_write = 0;
    if (plain_len < max_payload){
        chars_to_write = plain_len;
    } else {
        chars_to_write = max_payload;
    }

    for (int i = 0; i < chars_to_write; i++) {
        char c = *plaintext;
        
        if (c >= 'a' && c <= 'z') {
            int shift = key + i;
            *ciphertext = (char)('a' + mod((c - 'a') + shift, 26)); // shift forward for lowercase letters
        } else if (c >= 'A' && c <= 'Z') {
            int shift = key + i;
            *ciphertext = (char)('A' + mod((c - 'A') + shift, 26)); // shift forward for uppercase letters
        } else if (c >= '0' && c <= '9') {
            int shift = key + 2 * i;
            *ciphertext = (char)('0' + mod((c - '0') + shift, 10)); // shift forward for numbers
        } else {
            *ciphertext = c; // every character that's not a number or letter remains unchanged
        }
        plaintext++;
        ciphertext++;
    }
    // append the EOM marker
    const char *eom = EOM;
    while (*eom != '\0') {
        *ciphertext = *eom;
        ciphertext++;
        eom++;
    }
    // append the terminating character
    *ciphertext = '\0';

    return chars_to_write;
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
    // null check
    if (ciphertext == NULL || plaintext == NULL) {
        return -2;
    }

    // size of 0 or 1 cannot fit any characters plus '\0'
    if (size <= 1) {
        return 0;
    }

    // 3. scan for the first complete EOM marker
    const char *scan = ciphertext;
    const char *marker_pos = NULL;

    while (*scan != '\0') {
        const char *s_curr = scan;
        const char *m_curr = EOM;

        while (*m_curr != '\0' && *s_curr == *m_curr) {
            s_curr++;
            m_curr++;
        }

        if (*m_curr == '\0') {
            marker_pos = scan;
            break;
        }
        scan++;
    }

    // return -1 for missing marker
    if (marker_pos == NULL) {
        return -1;
    }

    // calculate payload size and truncate if plaintext is smaller
    int payload_len = (int)(marker_pos - ciphertext);
    int max_out = (int)size - 1;
    int chars_to_write = (payload_len < max_out) ? payload_len : max_out;

    for (int i = 0; i < chars_to_write; i++) {
        char c = *ciphertext;

        if (c >= 'a' && c <= 'z') {
            int shift = key + i;
            *plaintext = (char)('a' + mod((c - 'a') - shift, 26)); // shift backwards for lowercase letters
        } else if (c >= 'A' && c <= 'Z') {
            int shift = key + i;
            *plaintext = (char)('A' + mod((c - 'A') - shift, 26)); // shift backwards for uppercase letters
        } else if (c >= '0' && c <= '9') {
            int shift = key + 2 * i;
            *plaintext = (char)('0' + mod((c - '0') - shift, 10)); // shift backwards for numbers
        } else {
            *plaintext = c; // every other character that's not a number or letter remains unchanged
        }

        ciphertext++;
        plaintext++;
    }

    // append terminating character to plaintext
    *plaintext = '\0';

    return chars_to_write;
}
