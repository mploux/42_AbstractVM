//
// Created by Marc-andre PLOUX on 4/24/18.
//

#ifndef AVM_ACTION_HPP
# define AVM_ACTION_HPP

# include <iostream>
# include <deque>

class Action
{
public:
	enum ECommand
	{
		PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT
	};

private:
	std::string		m_strCmd;
	std::string		m_strType;
	std::string		m_strvalue;
	ECommand		m_cmd;
	std::string		m_type;
	float			m_value;

	Action();
public:
	Action(const std::string &cmd);
	Action(const std::string &cmd, const std::string &type, const std::string &value);

	Action(const Action &o);
	virtual ~Action();
	Action &operator=(const Action &o);

	void execute(std::deque<float> &stack);
};

std::ostream &operator<<(std::ostream &s, const Action &o);


#endif
