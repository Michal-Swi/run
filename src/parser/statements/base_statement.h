#include "statements.h"

enum class StatementType {
	LetStatement = 0,
	ForStatement = 1,
};

struct Statement {
	std::variant<LetStatement, ForStatement> statement;
};
