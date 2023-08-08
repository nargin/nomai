#pragma once

#include "ATarget.hpp"

class Dummy : class ATarget {
	public :
		Dummy();
		~Dummy();

		virtual ATarget *clone() const;
};