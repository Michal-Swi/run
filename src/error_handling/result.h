#include "error.h"

template<class T, class T1>
class Result {
	private: T first_argument;
	private: T1 second_argument;

	public: Result(const T& first_argument, 
					const T1& second_argument) {
				this->first_argument = first_argument;
				this->second_argument = second_argument;
			}

	public: auto get_first_argument() -> T {
				return first_argument;
			}

	public: auto get_second_argument() -> T1 {
				return second_argument;
			}
};

