//Anton Yarakhtin
#pragma once
#include <cmath>
#include <unordered_map>
#include "Converter.hpp"


namespace Tokens 
{
	enum class Type : int
	{
		NUMBER,
		U_OPERATOR,
		B_OPERATOR,
		L_PARENTHESIS,
		R_PARENTHESIS
	};

	enum class operatorID : int
	{
		PLUS, MINUS, MULTIPLICATION, DIVISION, EXPONENTIATION, SQRT, LG, LN,
		SINE, COSINE, TANGENT, COTANGENT, ARCSINE, ARCCOSINE, ARCTANGENT, ARCCOTANGENT,
		SECANT, COSECANT, ARCSECANT, ARCCOSECANT,
		HYPERBOLICSINE, HYPERBOLICCOSINE, HYPERBOLICTANGENT, HYPERBOLICCOTANGENT
	};

	const std::unordered_map<std::string, operatorID> supportedOperators = {
		{"+", operatorID::PLUS}, {"-", operatorID::MINUS},  {"*", operatorID::MULTIPLICATION}, {"/", operatorID::DIVISION}, 
		{"^", operatorID::EXPONENTIATION}, {"sqrt", operatorID::SQRT}, {"lg", operatorID::LG}, {"ln", operatorID::LN} ,
		{"sin", operatorID::SINE}, {"cos", operatorID::COSINE}, 
		{"tan", operatorID::TANGENT}, {"cot", operatorID::COTANGENT},
		{"asin", operatorID::ARCSINE}, {"acos", operatorID::ARCCOSINE},
		{"atan", operatorID::ARCTANGENT}, {"acot", operatorID::ARCCOTANGENT},
		{"sec", operatorID::SECANT}, {"csc", operatorID::COSECANT},
		{"asec", operatorID::ARCSECANT}, {"acsc", operatorID::ARCCOSECANT},
		{"hsin", operatorID::HYPERBOLICSINE}, {"hcos", operatorID::HYPERBOLICCOSINE},
		{"htan", operatorID::HYPERBOLICTANGENT}, {"hcot", operatorID::HYPERBOLICCOTANGENT}
	};

	const int operatorMaxLength = 4;

	class Token {
	public:
		Token(Type type) { this->type = type; }
		Type getType() const { return type; }
		virtual std::string toString() { return std::string("#"); }
		virtual int getPriority() const { return 0; }
	private:
		Type type;
	};

	class LParenthesis : public Token {
	public: 
		LParenthesis() : Token(Type::L_PARENTHESIS) {}
		std::string toString() override { return std::string("("); }
	};

	class RParenthesis : public Token{
	public: 
		RParenthesis() : Token(Type::R_PARENTHESIS) {}
		std::string toString() override { return std::string(")"); }
	};

	class Number : public Token {
	public:
		Number(double value) : Token(Type::NUMBER) { this->value = value; }

		double getValue() const { return value; }
		std::string toString() override { return Converter::toString<double>(value); }

	private:
		double value;
	};

	class UOperator : public Token {
	public:
		UOperator() : Token(Type::U_OPERATOR) {}
		virtual Number calc(const Number& A) const { return Number(0); }
	};

	class BOperator : public Token {
	public:
		BOperator(int priority) : Token(Type::B_OPERATOR) { this->priority = priority; }
		virtual Number calc(const Number& A, const Number& B) const { return Number(0); }
		int getPriority() const override { return priority; }

	private:
		int priority;
	};

	class Plus : public BOperator {
	public:
		Plus() : BOperator(1) {}
		Number calc(const Number& A, const Number& B) const override
		{
			return Number(A.getValue() + B.getValue());
		}
		std::string toString() override { return std::string("+"); }
	};

	class Minus : public BOperator {
	public:
		Minus() : BOperator(1) {}
		Number calc(const Number& A, const Number& B) const override
		{
			return Number(A.getValue() - B.getValue());
		}
		std::string toString() override { return std::string("-"); }
	};

	class Multiplication : public BOperator {
	public:
		Multiplication() : BOperator(2) {}
		Number calc(const Number& A, const Number& B) const override
		{
			return Number(A.getValue() * B.getValue());
		}
		std::string toString() override { return std::string("*"); }
	};

	class Division : public BOperator {
	public:
		Division() : BOperator(2) {}
		Number calc(const Number& A, const Number& B) const override
		{
			return Number(A.getValue() / B.getValue());
		}
		std::string toString() override { return std::string("/"); }
	};

	class Exponentiation : public BOperator {
	public:
		Exponentiation() : BOperator(3) {}
		Number calc(const Number& A, const Number& B) const override
		{
			return Number(std::pow(A.getValue(), B.getValue()));
		}
		std::string toString() override { return std::string("^"); }
	};

	class UMinus : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(-1 * A.getValue());
		}
		std::string toString() override { return std::string("-"); }
	};

	class Logarithm10 : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::log10(A.getValue()));
		}
		std::string toString() override { return std::string("log"); }
	};

	class LogarithmE : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::log(A.getValue()));
		}
		std::string toString() override { return std::string("ln"); }
	};

	class Sqrt : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::sqrt(A.getValue()));
		}
		std::string toString() override { return std::string("sqrt"); }
	};

	class Sine : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::sin(A.getValue()));
		}
		std::string toString() override { return std::string("sin"); }
	};

	class Cosine : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::cos(A.getValue()));
		}
		std::string toString() override { return std::string("cos"); }
	};

	class Tangent : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::tan(A.getValue()));
		}
		std::string toString() override { return std::string("tan"); }
	};

	class Cotangent : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::cos(A.getValue()) / std::sin(A.getValue()));
		}
		std::string toString() override { return std::string("cot"); }
	};

	class Arcsine : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::asin(A.getValue()));
		}
		std::string toString() override { return std::string("asin"); }
	};
	
	class Arccosine : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::acos(A.getValue()));
		}
		std::string toString() override { return std::string("acos"); }
	};

	class Arctangent : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::atan(A.getValue()));
		}
		std::string toString() override { return std::string("atan"); }
	};

	class Arccotangent : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::atan(1. / A.getValue()));
		}
		std::string toString() override { return std::string("acot"); }
	};

	class Secant : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(1. / std::cos(A.getValue()));
		}
		std::string toString() override { return std::string("sec"); }
	};

	class Cosecant : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(1. / std::sin(A.getValue()));
		}
		std::string toString() override { return std::string("csc"); }
	};

	class Arcsecant : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::acos(1. / A.getValue()));
		}
		std::string toString() override { return std::string("asec"); }
	};

	class Arccosecant : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number(std::asin(1. / A.getValue()));
		}
		std::string toString() override { return std::string("acsc"); }
	};

	class HyperbolicSine : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number((std::exp(A.getValue()) - std::exp(-A.getValue())) / 2.);
		}
		std::string toString() override { return std::string("hsin"); }
	};

	class HyperbolicCosine : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number((std::exp(A.getValue()) + std::exp(-A.getValue())) / 2.);
		}
		std::string toString() override { return std::string("hcos"); }
	};

	class HyperbolicTangent : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number((std::exp(2. * A.getValue()) - 1) / (std::exp(2. * A.getValue()) + 1));
		}
		std::string toString() override { return std::string("htan"); }
	};

	class HyperbolicCotangent : public UOperator {
	public:
		Number calc(const Number& A) const override
		{
			return Number((std::exp(2. * A.getValue()) + 1) / (std::exp(2. * A.getValue()) - 1));
		}
		std::string toString() override { return std::string("hcot"); }
	};
}

