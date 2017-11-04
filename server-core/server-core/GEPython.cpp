#include "GEPython.h"
#include "GEDefine.h"
#include "GELogger.h"

//����ǩ��
PyMODINIT_FUNC PyInit_PyGameServer(void);

GEPython::GEPython() {
	//������չPythonģ��
	PyImport_AppendInittab("PyGameServer", &PyInit_PyGameServer);
	//��ʼ��python������
	Py_Initialize();
	PyEval_InitThreads();

	//����Python��·��
	exec("import sys;sys.path = []");
	insert_path(0, PYTHON_PACKAGE_DIR);
	insert_path(0, PYTHON_MAIN_DIR);
	insert_path(0, PYTHON_DLL_DIR);
	insert_path(0, PYTHON_MODULE_DIR);

	//ִ�г�ʼ������
	call_module_function(PYTHON_INIT_SCRIPT, PYTHON_INIT_FUNCTION);
}

GEPython::~GEPython() {
	call_module_function(PYTHON_INIT_SCRIPT, PYTHON_FINAL_FUNCTION);
	//����python������
	Py_FinalizeEx();
}

void GEPython::show_stack() {
	//TODO
	PyErr_Print();
}

void GEPython::insert_path(uint32_t uPos, const char* sPath) {
	assert(Py_IsInitialized());
	const int sz = 256;
	char tmp[sz];

	/*
	* Notice that only when this returned value is non-negative and less than n,
	* the string has been completely written.
	*/
	int n = _snprintf_s(tmp, sz, "import sys\nif '%s' not in sys.path: sys.path.insert(%u, '%s')", sPath, uPos, sPath);
	if (n < 0 || n >= sz) {
		GELogger::instance()->log("Failed to insert python path, (%d) bytes is written while only support (%d) max", n, sz);
		return;
	}
	exec(tmp);
}

bool GEPython::exec(const char* code) {
	PyRun_SimpleString(code);
	return true;
}

bool GEPython::call_module_function(const char* sModuleName, const char* sFunctionName) {
	/*
	* ����ģ����������ģ��
	* Return value: New reference.
	* Return a new reference to the imported module, or NULL with an exception set on failure.
	*/
	PyObject* pyModule = PyImport_ImportModule(sModuleName);
	if (pyModule == NULL) {
		GELogger::instance()->log("Failed to import module(%s)\n", sModuleName);
		show_stack();
		return false;
	}

	/*
	* ���ݺ����������Һ���
	* Return value: New reference.
	* Retrieve an attribute named attr_name from object o. Returns the attribute value on success, or NULL on failure.
	* This is the equivalent of the Python expression o.attr_name.
	*/
	PyObject* pyFunction = PyObject_GetAttrString(pyModule, sFunctionName);
	if (pyFunction == NULL) {
		GELogger::instance()->log("Failed to find function(%s) in module(%s)\n", sFunctionName, sModuleName);
		show_stack();
		Py_DECREF(pyModule);
		return false;
	}

	/*
	* ����ģ�麯��
	* Return value: New reference.
	* Call a callable Python object callable_object, with arguments given by the tuple args.
	* If no arguments are needed, then args may be NULL. Returns the result of the call on success, or NULL on failure.
	* This is the equivalent of the Python expression callable_object(*args).
	*/
	PyObject* pyResult = PyObject_CallObject(pyFunction, NULL);
	if (pyResult == NULL) {
		GELogger::instance()->log("Failed to call function(%s) in module(%s)\n", sFunctionName, sModuleName);
		show_stack();
		Py_DECREF(pyModule);
		Py_DECREF(pyFunction);
		return false;
	}

	Py_DECREF(pyModule);
	Py_DECREF(pyFunction);
	Py_DECREF(pyResult);
	return true;
}