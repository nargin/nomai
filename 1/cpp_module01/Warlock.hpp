#pragma once

#include <iostream>
#include "ATarget.hpp"
#include "ASpell.hpp"
#include <map>

class Warlock {
	private :
		Warlock();
		Warlock(Warlock const &other);
		Warlock &operator=(const Warlock& rhs);
		std::string name;
		std::string title;

		std::map <std::string, ASpell *> spellBook;

	public :
		Warlock(std::string const &name, std::string const &title);
		~Warlock();
		std::string const &getName(void) const;
		std::string const &getTitle(void) const;
		void setTitle(std::string const &title);

		void introduce(void) const;

		void learnSpell(ASpell *rhs);
		void forgetSpell(std::string spell);
		void launchSpell(std::string name, ATarget const &rhs);
};