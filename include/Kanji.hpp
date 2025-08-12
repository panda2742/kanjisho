#ifndef KANJI_HPP
# define KANJI_HPP

# include <string>

/**
 * Represent a Kanji with all its attribute.
 */
typedef struct Kanji
{
	std::string	literal;
	struct s_codepoint
	{
		std::unord<>;
	};
	radical;
	misc;
	dic_number;
	query_code;
	reading_meaning;
}	Kanji_t;

#endif