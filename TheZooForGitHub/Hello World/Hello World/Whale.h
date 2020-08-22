#pragma once
#include "Mammal.h"
class Whale : public Mammal {
public:
	Whale() : Mammal() {
	};
	Whale(string name, int code, int nurse) : Mammal(name, code, nurse) {
	};

	virtual string classAsString() override {
		return "Whale";
	}
};

