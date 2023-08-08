#pragma once

#include <iostream>

class ATarget;

class ASpell {
	private :
		std::string name;
		std::string effects;

	public :
		ASpell();
		ASpell(std::string const &name, std::string const &effects);
		ASpell(ASpell const &other);
		ASpell &operator=(ASpell const &rhs);
		virtual ~ASpell();

		std::string const &getName(void) const;
		std::string const &getEffects(void) const;

		void launch(ATarget const &rhs) const;

		virtual ASpell *clone() const = 0;
};

#include "ATarget.hpp"