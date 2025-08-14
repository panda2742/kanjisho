#pragma once

#include "defines.hpp"
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <ostream>
#include <string>
#include <vector>

using namespace	std;

typedef struct Kanji
{
	u8string						literal;
	vector<u8string>				kun_readings;
	vector<u8string>				on_readings;
	vector<u8string>				name_readings;
	map<string, vector<u8string>>	meanings;
	unsigned char					stroke_count;
	char32_t						unicode;
	unsigned char					grade;
	unsigned char					former_jlpt;
	unsigned short int				freq;

	Kanji(void)
		: literal(),
		kun_readings(),
		on_readings(),
		name_readings(),
		meanings(),
		stroke_count(0),
		unicode(),
		grade(0),
		former_jlpt(0),
		freq(0) {};
	~Kanji(void) {}

	friend ostream &	operator<<(ostream & os, const struct Kanji & k)
	{

		os << "\n\t" C_BOLD << std::string(k.literal.begin(), k.literal.end()) << C_RESET "\n";

		os << "Kun\t";
		if (!k.kun_readings.empty())
		{
			for (size_t i = 0; i < k.kun_readings.size(); ++i)
			{
				os << C_ORANGE << std::string(k.kun_readings[i].begin(), k.kun_readings[i].end()) << C_RESET;
				if (i + 1 < k.kun_readings.size()) os << ", ";
			}
		}
		else os << "(empty)";
    	os << "\n";

		os << "On\t";
		if (!k.on_readings.empty())
		{
			for (size_t i = 0; i < k.on_readings.size(); ++i)
			{
				os << C_DARK_BLUE << std::string(k.on_readings[i].begin(), k.on_readings[i].end()) << C_RESET;
				if (i + 1 < k.on_readings.size()) os << ", ";
			}
		}
		else os << "(empty)";
    	os << "\n";

		os << "Defs:";
		for (auto &[lang, defs] : k.meanings)
		{
			os << "\t" C_GREY << lang << ": " C_RESET;
			for (size_t i = 0; i < defs.size(); ++i)
			{
				os << std::string(defs[i].begin(), defs[i].end());
				if (i + 1 < defs.size()) os << ", ";
			}
			os << "\n";
		}
		os << "\n";

		vector<string>	tag_content;

		if (k.former_jlpt)
			tag_content.push_back("JLPT: " + to_string(k.former_jlpt));
		if (k.grade)
			tag_content.push_back("Grade: " + to_string(k.grade));
		if (k.freq)
			tag_content.push_back("Freq: #" + to_string(k.freq));

		if (tag_content.size())
		{
			os << C_BG_GRAY C_YELLOW "\t[";
			for (size_t	i = 0; i < tag_content.size(); i++)
			{
				os << tag_content[i];
				if (i + 1 < tag_content.size()) os << ", ";
			}
			os << "]\t" C_RESET "\n";
		}
		
		os << "\n";

		return os;
	}
}	Kanji_t;

