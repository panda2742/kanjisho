#pragma once

#include "AException.hpp"

class FileNotValid : public AException
{
	public:
		FileNotValid(void) : AException("File is not a valid file.") {}
	
		const char	*type(void) const noexcept override { return "FileNotValid"; }
};
