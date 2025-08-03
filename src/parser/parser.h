#include <cctype>
#include <memory>
#include <unordered_map>
#include <vector>
#include "statements/base_statement.h"
#include "../errors/parser_errors/parser_errors.h"

class Parser {
	private:
	std::vector<Token> tokens;
	std::vector<Statement> parsed_statements;
		
	public:
	Parser(const std::vector<Token> &tokens) {
		this->tokens = tokens;
	}

	public:
	Parser() {}

	public:
	void set_tokens(std::vector<Token> &tokens) {
		this->tokens = tokens;
	}

	private:
	Token get_token(const int &i) {
		if (i >= tokens.size()) {
			throw internal_parser_error(InternalParserErrors::IteratorOverflow);
		}

		return tokens.at(i);
	}

	private:
	LetStatement parse_let_statement(int &i) {
		i += 1;
		std::string identifier = get_token(i).token_literal;

		std::vector<Token> values; 

		for (; i < tokens.size() and get_token(i).token_type != TokenType::EOW; i++) {
			values.push_back(get_token(i));
		}

		LetStatement let_statement;
		let_statement.set_values(values);
		let_statement.set_identifier(identifier);

		return let_statement;
	}	
	
	private:
	Statement parse_keyword(int &i) {
		Token curr_token = get_token(i);
		Statement statement;
		
		if (curr_token.token_literal == "let") {
			statement.statement = parse_let_statement(i);
		}

		return statement;
	}

	public:
	std::vector<Statement> parse_tokens() {
		int i = 0;
		Statement base_statement;

		for (; i < tokens.size(); i++) {
			switch (tokens.at(i).token_type) {
				case TokenType::KeyWord:
					parsed_statements.push_back(parse_keyword(i));
					break;
				default:
					break;
			}
		}

		return parsed_statements;
	}
};

