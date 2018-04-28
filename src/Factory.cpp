#include "Factory.hpp"
#include "Operand.hpp"

Factory::Factory()
{}

Factory::~Factory()
{}

const IOperand *Factory::createOperand(eOperandType type, const std::string &value) const
{
	// TODO: Use pointers to member function
	if (type == eOperandType::Int8)
		return createInt8(value);
	if (type == eOperandType::Int16)
		return createInt16(value);
	if (type == eOperandType::Int32)
		return createInt32(value);
	if (type == eOperandType::Float)
		return createFloat(value);
	if (type == eOperandType::Double)
		return createDouble(value);
	return nullptr;
}

const IOperand *Factory::createInt8(const std::string &value) const
{
	long double min = std::numeric_limits<char>::min();
	long double max = std::numeric_limits<char>::max();
	return new Operand<char>(value, Int8, 0, min, max, *this);
}

const IOperand *Factory::createInt16(const std::string &value) const
{
	long double min = std::numeric_limits<int>::min();
	long double max = std::numeric_limits<int>::max();
	return new Operand<int>(value, Int16, 1, min, max, *this);
}

const IOperand *Factory::createInt32(const std::string &value) const
{
	long double min = std::numeric_limits<long>::min();
	long double max = std::numeric_limits<long>::max();
	return new Operand<long>(value, Int32, 2, min, max, *this);
}

const IOperand *Factory::createFloat(const std::string &value) const
{
	long double min = std::numeric_limits<float>::min();
	long double max = std::numeric_limits<float>::max();
	return new Operand<float>(value, Float, 3, min, max, *this);
}

const IOperand *Factory::createDouble(const std::string &value) const
{
	long double min = std::numeric_limits<double>::min();
	long double max = std::numeric_limits<double>::max();
	return new Operand<double>(value, Double, 4, min, max, *this);
}