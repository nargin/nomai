#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title){
	this->name = name;
	this->title = title;
	std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() {
	std::cout << getName() << ": My job here is done!" << std::endl;
	std::map<std::string, ASpell *>::iterator it = this->spellBook.begin();
	std::map<std::string, ASpell *>::iterator ite = this->spellBook.end();
	while (it != ite)
		delete it++->second;
	this->spellBook.clear();
}

std::string const &Warlock::getName(void) const { return this->name;}
std::string const &Warlock::getTitle(void) const { return this->title;}
void Warlock::setTitle(std::string const &title) { this->title = title;}

void Warlock::introduce(void) const {
	std::cout << getName() << ": I am " << getName() << ", " << getTitle() << "!" << std::endl;
}

void	Warlock::learnSpell(ASpell *rhs) {
	if (rhs)
		this->spellBook.insert(std::pair<std::string, ASpell *>(rhs->getName(), rhs->clone()));
}

void Warlock::forgetSpell(std::string spell) {
	std::map<std::string, ASpell *>::iterator it = this->spellBook.find(spell);

	if (it != this->spellBook.end())
		delete it->second;
	this->spellBook.erase(spell);
}

void Warlock::launchSpell(std::string name, ATarget const &rhs) {
	ASpell *tolearn = this->spellBook[name];
	if (tolearn)
		tolearn->launch(rhs);
}