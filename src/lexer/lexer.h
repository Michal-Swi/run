#include <cctype>
#include <string>
#include <vector>
#include "token.h"

class Lexer {
	private: std::vector<Token> tokens;

	public: auto get_tokens() {
				return tokens;
			}

	public: auto is_number(const char &ch) -> bool {
				return std::isdigit(ch);
			}

	public: auto is_letter(const char &ch) -> bool {
				return std::isalpha(ch);
			}

	public: auto is_operator(const char &ch) -> bool {
				switch (ch) {
					case '<':	
						return true;
					case '>':
						return true;
					case '=':
						return true;
					case '+':
						return true;
					case '^':
						return true;
					case '*':
						return true;
					case ';':
						return true;
					case '/':
						return true;	
					case '-':
						return true;
				}

				return false;
			}

	public: auto is_whitespace(const char &ch) -> bool {
				 return ch == ' ' or ch == '\n' or 
					 ch == '\t' or ch == '\r';
			}
	
	public: auto get_next_token(const std::string &str, 
					int &i) -> Token {
				Token token;
				
				if (is_letter(str[i])) {
					token.token_type = Word;
				} else if (is_number(str[i])) {
					token.token_type = Number;	
				} else if (is_operator(str[i])) {
					token.token_type = Operator;	
				}

				for (; !is_whitespace(str[i]); i++) {
					
				}
			}

	public: auto tokenize(const std::string &str) {
				for (int i = 0; i < str.length(); i++) {
				}
			}
};
