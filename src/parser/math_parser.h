#include <deque>
#include <optional>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>
#include "../lexer/lexer.h"
#include "./node.h"

// TODO
// deleting all pointer memory from the heap
// actually make the math parser parse math

class MathParser {
	private: std::unordered_set<TokenType> allowed_types;
	
	public:
	MathParser() {
		allowed_types.insert(TokenType::FloatLiteral);
		allowed_types.insert(TokenType::IntegerLiteral);
	}

	private:
	auto string_to_optional_double(const std::string &s) 
		-> Result<std::optional<double>> {
		Result<std::optional<double>> result;
		
		double string_to_double; 
		try {
			string_to_double = std::stod(s);
		} catch (const std::invalid_argument &err) {
			result.error.set_error(err.what());
		} catch (const std::out_of_range &err) {
			result.error.set_error(err.what());
		} catch (...) {
			result.error.set_error
				("Unhandled conversion exception");
		}

		if (result.error.has_error()) {
			return result;
		}

		std::optional<double> double_to_optional;
		try {
			// make_optional is constexpr and there is no 
			// way that it will throw any exception 
			// but what if
			double_to_optional = 
				std::make_optional(string_to_double); 
		} catch (...) {
			result.error.set_error
				("Unhandled conversion exception");
			return result;
		}

		if (!double_to_optional.has_value()) {
			result.error.set_error
				("Unhandled conversion exception");
			return result;
		}

		result.ok.set_value(double_to_optional);	
		return result;
	}

	private:
	auto handle_size_one_expression(Token &token) 
		-> Result<Node> {
		Result<Node> result;

		if (allowed_types.count(token.token_type) == 0) {
			result.error.set_error("Wrong token type");
			return result;
		}

		Node node;
		node.node_type = NodeType::Number;

		auto conversion_result = 
			string_to_optional_double(token.value);

		if (conversion_result.error.has_error()) {
			result.error.set_error
				(conversion_result.error.to_string());
			return result;
		}

		node.number = conversion_result.ok.value();
		result.ok.set_value(node);
		return result;
	}

	private:
	auto get_number_from_token(Token &token) 
		-> Result<Node> {
		Result<Node> result;

		if (allowed_types.count(token.token_type) == 0) {
			result.error.set_error("Wrong token type");
			return result;
		}

		auto optional_conversion_result = 
			string_to_optional_double(token.value);

		if (optional_conversion_result.error.has_error()) {
			std::string error_message = 
				optional_conversion_result
				.error
				.to_string();
			result.error.set_error(error_message);
			return result;
		}

		Node result_node;
		result_node.node_type = NodeType::Number;
		result_node.number = 
			optional_conversion_result
			.ok
			.value();

		return result;
	}

	private:
	auto get_operator_from_token(Token &token) 
		-> Result<Node*> {
			Result<Node*> result;

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

			Node* result_node;
			result_node->node_operator = 
				conversion_result.ok.value();
			result_node->node_type = 
				NodeType::NumberOperator;

			result.ok.set_value(result_node);
			return result;
		}

	private:
	auto place_node
		(Node* &initial_node, Node* &current_node) 
		-> Result<Node*> {
		Result<Node*> result;	
		
		if (initial_node->node_type == NodeType::Number) {
			result.error.set_error("Wrong node type");
			return result;
		}

		if (current_node->node_type == NodeType::Number) {
			result.error.set_error("Wrong node type");
			return result;
		}

		return result;
	}

	private:
	auto get_initial_node(std::vector<Token> &expression) 
		-> Result<Node*> {
		Result<Node*> result;

		Node number1, number2;
		Node* number_operator;

		if (expression.size() < 3) {
			result.error.set_error("Wrong expression size");
			return result;
		}

		auto number_conversion_result = 
			get_number_from_token(expression[0]);

		if (number_conversion_result.error.has_error()) {
			std::string error_message = 
				number_conversion_result.error.to_string();
			result.error.set_error(error_message);

			return result;
		}

		number1 = number_conversion_result.ok.value();

		number_conversion_result = 
			get_number_from_token(expression[2]);

		if (number_conversion_result.error.has_error()) {
			std::string error_message = 
				number_conversion_result.error.to_string();
			result.error.set_error(error_message);

			return result;
		}

		number2 = number_conversion_result.ok.value();

		auto operator_conversion_result = 
			get_operator_from_token(expression[1]);

		if (operator_conversion_result.error.has_error()) {
			std::string error_message = 
				operator_conversion_result
				.error
				.to_string();
			result.error.set_error(error_message);

			return result;
		}

		number_operator = operator_conversion_result.ok.value(); 
	
		number_operator->left = &number1;
		number_operator->right = &number2;

		return result;
	}

	private:
	auto get_next_node
		(Token &number_operator, Token &number) 
		-> Result<Node*> {
		Result<Node*> result;

		auto operator_conversion_result = 
			get_operator_from_token(number_operator);

		if (operator_conversion_result.error.has_error()) {
			std::string error_message = 
				operator_conversion_result
				.error
				.to_string();
			result.error.set_error(error_message);
			return result;
		}

		Node* number_operator_node = 
			operator_conversion_result.ok.value();

		auto number_conversion_result = 
			get_number_from_token(number);

		if (number_conversion_result.error.has_error()) {
			std::string error_message = 
				number_conversion_result
				.error
				.to_string();
			result.error.set_error(error_message);
			return result;
		}

		Node number_node =
			number_conversion_result.ok.value();

		number_operator_node->right = &number_node;

		result.ok.set_value(number_operator_node);
		return result;
	}

	private:
	auto form_tree(std::vector<Token> &expression) 
		-> Result<Node> {
		Result<Node> result;
		
		if (expression.size() == 1) {
			auto handle_size_one_expression_result =
				handle_size_one_expression(expression[0]);

			bool is_error = 
				handle_size_one_expression_result
				.error
				.has_error();

			if (is_error) {
				std::string error_message = 
					handle_size_one_expression_result
					.error
					.to_string();

				result.error.set_error(error_message);
				return result;
			}
			
			Node node = 
				handle_size_one_expression_result
				.ok
				.value();

			result.ok.set_value(node);

			return result;
		}

		if (expression.empty()) {
			result.error.set_error("No expression");
			return result;
		}

		auto initial_node_result = 
			get_initial_node(expression);

		if (initial_node_result.error.has_error()) {
			std::string error_message = 
				initial_node_result.error.to_string();
			result.error.set_error(error_message);
			return result;
		}

		Node* initial_node = initial_node_result.ok.value();
	
		int i = 3;
		for (; i < expression.size() - 1; i += 2) {
			auto get_next_node_result = 
			get_next_node(expression[i], expression[i + 1]);
		}

		return result;
	}

	public: 
	auto parse_expression(std::vector<Token> &expression)
		-> Result<double> {
		Result<double> result;

		if (expression.empty()) {
			result.error.set_error("no expression to parse");
			return result;
		}
				
	}

};

