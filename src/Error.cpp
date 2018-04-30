#include "Error.hpp"

Error::Error()
	: m_line(0)
{}

Error::Error(const Error &o)
{
	*this = o;
}

Error::~Error()
{}

Error &Error::operator=(const Error &o)
{
	if (this != &o)
	{
		m_line = o.m_line;
		m_errors.clear();
		for (auto &pair : o.m_errors)
			m_errors[pair.first] = pair.second;
	}
	return *this;
}

void Error::error(const std::string &message)
{
	if (m_errors.find(m_line) == m_errors.end())
		m_errors.insert(std::pair<int, std::string>(m_line, message));
}

void Error::error(const std::string &message, const std::string &line)
{
	std::string finalMessage;

	finalMessage = message + "\n\033[0;36m>\033[0m  " + line + "\n";
	if (m_errors.find(m_line) == m_errors.end())
		m_errors.insert(std::pair<int, std::string>(m_line, finalMessage));
}

void Error::sever(const std::string &message)
{
	show();
	std::cout << "\033[1;31msever line " << m_line << ":  \033[0m" << message << "\n";
	exit(1);
}

void Error::show()
{
	for (auto &pair : m_errors)
		std::cout << "\x1B[1merror line " << pair.first << ":  \x1B[0m" << pair.second << "\n";
}

bool Error::hasErrors()
{
	return !m_errors.empty();
}

void Error::setLine(const int &line)
{
	m_line = line;
}

int &Error::getLine()
{
	return m_line;
}

Error &Error::getInstance()
{
	static Error e;
	return (e);
}
