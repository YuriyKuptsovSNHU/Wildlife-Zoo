#pragma once

#include <string>
#include "Animal.h"

using namespace std;

class Oviparous : public Animal {
private:
	int numberOfEggs;

public:
	Oviparous();
	Oviparous(string name, int code, int numberOfEggs);

	string getName() override;
	void setName(string name) override;

	int getCode() override;
	void setCode(int code) override;

	int getNumberOfEggs();
	void setNumberOfEggs(int eggCount);

	virtual string classAsString() override  {
		return "Oviparous";
	}

	virtual string toString() override {
		string asString = Animal::toString();
		char eggsAsString[256];

		sprintf(eggsAsString, "%d", getNumberOfEggs());

		asString = asString + "  name=" + getName() + ":\n"
			+ "  numberOfEggs=" + eggsAsString + ":\n";

		return asString;
	}
};

