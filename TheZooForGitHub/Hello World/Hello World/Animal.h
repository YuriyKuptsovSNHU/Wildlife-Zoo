#pragma once

#include <string>

using namespace std;

class Animal {
protected:
	// Using protected because we do not define the method bodies as they are abstract.
	// Child classes would not be able to access them if they are private.
	string name;
	int code;

public:
	// Abstract methods have no body, so pure virtual.
	virtual string getName() = 0;
	virtual void setName(string name) = 0;

	virtual int getCode() = 0;
	virtual void setCode(int code) = 0;

	virtual string classAsString() {
		return "Animal";
	}

	virtual string toString() {
		string asString;
		char codeAsString[256];

		sprintf(codeAsString, "%d", getCode());

		asString = "Instance of class " + classAsString() + ":\n"
			+ "  name=" + getName() + ":\n"
			+ "  code=" + codeAsString + ":\n";

		return asString;
	}
};

