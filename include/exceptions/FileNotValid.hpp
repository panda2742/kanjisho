#pragma once

#include "AException.hpp"

class FileNotValid : public AException
{
	public:
		FileNotValid(void) : AException("XML file is not a valid file.") {}
	
		const char	*type(void) const noexcept override { return "FileNotValid"; }
};
