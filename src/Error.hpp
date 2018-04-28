#pragma once

#include <iostream>
#include <map>

class Error
{
private:
	std::map<int, std::string>	m_errors;
	int							m_line;

public:
	Error();
	Error(const Error &o);
	virtual ~Error();
	Error &operator=(const Error &o);

	void error(const std::string &message);
	void error(const std::string &message, const std::string &line);

	void setLine(const int &line);
	int &getLine();

	void show();
	bool hasErrors();

	static Error &getInstance();
};
