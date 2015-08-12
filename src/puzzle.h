#ifndef PUZZLE_H
#define PUZZLE_H

// Standard Library Tools
#include <string>
#include <iostream>

// Project Files
#include "key.h"

/*
 * Created by Alex Dale
 * Date:        March     2015
 * Last Update: March 31, 2015
 */

// ******** Prototype Declaration ********

/*
 * Class prototype.  See below for details.
 * This is declared for the instertion operator
 * prototype below.
 */
class Puzzle;

/*
 * Insertion operator for the Puzzle class intended for
 * non-file output streams.  This is declared here for
 * the friend relation in the Puzzle below.
 */
std::ostream& operator<<(std::ostream&, Puzzle const &);

// ******** Class Declaration ********

/*
 * This class will store a both an encrypted string
 * and it's intended decrypted string based on the
 * the key mapping.
 */
class Puzzle {
	// ******** Private Instance Variables ********

	/*
	 * If true, will output as the decrypted string.
	 * If false, will output as the encrypted string.
	 */
	bool show_out;

	/*
	 * An upper case version of the original encrypted string.
	 */
	std::string  in_message;

	/*
	 * Fully or partially decrypted string, based on the 
	 * character mapping
	 */
	std::string out_message;

	/*
	 * Puzzle's character mapping.
	 */
	Key transcriber;

public:
	// ******** Public Constructor ********

	/**
	 * 
	 */
	Puzzle(const std::string&);
	
	friend std::ostream& operator<<(std::ostream&, Puzzle &);
	Key& get_transcriber() { return transcriber; }
	size_t char_count(char c);
	
	void out_mode() { show_out = true;  }
	void  in_mode() { show_out = false; }
};

#endif
