#include <iostream>
#include <optional>
#include "./error_handling/result.h"

auto func() -> Result<int> {
	Result<int> res;
	res.error.set_error("example");	

	return res;
}

int main() {
	Result<int> result = func();

	std::cout << result.ok.value() << std::endl;
}

