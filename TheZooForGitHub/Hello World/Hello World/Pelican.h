#pragma once
#include "Oviparous.h"
class Pelican : public Oviparous {
public:
	Pelican() : Oviparous() {
	};
	Pelican(string name, int code, int numberOfEggs) : Oviparous(name, code, numberOfEggs) {
	};

	virtual string classAsString() override {
		return "Pelican";
	}
};

