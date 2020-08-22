#pragma once
#include "Mammal.h"

class SeaLion : public Mammal {
public:
	SeaLion() : Mammal() {
	};
	SeaLion(string name, int code, int nurse) : Mammal(name, code, nurse) {
	};

	virtual string classAsString() override {
		return "SeaLion";
	}
};

