#include "utils.hpp"

bool utils::is_decimal(const std::string &str)
{
	std::regex	match("^[-]?[0-9]+\\.[0-9]+$");
	return std::regex_match(str, match);
}

bool utils::is_integer(const std::string &str)
{
	std::regex	match("^[-]?[0-9]+$");
	return std::regex_match(str, match);
}
