//Anton Yarakhtin
#pragma once
#include <vector>
#include <memory>
#include "Tokens.hpp"


namespace Tokens
{

	class Sequence {
	public:
		Sequence() {}
		Sequence(Sequence& a) = delete;
		Sequence(Sequence&& a) { data = std::move(a.data); }

		auto begin() { return data.begin(); }
		auto end() { return data.end(); }
		auto begin() const { return data.begin(); }
		auto end() const { return data.end(); }
		auto cbegin() const { return data.cbegin(); }
		auto cend() const { return data.cend(); }

		auto& at(size_t pos) { return data.at(pos); }
		auto& at(size_t pos) const { return data.at(pos); }
		auto& front() { return data.front(); }
		auto& front() const { return data.front(); }
		auto& back() { return data.back(); }
		auto& back() const { return data.back(); }

		bool empty() const { return data.empty(); }
		auto size() const { return data.size(); }

		void pop_back() { data.pop_back(); }
		void push_back(std::unique_ptr<Token>&& ptr) { data.push_back(std::move(ptr)); }

		void pushNumber(double value) { data.push_back(std::make_unique<Number>(value)); }
		void pushLParenthesis() { data.push_back(std::make_unique<LParenthesis>()); }
		void pushRParenthesis() { data.push_back(std::make_unique<RParenthesis>()); }
		void pushOperator(operatorID id);

		Sequence& operator=(Sequence& a) = delete;
		Sequence& operator=(Sequence&& a)
		{
			if (&a != this) { data = std::move(a.data); }
			return *this;
		}

	private:
		std::vector<std::unique_ptr<Token>> data;
	};


	void Sequence::pushOperator(operatorID id) {
		switch (id)
		{
		case operatorID::MINUS:
			if (data.empty() || data.back()->getType() == Type::B_OPERATOR) data.push_back(std::make_unique<UMinus>());
			else data.push_back(std::make_unique<Minus>());
			break;
		case operatorID::PLUS: data.push_back(std::make_unique<Plus>()); break;
		case operatorID::MULTIPLICATION: data.push_back(std::make_unique<Multiplication>()); break;
		case operatorID::DIVISION: data.push_back(std::make_unique<Division>()); break;
		case operatorID::EXPONENTIATION: data.push_back(std::make_unique<Exponentiation>()); break;
		case operatorID::LG: data.push_back(std::make_unique<Logarithm10>()); break;
		case operatorID::LN: data.push_back(std::make_unique<LogarithmE>()); break;
		case operatorID::SQRT: data.push_back(std::make_unique<Sqrt>()); break;

		case operatorID::SINE: data.push_back(std::make_unique<Sine>()); break;
		case operatorID::COSINE: data.push_back(std::make_unique<Cosine>()); break;
		case operatorID::TANGENT: data.push_back(std::make_unique<Tangent>()); break;
		case operatorID::COTANGENT: data.push_back(std::make_unique<Cotangent>()); break;

		case operatorID::ARCSINE: data.push_back(std::make_unique<Arcsine>()); break;
		case operatorID::ARCCOSINE: data.push_back(std::make_unique<Arccosine>()); break;
		case operatorID::ARCTANGENT: data.push_back(std::make_unique<Arctangent>()); break;
		case operatorID::ARCCOTANGENT: data.push_back(std::make_unique<Arccotangent>()); break;

		case operatorID::SECANT: data.push_back(std::make_unique<Secant>()); break;
		case operatorID::COSECANT: data.push_back(std::make_unique<Cosecant>()); break;
		case operatorID::ARCSECANT: data.push_back(std::make_unique<Arcsecant>()); break;
		case operatorID::ARCCOSECANT: data.push_back(std::make_unique<Arccosecant>()); break;

		case operatorID::HYPERBOLICSINE: data.push_back(std::make_unique<HyperbolicSine>()); break;
		case operatorID::HYPERBOLICCOSINE: data.push_back(std::make_unique<HyperbolicCosine>()); break;
		case operatorID::HYPERBOLICTANGENT: data.push_back(std::make_unique<HyperbolicTangent>()); break;
		case operatorID::HYPERBOLICCOTANGENT: data.push_back(std::make_unique<HyperbolicCotangent>()); break;

		default: break;
		}
	}
}


