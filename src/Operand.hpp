#pragma once

#include <sstream>

#include "IOperand.hpp"
#include "Error.hpp"
#include "utils.hpp"

template <typename T>
class Operand : public IOperand
{
private:
	std::string		m_strValue;
	T				m_value;
	long double 	m_min;
	long double 	m_max;
	eOperandType	m_type;
	int				m_precision;
	const Factory 	&m_factory;

	long double	convertValue(const std::string &str) const
	{
		if (!utils::is_decimal(str))
			Error::getInstance().error("Invalid decimal value !");
		return std::stold(str);
	}

	T	convertToTypeValue(const std::string &str) const
	{
		long double rawVal = convertValue(str);
		if (rawVal < m_min)
			Error::getInstance().error("Invalid minimum limit for type: (" + m_strValue + " < " + utils::to_string<long double>(m_min) + ") !");
		if (rawVal > m_max)
			Error::getInstance().error("Invalid maximum limit for type: (" + m_strValue + " > " + utils::to_string<long double>(m_max) + ") !");
		return static_cast<T>(rawVal);
	}

public:
	Operand(const std::string &value, eOperandType type, int precision, long double min, long double max, const Factory &factory)
		: m_strValue(value), m_min(min), m_max(max), m_type(type), m_precision(precision), m_factory(factory)
	{
		m_value = convertToTypeValue(m_strValue);
	}
	
	~Operand() {}

	const IOperand *operator+(const IOperand &rhs) const
	{
		eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

		T v1 = m_value;
		long double v2 = convertValue(rhs.toString());

		long double r = v1 + v2;

		std::stringstream ss;
		ss << r;

		const IOperand *result = m_factory.createOperand(type, ss.str());
		return result;
	}

	const IOperand *operator-(const IOperand &rhs) const
	{
		eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

		T v1 = m_value;
		long double v2 = convertValue(rhs.toString());

		long double r = v1 - v2;

		std::stringstream ss;
		ss << r;

		const IOperand *result = m_factory.createOperand(type, ss.str());
		return result;
	}

	const IOperand *operator*(const IOperand &rhs) const
	{
		eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

		T v1 = m_value;
		long double v2 = convertValue(rhs.toString());

		long double r = v1 * v2;

		std::stringstream ss;
		ss << r;

		const IOperand *result = m_factory.createOperand(type, ss.str());
		return result;
	}

	const IOperand *operator/(const IOperand &rhs) const
	{
		eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

		T v1 = m_value;
		long double v2 = convertValue(rhs.toString());

		long double r = v1 / v2;

		std::stringstream ss;
		ss << r;

		const IOperand *result = m_factory.createOperand(type, ss.str());
		return result;
	}

	const IOperand *operator%(const IOperand &rhs) const
	{
		(void) rhs;
		// eOperandType type = Int32;

		// long v1 = static_cast<long>(std::atol(m_value.c_str()));
		// long v2 = static_cast<long>(std::atol(rhs.toString().c_str()));
		// long r = v1 % v2;

		// std::stringstream ss;
		// ss << r;

		// const IOperand *result = m_factory.createOperand(type, ss.str());
		return nullptr;
	}

	int getPrecision(void) const { return m_precision; };
	eOperandType  getType(void) const { return m_type; };	
	std::string const &toString(void) const { return m_strValue; }
};
