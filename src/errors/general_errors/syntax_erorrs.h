#include "../error_includes.h"

inline constexpr const char* SyntaxError = "Syntax Error: ";

class syntax_error : public std::exception {
	private:
	std::string wrong_syntax;

	public:
	syntax_error(const std::string &wrong_syntax) {
		this->wrong_syntax = wrong_syntax;
	}

	public:
	const char* what() const noexcept override {
		std::string error = (SyntaxError + this->wrong_syntax);
		const char* error_message = error.c_str();
		return error_message;
	}
};
