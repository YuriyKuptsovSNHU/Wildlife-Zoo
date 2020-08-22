#pragma once
#include "Animal.h"
class Mammal : public Animal {
private:
	int nurse;
public:
	Mammal();
	Mammal(string name, int code, int nurse);

	string getName() override;
	void setName(string name) override;

	int getCode() override;
	void setCode(int code) override;

	int getNurse();
	void setNurse(int nurse);

	virtual string classAsString() override {
		return "Mammal";
	}

	virtual string toString() override {
		string asString = Animal::toString();
		char nursing[256];

		sprintf(nursing, "%s", (getNurse()) ? "true" : "false");

		asString = asString + "  name=" + getName() + ":\n"
			+ "  nurse=" + nursing + ":\n";

		return asString;
	}
};

