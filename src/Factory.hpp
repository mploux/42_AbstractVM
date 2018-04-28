#pragma once

#include <iostream>
#include <limits>

#include "IOperand.hpp"
#include "eOperandType.hpp"

class Factory
{
private:
	const IOperand *createInt8(const std::string &value) const;
	const IOperand *createInt16(const std::string &value) const;
	const IOperand *createInt32(const std::string &value) const;
	const IOperand *createFloat(const std::string &value) const;
	const IOperand *createDouble(const std::string &value) const;

public:
	Factory();
	virtual ~Factory();

	const IOperand *createOperand(eOperandType type, const std::string &value) const;
};