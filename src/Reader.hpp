//Anton Yarakhtin
#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Tokens.hpp"
#include "Sequence.hpp"
#include "Converter.hpp"

using namespace Tokens;

class Reader
{
public:
	Reader() = delete;

	static Sequence Read(std::string s) {

		Sequence seq;

		for (size_t i = 0; i < s.length(); i++)
		{
			if (isDigit(s[i]) || s[i] == '.' || s[i] == ',') exploreNumber(s, seq, i);
			else if (s[i] == '(') seq.pushLParenthesis();
			else if (s[i] == ')') seq.pushRParenthesis();
			else if (s[i] != ' ') exploreOperator(s, seq, i);
		}

		return seq;
	}

private:

	static void exploreNumber(std::string& s, Sequence& seq, size_t& i) {
		std::string temp;
		bool point = false;

		if (s[i] == '.' || s[i] == ',') { point = true; temp += "."; }
		else temp += s[i];

		while (i + 1 < s.length() && (isDigit(s[i + 1]) || s[i + 1] == '.' || s[i + 1] == ','))
		{
			if (s[i + 1] == '.' || s[i + 1] == ',')
				if (point) throw "incorrect input"; else { point = true; temp += "."; }
			else temp += s[i + 1];
			i++;
		}

		if (temp == ".") throw "incorrect input";
		seq.pushNumber(Converter::fromString<double>(temp));
	}

	static void exploreOperator(std::string& s, Sequence& seq, size_t& i) {
		std::string temp;
		bool detected = false;

		do {
			temp += s[i];
			i++;
			detected = detectOperator(temp);
		} while (
			i < s.length()
			&& s[i] != ' ' && s[i] != '.' && s[i] != ',' && s[i] != '(' && s[i] != ')'
			&& !isDigit(s[i])
			&& !detected
			&& temp.length() <= operatorMaxLength
			);
		i--;

		if (detected) seq.pushOperator(supportedOperators.at(temp));
		else throw "incorrect input";
	}

	static bool detectOperator(std::string s) {
		return supportedOperators.find(s) != supportedOperators.end();
	}

	static bool isDigit(int C) { if (C >= -1 && C <= 255) return isdigit(C); return false; }
};

