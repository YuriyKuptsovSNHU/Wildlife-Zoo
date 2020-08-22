#pragma once
#include "Mammal.h"

class Bat : public Mammal {
public:
	Bat() : Mammal() {
	};
	Bat(string name, int code, int nurse) : Mammal(name, code, nurse) {
	};

	virtual string classAsString() override {
		return "Bat";
	}
};

