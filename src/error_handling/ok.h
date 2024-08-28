
template <class T>
class Ok {
	private: T val;
	
	public: auto value() -> T {
				return val;
			}

	public: auto set_value(const T &val) -> T {
				this->val = val;
			}
};

