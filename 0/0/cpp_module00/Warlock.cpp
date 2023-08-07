#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title) {
	this->name = name;
	this->title = title;
	std::cout << this->name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() { std::cout << name << ": My job here is done!" << std::endl; }

void Warlock::setTitle(std::string const &_title) {
	this->title = _title;
}

std::string const &Warlock::getName(void) const { return this->name; }
std::string const &Warlock::getTitle(void) const { return this->title; }

void Warlock::introduce(void) const {
	std::cout << getName() << ": I am " << getName() << ", " << getTitle() << "!" << std::endl;
}