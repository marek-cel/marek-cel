#include <boost/python.hpp>
#include <iostream>

int main()
{
    try
    {
        Py_Initialize(); // Initialize Python interpreter

        // Import the script and call the function
        // boost::python::object main_module = boost::python::import("__main__");
        // boost::python::object main_namespace = main_module.attr("__dict__");

        // Execute the script (it defines greet())
        boost::python::exec_file("../scripts/hello.py");//, main_namespace);

        // Call the greet() function from the script
        //boost::python::object greet_func = main_namespace["greet"];
        //greet_func();

        Py_Finalize(); // Finalize Python interpreter
    }
    catch (boost::python::error_already_set const&)
    {
        PyErr_Print(); // Print the Python error to stderr
    }

    return 0;
}