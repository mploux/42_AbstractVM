//
// Created by Marc-andre PLOUX on 4/24/18.
//

#include "Action.hpp"

Action::Action()
	: m_cmd("none"), m_rawValue("none"), m_factory(nullptr)
{}

Action::Action(const std::string &cmd, Factory *factory)
	: m_cmd(cmd), m_rawValue("none"), m_factory(factory)
{}

Action::Action(const std::string &cmd, const std::string &type, const std::string &value, Factory *factory)
	: m_cmd(cmd), m_rawValue(value), m_factory(factory)
{
	m_operands["int8"] = Int8;
	m_operands["int16"] = Int16;
	m_operands["int32"] = Int32;
	m_operands["float"] = Float;
	m_operands["double"] = Double;

	if (m_operands.find(type) != m_operands.end())
	{
		if (utils::is_decimal(m_rawValue))
		{
			m_type = m_operands[type];
			m_value = m_factory->createOperand(m_type, m_rawValue);
		}
		else
			Error::getInstance().error("Invalid decimal value: " + m_rawValue);
	}
	else
		Error::getInstance().error("Invalid operand: " + type);
}

Action::Action(const Action &o)
{
	*this = o;
}

Action::~Action()
{
}

Action &Action::operator=(const Action &o)
{
	(void) o;

	if (this != &o)
	{
	}

	return *this;
}

void Action::execute(std::deque<const IOperand *> &stack)
{
	if (m_cmd == "add")
	{
		const IOperand &val1 = *stack.front();
		stack.pop_front();
		const IOperand &val2 = *stack.front();
		stack.pop_front();
		const IOperand *result = val1 + val2;
		stack.push_front(result);
	}
	if (m_cmd == "sub")
	{
		const IOperand &val1 = *stack.front();
		stack.pop_front();
		const IOperand &val2 = *stack.front();
		stack.pop_front();
		const IOperand *result = val1 - val2;
		stack.push_front(result);
	}
	if (m_cmd == "mul")
	{
		const IOperand &val1 = *stack.front();
		stack.pop_front();
		const IOperand &val2 = *stack.front();
		stack.pop_front();
		const IOperand *result = val1 * val2;
		stack.push_front(result);
	}
	if (m_cmd == "div")
	{
		const IOperand &val1 = *stack.front();
		stack.pop_front();
		const IOperand &val2 = *stack.front();
		stack.pop_front();
		const IOperand *result = val1 / val2;
		stack.push_front(result);
	}
	if (m_cmd == "dump")
	{
		for (const IOperand *val : stack)
			std::cout << val->toString() << "\n";
	}
	if (m_cmd == "pop")
		stack.pop_front();
	if (m_cmd == "push")
		stack.push_front(m_value);
}

std::ostream &operator<<(std::ostream &s, const Action &o)
{
	(void) o;
	return s;
}
