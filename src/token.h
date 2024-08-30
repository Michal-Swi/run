#include "operations.h"
#include <string>

class Token {
	private: Token* previous;	
	private: Token* next;
	private: Operations operation; 
	private: std::string number; 

	public: auto set_previous(Token* previous) -> void {
				this->previous = previous;
			}

	public: auto get_previous() -> Token* {
				return previous;
			}

	public: auto set_next(Token* next) -> void {
				this->next = next;
			}

	public: auto get_next() -> Token* {
				return next;
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

