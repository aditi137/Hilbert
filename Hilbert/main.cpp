#include "capi.h"


void main(int argc, char *argv[])
{
	/* Add a built-in module, before Py_Initialize */
	PyImport_AppendInittab("hilbert", PyInit_spam);

	/* Initialize the Python interpreter. Required. */
	Py_Initialize();

	/* Optionally import the module; alternatively, import can be deferred until the embedded script imports it. */
	PyImport_ImportModule("hilbert");

	Py_Finalize();
}