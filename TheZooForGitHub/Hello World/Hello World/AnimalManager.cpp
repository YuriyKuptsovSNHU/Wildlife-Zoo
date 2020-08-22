#include "AnimalManager.h"

using namespace std;

AnimalManager::AnimalManager() {
	name = "Animal";
}

AnimalManager* AnimalManager::createManager() {
	AnimalManager* manager = new AnimalManager();
	AnimalManager* subManager = nullptr;

	subManager = manager->addType("Oviparous");

	subManager->addType("Crocodile");
	subManager->addType("Goose");
	subManager->addType("Pelican");

	subManager = manager->addType("Mammal");

	subManager->addType("Bat");
	subManager->addType("Sea Lion");
	subManager->addType("Whale");

	return manager;
}

AnimalManager* AnimalManager::createManager(string type) {
	if (type.compare("Oviparous") == 0) {
		return new OviparousManager();
	}
	else if (type.compare("Mammal") == 0) {
		return new MammalManager();
	}

	return nullptr;
}

AnimalManager* AnimalManager::addType(string typeName) {
	bool found = false;
	AnimalManager* manager = nullptr;

	for (vector<string>::iterator it = begin(types); it != end(types); ++it) {
		if (it->compare(typeName) == 0) {
			found = true;
			break;
		}
	}

	if (!found) {
		types.push_back(typeName);

		manager = createManager(typeName);

		if (manager != nullptr)
			subtypeManagers.push_back(manager);

		return manager;
	}

	return nullptr;
}

vector<string> AnimalManager::getTypes() {
	return types;
}

string AnimalManager::getTypesAsString() {
	string typesAsString;
	int typeCount = types.size();

	for (int i = 0; i < typeCount; i++) {
		if (i != 0) typesAsString = typesAsString +  ", ";

		typesAsString = typesAsString + types[i];
	}

	return typesAsString;
}

vector<string> AnimalManager::getSubTypes() {
	vector<string> subtypes;

	int subManagerCount = subtypeManagers.size();
	AnimalManager* subtypeManager;

	for (int i = 0; i < subManagerCount; i++) {
		subtypeManager = subtypeManagers[i];
		vector<string> subManagerTypes = subtypeManager->getTypes();
		int subTypeCount = subManagerTypes.size();

		for (int j = 0; j < subTypeCount; j++) {
			subtypes.push_back(subManagerTypes[j]);
		}
	}

	return subtypes;
}

string AnimalManager::getSubTypesAsString() {
	vector<string> subtypes = getSubTypes();
	string typesAsString;
	int typeCount = subtypes.size();

	for (int i = 0; i < typeCount; i++) {
		if (i != 0) typesAsString = typesAsString + ", ";

		typesAsString = typesAsString + subtypes[i];
	}

	return typesAsString;
}

vector<string> AnimalManager::getSubTypes(string typeName) {
	vector<string> subtypes;

	int subManagerCount = subtypeManagers.size();
	AnimalManager* subtypeManager;

	for (int i = 0; i < subManagerCount; i++) {
		subtypeManager = subtypeManagers[i];
		vector<string> subManagerTypes = subtypeManager->getTypes();
		int subTypeCount = subManagerTypes.size();

		if (subtypeManager->name.compare(typeName) == 0) {
			for (int j = 0; j < subTypeCount; j++) {
				subtypes.push_back(subManagerTypes[j]);
			}
		}
	}

	return subtypes;
}

string AnimalManager::getSubTypesAsString(string typeName) {
	vector<string> subtypes = getSubTypes(typeName);
	string typesAsString;
	int typeCount = subtypes.size();

	for (int i = 0; i < typeCount; i++) {
		if (i != 0) typesAsString = typesAsString + ", ";

		typesAsString = typesAsString + subtypes[i];
	}

	return typesAsString;
}

Animal* AnimalManager::createSubtypeInstance(string subtypeName) {
	Animal* instance = nullptr;
	int subManagerCount = subtypeManagers.size();

	fprintf(stderr, "\nAnimalManager::createSubtypeInstance(%s):\n", subtypeName.c_str());

	for (int i = 0; i < subManagerCount; i++) {
		AnimalManager* subtypeManager = subtypeManagers[i];
		vector<string> subtypes = subtypeManager->getTypes();
		int subtypesCount = subtypes.size();

		fprintf(stderr, "\n  Looking for match in %s", subtypeManager->name.c_str());

		for (int j = 0; j < subtypesCount; j++) {
			if (subtypes[j].compare(subtypeName) == 0) {
				fprintf(stderr, "\nManager %s matches subtype %s.\n", subtypeManager->name.c_str(), subtypeName.c_str());
				return subtypeManager->createTypeInstance(subtypeName);
			}
		}

		fprintf(stderr, "\nNo manager matches subtype %s.\n", subtypeName.c_str());
	}

	return nullptr;
}

Animal* AnimalManager::createSubtypeInstance(string subtypeName, string name, int code, int eggsOrNursing) {
	Animal* instance = nullptr;
	int subManagerCount = subtypeManagers.size();

	fprintf(stderr, "\nAnimalManager::createSubtypeInstance(%s):\n", subtypeName.c_str());

	for (int i = 0; i < subManagerCount; i++) {
		AnimalManager* subtypeManager = subtypeManagers[i];
		vector<string> subtypes = subtypeManager->getTypes();
		int subtypesCount = subtypes.size();

		fprintf(stderr, "\n  Looking for match in %s", subtypeManager->name.c_str());

		for (int j = 0; j < subtypesCount; j++) {
			if (subtypes[j].compare(subtypeName) == 0) {
				fprintf(stderr, "\nManager %s matches subtype %s.\n", subtypeManager->name.c_str(), subtypeName.c_str());
				return subtypeManager->createTypeInstance(subtypeName, name, code, eggsOrNursing);
			}
		}

		fprintf(stderr, "\nNo manager matches subtype %s.\n", subtypeName.c_str());
	}

	return nullptr;
}

Animal* AnimalManager::createTypeInstance(string typeName) {
	if (typeName.compare("Oviparous") == 0) {
		return new Oviparous();
	}
	if (typeName.compare("Mammal") == 0) {
		return new Mammal();
	}
}

Animal* AnimalManager::createTypeInstance(string typeName, string name, int code, int eggsOrNursing) {
	if (typeName.compare("Oviparous") == 0) {
		return new Oviparous(name, code, eggsOrNursing);
	}
	if (typeName.compare("Mammal") == 0) {
		return new Mammal(name, code, eggsOrNursing);
	}
}

OviparousManager::OviparousManager() {
	name = "Oviparous";
}

AnimalManager* OviparousManager::addType(string typeName) {
	bool found = false;

	for (vector<string>::iterator it = begin(types); it != end(types); ++it) {
		if (it->compare(typeName) == 0) {
			found = true;
			break;
		}
	}

	if (!found) {
		types.push_back(typeName);
	}

	return nullptr;
}

Animal* OviparousManager::createTypeInstance(string typeName) {
	if (typeName.compare("Crocodile") == 0) {
		return new Crocodile();
	}
	if (typeName.compare("Goose") == 0) {
		return new Goose();
	}
	if (typeName.compare("Pelican") == 0) {
		return new Pelican();
	}
}

Animal* OviparousManager::createTypeInstance(string typeName, string name, int code, int eggsOrNursing) {
	if (typeName.compare("Crocodile") == 0) {
		return new Crocodile(name, code, eggsOrNursing);
	}
	if (typeName.compare("Goose") == 0) {
		return new Goose(name, code, eggsOrNursing);
	}
	if (typeName.compare("Pelican") == 0) {
		return new Pelican(name, code, eggsOrNursing);
	}
}

MammalManager::MammalManager() {
	name = "Mammal";
}

Animal* MammalManager::createTypeInstance(string typeName) {
	if (typeName.compare("Bat") == 0) {
		return new Bat();
	}
	if (typeName.compare("Sea Lion") == 0) {
		return new SeaLion();
	}
	if (typeName.compare("Whale") == 0) {
		return new Whale();
	}
}

Animal* MammalManager::createTypeInstance(string typeName, string name, int code, int eggsOrNursing) {
	if (typeName.compare("Bat") == 0) {
		return new Bat(name, code, eggsOrNursing);
	}
	if (typeName.compare("Sea Lion") == 0) {
		return new SeaLion(name, code, eggsOrNursing);
	}
	if (typeName.compare("Whale") == 0) {
		return new Whale(name, code, eggsOrNursing);
	}
}

AnimalManager* MammalManager::addType(string typeName) {
	bool found = false;

	for (vector<string>::iterator it = begin(types); it != end(types); ++it) {
		if (it->compare(typeName) == 0) {
			found = true;
			break;
		}
	}

	if (!found) {
		types.push_back(typeName);
	}

	return nullptr;
}

AnimalManager* AnimalManager::Factory = AnimalManager::createManager();
