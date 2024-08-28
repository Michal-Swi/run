#include <string>

class Error {
	private: std::string error;

	public: Error(const std::string &error = "") {
				this->error = error;
			}

	public: auto to_string() -> std::string {
				return error;
			}

	public: auto set_error(const std::string &error = "") -> void {
				this->error = error;
			}
};

