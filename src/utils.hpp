#pragma once

#include <iostream>
#include <cmath>
#include <sstream>

#include "Error.hpp"
#include "eOperandType.hpp"

namespace utils
{
	bool is_decimal(const std::string &str);
	bool is_decimal(const std::string &str, long double &value);

	template <typename T>
	std::string	to_string(const T &val)
	{
		std::stringstream ss;

		ss << val;
		return ss.str();
	}
}