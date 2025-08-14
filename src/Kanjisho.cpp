#include "Kanjisho.hpp"

#include "exceptions/AlreadyInitialized.hpp"
#include "exceptions/FileNotValid.hpp"
#include "exceptions/NotInitialized.hpp"
#include <fstream>
#include <iostream>

void	Kanjisho::LoadingSpinner(stop_token stoken)
{
	const vector<string>	frames = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
	const vector<string>	colors = {
		C_RED,
		C_ORANGE,
		C_YELLOW,
		C_GREEN,
		C_DARK_GREEN,
		C_CYAN,
		C_BLUE,
		C_DARK_BLUE,
		C_MAGENTA,
		C_PURPLE
	};

	uint8_t	i = 0;
	while (!stoken.stop_requested())
	{
		// cout << C_CLEARLN C_GREY "[ " << colors[i] << frames[i] << C_GREY " ] Loading..." C_RESET << flush;
		i = (i + 1) % frames.size();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

Kanjisho::Kanjisho(const string & xml_filename)
	: _has_been_initiated(false),
	_xml_filename(xml_filename) {}

void	Kanjisho::ReadXML(void)
{
	std::jthread	spinner(LoadingSpinner);

	cout << C_CLEARLN C_GREY "Opening XML." C_RESET << endl;

	if (_has_been_initiated)
		throw AlreadyInitialized();

	ifstream	xml(_xml_filename);

	if (!xml || xml.fail())
		throw FileNotValid();

	cout << C_CLEARLN C_GREY "Allocating database memory." C_RESET << endl;

	_db.reserve(15000);

	cout << C_CLEARLN C_GREY "Reading XML." C_RESET << endl;

	string			line;
	Kanji_t			new_kanji;

	while (getline(xml, line))
	{
		if (line.starts_with("<character>"))
			_ParseKanji(xml);
	}

	spinner.request_stop();
	_has_been_initiated = true;
	xml.close();

	cout << C_CLEARLN C_GREY "Successfully registered " << _db.size() << " kanji." C_RESET << endl;
}

void	Kanjisho::DisplayPrompt(void)
{
	if (!_has_been_initiated)
		throw NotInitialized();
	
	const vector<Kanji_t>	db = GetDatabase();
	for (size_t	i = 0; i < 4; i++)
		cout << db[i];
}

void	Kanjisho::_ParseKanji(ifstream & xml)
{
	Kanji_t	kanji{};
	string	line;

	while (getline(xml, line))
	{
		if (line.starts_with("<literal>"))
		{
			size_t start = line.find(">");
			size_t end   = line.find("</literal>");
			if (start != string::npos && end != string::npos && end > start)
				kanji.literal.assign(line.begin() + start + 1, line.begin() + end);
		}
		else if (line.starts_with("<stroke_count>"))
		{
			size_t start = line.find(">");
			size_t end   = line.find("</stroke_count>");
			if (start != string::npos && end != string::npos && end > start)
				kanji.stroke_count = atoi(string(line.begin() + start + 1, line.begin() + end).c_str());
		}
		else if (line.starts_with("<cp_value cp_type=\"ucs\">"))
		{
			size_t start = line.find(">");
			size_t end   = line.find("</cp_value>");
			if (start != string::npos && end != string::npos && end > start)
				kanji.unicode = static_cast<char32_t>(strtoul(string(line.begin() + start + 1, line.begin() + end).c_str(), nullptr, 16));
		}
		else if (line.starts_with("<grade>"))
		{
			size_t start = line.find(">");
			size_t end   = line.find("</grade>");
			if (start != string::npos && end != string::npos && end > start)
				kanji.grade = atoi(string(line.begin() + start + 1, line.begin() + end).c_str());
		}
		else if (line.starts_with("<jlpt>"))
		{
			size_t start = line.find(">");
			size_t end   = line.find("</jlpt>");
			if (start != string::npos && end != string::npos && end > start)
				kanji.former_jlpt = atoi(string(line.begin() + start + 1, line.begin() + end).c_str());
		}
		else if (line.starts_with("<freq>"))
		{
			size_t start = line.find(">");
			size_t end   = line.find("</freq>");
			if (start != string::npos && end != string::npos && end > start)
				kanji.freq = atoi(string(line.begin() + start + 1, line.begin() + end).c_str());
		}
		else if (line.starts_with("<reading r_type=\"ja_kun\">"))
		{
			size_t start = line.find(">");
			size_t end   = line.find("</reading>");
			if (start != string::npos && end != string::npos && end > start)
				kanji.kun_readings.emplace_back(line.begin() + start + 1, line.begin() + end);
		}
		else if (line.starts_with("<reading r_type=\"ja_on\">"))
		{
			size_t start = line.find(">");
			size_t end   = line.find("</reading>");
			if (start != string::npos && end != string::npos && end > start)
				kanji.on_readings.emplace_back(line.begin() + start + 1, line.begin() + end);
		}
		else if (line.starts_with("<nanori>"))
		{
			size_t start = line.find(">");
			size_t end   = line.find("</nanori>");
			if (start != string::npos && end != string::npos && end > start)
				kanji.name_readings.emplace_back(line.begin() + start + 1, line.begin() + end);
		}
		else if (line.starts_with("<meaning"))
		{
			// Récupération langue (si présente)
			string lang = "en"; // défaut anglais
			size_t attrPos = line.find("m_lang=");
			if (attrPos != string::npos)
			{
				size_t q1 = line.find("\"", attrPos);
				size_t q2 = line.find("\"", q1 + 1);
				if (q1 != string::npos && q2 != string::npos)
					lang.assign(line.begin() + q1 + 1, line.begin() + q2);
			}
			// Récupération texte
			size_t start = line.find(">");
			size_t end   = line.find("</meaning>");
			if (start != string::npos && end != string::npos && end > start)
				kanji.meanings[lang].emplace_back(line.begin() + start + 1, line.begin() + end);
		}
		else if (line.starts_with("</character>"))
		{
			_db.push_back(kanji);
			return;
		}
	}
}

const vector<Kanji_t> &	Kanjisho::GetDatabase(void) const
{
	return _db;
}
