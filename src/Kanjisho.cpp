#include "Kanjisho.hpp"

#include "exceptions/AlreadyInitialized.hpp"
#include "exceptions/FileNotValid.hpp"
#include "exceptions/NotInitialized.hpp"
#include <fstream>
#include <iostream>

Kanjisho::Kanjisho(const string & xml_filename)
	: __has_been_initiated(false),
	__xml_filename(xml_filename) {}

void	Kanjisho::ReadXML(void)
{
	if (__has_been_initiated)
		throw AlreadyInitialized();

	ifstream	xml(__xml_filename);

	if (xml.fail())
		throw FileNotValid();

	__has_been_initiated = true;
	xml.close();
}

void	Kanjisho::DisplayPrompt(void)
{
	if (!__has_been_initiated)
		throw NotInitialized();
}
