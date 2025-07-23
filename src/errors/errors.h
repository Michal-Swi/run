#include <exception>
#include <string>

// Macro hell (modern C++ friendly) 
// here so that I do not use "" strings
// Also group erros by type e.g. SyntaxErrors, FileErrors, etc.
inline constexpr const char* _TemplateError = "TemplateError";

inline constexpr const char* SyntaxError = "Syntax Error: "; 

// File Errors (not grouped, group later)
inline constexpr const char* FilePathEmpty = "No file given";
inline constexpr const char* NoFileAtLocation = "No file at: ";
inline constexpr const char* FileIsEmpty = "Provided file is empty";

// Internal Lexer Errors
inline constexpr const char* InternalLexerError = "Internal Lexer Error";
inline constexpr const char* InternalLexerErrorIteratorOverflow = "Internal Lexer Error, i >= file_literal.length()";


// DO NOT EDIT, JUST COPY THE TEMPLATE
// MORE COMPLEX ERORRS SHOULD BE CONSTRUCTED
// LIKE SO: 
// std::string error = ...;
// const char* error_message = error.c_str()
// return error_message
//
// Also, group errors
class template_error : public std::exception {
	public:
	const char* what() const noexcept override {
		return "";
	}
};

enum class InternalLexerErrors {
	IteratorOverflow,
};

class internal_lexer_error : public std::exception {
	private:
	std::string error;

	public:
	internal_lexer_error(const InternalLexerErrors &err_type) {
		switch (err_type) {
			case InternalLexerErrors::IteratorOverflow:
				error = InternalLexerErrorIteratorOverflow;
				break;
			default:
				error = InternalLexerError; 
		}
	}

	public:
	internal_lexer_error(const InternalLexerErrors &err_type, const std::string &additional_info) {
		switch (err_type) {
			case InternalLexerErrors::IteratorOverflow:
				error = InternalLexerErrorIteratorOverflow;
				error += " " + additional_info;
				break;
			default:
				error = InternalLexerError; 
		}
	}


	public:
	const char* what() const noexcept override {
		const char* error_message = error.c_str();
		return error_message;
	}
};

class no_file : public std::exception {
	public:
	std::string file_path;

	public:
	no_file(const std::string &file_path) {
		this->file_path = file_path;
	}

	public:
	const char* what() const noexcept override {
		if (file_path.empty()) {
			return FilePathEmpty;
		}
		
		std::string error = NoFileAtLocation + this->file_path;
		const char* error_message = error.c_str();
		return error_message;
	}
};

class file_is_empty : public std::exception {
	public:
	const char* what() const noexcept override {
		return FileIsEmpty;
	}
};

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

