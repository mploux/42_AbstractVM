#include "AvmException.hpp"

AvmException::AvmException()
	: m_msg(""), m_line("")
{}

AvmException::AvmException(const std::string &msg)
	: m_msg(msg), m_line("")
{}

AvmException::AvmException(const std::string &msg, const std::string &line)
	: m_msg(msg), m_line(line)
{}

AvmException::AvmException(const AvmException &o)
{
	*this = o;
}

AvmException::~AvmException() throw()
{}

AvmException &AvmException::operator=(const AvmException &o)
{
	if (this != &o)
	{
		m_msg = o.m_msg;
	}
	return *this;
}

const std::string &AvmException::getMessage() const
{
	return m_msg;
}

const std::string &AvmException::getLine() const
{
	return m_line;
}

bool AvmException::hasLine() const
{
	return !m_line.empty();
}

const char *AvmException::what() const throw()
{
	return m_msg.c_str();
}
