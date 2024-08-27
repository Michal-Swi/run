#include <string>

class Error {
	private: std::string error_name;
	private: bool error;

	public: Error(const bool &error = false, 
					const std::string &error_name = "") {
				this->error = error;
				this->error_name = error_name;
			}

	public: auto set_is_error(const bool &is_error) -> void {
				this->error = is_error;	
			}

	public: auto set_error_name(const std::string &error_name) -> void {
				this->error_name = error_name;
			}

	public: auto get_is_error() -> bool {
				if (error == static_cast<bool>(NULL) or error == false) {
					return false;
				}

				return true;
			}

	public: auto get_error_name() -> std::string {
				if (!error_name.empty()) {
					return error_name;
				}

				return "";
			}
};

