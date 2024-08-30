#include "lexer.h"
#include <iostream>

int main() {
	Lexer l;	

	std::cout << std::boolalpha << l.is_whitespace(' ') << std::endl;

	return 0;
}
