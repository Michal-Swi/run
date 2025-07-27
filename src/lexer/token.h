#include <regex>
#include <iostream>
#include <string>

enum class TokenType {
	None,
	Type,
	Number, 
	
	// Single character operators
	Plus,
	Minus,
	Times,
	Divide, 
	EqualSign,
	Lesser,
	Greater,
	OpenParentheses,
	CloseParentheses,
	Not,

	// Two character operators
	IsEqualTo, 
	LesserEqual,
	GreaterEqual,
	IsDifferentFrom,

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
			case TokenType::Plus:
				std::cout << "Plus ";
				break;
			case TokenType::Minus:
				std::cout << "Minus ";
				break;
			case TokenType::Times:
				std::cout << "Times ";
				break;
			case TokenType::Divide:
				std::cout << "Divide ";
				break;
			case TokenType::CloseParentheses:
				std::cout << "Close P ";
				break;
			case TokenType::OpenParentheses:
				std::cout << "Open P ";
				break;
			case TokenType::Greater:
				std::cout << "Greater ";
				break;
			case TokenType::Lesser:
				std::cout << "Lesser ";
				break;
			case TokenType::LesserEqual:
				std::cout << "Lesser E ";
				break;
			case TokenType::GreaterEqual:
				std::cout << "Greater E ";
				break;
			case TokenType::IsEqualTo:
				std::cout << "Is Equal To ";
				break;
			case TokenType::EqualSign:
				std::cout << "Equal Sign ";
				break;
			case TokenType::EOW:
				std::cout << "EOW ";
				break;
			case TokenType::IsDifferentFrom:
				std::cout << "Is Different From ";
				break;
			case TokenType::Not:
				std::cout << "Not ";
				break;
			default:
				std::cout << "None ";
		}
	}
};

