#pragma once
#include "Oviparous.h"
class Crocodile : public Oviparous {
public:
	Crocodile() : Oviparous() {
	};
	Crocodile(string name, int code, int numberOfEggs) : Oviparous(name, code, numberOfEggs) {
	};

	virtual string classAsString() override {
		return "Crocodile";
	}
};
