/*
Реализуйте Python-модуль matrix с функцией dot, 
которая выполняет алгебраическое умножение двух 
квадратных вещественных матриц заданного размера, 
представленных в виде списка списков.

В случае, если в качестве аргументов переданы матрицы, 
в которых количество строк или столбцов меньше указанного размера, 
то оставшаяся часть матриц дополняется нулями. 
Если больше указанного размера - то лишние строки или столбцы не используются.

Пример использования модуля:

import matrix

A = [[1,2], [3,4]]
B = [[1,2], [3,4]]

R = matrix.dot(2, A, B)
print(R)

На сервер нужно отпарвить только исходный файл, 
который будет скомпилирован и слинкован с нужными опциями.
*/

#include <stdio.h>
#include <Python.h>
#include <stdint.h>

#define PY_SSIZE_T_CLEAN

uint32_t GetCell(PyObject *matrix, uint32_t i, uint32_t j) {
    if (PyList_Size(matrix) <= i) {
        return 0;
    }
    PyObject *list = PyList_GetItem(matrix, i);
    if (PyList_Size(list) <= j) {
        return 0;
    }
    PyObject *cell = PyList_GetItem(list, j);
    uint32_t num = PyLong_AsLong(cell);
    return num;
}


static PyObject *dot_(PyObject *self, PyObject *args) {
    int32_t n;
    PyObject *a_mat = NULL;
    PyObject *b_mat = NULL;
    if (!PyArg_ParseTuple(args, "lOO", &n, &a_mat, &b_mat)) {
        return NULL;
    }
    PyObject *total = PyList_New(n);

    for (u_int32_t a = 0; a < n; ++a) {
        PyObject *total_list = PyList_New(n);
        for (u_int32_t b = 0; b < n; ++b) {
            int32_t total_cell = 0;
            for (u_int32_t x = 0; x < n; ++x) {
                int32_t a_cell = GetCell(a_mat, a, x);
                int32_t b_cell = GetCell(b_mat, x, b);
                total_cell += a_cell * b_cell;
            }
            PyList_SetItem(total_list, b, Py_BuildValue("l", total_cell));
        }
        PyList_SetItem(total, a, total_list);
    }
    return total;
}

static PyMethodDef methods[] = {
        {"dot", dot_, METH_VARARGS, "help func_1"},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mod = {
        PyModuleDef_HEAD_INIT, "matrix",
        "Test module", -1, methods
};

PyMODINIT_FUNC PyInit_matrix(void) {
    return PyModule_Create(&mod);
}