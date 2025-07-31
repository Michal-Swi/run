#include <cctype>
#include <unordered_map>
#include <cstddef>
#include <fstream>
#include <ios>
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include "token.h"
#include "../errors/lexer_errors/file_erorrs.h"
#include "../errors/lexer_errors/bad_token_erorrs.h"
#include "../errors/lexer_errors/internal_lexer_erorrs.h"

class Lexer {
	private:
	std::vector<Token> tokens;
	std::fstream file;
	std::string file_literal;
	std::unordered_set<char> operators;
	std::unordered_set<std::string> key_words;
	std::unordered_map<std::string, TokenType> two_character_operators;

	public:
	Lexer() {
		operators = {'+', '-', '*', '/', 
							'<', '>', '=', '(', ')', '!'};

		key_words = {"let", "if", "for", "fn"}; 
		
		two_character_operators[">="] = TokenType::GreaterEqual;
		two_character_operators["<="] = TokenType::LesserEqual;
		two_character_operators["=="] = TokenType::IsEqualTo;
		two_character_operators["!="] = TokenType::IsDifferentFrom;
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

	private:
	TokenType match_one_character_operator(const char &ch) {
		switch (ch) {
			case '=':
				return TokenType::EqualSign;
			case '+':
				return TokenType::Plus;
			case '-':
				return TokenType::Minus;
			case '*':
				return TokenType::Times;
			case '/':
				return TokenType::Divide;
			case '>':
				return TokenType::Greater;
			case '<':
				return TokenType::Lesser;
			case '(':
				return TokenType::OpenParentheses;
			case ')':
				return TokenType::CloseParentheses;
			case '!':
				return TokenType::Not;
		}
		
		std::string error(1, ch);
		error += " is not a valid token";
		throw bad_token(error);
	}

	private:
	TokenType match_two_character_operator(const std::string &full_operator) {
		if (two_character_operators.find(full_operator) != two_character_operators.end()) {
			return two_character_operators.at(full_operator);
		}

		throw bad_token();
	}

	private:
	TokenType get_operator_token(const std::string &full_operator) {
		if (full_operator.length() == 1) {
			return match_one_character_operator(full_operator.at(0));
		}

		return match_two_character_operator(full_operator);
	}

	private:
	std::string get_operator_string(const char &first_operator, int &i) {
		if (i >= file_literal.length() - 1) {
			return std::string(1, first_operator);
		}
		
		i += 1;
		char second_operator = get_letter(i);
		if (!is_operator(second_operator)) {
			i -= 1;
			return std::string(1, first_operator);
		}
		
		std::string return_operator(1, first_operator);
		return_operator += second_operator;

		return return_operator;
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
				std::string operator_string = get_operator_string(first_letter, i);
				tokens.push_back(tokenize(operator_string, get_operator_token(operator_string)));
				continue;
			}
			
			if (first_letter == ';') {
				tokens.push_back(tokenize(std::string(1, first_letter), TokenType::EOW));
				continue;
			}
			
			if (std::isalpha(first_letter)) {
				word = get_next_word(first_letter, i);

				// That's fuckin ugly, change that later
				if (is_keyword(word)) {
					tokens.push_back(tokenize(word, TokenType::KeyWord));		
				} else {
					tokens.push_back(tokenize(word, TokenType::Identifier));
				}

				continue;
			}

			if (std::isdigit(first_letter)) {
				std::string word = get_next_number(first_letter, i);
				tokens.push_back(tokenize(word, TokenType::Number));
				continue;
			}
		}

		throw bad_token();
	}

	public:
	std::vector<Token> get_tokens() {
		return tokens;
	}
};

