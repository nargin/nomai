#pragma once

#include <iostream>

class ASpell;

class ATarget {
	private :
		std::string type;

	public :
		ATarget();
		ATarget(std::string const &type);
		ATarget(ATarget const &other);
		virtual ~ATarget();
		ATarget &operator=(ATarget const &rhs);

		std::string const &getType(void) const;

		void getHitBySpell(ASpell const &rhs) const;

		virtual ATarget *clone() const = 0;
};

#include "ASpell.hpp"