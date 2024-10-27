#include "../error_handling/result.h"
#include <string>

enum Operations {
	plus = '+',
	minus = '-',
	times = '*',
	divide = '/',
	power = '^',
	no_operator
};

class OperationsHelperFunctions {
	public:
	static auto match_with_operator(const std::string &s) 
			-> Result<Operations> {
		Result<Operations> result;
		
		if (s.length() != 1) {
			result.error.set_error
				("No operator matching: " + s);
			return result;
		}
		
		char ch = static_cast<char>(s[0]);

		switch (ch) {
			case Operations::plus:	
				result.ok.set_value(Operations::plus);
				break;
			case Operations::minus:
				result.ok.set_value(Operations::minus);
				break;
			case Operations::times:
				result.ok.set_value(Operations::times);
				break;
			case Operations::divide:
				result.ok.set_value(Operations::divide);
				break;;
			case Operations::power:
				result.ok.set_value(Operations::power);
				break;
			default:
				result.error.set_error
					("No operator matching: " + s);
		}

		return result;
	}
};

