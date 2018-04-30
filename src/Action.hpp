//
// Created by Marc-andre PLOUX on 4/24/18.
//

#pragma once

#include <iostream>
#include <deque>
#include <map>

#include "Factory.hpp"
#include "Error.hpp"
#include "utils.hpp"
#include "Operand.hpp"
#include "Stack.hpp"

class Action
{
private:
	typedef void (Action::*funcPtr)(void);

	std::map<std::string, eOperandType>	m_operands;
	std::string							m_cmd;
	eOperandType						m_type;
	std::string							m_rawValue;
	const IOperand						*m_value;
	Factory								*m_factory;

	Action();

	void add();
	void sub();
	void mul();
	void div();
	void mod();
	void dump();
	void pop();
	void push();
	void assert();

	static funcPtr	action(const std::string &action);

public:
	Action(const std::string &cmd, Factory *factory);
	Action(const std::string &cmd, const std::string &type, const std::string &value, Factory *factory);

	Action(const Action &o);
	virtual ~Action();
	Action &operator=(const Action &o);

	void execute();
};

std::ostream &operator<<(std::ostream &s, const Action &o);
