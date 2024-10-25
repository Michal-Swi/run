#include <optional>
#include <stack>
#include <string>
#include <vector>
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
	auto get_number_from_token(Token &token) 
		-> Result<Node> {
		Result<Node> result;
		
		bool is_float = 
			(token.token_type == 
			 TokenType::FloatLiteral);

		bool is_integer = 
			(token.token_type == 
			 TokenType::IntegerLiteral);

		std::optional<double> number;
		if (is_float or is_integer) {
			number = 
				static_cast<std::optional<double>>
				(std::stod(token.value));
		} else {
			result.error.set_error
			("expression " + 
			 token.value + 
			 " is NaN");

			return result;
		}	
		
		Node node;
		node.number = number;
		node.node_type = NodeType::Number;
		
		result.ok.set_value(node);
		return result;
	}

	private:
	auto get_operator_from_token(Token &token) 
		-> Result<Node> {
			Result<Node> result;

			bool is_operator = 
				(token.token_type == 
				TokenType::Operator);

			Result<Operations> conversion_result;
			if (is_operator) {
				conversion_result = 
					OperationsHelperFunctions::
					match_with_operator
					(token.value);
				
				if (!conversion_result
						.error
						.to_string()
						.empty()) {
					result
						.error
						.set_error
						(conversion_result
						.error
						.to_string());
					return result;
				}
			}

			Node result_node;
			result_node.node_operator = 
				conversion_result.ok.value();
			result_node.node_type = 
				NodeType::NumberOperator;

			result.ok.set_value(result_node);
			return result;
		}

	private:
	auto place_node
		(Node &initial_node, Node &current_node) 
		-> Result<Node> {
		Result<Node> result;	

		if (initial_node.node_type == NodeType::Number) {
			result.error.set_error
				("Parsing error, wrong initial_node type");
			return result;
		}

		if (current_node.node_type == NodeType::Number) {
			result.error.set_error
				("Parsing error, wrong current_node type");
			return result;
		}

	}

	private:
	auto form_tree() -> Result<Node> {
		Result<Node> result;

		if (expression.empty()) {
			result.error.set_error("No expression");
			return result;
		}

		Result<Node> operator_result = 
			get_operator_from_token(expression[1]);

		if (!operator_result.error.to_string().empty()) {
			result.error.set_error
				(operator_result.error.to_string());
			return result;
		}

		Node initial_node = operator_result.ok.value();

		Result<Node> number_result = 
			get_number_from_token(expression[0]);

		if (!number_result.error.to_string().empty()) {
			result.error.set_error
				(number_result.error.to_string());
			return result;
		}

		Node initial_number_left = number_result.ok.value();

		number_result = 
			get_number_from_token(expression[2]);
		
		if (!number_result.error.to_string().empty()) {
			result.error.set_error
				(number_result.error.to_string());
			return result;
		}

		Node initial_number_right = 
			number_result.ok.value();

		initial_node.left = &initial_number_left;
		initial_node.right = &initial_number_right;

		int i = 2;
		for (; i < expression.size() - 1; i += 2) {
			Node number, number_operator;
					
			Result<Node> number_result = 
				get_number_from_token(expression[i]);	
			
			if (!number_result.error.to_string().empty()) { 
				result.error.set_error
					(number_result.error.to_string());
				return result;
			}

			number = number_result.ok.value();

			Result<Node> operator_result = 
				get_operator_from_token(expression[i + 1]);
			
			if (!operator_result
					.error.to_string().empty()) {
				result.error.set_error
					(operator_result.error.to_string());
				return result;
			}

			number_operator = operator_result.ok.value();
	
			number_operator.left = &number;
		}

		return result;
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

