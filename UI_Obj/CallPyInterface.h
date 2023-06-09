#ifndef CALLPYINTERFACE_H
#define CALLPYINTERFACE_H

#include <Python.h>
#include "SigDistribution.h"

class CallPyInterface
{
public:
    SigDistribution* sigDisObj = NULL;
    CallPyInterface(SigDistribution* obj);
    ~CallPyInterface();

    static PyObject* DocxSwitchExcelCbk(PyObject* self, PyObject* args);

    void CallPyDocxToExcel(const char* fileName);

    void CallPyExcelToDocx(const char* fileName);

private:
    void CallPy(const char* pyFileName);
};

#endif
