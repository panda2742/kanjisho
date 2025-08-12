#pragma once

#include "AException.hpp"

class AlreadyInitialized : public AException
{
	public:
		AlreadyInitialized(void) : AException("The program has already been initialized.") {}
	
		const char	*type(void) const noexcept override { return "AlreadyInitialized"; }
};
