#define PY_SSIZE_T_CLEAN
#include ".venv/lib/python3.9/site-packages/numpy/core/include/numpy/arrayobject.h"
#include "linearregression.c"
#include <python3.10/Python.h>
#include <python3.10/methodobject.h>
#include <python3.10/modsupport.h>
#include <python3.10/moduleobject.h>
#include <python3.10/object.h>
#include <python3.10/pyport.h>

// python setup.py install
// git add*
// git commit -m "msg"
// git push origin master
// installation using pip instead of setup.py
//

// returns simple integer
/*
static PyObject *MyMethod(PyObject *self, PyObject *args) {
  return PyLong_FromLong(1);
}
*/

// takes a numpy array as argument
/*
static PyObject *mymethod(PyObject *self, PyObject *args) {
  PyArrayObject *arr = NULL;
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &arr)) { //pyarraytype
indicates it must be ndarray return NULL;
  }
  return Py_BuildValue("d", 0);
}
*/

static PyObject *mymethod(PyObject *self, PyObject *args) {
  PyArrayObject *inputNdArray = NULL;
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &inputNdArray)) {
    // O! to only accept ndarray(PyArrayType)
    return NULL;
  }

  struct arrayInfo inputArrayInfo;
  inputArrayInfo.nDimensions = (int)PyArray_NDIM(inputNdArray);
  inputArrayInfo.dimensions = (long *)PyArray_DIMS(inputNdArray);
  inputArrayInfo.arrayData = (double *)PyArray_DATA(inputNdArray);

  struct arrayInfo outputArrayInfo = linearregression(inputArrayInfo);

  PyObject *outputNdArray = PyArray_SimpleNewFromData(
      outputArrayInfo.nDimensions, outputArrayInfo.dimensions, NPY_DOUBLE,
      (void *)outputArrayInfo.arrayData);
  return Py_BuildValue("O", outputNdArray);
}

static PyMethodDef mymodulemethods[] = {
    {"mymethod", mymethod, METH_VARARGS, "Method Description!"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef mymodule = {PyModuleDef_HEAD_INIT, "mymodule",
                                      "Module Description!", -1,
                                      mymodulemethods};

PyMODINIT_FUNC PyInit_mymodule(void) {
  import_array();
  return PyModule_Create(&mymodule);
}