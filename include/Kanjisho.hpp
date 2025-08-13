#pragma once

#include "Kanji.hpp"
#include <string>
#include <thread>
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

		static void	LoadingSpinner(stop_token);
	private:
		Kanjisho(void) = default;

		bool			_has_been_initiated;
		const string	_xml_filename;
		vector<Kanji_t>	_db;

		unordered_map<u8string, const Kanji_t *>					_index_literal;
		unordered_map<u8string, vector<const Kanji_t *>>			_index_kun;
		unordered_map<u8string, vector<const Kanji_t *>>			_index_on;
		unordered_map<u8string, vector<const Kanji_t *>>			_index_nanori;
		unordered_map<string, vector<const Kanji_t *>>				_index_meanings;
		unordered_map<char32_t, const Kanji_t *>					_index_unicode;
		unordered_map<unsigned char, vector<const Kanji_t *>>		_index_grade;
		unordered_map<unsigned char, vector<const Kanji_t *>>		_index_jlpt;
		unordered_map<unsigned short int, vector<const Kanji_t *>>	_index_freq;

		void	_ParseKanji(ifstream & xml);
};
