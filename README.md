1. IMPLEMENTATION OVERVIEW

Part 1: String Manipulation (strgPtr.c)
- strgLen: Computes the length of a null-terminated string by advancing a pointer
  until the null byte ('\0') is reached, calculating the length via pointer
  subtraction between the current position and the start.
- strgCopy: Copies characters from a source pointer to a destination pointer up to
  the maximum capacity (size - 1) using pointer dereferencing and increments, then
  appends a terminating null byte.
- strgChangeCase: Iterates through the input string using a pointer, converting
  lowercase letters ('a'-'z') to uppercase by subtracting 32, uppercase letters
  ('A'-'Z') to lowercase by adding 32, and preserving all other characters intact.
- strgDiff: Compares two strings using dual pointer traversal, returning the 0-based
  index of the first mismatched byte, or -1 if the strings are identical in length
  and character content.
- strgInterleave: Interleaves characters alternating between two input source pointers
  into a destination buffer up to buffer capacity, continuing with the remaining
  tail of either string once one ends, and null-terminates the result.
- strgReverseLetters: Uses a two-pointer approach to reverse only alphabetic letters
  in-place while preserving non-letter characters in their original positions:
    * Left pointer advances forward to find the next alphabetic character.
    * Right pointer steps backward to find the previous alphabetic character.
    * Swaps the two characters in memory until the pointers cross.

Part 2: Position-Aware Caesar Cipher (caesar.c)
- encryptCaesar: Encrypts plaintext into ciphertext using position-based shifting,
  then appends the 7-character "__EOM__" marker and null-terminates:
    * Error Handling: Returns -2 on NULL arguments, and -1 if buffer size is less
      than 8 bytes (no room for marker + '\0').
    * Truncation: Calculates payload limit as size - 8. Encrypts up to this limit
      and returns the number of payload characters actually written.
    * Shifting Rules:
        - Lowercase ('a'-'z'): Shifted by (key + index) mod 26.
        - Uppercase ('A'-'Z'): Shifted by (key + index) mod 26.
        - Digits ('0'-'9'): Shifted by (key + 2 * index) mod 10.
        - Non-alphanumeric: Copied unchanged while still advancing the index.
    * Modulo Arithmetic: Employs a helper function mod() to ensure negative C
      remainders wrap strictly into positive bounds [0, m - 1].
    * Marker: Appends "__EOM__" byte-by-byte via pointer traversal, followed by '\0'.
- decryptCaesar: Decrypts ciphertext into plaintext by reversing the position shift:
    * Error Handling: Returns -2 on NULL arguments, 0 if size <= 1, and -1 if the
      cipher text does not contain a complete 7-character "__EOM__" marker.
    * Marker Search: Walks the ciphertext using pointer traversal to locate the
      first complete "__EOM__" marker, ignoring any characters that appear after it.
    * Payload Length: Computes payload length via pointer subtraction (marker - start),
      writing at most size - 1 characters to plaintext.
    * Inverse Shifting: Reverses encryption shifts using subtraction:
        - Letters shift backward by (key + index) mod 26.
        - Digits shift backward by (key + 2 * index) mod 10.
        - Non-alphanumeric characters remain unchanged.



2. TESTS AND RESULTS

Test Breakdown:

tests in test_strgPtr.c:
- strgLen_basic: Validates string length computation on standard strings.
- strgLen_empty: Verifies length calculation on an empty string ("").
- strgCopy_basic: Tests normal copy within sufficient buffer capacity.
- strgCopy_truncate: Verifies proper truncation and null termination on small buffers.
- strgCopy_empty: Tests copying an empty source string.
- strgChangeCase_mixed: Tests case conversion on mixed alphanumeric strings.
- strgChangeCase_no_alpha: Verifies symbols, spaces, and numbers remain unchanged.
- strgChangeCase_empty: Tests case conversion on an empty string.
- strgDiff_identical: Validates -1 return for identical strings.
- strgDiff_mismatch_start: Tests mismatch detection at index 0.
- strgDiff_mismatch_middle: Tests mismatch detection in intermediate positions.
- strgDiff_length_mismatch: Verifies mismatch index when one string is a prefix of another.
- strgDiff_empty_strings: Tests comparison between two empty strings.
- strgInterleave_equal_length: Validates interleaving strings of equal length.
- strgInterleave_unequal_length: Tests interleaving when source strings have differing lengths.
- strgInterleave_buffer_truncation: Verifies truncation behavior to buffer capacity.
- strgInterleave_one_empty: Tests interleaving when one input string is empty.
- strgReverseLetters_standard: Tests reversing letters with symbols kept fixed.
- strgReverseLetters_no_letters: Verifies no movement when string contains only digits/symbols.
- strgReverseLetters_palindrome: Validates in-place reversal on palindrome strings.

tests in test_caesar.c:
- encryptCaesar_shifts_letters: Validates letter shift by key + index.
- encryptCaesar_shifts_digits: Validates digit shift by key + 2 * index.
- encryptCaesar_buffer_too_small: Confirms -1 return when size < 8 bytes.
- encryptCaesar_null_arguments: Verifies -2 return when plaintext or ciphertext is NULL.
- encryptCaesar_empty_plaintext: Validates outputting only "__EOM__" on empty input.
- encryptCaesar_negative_key: Verifies correct modular wrapping for negative keys.
- encryptCaesar_truncates_payload: Checks payload truncation when buffer is small.
- encryptCaesar_punctuation_unchanged: Verifies non-alphanumeric characters remain intact.
- decryptCaesar_recovers_message: Validates standard decryption matching original message.
- decryptCaesar_missing_marker: Confirms -1 return when ciphertext lacks "__EOM__".
- decryptCaesar_null_arguments: Verifies -2 return when ciphertext or plaintext is NULL.
- decryptCaesar_size_zero_or_one: Confirms 0 return and unmodified buffer when size <= 1.
- decryptCaesar_ignores_text_after_marker: Validates discarding trailing data after marker.
- decryptCaesar_incomplete_marker: Confirms -1 return on incomplete marker prefix ("__EOM_").
- decryptCaesar_decrypts_negative_key: Tests reverse shifting with negative keys.
- caesar_full_round_trip: Validates end-to-end encryption followed by decryption.