#include "Kanjisho.hpp"

#include <iostream>

int	main(void)
{
	Kanjisho	kanjisho("data/kanjidic2.xml");

	try
	{
		kanjisho.ReadXML();
		kanjisho.DisplayPrompt();
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
