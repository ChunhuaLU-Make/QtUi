#define _CRT_SECURE_NO_WARNINGS
#include <QDebug>
#include <QDir>
#include "CallPyInterface.h"


CallPyInterface::CallPyInterface(SigDistribution* obj)
{
    if(obj == NULL)
    {
        qDebug()<< "Obj is NULL";
        return ;
    }

    this->sigDisObj = obj;
}

CallPyInterface::~CallPyInterface()
{

}


void CallPyInterface::CallPy(const char* pyFileName)
{
    //FILE* fp = fopen(R"(C:\Users\902216\Downloads\qt-ui-master\qt-ui-master\build-UI_Obj-Desktop_Qt_5_15_2_MSVC2019_64bit-Release\release\WordToExcel.py)", "r");
    FILE* fp = fopen(pyFileName, "r");
    if (fp == NULL)
    {
        Py_Finalize();
        qDebug() << "Open file error:" << pyFileName;
        return ;
    }
    int ret = PyRun_AnyFile(fp, pyFileName);
    if (ret != 0)
    {
        PyErr_Print();
    }

    fclose(fp);
}

static PyObject* DocxSwitchExcelCbk(PyObject* self, PyObject* args)
{
    char* msg = 0;
    if (!PyArg_ParseTuple(args, "s", &msg))
    {
        return NULL;
    }
    qDebug() << "The c++ function a:" << msg;
    Py_RETURN_TRUE;
}

void CallPyInterface::CallPyDocxToExcel(const char* fileName)
{
    QString currentPath = QDir::currentPath();
    qDebug() << "Current Path: " << currentPath;

    Py_Initialize();
    if (!Py_IsInitialized())
    {

        qDebug() << "Python init fail:";
        PyErr_Print();
        return;
    }


    PyObject* key = PyUnicode_FromString("__main__"); //把字符串转换为Python对象
    PyObject* module = PyImport_GetModule(key); //获取这个主模块
    Py_XDECREF(key);

    if(module == NULL)
    {
        qDebug() << "CallPyInterface create fail:";
        PyErr_Print();
        return;
    }

   #if 1
    PyObject* docx_m = PyImport_ImportModule("docx");
    if (docx_m == 0)
    {
        PyErr_Print();
        qDebug() << "Docx module is error.";
        return;
    }
    else
    {
        PyModule_AddObject(module, "docx_m", docx_m);
    }

    PyObject* excel_mod = PyImport_ImportModule("openpyxl");
    if (excel_mod == nullptr)
    {
        PyErr_Print();
        qDebug() << "Excel module is error.";
        return;
    }
    else
    {
        PyModule_AddObject(module, "excel_mod", excel_mod);
    }

    int ret = PyObject_SetAttrString(module, "fileName", PyUnicode_FromString(fileName));
    if(ret != 0)
    {
        qDebug() << "CallPyDocxToExcel error:" << fileName;
        PyErr_Print();
        return ;
    }



    PyMethodDef cfuns[] = {
        {"DocxSwitchExcelCbk", DocxSwitchExcelCbk, METH_VARARGS, NULL},
        {NULL}
    };
    PyModule_AddFunctions(module, cfuns);
#endif

    this->CallPy("./release/WordToExcel.py");

     Py_Finalize();

}


void CallPyInterface::CallPyExcelToDocx(const char* fileName)
{

}
