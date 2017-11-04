#pragma once

#include <Python.h>
#include "GESingleton.h"

class GEPython : public GESingleton<GEPython> {

public:
	GEPython();
	~GEPython();
	
	//��logger��ӡ��ջ
	void show_stack();
	//����pathĿ¼
	void insert_path(uint32_t uPos, const char* sPath);
	//ֱ��ִ��һ��python����
	bool exec(const char* code);
	//��pythonģ��ִ��һ������
	bool call_module_function(const char* sModuleName, const char* sFunctionName);
};