#include "operations.h"
#include <string>

class Token {
	private: Token* left;	
	private: Token* right;
	private: Token* father;
	private: Operations operation; 
	private: std::string number; 

	public: auto set_left(Token* left) -> void {
				this->left = left;
			}

	public: auto get_left() -> Token* {
				return left;
			}

	public: auto set_right(Token* right) -> void {
				this->right = right;
			}

	public: auto get_right() -> Token* {
				return right;
			}

	public: auto set_operation(const Operations &operation) -> void {
				this->operation = operation;	
			}

	public: auto get_operation() -> Operations {
				return operation;
			}

	public: auto set_number(const std::string& number) -> void {
				this->number = number;
			}

	public: auto get_number() -> std::string {
				return number;
			}
};

