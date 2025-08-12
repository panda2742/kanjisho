#pragma once

#include <stdexcept>
#include <string>

using namespace	std;

class AException : public runtime_error
{
	public:
		virtual const char	*type() const noexcept = 0;

	protected:
		explicit AException(const string & err_message) : runtime_error(err_message) {}
};
