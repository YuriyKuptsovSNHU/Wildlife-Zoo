#include "Oviparous.h"


Oviparous::Oviparous() {
	name = "";
	code = 0;
	numberOfEggs = 0;
}

Oviparous::Oviparous(string name, int code, int numberOfEggs) {
	this->name = name;
	this->code = code;
	this->numberOfEggs = numberOfEggs;
}

string Oviparous::getName() {
	return name;
}

void Oviparous::setName(string name) {
	this->name = name;
}

int Oviparous::getCode() {
	return this->code;
}

void Oviparous::setCode(int code) {
	this->code = code;
}

int Oviparous::getNumberOfEggs() {
	return this->numberOfEggs;
}

void Oviparous::setNumberOfEggs(int eggCount) {
	this->numberOfEggs = eggCount;
}
