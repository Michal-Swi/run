#include "../error_includes.h"

inline constexpr const char* BadToken = "Bad Token";

class bad_token : public std::exception {
	private:
	std::string error = BadToken;

	public:
	bad_token(const std::string &additional_info) {
		error += ": " + additional_info;
	}

	public:
	bad_token() {}

	public:
	const char* what() const noexcept override {
		const char* error_message = error.c_str();
		return error_message;
	}
};

