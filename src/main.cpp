#include <iostream>
#include <optional>
#include "./error_handling/result.h"
#include <cstddef>

auto func() -> Result<int> {
	Result<int> res;
	res.error.set_error("example");	

	return res;
}

int main() {
	Result<int> result = func();

	std::optional<double> n;

	std::cout << n.has_value() << std::endl;
}

