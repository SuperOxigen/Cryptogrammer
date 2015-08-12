#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>

#include "puzzle.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
using std::ifstream;

string to_upper(string const & in) {
	string out(in);
	for (size_t i = 0; i < out.size(); i++) {
		out[i] = to_upper(out[i]);
	}
	return out;
}

void print_char_count(Puzzle& cipher, char c) {
	size_t count = cipher.char_count(c);
	cout << c << ": ";
	for (size_t i = 0; i < count; i++) {
		cout << "*";
	}
}

void print_all_char_count(Puzzle& cipher) {
	cout << "Character Count" << endl;
	for (char c = 'A'; c <= 'Z'; c++) {
		print_char_count(cipher, c);
		cout << endl;
	}
}

void print_mapping(Key& transcriber) {
	for (char c = 'A'; c <= 'Z'; c++) {
		cout << c << " => " << transcriber.get_to(c) << endl;
	}
	cout << endl;
}

void print_unmapped_to(Key& transcriber) {
	for (char c = 'A'; c <= 'Z'; c++) {
		if (transcriber.get_from(c) == '*') {
			cout << c << " ";
		}
	}
	cout << endl << endl;
}

void print_backing(Key& transcriber) {
	for (char c = 'A'; c <= 'Z'; c++) {
		cout << c << " => " << transcriber.get_from(c) << endl;
	}
	cout << endl;
}

void set_character(Puzzle& cipher) {
	Key& transcriber = cipher.get_transcriber();
	char from, to;
	cout << "From> ";
	cin >> from;
	cout << "To> ";
	cin >> to;

	from = to_upper(from);
	to   = to_upper(to);

	cout << from << " => " << to << endl;

	transcriber.set(from, to);
}

void unbind_character(Puzzle& cipher) {
	Key& transcriber = cipher.get_transcriber();
	char c;
	cout << "Unbind> ";
	cin >> c;

	c = to_upper(c);
	transcriber.remove(c);
	cout << endl;
}

void print_help() {
	cout << "Commands" << endl;
	cout << "SET [char char] - Set Ciphered to Deciphered" << endl;
	cout << "UNB [char]      - Unbind" << endl;
	cout << "CLR             - Clear" << endl;
	cout << "CHR             - Character Count" << endl;
	cout << "MAP             - Ciphered => Deciphered" << endl;
	cout << "BCK             - Deciphered => Ciphered" << endl;
	cout << "NSET            - List no set characters" << endl;
	cout << "HELP            - Show help" << endl << endl;
}

void play(Puzzle& cipher) {
	string cmd;

	while (cmd != "QUIT") {
		cipher.in_mode();
		cout << cipher << endl;
		cipher.out_mode();
		cout << cipher << endl << endl;
		cout << "> ";
		cin >> cmd;
		cmd = to_upper(cmd);

		if (cmd == "UNB") {
			unbind_character(cipher);
		} else if (cmd == "SET") {
			set_character(cipher);
		} else if (cmd == "CLR") {
			cipher.get_transcriber().clear();
		} else if (cmd == "CHR") {
			print_all_char_count(cipher);
		} else if (cmd == "MAP") {
			print_mapping(cipher.get_transcriber());
		} else if (cmd == "BCK") {
			print_backing(cipher.get_transcriber());
		} else if (cmd == "NSET") {
			print_unmapped_to(cipher.get_transcriber());
		} else if (cmd == "HELP") {
			print_help();
		} else {
			cout << "Command not found!!" << endl;
			print_help();
		}
	}
}

string read_file(const string & file_name) {
	stringstream ss;
	string file_line;
	ifstream fin(file_name);

	if (!fin.is_open()) {
		cout << "Cannot open file " << file_name << endl;
		return "";
	}

	while (getline(fin, file_line)) {
		ss << file_line << endl;
	}
	return ss.str();
}

bool exists(const string& file_name) {
	struct stat buffer;
	return (stat (file_name.c_str(), &buffer) == 0);
}

#define DEFAULT_FILE "puzzles/test_puzzle.txt"

int main(int argc, const char* argv[]) {
	string message;
	
	if (argc > 1 && exists(string(*argv))) {
		message = read_file(string(argv[1]));
	} else {
		message = read_file(DEFAULT_FILE);
	}

	if (message.size() == 0) {
		return 1;
	}


	Puzzle my_puzzle(message);

	play(my_puzzle);

	return 0;
}