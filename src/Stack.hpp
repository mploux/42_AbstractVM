#pragma once

#include <iostream>
#include <deque>
#include <vector>

#include "IOperand.hpp"

class Stack
{
private:
	std::deque<const IOperand *>	m_stack;
	std::vector<std::string>		m_dump;

public:
	Stack();
	Stack(const Stack &o);
	virtual ~Stack();
	Stack	&operator=(const Stack &o);

	void pop();
	void push(const IOperand *o);
	const IOperand *front();
	void dump();
	void showDump();
	std::size_t	size();
	bool empty();
	void clean();

	static Stack &getInstance();
};
