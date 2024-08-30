#include "error.h"
#include "ok.h"

template <class T>
struct Result {
	public: Ok<T> ok;
	public: Error error;
};
