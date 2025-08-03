#include <memory>
#include <variant>
#include <vector>
#include "../../lexer/lexer.h" // Why whole lexer?? because c++ include is shit

struct Statement;

class LetStatement {
	private:
	std::vector<Token> values; // let a = 3 + 5; has multiple values
	std::string identifier;

	public:
	void set_identifier(const std::string &identifier) {
		this->identifier = identifier;
	}

	public:
	std::string get_identifier() {
		return identifier;
	}

	public:
	void set_values(std::vector<Token> &values) {
		this->values = values;
	}

	public:
	std::vector<Token> get_values() {
		return values;
	}
};

class ForStatement {
	private:
	std::vector<Statement> operations; // Everything between { }
	std::vector<Statement> conditions;
	std::vector<Statement> iterators;
	std::vector<Statement> every_iteration_operation; // i++, etc.
};

