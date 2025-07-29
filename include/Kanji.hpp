#ifndef KANJI_HPP
# define KANJI_HPP

# include <string>

/**
 * Represent a Kanji with all its attribute.
 */
typedef struct Kanji
{
	/**
	 * The character itself in UTF8 coding.
	 */
	const std::string	literal;
	/**
	 * The cp_value contains the codepoint of the character in a particular
	 * standard. The standard will be identified in the cp_type attribute.
	 */
	const uint8_t	grade;
	const uint8_t	stroke_count;

}	Kanji_t;

#endif