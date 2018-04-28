#include "utils.hpp"

bool utils::is_decimal(const std::string &str)
{
	long double value;
	bool result;
	size_t	spos;

	value = 0.0;
	try
	{
		value = std::stold(str, &spos);
	}
	catch (std::invalid_argument &e)
	{
		std::string err = e.what();
		Error::getInstance().error(err);
		return false;
	}
	catch (std::out_of_range &e)
	{
		std::string err = e.what();
		Error::getInstance().error(err);
		return false;
	}
	catch (std::exception &e)
	{
		Error::getInstance().error("Unknown decimal error !");
		return false;
	}

	result = spos == str.size() && !std::isnan(value);
	return (result);
}

bool utils::is_decimal(const std::string &str, long double &value)
{
	bool result;
	size_t	spos;

	value = 0.0;
	try
	{
		value = std::stold(str, &spos);
	}
	catch (std::invalid_argument &e)
	{
		std::string err = e.what();
		Error::getInstance().error(err);
		return false;
	}
	catch (std::out_of_range &e)
	{
		std::string err = e.what();
		Error::getInstance().error(err);
		return false;
	}
	catch (std::exception &e)
	{
		Error::getInstance().error("Unknown decimal error !");
		return false;
	}

	result = spos == str.size() && !std::isnan(value);
	return (result);
}
