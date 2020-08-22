#include <iostream>
#include <jni.h>
#include "tchar.h"
#include "WildlifeZooMenu.h"

using namespace std;

bool loadJVM(JavaVM** jvm, JNIEnv** env, jclass* cls2) {
	//================== prepare loading of Java VM ============================
	JavaVMInitArgs vm_args; // Initialization arguments
	JavaVMOption* options = new JavaVMOption[1]; // JVM invocation options
	options[0].optionString = (char*)"-Djava.class.path=F:/Downloads/Project3/Project3/WildLifeZooFiles/WildLifeZooFiles/TheZoo"; // where to find java .class
	vm_args.version = JNI_VERSION_1_6; // minimum Java version
	vm_args.nOptions = 1; // number of options
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false; // invalid options make the JVM init fail
	//=============== load and initialize Java VM and JNI interface =============
	jint rc = JNI_CreateJavaVM(jvm, (void**)env, &vm_args); // YES !!
	delete options; // we then no longer need the initialisation options.
	if (rc != JNI_OK) {
		// TO DO: error processing...
		cin.get();
		exit(EXIT_FAILURE);
	}
	//=============== Display JVM version =======================================
	cout << "JVM load succeeded: Version ";
	jint ver = (*env)->GetVersion();
	cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;
	*cls2 = (*env)->FindClass("ZooFileWriter"); // try to find the class

	if (*cls2 == nullptr) {
		cerr << "ERROR: class not found !";
		return false;
	}

	return true;
}

bool createZooFile(JNIEnv** env, jclass* cls2) {
	jmethodID mid = (*env)->GetStaticMethodID(*cls2, "createZooFile", "()V"); // find method
	if (mid == nullptr) {
		cerr << "ERROR: method not found !" << endl;
		return false;
	}
	else {
		(*env)->CallStaticVoidMethod(*cls2, mid); // call method
		cout << endl;
		return true;
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	JavaVM* jvm; // Pointer to the JVM (Java Virtual Machine)
	JNIEnv* env; // Pointer to native interface
	jclass cls2; // try to find the class

	if (! loadJVM(&jvm, &env, &cls2))
		return 1;
	else
		cout << "Class MyTest found" << endl;
	
	WildlifeZooMenu menu;
	int userChoice;
	char trackNumber[7];
	char name[16];
	char type[16];
	char subtype[16];
	int eggs;
	int nurse;

	userChoice = menu.promptUserSelection(trackNumber, name, type, subtype, &eggs, &nurse);

	while (!menu.quit(userChoice)) {
		userChoice = menu.promptUserSelection(trackNumber, name, type, subtype, &eggs, &nurse);

		switch (userChoice) {
		case 1: // Load Animal Data
			cout << "\nLoading animal data!\n";

			if (! createZooFile(&env, &cls2)) {
				cerr << "\nFailed to load animal data!\n";
			}
			break;
		}
	}

	/*
	{ // if class found, continue
		cout << "Class MyTest found" << endl;
		jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V"); // find method
		if (mid == nullptr)
			cerr << "ERROR: method not found !" << endl;
		else {
			env->CallStaticVoidMethod(cls2, mid); // call method
			cout << endl;
		}
	}
	*/

	jvm->DestroyJavaVM();

	return 0;
}