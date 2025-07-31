#include "../error_includes.h"

// Internal Lexer Errors
inline constexpr const char* InternalLexerError = "Internal Lexer Error ";
inline constexpr const char* InternalLexerErrorIteratorOverflow = "i >= file_literal.length()";

enum class InternalLexerErrors {
	IteratorOverflow,
};

class internal_lexer_error : public std::exception {
	private:
	std::string error = InternalLexerError;

	public:
	internal_lexer_error(const InternalLexerErrors &err_type) {
		switch (err_type) {
			case InternalLexerErrors::IteratorOverflow:
				error += InternalLexerErrorIteratorOverflow;
				break;
			default:
				break;
		}
	}

	public:
	internal_lexer_error(const InternalLexerErrors &err_type, const std::string &additional_info) {
		switch (err_type) {
			case InternalLexerErrors::IteratorOverflow:
				error += InternalLexerErrorIteratorOverflow;
				error += " " + additional_info;
				break;
			default:
				break;
		}
	}


	public:
	const char* what() const noexcept override {
		const char* error_message = error.c_str();
		return error_message;
	}
};

