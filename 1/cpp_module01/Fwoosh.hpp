#pragma once

#include "ASpell.hpp"

class Fwoosh : class ASpell {
	public :
		Fwoosh();
		~Fwoosh();

		virtual *ASpell clone() const;
};