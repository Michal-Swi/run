#include <cctype>
#include <cstddef>
#include <fstream>
#include <ios>
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include "token.h"
#include "expression_types.h"
#include "../errors/errors.h"

class Lexer {
	private:
	std::vector<Token> tokens;
	std::fstream file;
	std::string file_literal;
	std::unordered_set<char> operators;
	std::unordered_set<std::string> key_words;

	public:
	Lexer() {
		operators = {'+', '-', '*', '/', 
							'<', '>', '='};

		key_words = {"let", "if", "for", "fn"}; 
	}

	private:
	// Loads directly to file string
	void load_file(const std::string &file_path) {
		file.open(file_path, std::ios::in);
		
		if (!file.is_open()) {
			throw no_file(file_path);
		}

		std::string word;
		while (file >> word) {
			file_literal += word;
			file_literal += ' '; 
		}

		file.close();
	}

	private:
	Token tokenize(const std::string &literal, const TokenType &token_type) {
		Token token(token_type, literal);
		return token;
	}

	private:
	bool is_ignorable(const char &ch) {
		return ch == ' ' or ch == '\n' or ch == '\r' or ch == -1;
	}

	private:
	char get_letter(const int &i) {
		if (i >= file_literal.length()) {
			throw internal_lexer_error(InternalLexerErrors::IteratorOverflow);
		}

		return file_literal[i];
	}

	private:
	std::string get_next_word(const char &first_letter, int &i) {
		std::string word(1, first_letter); 
		
		char letter = first_letter;
		while (std::isalpha(letter) or std::isdigit(letter)) {
			i += 1;
			letter = get_letter(i);	
			
			if (is_ignorable(letter)) {
				break;
			}

			if (!std::isalpha(letter) and !std::isdigit(letter)) {
				break;
			}

			word += letter;
		}
		
		i -= 1; // For situations like: let i=...
		return word;
	}

	private:
	bool is_keyword(const std::string &word) {
		return key_words.find(word) != key_words.end();
	}

	private:
	std::string get_next_number(const char &first_letter, int &i) {
		std::string number(1, first_letter);

		char ch = first_letter;
		while (std::isdigit(ch) or ch == '.') {
			i += 1;
			ch = get_letter(i);
			
			if (is_ignorable(ch)) {
				break;
			}

			if (!std::isdigit(ch) and ch != '.') {
				break;
			}

			number += ch;
		}
		
		i -= 1;
		return number;
	}

	private:
	bool is_operator(const char &ch) {
		return operators.find(ch) != operators.end();
	}

	public:
	void lexical_analysis(const std::string &file_path) {
		load_file(file_path); // If throws do nothing the  
							  // program should and will terminate
		
		std::string word;
		int i = 0;
		for (; i < file_literal.length(); i++) {
			const char first_letter = get_letter(i);
			
			if (is_ignorable(first_letter)) {
				continue;
			}

			if (is_operator(first_letter)) {
				tokens.push_back(tokenize(std::string(1, first_letter), TokenType::Operator));
			}
			
			if (first_letter == ';') {
				tokens.push_back(tokenize(std::string(1, first_letter), TokenType::EOW));
			}
			
			if (std::isalpha(first_letter)) {
				word = get_next_word(first_letter, i);

				// That's fuckin ugly, change that later
				if (is_keyword(word)) {
					tokens.push_back(tokenize(word, TokenType::KeyWord));		
				} else {
					tokens.push_back(tokenize(word, TokenType::Identifier));
				}
			}

			if (std::isdigit(first_letter)) {
				std::string word = get_next_number(first_letter, i);
				tokens.push_back(tokenize(word, TokenType::Number));
			}
		}
	}

	public:
	std::vector<Token> get_tokens() {
		return tokens;
	}
};

