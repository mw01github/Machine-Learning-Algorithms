#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include "linearregression.c"

static PyObject *testmethod(PyObject *self, PyObject *args) {
    PyArrayObject *inputNdArray = NULL;
    if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &inputNdArray)) {
        return NULL;
    }
    /*
    arrayInfo inputArrayInfo;
    inputArrayInfo.nDimensions = PyArray_NDIM(inputNdArray);
    inputArrayInfo.dimensions = PyArray_DIMS(inputNdArray);
    inputArrayInfo.arrayData = PyArray_DATA(inputNdArray);

    arrayInfo outputArrayInfo = linearregression(inputArrayInfo);


    int ndtemp = 2;
    long dtemp[] = {3, 3};
    double atemp[] = {7, 4, 5, 6, 1, 3, 8, 0, 111};

    PyObject *outputNdArray = PyArray_SimpleNew(
        ndtemp,
        dtemp,
        NPY_DOUBLE
    );
    double *outputArray = PyArray_DATA(outputNdArray);
    outputArray = outputArrayInfo.arrayData;

    return outputNdArray;
    */

    long *outputNdArrayDimensions;
    
    PyObject *outputNdArray = PyArray_SimpleNew(
        ndtemp,
        dtemp,
        NPY_DOUBLE
    );

}

static PyMethodDef testmodulemethods[] = {
    {"testmethod", testmethod, METH_VARARGS, "Method Description!"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef testmodule = {
    PyModuleDef_HEAD_INIT,
    "testmodule",
    "Module Description!",
    -1,
    testmodulemethods
};

PyMODINIT_FUNC PyInit_testmodule(void) {
    import_array();
    return PyModule_Create(&testmodule); 
}
