#include "Factory.hpp"
#include "Operand.hpp"

Factory::Factory()
{
	m_funcPtrs[Int8] = &Factory::createInt8;
	m_funcPtrs[Int16] = &Factory::createInt16;
	m_funcPtrs[Int32] = &Factory::createInt32;
	m_funcPtrs[Float] = &Factory::createFloat;
	m_funcPtrs[Double] = &Factory::createDouble;
}

Factory::~Factory()
{}

const IOperand *Factory::createOperand(eOperandType type, const std::string &value) const
{
	if (m_funcPtrs.find(type) == m_funcPtrs.end())
	{
		Error::getInstance().error("Invalid type !");
		return nullptr;
	}
	return (this->*m_funcPtrs.at(type))(value);
}

const IOperand *Factory::createInt8(const std::string &value) const
{
	long double min = std::numeric_limits<char>::min();
	long double max = std::numeric_limits<char>::max();
	return new Operand<int8_t>(value, Int8, "int8", 0, min, max, *this);
}

const IOperand *Factory::createInt16(const std::string &value) const
{
	long double min = std::numeric_limits<int>::min();
	long double max = std::numeric_limits<int>::max();
	return new Operand<int16_t>(value, Int16, "int16", 1, min, max, *this);
}

const IOperand *Factory::createInt32(const std::string &value) const
{
	long double min = std::numeric_limits<long>::min();
	long double max = std::numeric_limits<long>::max();
	return new Operand<int32_t>(value, Int32, "int32", 2, min, max, *this);
}

const IOperand *Factory::createFloat(const std::string &value) const
{
	long double min = std::numeric_limits<float>::min();
	long double max = std::numeric_limits<float>::max();
	return new Operand<float>(value, Float, "float", 3, min, max, *this);
}

const IOperand *Factory::createDouble(const std::string &value) const
{
	long double min = std::numeric_limits<double>::min();
	long double max = std::numeric_limits<double>::max();
	return new Operand<double>(value, Double, "double", 4, min, max, *this);
}
