#pragma once

#include <string>
#include <map>
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
		grade(1),
		former_jlpt(1),
		freq(1) {};
	~Kanji(void) {}
}	Kanji_t;
