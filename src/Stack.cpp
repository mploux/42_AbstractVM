#include "Stack.hpp"

Stack::Stack()
{}

Stack::Stack(const Stack &o)
{ *this = o; }

Stack::~Stack()
{}

Stack	&Stack::operator=(const Stack &o)
{
	if (this != &o)
	{

	}
	return *this;
}

void Stack::pop()
{
	m_stack.pop_front();
}

void Stack::push(const IOperand *o)
{
	m_stack.push_front(o);
}

const IOperand *Stack::front()
{
	return m_stack.front();
}

void Stack::dump()
{
	for (const IOperand *o : m_stack)
		m_dump.push_back(o->toString() + "\n");
}

void Stack::print(const std::string &str)
{
	m_print.push_back(str);
}

void Stack::showDump()
{
	for (std::string &o : m_dump)
		std::cout << o;
	m_dump.clear();
}

void Stack::showPrint()
{
	std::cout << m_print.front();
	m_print.pop_front();
}

std::size_t	Stack::size()
{
	return m_stack.size();
}

bool Stack::empty()
{
	return m_stack.empty();
}

void Stack::clean()
{
	for (const IOperand *o : m_stack)
		delete o;
	m_stack.clear();
}

Stack &Stack::getInstance()
{
	static Stack stack;
	return stack;
}
