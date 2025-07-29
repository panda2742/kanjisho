#ifndef XML_ELEMENT_HPP
# define XML_ELEMENT_HPP

# include <string>

/**
 * Represent an element (or a sub element) into a XML file.
 */
class XMLElement
{
private:
	/**
	 * The name of the element.
	 */
	const std::string	_name;
	/**
	 * The value of the element WITHOUT ANY sub element.
	 */
	const std::string	_content;
	/**
	 * Every sub element of the element.
	 */
	XMLElement			*_subelements;
public:
	/**
	 * The default constructor.
	 */
	XMLElement(void) throw();
	/**
	 * The string constructor takes the name of the element.
	 * 
	 * @param name The name of the element.
	 */
	XMLElement(const std::string & name) throw();
	/**
	 * The copy assignment constructor.
	 * 
	 * @param other The other instance to copy.
	 */
	XMLElement(const XMLElement & other) throw();
	/**
	 * The default destructor.
	 */
	~XMLElement(void) throw();
};

#endif /* XML_ELEMENT_HPP */