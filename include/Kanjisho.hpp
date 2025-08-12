#pragma once

#include "Kanji.hpp"
#include <string>
#include <unordered_map>

using namespace	std;

class Kanjisho
{
	public:
		Kanjisho(const string & xml_filename);
		~Kanjisho(void) = default;
		Kanjisho(const Kanjisho & other) = default;
		Kanjisho &	operator=(const Kanjisho & other) = default;
		Kanjisho(Kanjisho && other) noexcept = default;
		Kanjisho &	operator=(Kanjisho && other) noexcept = default;
	
		void	ReadXML(void);
		void	DisplayPrompt(void);
	private:
		Kanjisho(void) = default;

		bool			__has_been_initiated;
		const string	__xml_filename;
		vector<Kanji_t>	__db;

		unordered_map<u8string, const Kanji_t *>					__index_literal;
		unordered_map<u8string, vector<const Kanji_t *>>			__index_kun;
		unordered_map<u8string, vector<const Kanji_t *>>			__index_on;
		unordered_map<u8string, vector<const Kanji_t *>>			__index_nanori;
		unordered_map<string, vector<const Kanji_t *>>				__index_meanings;
		unordered_map<char32_t, const Kanji_t *>					__index_unicode;
		unordered_map<unsigned char, vector<const Kanji_t *>>		__index_grade;
		unordered_map<unsigned char, vector<const Kanji_t *>>		__index_jlpt;
		unordered_map<unsigned short int, vector<const Kanji_t *>>	__index_freq;
};
