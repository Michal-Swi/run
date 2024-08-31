#include "lexer.h"
#include <iostream>

int main() {
	Lexer l;
	l.tokenize("file");
	l.print();

	return 0;
}
