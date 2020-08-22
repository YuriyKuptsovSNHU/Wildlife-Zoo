#pragma once

#include <string>
#include <vector>
#include "Animal.h";
#include "Oviparous.h"
#include "Mammal.h"
#include "Bat.h"
#include "Crocodile.h"
#include "Goose.h"
#include "Pelican.h"
#include "SeaLion.h"
#include "Whale.h"

using namespace std;

class AnimalManager;

class AnimalManager {
protected:
	string name;
	vector<string> types;
	vector<AnimalManager*> subtypeManagers;

public:
	AnimalManager();

	static AnimalManager* createManager();

	static AnimalManager* Factory;

protected:

	static AnimalManager* createManager(string type);

	virtual AnimalManager* addType(string typeName);

public:

	virtual vector<string> getTypes();

	virtual string getTypesAsString();

	virtual vector<string> getSubTypes();

	virtual string getSubTypesAsString();

	virtual vector<string> getSubTypes(string typeName);

	virtual string getSubTypesAsString(string typeName);

	virtual Animal* createSubtypeInstance(string subtypeName);

	virtual Animal* createSubtypeInstance(string subtypeName, string name, int code, int eggsOrNursing);

	virtual Animal* createTypeInstance(string typeName);

	virtual Animal* createTypeInstance(string typeName, string name, int code, int eggsOrNursing);
};

class OviparousManager : public AnimalManager {
public:
	OviparousManager();

protected:

	AnimalManager* addType(string typeName) override;

public:

	Animal* createTypeInstance(string typeName) override;

	Animal* createTypeInstance(string typeName, string name, int code, int eggsOrNursing) override;
};

class MammalManager : public AnimalManager {
public:
	MammalManager();

protected:

	AnimalManager* addType(string typeName) override;

public:

	Animal* createTypeInstance(string typeName) override;

	Animal* createTypeInstance(string typeName, string name, int code, int eggsOrNursing) override;
};

