//
// Created by Marc-andre PLOUX on 4/24/18.
//

#include "Action.hpp"

Action::Action()
	: m_cmd("none"), m_rawValue("none"), m_factory(nullptr)
{}

Action::Action(const std::string &cmd, Factory *factory)
	: m_cmd(cmd), m_rawValue("none"), m_factory(factory)
{
	(this->*action(m_cmd))();
}

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
		m_type = m_operands[type];
		m_value = m_factory->createOperand(m_type, m_rawValue);
		(this->*action(m_cmd))();
	}
	else
		throw AvmException("Invalid operand: " + type);
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

void Action::add()
{
	if (Stack::getInstance().size() < 2)
	{
		throw AvmException("Invalid add on a stack size below 2 !");
		return;
	}
	const IOperand &val1 = *Stack::getInstance().front();
	Stack::getInstance().pop();
	const IOperand &val2 = *Stack::getInstance().front();
	Stack::getInstance().pop();
	const IOperand *result = val1 + val2;
	delete &val1;
	delete &val2;
	Stack::getInstance().push(result);
}

void Action::sub()
{
	if (Stack::getInstance().size() < 2)
	{
		throw AvmException("Invalid sub on a stack size below 2 !");
		return;
	}
	const IOperand &val1 = *Stack::getInstance().front();
	Stack::getInstance().pop();
	const IOperand &val2 = *Stack::getInstance().front();
	Stack::getInstance().pop();
	const IOperand *result = val1 - val2;
	delete &val1;
	delete &val2;
	Stack::getInstance().push(result);
}

void Action::mul()
{
	if (Stack::getInstance().size() < 2)
	{
		throw AvmException("Invalid mul on a stack size below 2 !");
		return;
	}
	const IOperand &val1 = *Stack::getInstance().front();
	Stack::getInstance().pop();
	const IOperand &val2 = *Stack::getInstance().front();
	Stack::getInstance().pop();
	const IOperand *result = val1 * val2;
	delete &val1;
	delete &val2;
	Stack::getInstance().push(result);
}

void Action::div()
{
	if (Stack::getInstance().size() < 2)
	{
		throw AvmException("Invalid div on a stack size below 2 !");
		return;
	}
	const IOperand &val1 = *Stack::getInstance().front();
	Stack::getInstance().pop();
	const IOperand &val2 = *Stack::getInstance().front();
	Stack::getInstance().pop();
	const IOperand *result = val1 / val2;
	delete &val1;
	delete &val2;
	Stack::getInstance().push(result);
}

void Action::mod()
{
	if (Stack::getInstance().size() < 2)
	{
		throw AvmException("Invalid mod on a stack size below 2 !");
		return;
	}
	const IOperand &val1 = *Stack::getInstance().front();
	Stack::getInstance().pop();
	const IOperand &val2 = *Stack::getInstance().front();
	Stack::getInstance().pop();
	if (val1.getPrecision() > 3 || val2.getPrecision() > 3)
	{
		throw AvmException("Invalid modulus on floating point type !");
		delete &val1;
		delete &val2;
		return;
	}
	const IOperand *result = val1 % val2;
	delete &val1;
	delete &val2;
	Stack::getInstance().push(result);
}

void Action::dump()
{
	Stack::getInstance().dump();
}

void Action::pop()
{
	if (Stack::getInstance().empty())
	{
		throw AvmException("Invalid pop on empty stack !");
		return;
	}
	delete Stack::getInstance().front();
	Stack::getInstance().pop();
}

void Action::assert()
{
	if (Stack::getInstance().empty())
	{
		throw AvmException("Invalid assert on empty stack !");
		return;
	}
	static std::string types[] = {
		"int8", "int16", "int32", "float", "double", "invalid_type"
	};
	const std::string v1 = m_value->toString();
	const std::string v2 = Stack::getInstance().front()->toString();
	int p1 = m_value->getPrecision();
	int p2 = Stack::getInstance().front()->getPrecision();

	if (p1 < 0 || p1 > 4)
		p1 = 5;
	if (p2 < 0 || p2 > 4)
		p2 = 5;
	if (v1 != v2)
		throw AvmException("Invalid assert: (" + v1 + " != " + v2 + ")");
	if (p1 != p2)
		throw AvmException("Invalid assert: (" + types[p1] + " != " + types[p2] + ")");

	delete m_value;
}

void Action::print()
{
	if (Stack::getInstance().empty())
	{
		throw AvmException("Invalid print on empty stack !");
		return;
	}
	static std::string types[] = {
		"int8", "int16", "int32", "float", "double", "invalid_type"
	};
	std::size_t pos;
	const IOperand *val = Stack::getInstance().front();
	int precision = val->getPrecision();
		if (precision < 0 || precision > 4)
		precision = 5;
	if (precision != 0)
	{
		throw AvmException("Invalid assert: (int8 != " + types[precision] + ")");
		return;
	}
	char ascii_val = static_cast<char>(std::stoi(val->toString(), &pos));
	std::stringstream ss;
	ss << ascii_val;
	Stack::getInstance().dump(ss.str());
}

void Action::push()
{
	Stack::getInstance().push(m_value);
}

void Action::execute()
{
	if (m_cmd == "dump")
		Stack::getInstance().showDump();
}

Action::funcPtr	Action::action(const std::string &action)
{
	static std::map<std::string, funcPtr> actions;

	if (actions.empty())
	{
		actions["add"] = &Action::add;
		actions["sub"] = &Action::sub;
		actions["mul"] = &Action::mul;
		actions["div"] = &Action::div;
		actions["dump"] = &Action::dump;
		actions["pop"] = &Action::pop;
		actions["mod"] = &Action::mod;
		actions["push"] = &Action::push;
		actions["assert"] = &Action::assert;
		actions["print"] = &Action::print;
	}

	return actions[action];
}

std::ostream &operator<<(std::ostream &s, const Action &o)
{
	(void) o;
	return s;
}
