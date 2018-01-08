#include "Python.h"
//#include "hilbert.h"
#include <iostream>

typedef unsigned long coord_t;


static PyObject* some_func(PyObject* self, PyObject* args)
{
	__int64 input_value;
	if (!PyArg_ParseTuple(args, "L", &input_value))
		return 0;
	return PyLong_FromLongLong(input_value + 1);
}

/*
static PyObject* TransposetoLine(PyObject* self, PyObject* args)
{
	coord_t* Line, *X;	// Hilbert integer, transpose
	int b, n;			// # bits, dimension
	PyArg_ParseTuple(args, "(I*)(I*)ii", &X, &b, &n);	//TODO: Find the string config that works "Array Array ii" because Array size is variable

	coord_t M = 1 << (b - 1), p, q;
	int i, j = 0;
	p = M;

	for (i = 0; i < n; i++) {
		Line[i] = 0;
		for (q = M; q > 0; q >>= 1) {
			if (X[j] & p)
				Line[i] |= q;
			if (++j == n) {
				j = 0;
				p >>= 1;
			}
		}
	}
}


static PyObject* TransposetoAxes(PyObject* self, PyObject* args)
{
	coord_t* X;		// position
	int b, n, i;	// # bits, dimension, counter
	PyArg_ParseTuple(args, "(III)ii", &X, &b, &n);

	coord_t M = 2 << (b - 1), p, q, t;

	// Gray decode by H ^ (H/2)
	t = X[n - 1] >> 1;
	for (i = n - 1; i > 0; i--)
		X[i] ^= X[i - 1];
	X[0] ^= t;

	// Undo excess work
	for (q = 2; q != M; q <<= 1) {
		p = q - 1;
		for (i = n - 1; i >= 0; i--) {
			// invert
			if (X[i] & q)
				X[0] ^= p;
			// exchange
			else {
				t = (X[0] ^ X[i]) & p;
				X[0] ^= t;
				X[i] ^= t;
			}
		}
	}
}
*/

static PyObject* AxestoTranspose(PyObject* self, PyObject* args)
{
	coord_t* X = new coord_t;	// position
	int b, n, i;				// # bits, dimension, counter
	PyObject *pX, *pItem;

	if (!PyArg_ParseTuple(args, "iiO!", &b, &n, &PyList_Type, &pX)) {
		PyErr_SetString(PyExc_TypeError, "Parameters must be an int, an int, and a list.");
		return NULL;
	}
	//PyArg_ParseTuple(args, "ii", &b, &n);
	std::cout << "b = " << b << ", n = " << n << std::endl;
	std::cout << "Check 1\nX = [";
	for (i = 0; i < PyList_Size(pX); i++) {
		pItem = PyList_GetItem(pX, i);
		if (!PyLong_Check(pItem)) {
			PyErr_SetString(PyExc_TypeError, "List items must be integers.");
			return NULL;
		}
		X[i] = PyLong_AsUnsignedLong(pItem);
		std::cout << X[i] << " ";
	}
	std::cout << "]\nCheck 2.\nX new = [";
	
	coord_t M = 1 << (b - 1), p, q, t;
	// Inverse undo
	for (q = M; q > 1; q >>= 1) {
		p = q - 1;
		for (i = 0; i < n; i++) {
			// invert
			if (X[i] & q)
				X[0] ^= p;
			// exchange
			else {
				t = (X[0] ^ X[i]) & p;
				X[0] ^= t;
				X[i] ^= t;
			}
		}
	}
	// Gray encode (inverse of decode)
	for (i = 1; i < n; i++)
		X[i] ^= X[i - 1];
	t = 0;
	for (q = M; q > 1; q >>= 1)
	if (X[n - 1] & q)
		t ^= q - 1;
	for (i = 0; i < n; i++)
		X[i] ^= t;
	
	for (i = 0; i < PyList_Size(pX); i++) {
		std::cout << X[i] << ' ';
	}
	std::cout << "]\nCheck 3.\n";

	return Py_BuildValue("[I,I,I]", X[0], X[1], X[2]);
}

/*
PyObject* AxestoLine(
	coord_t* Line,	// linear serial # 
	coord_t* Axes,	// multidimensional geometrical axes
	int b,			// # bits
	int n)			// dimension
{
	coord_t store[1024];	// avoid overwriting Axes
	int i;

	// trivial case
	if (n <= 1)
		*Line = *Axes;
	// surely the usual case
	else if (n <= 1024) {
		for (i = 0; i < n; i++)
			store[i] = Axes[i];
		AxestoTranspose(store, b, n);
		TransposetoLine(Line, store, b, n);
	}
	// must do in place at greater cost
	else {
		AxestoTranspose(Axes, b, n);
		TransposetoLine(Line, Axes, b, n);
		TransposetoAxes(Axes, b, n);
	}
	return (PyObject*)Line;
}
*/

PyMODINIT_FUNC PyInit_Hilbert(void)
{
	static PyMethodDef HilbertMethods[] = {
		{ "add_one", some_func, METH_VARARGS /* flag telling the interpreter the calling convention to be used for the C function */, NULL },
		{"r2t", AxestoTranspose, METH_VARARGS, NULL},
		{ NULL, NULL, 0, NULL }		/* Sentinel */
	};

	static struct PyModuleDef hilbertmodule = {
		PyModuleDef_HEAD_INIT,
		"Hilbert",	/* name of module */
		NULL,		/* module documentation, may be NULL */
		-1,			/* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
		HilbertMethods	/* array of exported functions */
	};

	PyObject *m = PyModule_Create(&hilbertmodule);
	if (m == NULL)
		return NULL;
	return m;
}


void main()
{

}
//TODO: add exception handling for each function