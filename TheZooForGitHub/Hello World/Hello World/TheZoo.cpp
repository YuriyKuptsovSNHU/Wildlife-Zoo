#include <iostream>
#include <jni.h>
#include <vector>
#include <stdio.h>
#include "tchar.h"
#include "WildlifeZooMenu.h"
#include "ZooDatum.h"

using namespace std;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=F:/Downloads/Project3/Project3/WildLifeZooFiles/WildLifeZooFiles/TheZoo";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

void AddAnimal(WildlifeZooMenu *menu, vector<ZooDatum>* zooData)
{
     /*
            TODO: Write proper code to add an animal to your vector (or array)
     */

    char trackNumber[8];
    char name[16];
    char type[16];
    char subtype[16];
    int eggs;
    int nurse;
    char userResponse;
    char* ptr2;

    menu->prompToAddRecord(trackNumber, name, type, subtype, &eggs, &nurse);

    ZooDatum newDatum(trackNumber, name, type, subtype, eggs, nurse);

    cout << "\nYou entered:\n";

    newDatum.print(stdout);

    cout << "\nSave or Cancel? (S/C) ";
    cin >> userResponse;
    userResponse = tolower(userResponse);

    while ((userResponse != 's') && (userResponse != 'S') && (userResponse != 'c') && (userResponse != 'C')) {
        cout << "\n\"" << userResponse << "\" is not a valid response. Please enter 'S' or 'C': ";
        cin >> userResponse;
        userResponse = tolower(userResponse);
    }

    switch (userResponse) {
    case 'c': cout << "\nCanceled...";
        return;
    case 's': cout << "\nAdded to records in memory. Use \"Save Data\" menu option to save permanently.\n";
        zooData->push_back(newDatum);
        return;
    }

    return;
}

void DisplayAnimals (vector<ZooDatum>* zooData) {
    int count = zooData->size();

    for (ZooDatum datum : *zooData) {
        cout << "\n";
        datum.print(stdout);
        cout << "\n";
    }

    cout << "\n" << count << " records displayed.\n";
}

bool validTrackNumber(string tracknumber) {
    int size = tracknumber.size();

    return ((size >= 0) && (size <= 7));
}

void promptForTrackNumber(char *trackNumber) {
    char fieldName[256];
    char workingBuffer[256];
    int len, i;
    char* ptr;

    strcpy(fieldName, "Track Number");
    WildlifeZooMenu::promptForDigitString(fieldName, workingBuffer, 7);

    if ((len = strlen(workingBuffer)) < 7) {
        ptr = trackNumber;
        for (i = 0; i < 7 - len; i++) *ptr++ = '0';
        strncpy(ptr, workingBuffer, len + 1);
    }
    else {
        strcpy(trackNumber, workingBuffer);
    }
}

void RemoveAnimal(vector<ZooDatum> &zooData)
{
     /*
            TODO: Write proper code to remove an animal from your vector (or array. Remmber to re-allocate proper size if using array)
     */

    string userEnteredTracknumber;
    char trackNumber[256];
    bool recordExists = false;
    char userChoice;
    int index;

    do {
        promptForTrackNumber(trackNumber);
        userEnteredTracknumber = trackNumber;

        while (!validTrackNumber(userEnteredTracknumber)) {
            cout << "\nYou entered \"" << userEnteredTracknumber << "\", which is not a valid TrackID.";
            cout << "\nA valid TrackID has between 0 and 7 characters.\n";

            promptForTrackNumber(trackNumber);
            userEnteredTracknumber = trackNumber;
        }

        int indexOfRecordToDelete = ZooDatum::queryZooData(userEnteredTracknumber, zooData);

        if (indexOfRecordToDelete >= 0) {
            ZooDatum dat = zooData[indexOfRecordToDelete];

            dat.print(stdout);

            cout << "\n\nDelete? (Y/N)";
            cin >> userChoice;
            userChoice = tolower(userChoice);

            while ((userChoice != 'y') && (userChoice != 'n')) {
                cout << "\"" << userChoice << "\" is not a valid response.\n";
                cout << "\nDelete? (Y/N)";
                cin >> userChoice;
                userChoice = tolower(userChoice);
            }

            switch (userChoice) {
            case 'y':
                index = 0;
                zooData.erase(zooData.begin() + indexOfRecordToDelete);
                cout << "\n\nRecord deleted.\n";
                return;
            case 'n':
                return;
            }
        }
        else {
            cout << "\nNo record with TrackID \"" + userEnteredTracknumber + "\" exists.\n";
            cout << "\nEnter another? (Y/N)";
            cin >> userChoice;
            userChoice = tolower(userChoice);

            while ((userChoice != 'y') && (userChoice != 'n')) {
                cout << "\"" << userChoice << "\" is not a valid response.\n";
                cout << "\nEnter another? (Y/N)";
                cin >> userChoice;
                userChoice = tolower(userChoice);
            }
        }

    }  while (!recordExists);
}

vector<ZooDatum> LoadDataFromFile()
{
     /*
            TODO: Write proper code to load data from input file (generated using JNI) into vector/array.
     */

    FILE* dataInput = fopen("zoodata.txt", "r");

    printf("\nLoading animal data from zoodata.txt\n");

    if (dataInput == 0) {
        cerr << "\nFailed to open file: zoodata.txt!\n";
        vector<ZooDatum> emptyVector;
        return emptyVector;
    }

    return ZooDatum::readZooData(dataInput);
}

void SaveDataToFile(vector<ZooDatum> data)
{
     /*
            TODO: Write proper code to store vector/array to file.
     */

    FILE* dataOutput = fopen("zoodata.txt", "w");
    ZooDatum::saveZooData(dataOutput, data);
    fclose(dataOutput);
}

void DisplayMenu(vector<ZooDatum> &zooData)
{
     /*
            TODO: write proper code to display menu to user to select from
     */
    WildlifeZooMenu menu;
    int userChoice;
    char trackNumber[8];
    char name[16];
    char type[16];
    char subtype[16];
    int eggs;
    int nurse;

    userChoice = menu.promptUserSelection(trackNumber, name, type, subtype, &eggs, &nurse);

    while (!menu.quit(userChoice)) {
        printf("\nUser Choice: %d\n", userChoice);

        switch (userChoice) {
        case 1: // Load Animal Data
            cout << "\nLoading animal data!\n";

            zooData = LoadDataFromFile();

            printf("\nRead in %d records.\n", zooData.size());

            ZooDatum::printZooData(stdout, zooData);

            break;

        case 2:	// Generate Data
            cout << "\nGenerating data!\n";

            GenerateData();

            break;
        case 3:	// Display Animal Data
            cout << "\nDisplaying animal data!\n";

            DisplayAnimals(&zooData);

            break;
        case 4:	// Add Record
            cout << "\nAdding record!\n";

            AddAnimal(&menu, &zooData);

            break;
        case 5:	// Delete Record
            cout << "\nDeleting record!\n";

            RemoveAnimal(zooData);

            break;
        case 6:	// Save Animal Data
            cout << "\nSaving data!\n";

            SaveDataToFile(zooData);

            cout << "\nSaved data to file.\n";

            break;
        case 7:	// Quit
            cout << "\nGoodbye!\n";

            break;
        }

        userChoice = menu.promptUserSelection(trackNumber, name, type, subtype, &eggs, &nurse);
    }
}



int _tmain(int argc, _TCHAR* argv[]) {
    vector<ZooDatum> zooData;

    DisplayMenu(zooData);

	return 1;
}
