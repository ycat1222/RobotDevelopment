#pragma once
#include <exception>
#include <string>

namespace BBB {
	class ErrorBBB : public std::exception {
	private:
		std::string str;

	public:
		ErrorBBB(char* str_)
			{ str = str_; }

		const char* what() const override
			{ return str.c_str(); }

	};
};