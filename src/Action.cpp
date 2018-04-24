//
// Created by Marc-andre PLOUX on 4/24/18.
//

#include "Action.hpp"

Action::Action()
{
}

Action::Action(const std::string &cmd)
{
	m_value = -1;
	m_strCmd = cmd;
}

Action::Action(const std::string &cmd, const std::string &type, const std::string &value)
{
	m_strCmd = cmd;
	m_value = static_cast<float>(atof(value.c_str()));
}

Action::Action(const Action &o)
{
}

Action::~Action()
{
}

Action &Action::operator=(const Action &o)
{
}

void Action::execute(std::deque<float> &stack)
{
	if (m_strCmd == "add")
	{
		float val1 = stack.front();
		stack.pop_front();
		float val2 = stack.front();
		stack.pop_front();
		stack.push_front(val1 + val2);
	}
	if (m_strCmd == "mul")
	{
		float val1 = stack.front();
		stack.pop_front();
		float val2 = stack.front();
		stack.pop_front();
		stack.push_front(val1 * val2);
	}
	if (m_strCmd == "dump")
	{
		for (float &val : stack)
		{
			std::cout << val << "\n";
		}
	}
	if (m_strCmd == "pop")
		stack.pop_front();
	if (m_strCmd == "push")
		stack.push_front(m_value);
}

std::ostream &operator<<(std::ostream &s, const Action &o)
{
	return s;
}