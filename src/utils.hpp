#pragma once

#include <iostream>
#include <cmath>
#include <sstream>
#include <regex>

#include "Error.hpp"
#include "eOperandType.hpp"

namespace utils
{
	bool is_decimal(const std::string &str);
	bool is_integer(const std::string &str);

	template <typename T>
	std::string	to_string(const T &val)
	{
		std::stringstream ss;

		ss << val;
		return ss.str();
	}
}