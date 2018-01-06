#include <Python.h>
#include <iostream>

static PyObject *HilbertError;


static PyObject* hilbert_AxistoLine(PyObject *self, PyObject *args)
{
	const char *command;
	int sts;

	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;
	sts = system(command);
	return PyLong_FromLong(sts);
}



static PyMethodDef HilbertMethods[] = {
	{"r2l", hilbert_AxistoLine, METH_VARARGS,"map real coordinates to 1D."},
	{NULL, NULL, 0, NULL}		/* Sentinel */
};
// move to  main


static struct PyModuleDef hilbertmodule = {
	PyModuleDef_HEAD_INIT,
	"hilbert",	/* name of module */
	NULL,		/* module documentation, may be NULL */
	-1,			/* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
			  HilbertMethods
};


PyMODINIT_FUNC PyInit_spam(void)
{
	PyObject *m;
	m = PyModule_Create(&hilbertmodule);
	if (m == NULL)
		return NULL;

	HilbertError = PyErr_NewException("hilbert.error", NULL, NULL);
	Py_INCREF(HilbertError);
	PyModule_AddObject(m, "error", HilbertError);
	return m;
}


void main(int argc, char *argv[])
{
	wchar_t *program = Py_DecodeLocale(argv[0], NULL);
	if (program == NULL) {
		std::cerr << "Fatal error: cannot decode argv[0]\n";
		exit(1);
	}

	/* Add a built-in module, before Py_Initialize */
	PyImport_AppendInittab("hilbert", PyInit_spam);

	/* Pass argv[0] to the Python interpreter */
	Py_SetProgramName(program);

	/* Initialize the Python interpreter. Required. */
	Py_Initialize();

	/* Optionally import the module; alternatively, import can be deferred until the embedded script imports it. */
	PyImport_ImportModule("spam");

	PyMem_RawFree(program);
}