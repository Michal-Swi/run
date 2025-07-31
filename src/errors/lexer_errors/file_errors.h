#include "../error_includes.h"

// File Errors (not grouped, group later)
inline constexpr const char* FilePathEmpty = "No file given";
inline constexpr const char* NoFileAtLocation = "No file at: ";
inline constexpr const char* FileIsEmpty = "Provided file is empty";

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
