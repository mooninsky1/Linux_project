#include "Python.h"

class CPythonTest
{
public:
	static void Test();
	//
	static int InitPython();
	static void ClosePython();
	//
	static int C_Call_python();
	static int Python_Call_C();
};

