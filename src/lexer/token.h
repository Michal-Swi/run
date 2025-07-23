#include <regex>
#include <iostream>
#include <string>

enum class TokenType {
	None,
	Type,
	Number, 
	Operator,
	Identifier,
	KeyWord,
	EOW, // end of word 
};

struct Token {
	TokenType token_type;
	std::string token_literal;

	Token(const TokenType &token_type, const std::string &token_literal) : 
		token_type(token_type), token_literal(token_literal)
	{}

	public:
	Token() {}
	
	public:
	void print_type() {
		switch (token_type) {
			case TokenType::Type:
				std::cout << "Type ";
				break;
			case TokenType::KeyWord:
				std::cout << "KeyWord ";
				break;
			case TokenType::Identifier:
				std::cout << "Identifier ";
				break;
			case TokenType::Number:
				std::cout << "Number ";
				break;
			case TokenType::Operator:
				std::cout << "Operator ";
				break;
			case TokenType::EOW:
				std::cout << "EOW ";
				break;
			default:
				std::cout << "None ";
		}
	}
};

