#include "ASpell.hpp"

ASpell::ASpell() {}
ASpell::ASpell(std::string const &name, std::string const &effects) {
	this->name = name; this->effects = effects; }
ASpell::ASpell(ASpell const &other) { *this = other; }
ASpell &ASpell operator=(ASpell const &rhs) {
	this->name = rhs.name;
	this->effects = rhs.effects;
	*this = rhs;
}
ASpell::~ASpell() {}

std::string const &Warlock::getName(void) const { return this->name; }
std::string const &Warlock::getEffects(void) const { return this->effects; }

void ASpell::launch(ATarget const &rhs) const{
	rhs.getHitBySpell(*this);
}