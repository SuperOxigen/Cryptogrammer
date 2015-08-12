#include "puzzle.h"

using std::string;
using std::ostream;

void format_string(string& message) {
	for (size_t i = 0; i < message.size(); i++) {
		message[i] = to_upper(message[i]);
	}
}

void transcribe(string& in_message, string& out_message, Key& transcriber) {
	out_message = in_message;
	for (size_t i = 0; i < in_message.size(); i++) {
		out_message[i] = transcriber.get_to(in_message[i]);
	}	
}

Puzzle::Puzzle(const string& message) : in_message(message), show_out(false), transcriber(Key()) {
	format_string(in_message);
	transcribe(in_message, out_message, transcriber);
}

size_t Puzzle::char_count(char c) {
	if (is_lower(c)) {
		c = to_upper(c);
	}
	if (!is_upper(c)) return 0;

	size_t count(0);
	for (size_t i = 0; i < in_message.size(); i++) {
		if (in_message[i] == c) count++;
	}

	return count;
}

ostream& operator<<(ostream& os, Puzzle & puzzle) {

	if (puzzle.show_out) {
		transcribe(puzzle.in_message, puzzle.out_message, puzzle.transcriber);
		os << puzzle.out_message;
	} else {
		os << puzzle.in_message;
	}

	return os;
}