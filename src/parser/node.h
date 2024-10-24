#include "./operations.h"
#include <cstddef>
#include <optional>

struct Node {
	std::optional<double> number;
	Operations node_operator;
	Node* left;
	Node* right;
	Node *up;

	Node() : left(nullptr), 
			 right(nullptr), 
			 up(nullptr), 
			 node_operator(Operations::no_operator)
			 {} 
};

