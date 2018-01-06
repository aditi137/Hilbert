#include "capi.h"


PyObject* some_func(PyObject* self, PyObject* args)
{
	__int64 input_value;
	if (!PyArg_ParseTuple(args, "L", &input_value)) {
		goto error;
	}
	return PyLong_FromLongLong(input_value + 1);
error:
	return 0;
}


static PyMethodDef HilbertMethods[] = {
	{ "add_one", PyCFunction(some_func), METH_VARARGS /* flag telling the interpreter the calling convention to be used for the C function */,
	NULL },
	{ NULL, NULL, 0, NULL }		/* Sentinel */
};


static struct PyModuleDef hilbertmodule = {
	PyModuleDef_HEAD_INIT,
	"Hilbert",	/* name of module */
	NULL,		/* module documentation, may be NULL */
	-1,			/* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
	HilbertMethods	/* array of exported functions */
};


PyMODINIT_FUNC PyInit_Hilbert(void)
{
	return PyModule_Create(&hilbertmodule);
}