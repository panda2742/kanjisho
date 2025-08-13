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
}

void	Kanjisho::_ParseKanji(ifstream & xml)
{
	Kanji_t	kanji{};
	string	line;

	while (getline(xml, line))
	{
		if (line.starts_with("<literal>"))
		{
			size_t	start = line.find(">"),
					end   = line.find("</literal>");

			if (start != string::npos && end != string::npos && end > start)
				kanji.literal.assign(line.begin() + start + 1, line.begin() + end);
		}
		if (line.starts_with("</character>"))
		{
			_db.push_back(kanji);
			return ;
		}
	}
}
