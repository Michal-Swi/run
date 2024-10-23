#include <string>
#include <vector>
#include "../error_handling/result.h"
#include "operations.h"

class Expression {
	private: std::vector<char> expression; 

	private: auto is_operation(const char &ch) -> bool {
				 switch (ch) {
					case Operations::divide:
						return true;
					case Operations::minus:
						return true;
					case Operations::plus:
						return true;
					case Operations::power:
						return true;
					case Operations::times:
						return true;
					default:
						return false;
				 }
			 }

	private: auto is_expression_valid(const std::string &expression) -> bool {
				 for (const auto &ch : expression) {
				 }
			 }

	public: auto set_expression(const std::string &expression) -> Result<int> {

			}
};
