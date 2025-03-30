#include <iostream>

#include <Python.h> // Python C API

void runPythonScript(const char* script_name, const char* name)
{
    Py_Initialize(); // Initialize Python interpreter

    Py_Initialize(); // Initialize Python interpreter

    // Create a dictionary to store variables
    PyObject* global = PyDict_New();

    // Set variables
    PyDict_SetItemString(global, "name", PyUnicode_FromString(name));

    // Execute script with variables
    FILE* fp = fopen(script_name, "r");
    if (fp) {
        PyRun_File(fp, script_name, Py_file_input, global, global);
        fclose(fp);
    } else {
        std::cerr << "Error: Could not open " << script_name << std::endl;
    }

    Py_Finalize(); // Finalize Python interpreter
}

int main()
{
    std::cout << "Hello, Python!" << std::endl;

    runPythonScript("../scripts/hello.py", "World");

    return 0;
}
