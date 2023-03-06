#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include <stdio.h>
#include "matrixmultiplicationimp.c"

typedef enum MethodType {bruteForceMethod = 1, divideMethod = 2, strassenMethod = 3} METHODTYPE;

static PyObject *matrixmultiplicationmethod(PyObject *self, PyObject *args, METHODTYPE methodType) {
    PyArrayObject *inputNdArrayX = NULL;
    PyArrayObject *inputNdArrayY = NULL;

    if (!PyArg_ParseTuple(args, "O!O!", &PyArray_Type, &inputNdArrayX, &PyArray_Type, &inputNdArrayY)) {
        return NULL;
    }
    if (PyArray_NDIM(inputNdArrayX) != 2 || PyArray_NDIM(inputNdArrayY) != 2) {
        PyErr_SetString(PyExc_TypeError, "Both matrices must be of 2 dimensions");
        return NULL;
    }

    long *XDims = PyArray_DIMS(inputNdArrayX);
    long *YDims = PyArray_DIMS(inputNdArrayY);

    if (XDims[1] != YDims[0]) {
        PyErr_SetString(PyExc_TypeError, "Dimensions unmatched");
        return NULL;
    }
    if (XDims[0] != XDims[1] || YDims[0] != YDims[1]) {
        PyErr_SetString(PyExc_TypeError, "Both matrices must be square");
        return NULL;
    }
    // +check the size of matrix which must be 2^n
    
    long outputDim[] = {XDims[0], YDims[1]};
    PyObject *outputNdArray = PyArray_Zeros(2, outputDim, PyArray_DescrFromType(NPY_DOUBLE), 0);

    switch(methodType) {
        case bruteForceMethod:
            bruteForceImplementation(PyArray_DATA((void *)outputNdArray), PyArray_DATA(inputNdArrayX), PyArray_DATA(inputNdArrayY), XDims, YDims);
            break;
        case divideMethod:
            divideImplementation(PyArray_DATA((void *)outputNdArray), PyArray_DATA(inputNdArrayX), PyArray_DATA(inputNdArrayY), XDims[0]);
            break;
        case strassenMethod:
            strassenImplementation(PyArray_DATA((void *)outputNdArray), PyArray_DATA(inputNdArrayX), PyArray_DATA(inputNdArrayY), XDims[0]);
            break;
    }

    return outputNdArray;
}

static PyObject *bruteforcemethod(PyObject *self, PyObject *args) { matrixmultiplicationmethod(self, args, bruteForceMethod); }
static PyObject *dividemethod(PyObject *self, PyObject *args) { matrixmultiplicationmethod(self, args, divideMethod); }
static PyObject *strassenmethod(PyObject *self, PyObject *args) { matrixmultiplicationmethod(self, args, strassenMethod); }

static PyMethodDef matrixmultiplicationmethods[] = {
    {"bruteforcemethod", bruteforcemethod, METH_VARARGS, "Brute Force Method"},
    {"dividemethod", dividemethod, METH_VARARGS, "Divide and Conquer Method"},
    {"strassenmethod", strassenmethod, METH_VARARGS, "Strassen and Conquer Method"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef matrixmultiplication = {
    PyModuleDef_HEAD_INIT,
    "matrixmultiplication",
    "Matrix Multiplication Algorithms",
    -1,
    matrixmultiplicationmethods
};

PyMODINIT_FUNC PyInit_matrixmultiplication(void) {
    import_array();
    return PyModule_Create(&matrixmultiplication); 
}
