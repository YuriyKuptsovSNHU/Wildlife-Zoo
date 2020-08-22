#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include "animalManager.h"

using namespace std;

class WildlifeZooMenu {
private:
	int optionsCount;
	vector<string> options;

	static int readUntilEndOfLine(char* buffer, int max) {
		char* bp = buffer;
		char c;
		int count = 0;

		while ((c = getc(stdin)) == '\n');

		while (c != '\n') {
			if (count == max) {
				*bp = '\0';

				return count;
			}

			*bp++ = c;
			c = getc(stdin);
		}

		*bp = '\0';

		return count;
	}

	static bool isStringOfDigits(char* str) {
		int len = strlen(str);

		for (int i = 0; i < len; i++)
			if (!isdigit(str[i])) return false;

		return true;
	}

	int promptForString(char* name, char* output, int size) {
		char inputBuffer[1024];

		cout << "\nEnter a " << name << " " << "(maxium of " << size << " characters): ";
		readUntilEndOfLine(inputBuffer, 1024);
		// fscanf(stdin, "%s%*[^\n]", &inputBuffer);

		int len = strlen(inputBuffer);

		while (len > size) {
			cout << "\nThe " << name << " you entered \"" << inputBuffer << "\" is too long. The limit is " << size << " characters.\n";
			cout << "\nEnter a " << name << "(maxium of " << size << " characters): ";
			readUntilEndOfLine(inputBuffer, 1024);
			// fscanf(stdin, "%s%*[^\n]", &inputBuffer);
			len = strlen(inputBuffer);
		}

		strcpy(output, inputBuffer);

		return 1;
	}

	int promptForAnimalType(char* name, char* output, int size) {
		string validTypes = AnimalManager::Factory->getTypesAsString();

		char inputBuffer[1024];
		int i;
		bool validType = false;

		cout << "\nEnter a " << name << ". The type must be one of the following types- " << validTypes;
		cout << ": \n";

		readUntilEndOfLine(inputBuffer, 1024);
		validType = validTypes.find(inputBuffer) != string::npos;

		while (!validType) {
			cout << "\nThe " << name << " you entered \"" << inputBuffer << "\" is either not one of the listed types or is too long. The limit is " << size << " characters.\n";
			cout << "\nEnter a " << name << ". The type must be one of the following types- " << validTypes;

			cout << ": \n";

			readUntilEndOfLine(inputBuffer, 1024);
			validType = validTypes.find(inputBuffer) != string::npos;
		}

		strcpy(output, inputBuffer);

		return 1;
	}

	int promptForAnimalSubType(char* type, char* name, char* output, int size) {
		string validSubTypes = AnimalManager::Factory->getSubTypesAsString(type);

		char inputBuffer[1024];
		int i;
		bool validType = false;

		cout << "\nEnter a " << name << ". The type must be one of the following sub-types- " << validSubTypes;
		cout << ": \n";

		readUntilEndOfLine(inputBuffer, 1024);
		validType = validSubTypes.find(inputBuffer) != string::npos;

		while (!validType) {
			cout << "\nThe " << name << " you entered \"" << inputBuffer << "\" is either not one of the listed sub-types or is too long. The limit is " << size << " characters.\n";
			cout << "\nEnter a " << name << ". The type must be one of the following sub-types- " << validSubTypes;

			cout << ": \n";

			readUntilEndOfLine(inputBuffer, 1024);
			validType = validSubTypes.find(inputBuffer) != string::npos;
		}

		strcpy(output, inputBuffer);

		return 1;
	}

	int promptForInt(char* name) {
		int value;

		// Add exception handling in case someone enters a non-number!

		cout << "\nEnter a number of " << name << " " << "(integer value 0 or greater): ";
		cin >> value;

		while (value < 0) {
			cout << "\nThe value for " << name << " you entered \"" << value << "\" is not a non-negative integer.\n";
			cout << "\nEnter a number of " << name << "(integer value 0 or greater): ";
			cin >> value;
		}

		cout << "\n" << name << " = " << value << "\n";

		return value;
	}

	int promptForBool(char* name) {
		int value;
		char charValue;

		cout << "\nIs she " << name << " " << "(Y/N): ";
		cin >> charValue;

		charValue = tolower(charValue);

		while ((charValue != 'y') && (charValue != 'n')) {
			cout << "\nThe value for " << name << " that you entered \"" << charValue << "\" is neither 'Y' nor 'N'.\n";
			cout << "\nIs she " << name << " " << "(Y/N): ";
			cin >> charValue;
			charValue = tolower(charValue);
		}

		cout << "\n" << name << " = " << charValue << "\n";

		return (charValue == 'y') ? 1 : 0;
	}

public:

	static int promptForDigitString(char* name, char* output, int size) {
		char inputBuffer[1024];

		cout << "\nEnter a " << name << " " << "(maxium of " << size << " digits): ";
		readUntilEndOfLine(inputBuffer, 1024);
		// fscanf(stdin, "%s%*[^\n]", &inputBuffer);

		int len = strlen(inputBuffer);

		while ((len > size) || (!isStringOfDigits(inputBuffer))) {
			cout << "\nThe " << name << " you entered \"" << inputBuffer << "\" is either too long or contains non-digit characters.\n";
			cout << "\nEnter a " << name << "(maxium of " << size << " digits): ";
			readUntilEndOfLine(inputBuffer, 1024);
			// fscanf(stdin, "%s%*[^\n]", &inputBuffer);
			len = strlen(inputBuffer);
		}

		strcpy(output, inputBuffer);

		return 1;
	}

	WildlifeZooMenu() {
		optionsCount = 7;
		options.push_back("Load Animal Data");
		options.push_back("Generate Data");
		options.push_back("Display Animal Data");
		options.push_back("Add Record");
		options.push_back("Delete Record");
		options.push_back("Save Animal Data");
		options.push_back("Quit");
	}

	void printMenuOptions() {
		int optionNumber = 0;

		cout << "\nPlease select an option from the following menu.\n\n";

		for (std::string str : options) {
			cout << "  " << str << " (" << ++optionNumber << "):\n";
		}
	}

	int readMenuChoice() {
		string userInput;
		int userChoice;

		cin >> userInput;
		userChoice = atoi(userInput.c_str());

		while ((userChoice < 1) || (userChoice > optionsCount)) {
			cout << userInput << " is not a valid menu option. Please enter a value from 1 to " << optionsCount << "\n";
			cin >> userInput;
			userChoice = atoi(userInput.c_str());
		}

		return userChoice;
	}

	int prompToAddRecord(char* trackNumber, char* name, char* type, char* subtype, int* eggs, int* nurse) {
		char fieldName[256];
		char workingBuffer[256];
		int len, i;
		char* ptr;

		strcpy(fieldName, "Track Number");
		promptForDigitString(fieldName, workingBuffer, 7);

		if ((len = strlen(workingBuffer)) < 7) {
			ptr = trackNumber;
			for (i = 0; i < 7 - len; i++) *ptr++ = '0';
			strncpy(ptr, workingBuffer, len + 1);
		}
		else {
			strcpy(trackNumber, workingBuffer);
		}

		cout << "\n" << fieldName << " = " << trackNumber << "\n";

		strcpy(fieldName, "Name");
		promptForString(fieldName, name, 15);

		cout << "\n" << fieldName << " = " << name << "\n";

		strcpy(fieldName, "Type");
		promptForAnimalType(fieldName, type, 15);

		cout << "\n" << fieldName << " = " << type << "\n";

		strcpy(fieldName, "Sub-type");
		promptForAnimalSubType(type, fieldName, subtype, 15);

		cout << "\n" << fieldName << " = " << subtype << "\n";

		if (strcmp(type, "Oviparous") == 0) {
			strcpy(fieldName, "Eggs");
			*eggs = promptForInt(fieldName);

			cout << "\n" << fieldName << " = " << *eggs << "\n";
		}
		else {
			*eggs = 0;
		}

		if (strcmp(type, "Mammal") == 0) {
			strcpy(fieldName, "Nursing?");
			*nurse = promptForBool(fieldName);

			cout << "\n" << fieldName << " = " << *nurse << "\n";
		}
		else {
			*nurse = 0;
		}

		return 1;
	}

	int promptUserSelection(char* trackNumber, char* name, char* type, char* subtype, int* eggs, int* nurse) {
		printMenuOptions();
		int userChoice = readMenuChoice();

		cout << "\nYou chose to " + options[userChoice - 1] + "\n\n";

		return userChoice;
	}

	bool quit(int userChoice) {
		return userChoice == 7;
	}
};

