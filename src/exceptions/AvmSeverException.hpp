#pragma once

#include <iostream>

#include "AvmException.hpp"

class AvmSeverException : public AvmException
{
private:
	AvmSeverException();

public:
	AvmSeverException(const std::string &msg);
	AvmSeverException(const std::string &msg, const std::string &line);
	AvmSeverException(const AvmSeverException &o);
	~AvmSeverException() throw();
	AvmSeverException &operator=(const AvmSeverException &o);

	virtual const char *what() const throw();
};
