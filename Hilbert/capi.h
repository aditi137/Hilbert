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