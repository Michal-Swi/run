#include "./operations.h"
#include <cstddef>
#include <optional>

enum NodeType {
	Number, 
	NumberOperator
};

struct Node {
	NodeType node_type;
	std::optional<double> number;
	Operations node_operator;
	Node* left;
	Node* right;

	Node() : left(nullptr), 
			 right(nullptr), 
			 node_operator(Operations::no_operator)
			 {} 
};

