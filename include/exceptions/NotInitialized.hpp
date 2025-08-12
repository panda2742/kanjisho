#pragma once

#include "AException.hpp"

class NotInitialized : public AException
{
	public:
		NotInitialized(void) : AException("The program must be initialized before displaying the prompt.") {}
	
		const char	*type(void) const noexcept override { return "NotInitialized"; }
};
