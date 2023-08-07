#pragma once

#include <iostream>

class Warlock {
	private :
		std::string name;
		std::string title;
		Warlock();
		Warlock(const Warlock&rhs);
		Warlock &operator=(const Warlock&rhs);

	public :
		Warlock(std::string const &name, std::string const &title);
		~Warlock();
		void setTitle(std::string const &_title);
		std::string const &getName(void) const;
		std::string const &getTitle(void) const;

		void introduce(void) const;
};