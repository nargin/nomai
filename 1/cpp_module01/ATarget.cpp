#include "ATarget.hpp"

ATarget::ATarget() {}
ATarget::ATarget(std::string const &type) { this->type = type;}
ATarget::ATarget(ATarget const &other) {*this = other;}
ATarget::~ATarget() {}

ATarget &ATarget::operator=(ATarget const &rhs) { this->type = other.type; return *this;}

void ATarget::getHitBySpell(ASpell const &rhs) const {
	std::cout << this->type << " has been " << rhs.getEffects() << "!" << std::endl;
}

std::string const &ATarget::getType(void) const {return this->type;}