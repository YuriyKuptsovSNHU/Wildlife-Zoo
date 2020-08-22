#pragma once
#include "Oviparous.h"
class Goose : public Oviparous {
public:
	Goose() : Oviparous() {
	};
	Goose(string name, int code, int numberOfEggs) : Oviparous(name, code, numberOfEggs) {
	};

	virtual string classAsString() override {
		return "Goose";
	}
};

