#ifndef KANJI_HPP
#define KANJI_HPP

#include <string>
#include <map>
#include <vector>

using namespace	std;

/**
 * Represent a Kanji with all its attribute.
 */
typedef struct Kanji
{
	u8string					literal;
	vector<u8string>			kun_readings;
	vector<u8string>			on_readings;
	vector<u8string>			name_readings;
	map<string, vector<string>>	meanings;
	unsigned char				stroke_count;
	u8string					unicode;
	unsigned char				grade;
	unsigned char				former_jlpt;
	unsigned short int			freq;
}	Kanji_t;

#endif