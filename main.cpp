#include <python3.9/Python.h>
#include <iostream>
#include <iomanip>
#include <fstream> //used to read files
#include <limits> //used in cin.ignore located in catch statements
//#include <Windows.h>
#include <cmath>
#include <string>

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
    strcpy(procname, pName.c_str()); //removed std::

    Py_Initialize();
    //set path for Python library in this program
    PySys_SetPath(L".:/home/dylan/CLionProjects/projectThree:/usr/lib/python3.9");
    PyObject* my_module = PyImport_ImportModule("PythonCode");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
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
    strcpy(procname, proc.c_str()); //removed std::

    char *paramval = new char[param.length() + 1];
    strcpy(paramval, param.c_str()); //removed std::


    PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    //set path for Python library in this program
    PySys_SetPath(L".:/home/dylan/CLionProjects/projectThree:/usr/lib/python3.9");
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
    strcpy(procname, proc.c_str()); //removed std::

    PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    //set path for Python library in this program
    PySys_SetPath(L".:/home/dylan/CLionProjects/projectThree:/usr/lib/python3.9");
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

//print the menu that will be displayed to the user
void printMenu()
{
    cout << "1: List items purchased today\n";
    cout << "2: List number of times each item was purchased\n";
    cout << "3: display histogram\n";
    cout << "4: Exit\n";
    cout << "Enter your selection as a number 1, 2, 3, or 4.\n";
    cout << "Select: ";
}

//clear the terminal window
void clearWindow()
{

//if the user is on Windows use the "CLS" command to clear the terminal window
#ifdef _WIN32
    system("CLS");
#endif
//if the user is on Unix use the "clear" command to clear the terminal window
#ifdef __unix__
    system("clear"); //clear the console
#endif
}

//prompt the user for the item they would like to search for in the provided input file
string getSearchItem()
{
    //Variable declaration/initialization
    unsigned int i;
    string userInput;
    bool isString = true;

    //clear error flags and extract/discard characters from input sequence until a new line is reached
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    //loop until the user has entered a valid string
    while (true) {
       
        //try will throw an error if the string entered contains value that is not alpha or whitespace
        try {
            cout << "Please enter item name: "; 
            getline(cin, userInput);

            //check each index of the string for alpha value or whitespace
            for (i = 0; i < userInput.size(); ++i) {
                //if user input contains something that is not an alpha value or whitespace set isString to false
                if (!isalpha(userInput.at(i)) && !isspace(userInput.at(i))) {
                    isString = false;
                }
            }

            //if isString is false throw an error and return to the top of the loop
            if (isString == false) {
                throw("\nERROR: this field only accepts characters and spaces\n");

            }
            //if isString is true return the string entered by the user
            else {
                return userInput;
            }
        }

        //catch thrown error
        catch (const char* excpt) {
            cout << excpt; 
            isString = true; 
            
            //clear error flags and extract/discard characters from input sequence until a new line is reached
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
}

//print histogram from the frequency.dat file created by python
void printFile()
{

    //Variable declaration/initialization
    ifstream itemFS; 
    string itemInfo; 
    unsigned int numSold; 
    unsigned int numLocation; 

    itemFS.open("/home/dylan/CLionProjects/projectThree/frequency.dat");

    //if the file cannot be opened display
    if (!itemFS.is_open()) {
        cout << "Could not open file freqency.dat!" << endl;
    }

    //if the file can be opened extract and print data
    else {

        //display header for histogram
        cout << setw(30) << setfill('*') << '*' << endl;
        cout << setw(15) << left << setfill(' ') << "ITEM";
        cout << "AMOUNT SOLD" << endl;
        cout << setw(30) << setfill('-') << '-' << endl;

        getline(itemFS, itemInfo); //get the first line from the file and assign it to itemInfo

        //loop until data cannot be extracted from the file
        while (!itemFS.fail()) {

            //get the index of the last space in itemInfo string
            //the last space is between the item name and the number sold allowing us to extract the number
            numLocation = itemInfo.find_last_of(' ');
            //using numLocation create a substring from itemInfor extracting the number and convert it to an int
            numSold = stoi(itemInfo.substr(numLocation + 1, itemInfo.size() - 1));

            //create a substring containing just the item name and print it
            cout << setw(15) << setfill(' ') << left << itemInfo.substr(0, numLocation);
            cout << setw(numSold) << setfill('*') << '*' << endl; //print '*' equal to numSold

            getline(itemFS, itemInfo); //read the next line in the opened file
        }
        cout << endl;
        itemFS.close();
    }

}

void menuSelect()
{
    //Variable declaration/initialization
    int menuChoice = 1;

    //menu - loop while menu choice is equal to 1, 2, or 3
    while (menuChoice == 1 || menuChoice == 2 || menuChoice == 3) {

        printMenu();

        //this try/catch statement was added to prevent the user from entering a string
        //without it the program will return to the top of the loop and use the next character in the string
        //as input until the end of the string is reached. for example if 'Bob' is entered the program would loop 3 times
        try {
            cin >> menuChoice; 

            //if the user does not enter a number throw an error and return to the top of the loop
            if (cin.fail()){
                throw runtime_error("ERROR: Please enter a number between 1 and 4\n");
            }

                //if an int has been entered continue with loop
            else {
                switch (menuChoice) {
                    case 1: 
                        clearWindow(); 
                        CallProcedure("itemsSold"); //call itemsSold python function
                        break; 

                    case 2:
                        clearWindow();
                        //call getSearchItem and itemLookup python function passing the returned value from
                        //getSearchItem to python
                        callIntFunc("itemLookup",getSearchItem());
                        break; 

                    case 3:
                        clearWindow(); 
                        CallProcedure("saveFile"); //call saveFile python function
                        printFile(); 
                        break; 

                    case 4: ///exit the program
                        cout << "\nExiting the program.\n";
                        break; 

                    default: //if the user does not enter 1, 2, or 3 print an error and return to the top of the menu loop
                        clearWindow(); 
                        menuChoice = 1; //set menuChoice to 1 so we can return to the top of the menu loop
                        cout << "ERROR: Please enter a number between 1 and 4\n\n"; 
                        break; 
                }
            }
        }
            
        catch(runtime_error &excpt){
            clearWindow(); 
            cout << excpt.what() << endl; 
            cin.clear(); //clear cin of error flags
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); //extract and discard character from input sequence
            menuChoice = 1; //set menuChoice to 1 so we can return to the top of the menu loop
        }
    }
}

int main()
{
    menuSelect();

    return 0;
}