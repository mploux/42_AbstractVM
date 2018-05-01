#pragma once

#include <sstream>

#include "exceptions/AvmException.hpp"
#include "exceptions/AvmSeverException.hpp"
#include "IOperand.hpp"
#include "Error.hpp"
#include "utils.hpp"

template <typename T>
class Operand : public IOperand
{
private:
	std::string		m_strValue;
	std::string		m_typeName;
	T				m_value;
	long double 	m_min;
	long double 	m_max;
	eOperandType	m_type;
	int				m_precision;
	const Factory 	&m_factory;

	long double	convertValue(const std::string &str, bool verbose) const
	{
		if (m_precision > 2 && !utils::is_decimal(str) && verbose)
			throw AvmSeverException("Invalid decimal value: [" + str + "]");
		if (m_precision <= 2 && !utils::is_integer(str) && verbose)
			throw AvmSeverException("Invalid integer value: [" + str + "]");
		return std::stold(str);
	}

	T	convertToTypeValue(const std::string &str) const
	{
		long double rawVal = convertValue(str, true);
		if (rawVal < m_min)
			throw AvmException("Invalid minimum limit for type: " + m_typeName + " (" + m_strValue + " < " + utils::to_string<long double>(m_min) + ") !");
		if (rawVal > m_max)
			throw AvmException("Invalid maximum limit for type: " + m_typeName + " (" + m_strValue + " > " + utils::to_string<long double>(m_max) + ") !");
		return static_cast<T>(rawVal);
	}

public:
	Operand(const std::string &value, eOperandType type, const std::string &typeName, int precision, long double min, long double max, const Factory &factory)
		: m_strValue(value), m_typeName(typeName), m_min(min), m_max(max), m_type(type), m_precision(precision), m_factory(factory)
	{
		m_value = convertToTypeValue(m_strValue);
	}

	~Operand() {}

	const IOperand *operator+(const IOperand &rhs) const
	{
		eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

		T v1 = m_value;
		long double v2 = convertValue(rhs.toString(), false);

		long double r = v2 + v1;

		std::stringstream ss;
		ss << r;

		const IOperand *result = m_factory.createOperand(type, ss.str());
		return result;
	}

	const IOperand *operator-(const IOperand &rhs) const
	{
		eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

		T v1 = m_value;
		long double v2 = convertValue(rhs.toString(), false);

		long double r = v2 - v1;

		std::stringstream ss;
		ss << r;

		const IOperand *result = m_factory.createOperand(type, ss.str());
		return result;
	}

	const IOperand *operator*(const IOperand &rhs) const
	{
		eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

		T v1 = m_value;
		long double v2 = convertValue(rhs.toString(), false);

		long double r = v2 * v1;

		std::stringstream ss;
		ss << r;

		const IOperand *result = m_factory.createOperand(type, ss.str());
		return result;
	}

	const IOperand *operator/(const IOperand &rhs) const
	{
		eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

		T v1 = m_value;
		long double v2 = convertValue(rhs.toString(), false);

		if (v1 == 0)
			throw AvmSeverException("Invalid division by zero !");

		long double r = v2 / v1;

		std::stringstream ss;
		ss << r;

		const IOperand *result = m_factory.createOperand(type, ss.str());
		return result;
	}

	const IOperand *operator%(const IOperand &rhs) const
	{
		if (this->getPrecision() > 2 || rhs.getPrecision() > 2)
			throw AvmSeverException("Invalid modulus on floating point type !");
		if (!utils::is_integer(this->toString()) || !utils::is_integer(rhs.toString()))
			throw AvmSeverException("Invalid modulus on floating point type !");

		eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

		std::size_t pos;
		long v1 = static_cast<long>(m_value);
		long v2 = static_cast<long>(stol(rhs.toString(), &pos));

		if (v1 == 0)
			throw AvmSeverException("Invalid modulus by zero !");

		long r = v2 % v1;

		std::stringstream ss;
		ss << r;

		const IOperand *result = m_factory.createOperand(type, ss.str());
		return result;
	}

	int getPrecision(void) const { return m_precision; };
	eOperandType  getType(void) const { return m_type; };
	std::string const &toString(void) const { return m_strValue; }
};
