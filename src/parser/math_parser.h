#include <optional>
#include <stack>
#include <string>
#include <vector>
#include "parser.h"
#include "../lexer/lexer.h"
#include "./node.h"

class MathParser {
	private: std::vector<Token> expression;

	public: 
	auto set_expression(std::vector<Token> 
			&expression) -> void {
		this->expression = expression;			
	}

	private:
	auto form_tree() -> Result<Node> {
		Result<Node> result;

		int i = 0;

		for (; i < expression.size() - 2; i++) {
			Node number1, number2, number_operator;
					
			bool is_float = 
				(expression[i].token_type == 
				 TokenType::FloatLiteral);

			bool is_integer = 
				(expression[i].token_type == 
				 TokenType::IntegerLiteral);

			if (is_float or is_integer) {
				number1.number = 
					static_cast<std::optional<double>>
					(std::stod(expression[i].value));
			} else {
				result.error.set_error
				("expression " + 
				 expression[i].value + 
				 " is NaN");

				return result;
			}

			bool is_operator = 
				(expression[i + 1].token_type == 
				TokenType::Operator);

			if (is_operator) {
				auto conversion_result = 
					OperationsHelperFunctions::
					match_with_operator
					(expression[i + 1].value);

				if (result.error.to_string().empty()) {
					number_operator.node_operator = 
						conversion_result.ok.value();
				} else {
					result.error.set_error
					(conversion_result.error.to_string());
					return result;
				}
			}
		}
	}

	public: 
	auto parse_expression() -> Result<double> {
		Result<double> result;

		if (expression.empty()) {
			result.error.set_error("no expression to parse");
			return result;
		}
				
	}

};
