#pragma once

#include <iostream>

class AvmException : public std::exception
{
protected:
	std::string		m_msg;
	std::string		m_line;

	AvmException();
public:
	AvmException(const std::string &msg);
	AvmException(const std::string &msg, const std::string &line);
	AvmException(const AvmException &o);
	~AvmException() throw();
	AvmException &operator=(const AvmException &o);

	virtual const std::string &getMessage() const;
	virtual const std::string &getLine() const;
	virtual bool hasLine() const;

	virtual const char *what() const throw();
};
