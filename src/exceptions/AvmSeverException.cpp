#include "AvmSeverException.hpp"

AvmSeverException::AvmSeverException()
	: AvmException()
{}

AvmSeverException::AvmSeverException(const std::string &msg)
	: AvmException(msg)
{}

AvmSeverException::AvmSeverException(const std::string &msg, const std::string &line)
	: AvmException(msg, line)
{}

AvmSeverException::AvmSeverException(const AvmSeverException &o)
	: AvmException()
{
	*this = o;
}

AvmSeverException::~AvmSeverException() throw()
{}

AvmSeverException &AvmSeverException::operator=(const AvmSeverException &o)
{
	if (this != &o)
	{
		m_msg = o.m_msg;
	}
	return *this;
}

const char *AvmSeverException::what() const throw()
{
	return m_msg.c_str();
}
