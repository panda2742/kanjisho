#pragma once

#include "AException.hpp"

class NotInitialized : public AException
{
	public:
		NotInitialized(void) : AException("The database must be initialized before displaying the prompt.") {}
	
		const char	*type(void) const noexcept override { return "NotInitialized"; }
};
