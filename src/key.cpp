#include "key.h"

/*
 * Created by Alex Dale
 * Date:        March     2015
 * Last Update: March 31, 2015
 */

// ******** Helper methods ********

/*
 *  Returns true if the character is upper case
 */
bool is_upper(char c) {
	return (c >= 'A' && c <= 'Z');
}

/*
 *  Returns true if the character is lower case
 */
bool is_lower(char c) {
	return (c >= 'a' && c <= 'z');
}

/*
 *  Returns the upper case of the character
 */
char to_upper(char c) {
	if (is_lower(c)) {
		c = c + 'A' - 'a';
	}
	return c;
}


// ******** Public Class Constants ********

/*
 * Default null character for the Encrypted character set.
 * All Decrypted characters will map to this initially or
 * when mapping is removed.
 */
char const Key::null_decrypt('_');

/*
 * Default null character for the Decrypted character set.
 * All Encrypted characters will map to this initially or
 * when mapping is removed.
 */
char const Key::null_encrypt('*');


// ******** Public Constructor ********

/*
 *  Default constructor.  Will initialized the both mappings to
 *  their null character.
 */
Key::Key() {
	// Maps all upper case characters to the null character
	for (char c = 'A'; is_upper(c); c++) { 
		decrypt_map[c] = null_decrypt;
		encrypt_map[c] = null_encrypt;
	}
}


// ******** Public Instance Modifiers ********

/*
 * Will map a Encrypted character to the Decrypted character
 * set.  Will remove any previous mappings of the given 
 * characters.  First parameter is Encrypted character, the
 * second is the Decrypted character to be mapped to.
 */
void Key::set(char from, char to) {
	if (is_upper(from) && (is_upper(to))) {
		free_both(from, to);       // Removes previous mappings of the characters
		decrypt_map[from] = to;
		encrypt_map[to] = from;
	}
}

/* Will remove the given Encrypted character's mapping if it
 * existes.
 */
void Key::remove(char from) {
	if (is_upper(from)) {
		if (decrypt_map[from] != null_decrypt) { // Checks if it is actually mapped
			encrypt_map[decrypt_map[from]] = null_encrypt;
			decrypt_map[from]              = null_decrypt;
		}
	}
}

// ******** Private Instance Functions ********

/*
 * Will unmap the two given characters from any previous mapping.
 * First paramater is from the Encrypted character set, the second
 * paramater is from the Decrypted character set.
 */
void Key::free_both(char from, char to) {
	remove(from);
	if (encrypt_map[to] != null_encrypt) {
		remove(encrypt_map[to]);
	}
}

/*
 * Will remove all the mappings and reset them to the null
 * null characters of the given sets.
 */
void Key::clear() {
	for (char c = 'A'; is_upper(c); c++) {
		decrypt_map[c] = null_decrypt;
		encrypt_map[c] = null_encrypt;
	}
}


// ******** Public Instance Getters ********

/*
 * Returns the Decrypted character that the given Encrypted 
 * character is mapped to, or returns the decrypted null
 * character if there is no mapping.
 */	
char Key::get_to(char from) {
	if (is_upper(from)) {
		return decrypt_map[from];
	} else {
		return from;
	}
}

/*
 * Returns the Encrypted character that the given Decrypted
 * character is mapped to, or returns the encrypted null
 * character if there is no mapping.
 */
char Key::get_from(char to) {
	if (is_upper(to)) {
		return encrypt_map[to];
	} else {
		return to;
	}
}
