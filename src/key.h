#ifndef KEY_H
#define KEY_H

#include <map>

/*
 * Created by Alex Dale
 * Date:        March     2015
 * Last Update: March 31, 2015
 */

// ******** Helper methods ********

/*
 *  Returns true if the character is upper case
 */
bool is_upper(char c);

/*
 *  Returns true if the character is lower case
 */
bool is_lower(char c);

/*
 *  Returns the upper case of the character
 */
char to_upper(char c);

/* 
 * This class will map on character set to another chaacter set.
 * Character sets must be capatilized.  Mapping is one-to-one
 * and will remove any double mappings.
 */
class Key {
	// ******** Private Instance variables ********

	/*
	 *	Maps Encrypted character set to the Decrypted character
	 *  set.
	 */
	std::map<char, char> decrypt_map;

	/*
	 *	Maps Decrypted character set to the Encrypted character
	 *  set.
	 */
	std::map<char, char> encrypt_map;

	// ******** Private Instance Functions ********

	/*
	 * Will unmap the two given characters from any previous mapping.
	 * First paramater is from the Encrypted character set, the second
	 * paramater is from the Decrypted character set.
	 */
	void free_both(char,char);

public:
	// ******** Public Constructor ********
	/*
	 *  Default constructor.  Will initialized the both mappings to
	 *  their null character.
	 */
	Key();

	// ******** Public Instance Modifiers ********

	/*
	 * Will map a Encrypted character to the Decrypted character
	 * set.  Will remove any previous mappings of the given 
	 * characters.  First parameter is Encrypted character, the
	 * second is the Decrypted character to be mapped to.
	 */
	void set(char, char);

	/* Will remove the given Encrypted character's mapping if it
	 * existes.
	 */
	void remove(char);

	/*
	 * Will remove all the mappings and reset them to the null
	 * null characters of the given sets.
	 */
	void clear();

	// ******** Public Instance Getters ********

	/*
	 * Returns the Decrypted character that the given Encrypted 
	 * character is mapped to, or returns the decrypted null
	 * character if there is no mapping.
	 */	
	char get_to(char);

	/*
	 * Returns the Encrypted character that the given Decrypted
	 * character is mapped to, or returns the encrypted null
	 * character if there is no mapping.
	 */
	char get_from(char);

	// ******** Public Class Constants ********

	/*
	 * Default null character for the Encrypted character set.
	 * All Decrypted characters will map to this initially or
	 * when mapping is removed.
	 */
	static char const null_decrypt;

	/*
	 * Default null character for the Decrypted character set.
	 * All Encrypted characters will map to this initially or
	 * when mapping is removed.
	 */
	static char const null_encrypt;
};

#endif
