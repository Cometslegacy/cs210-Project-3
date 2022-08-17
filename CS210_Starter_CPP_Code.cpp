#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>	
#include <fstream>
#include <iomanip>
//#include <stdlib.h>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char *procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();	
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen: 
		You sent me: Test
Return:
	100 is returned to the C++	
*/
int callIntFunc(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void displayMenu() {
	system("CLS");
	cout << "===========Display Menu===========" << endl;
	cout << "1. List all items purchased today" << endl;
	cout << "2. How many times was a specific item purchased" << endl;
	cout << "3. Histogram" << endl;
	cout << "4. Exit" << endl;
	cout << "Please input a number: 1, 2, 3, or 4." << endl;
}

string histogram(int x) {
	string stars;
	for (int i = 0; i < x; i++) {
		stars += "*";
	}
	return stars;
}

void main()
{

	int userInput = 0;
	string userItemChoice;
	string frequencyString;
	string myText;
	string objectType;
	int objectAmount = 0;

	while (true) {
		do { // Menu Loop
			displayMenu();
			cin >> userInput;
		} while (userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4);

		switch (userInput) {
		case(1): { //display Items purchased on given day
			CallProcedure("displayItems");
			break;
		}
		case(2): {//How many times was specific item purchased
			cout << "Which item would you like to know details about?" << endl;
			cin >> userItemChoice;
			cout << userItemChoice << ": " << callIntFunc("displaySpecificItem", userItemChoice);
			break;
		}
		case(3): {//Histogram
			CallProcedure("createFrequencyFile");

			ifstream frequencyFile("frequency.dat");
			if (!frequencyFile.is_open()) { //check that file opened properly
				cout << "could not open file - frequency.dat" << endl;
			}

			while (frequencyFile >> objectType >> objectAmount) {
				cout << objectType << ": " << histogram(objectAmount) << endl;
			}

			if (frequencyFile.is_open()) { //check if file is open and close it if true
				frequencyFile.close();
			}
			break;
		}
		case(4): { //exit
			return;
		}
		}
		cout << endl << "------Press any button to continue------";
		system("pause > 0");
	}



}
//CallProcedure("printsomething");
//cout << callIntFunc("PrintMe","House") << endl;
//cout << callIntFunc("SquareValue", 2);