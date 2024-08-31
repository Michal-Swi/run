#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
#include "token.h"

class Lexer {
	private: std::vector<Token> tokens;
	private: std::unordered_set<char> operators;
	private: std::unordered_set<std::string> key_words;

	public: Lexer() {
				operators.insert('<');
				operators.insert('>');
				operators.insert('=');
				operators.insert('+');
				operators.insert('-');
				operators.insert('*');
				operators.insert('/');
				operators.insert(';');
				key_words.insert("let");
			}

	private: auto get_tokens() {
				return tokens;
			}

	private: auto is_number(const char &ch) -> bool {
				return std::isdigit(ch);
			}

	private: auto is_letter(const char &ch) -> bool {
				return std::isalpha(ch);
			}

	private: auto is_operator(const char &ch) -> bool {
				if (operators.count(ch) > 0) {
					return true;
				}

				return false;
			}

	private: auto is_whitespace(const char &ch) -> bool {
				 return ch == ' ' or ch == '\n' or 
					 ch == '\t' or ch == '\r';
			}

	private: auto is_string(const char &ch) -> bool {
				 return ch == '"';
			 }
	
	private: auto read_file(const std::string &path_to_file) -> std::string {
				std::ifstream file(path_to_file);

				char ch;
				std::string file_str;

				while (file.get(ch)) {
					file_str += ch;	
				}

				return file_str;
			}	

	private: auto get_next_token_number(const std::string &str, 
					 int &i) -> Token {
				 Token token;
				 token.token_type = TokenType::IntegerLiteral;

				 for (; !is_whitespace(str[i]); i++) {
					 if (!is_number(str[i]) and str[i] != '.') {
						 i--;
						 break;
					 } else if (str[i] == '.') {
						 token.token_type = TokenType::FloatLiteral;
					 }

					 token.value += str[i];
				 }

				 return token;
			 }

	private: auto get_next_token(const std::string &str, 
					int &i) -> Token {
				Token token;
				
				if (is_letter(str[i])) {
					token.token_type = TokenType::KeyWord;
				} else if (is_operator(str[i])) {
					token.token_type = TokenType::Operator;	
				} else if (is_string(str[i])) {
					token.token_type = TokenType::StringLiteral;
				}

				for (; !is_whitespace(str[i]); i++) {
					if (token.token_type == KeyWord and !is_letter(str[i])) {
						i--;
						break;
					} else if (token.token_type == Operator and !is_operator(str[i])) {
						i--;
						break;
					}
					
					token.value += str[i];
				}

				if (token.token_type == KeyWord and key_words.count(token.value) <= 0) {
					token.token_type = TokenType::Variable;
				}

				return token;
			}

	public: auto tokenize(const std::string &path_to_file) {
				std::string str = read_file(path_to_file);	

				for (int i = 0; i < str.length(); i++) {
					Token new_token;
					if (is_number(str[i])) {
						new_token = get_next_token_number(str, i);
					} else {
						new_token = get_next_token(str, i);
					}

					tokens.push_back(new_token);
				}
			}

	public: auto print() {
				for (const Token &token : tokens) {
					std::cout << token.value << ", token type: "; 
					switch (token.token_type) {
						case TokenType::KeyWord:
							std::cout << "KeyWord" << std::endl;
							break;
						case TokenType::IntegerLiteral:
							std::cout << "IntegerLiteral" << std::endl;
							break;
						case TokenType::FloatLiteral:
							std::cout << "FloatLiteral" << std::endl;
							break;
						case TokenType::Operator:
							std::cout << "Operator" << std::endl;
							break;
						case TokenType::Variable:
							std::cout << "Variable" << std::endl;
							break;
						default:
							std::cout << "Errors beyond my comperhension" << std::endl; 
					}
				}
			}

	
};
