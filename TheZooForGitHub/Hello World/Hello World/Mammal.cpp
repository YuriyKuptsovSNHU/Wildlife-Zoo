#include "Mammal.h"


Mammal::Mammal() {
	this->name = "";
	this->code = 0;
	this->nurse = 0;
}

Mammal::Mammal(string name, int code, int nurse) {
	this->name = name;
	this->code = code;
	this->nurse = nurse;
}

string Mammal::getName() {
	return name;
}

void Mammal::setName(string name) {
	this->name = name;
}

int Mammal::getCode() {
	return this->code;
}

void Mammal::setCode(int code) {
	this->code = code;
}

int Mammal::getNurse() {
	return this->nurse;
}

void Mammal::setNurse(int nurse) {
	this->nurse = nurse;
}
