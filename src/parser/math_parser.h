#include <stack>
#include <vector>
#include "parser.h"
#include "../lexer/lexer.h"

class MathParser {
	private: std::vector<Token> expression;

	public: auto set_expression(std::vector<Token> &expression) -> void {
				this->expression = expression;
			}

	public: auto parse_expression() -> Result<double> {
				Result<double> result;

				if (expression.empty()) {
					result.error.set_error("no expression to parse");
					return result;
				}



			}

};
