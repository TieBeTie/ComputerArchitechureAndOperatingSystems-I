/*
Реализуйте Python-модуль primes с функцией factor_out, 
которая выполняет разложение целого числа на простые множители,
 и возвращает их в виде списка.

В случае, если число уже является простым, 
то не нужно раскладывать на множители, а вернуть строку Prime!.

Не забывайте обрабатыать ошибочные ситуации!

Пример использования модуля:

Python 3.8.5 (default, Jul 21 2020, 10:48:26)
[Clang 11.0.3 (clang-1103.0.32.62)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> import primes
>>> primes.factor_out(100)
[1, 2, 2, 5, 5]
>>> primes.factor_out(17)
'Prime!'
>>>

На сервер нужно отпарвить только исходный файл,
 который будет скомпилирован и слинкован с нужными опциями.
*/

#include <stdio.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *factor_out_(PyObject *self, PyObject *args) {
    long int n;
    if (!PyArg_ParseTuple(args, "l", &n)) {
        return NULL;
    }

    if (n < 1) {
        PyErr_SetString(PyExc_ValueError,
                        "factorization number must be greater than zero");
        return NULL;
    }

    PyObject *py_factorization = PyList_New(1);
    PyList_SetItem(py_factorization, 0, PyLong_FromLong(1l));
    long int p = 2;

    while (p <= n) {
        if (n % p) {
            p += 1;
            if (p * p > n) {
                p = n;
            }
        } else {
            PyList_Append(py_factorization, PyLong_FromLong(p));
            n /= p;
        }
    }
    if (PyList_Size(py_factorization) <= 2) {
        Py_XDECREF(py_factorization);
        return PyUnicode_FromString("Prime!");
    } else {
        return py_factorization;
    }
}

static PyMethodDef methods[] = {
        {"factor_out", factor_out_, METH_VARARGS, "help func_1"},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mod = {
        PyModuleDef_HEAD_INIT, "primes", "Test module", -1, methods
};

PyMODINIT_FUNC PyInit_primes(void) {
    return PyModule_Create(&mod);
}