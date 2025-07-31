#include "../error_includes.h"

// Internal Parser Errors
inline constexpr const char* InternalParserError = "Internal Parser Error ";
inline constexpr const char* InternalParserErrorIteratorOverflow = "i >= tokens.size()";

enum class InternalParserErrors {
	IteratorOverflow,
};

class internal_parser_error : public std::exception {
	private:
	std::string error = InternalParserError;

	public:
	internal_parser_error(const InternalParserErrors &internal_parser_error, const std::string &additional_info) {
		switch (internal_parser_error) {
			case InternalParserErrors::IteratorOverflow:
				error += InternalParserErrorIteratorOverflow;
				error += " " + additional_info;
				break;
			default:
				break;	
		}
	}

	internal_parser_error(const InternalParserErrors &internal_parser_error) {
		switch (internal_parser_error) {
			case InternalParserErrors::IteratorOverflow:
				error += InternalParserErrorIteratorOverflow;
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

