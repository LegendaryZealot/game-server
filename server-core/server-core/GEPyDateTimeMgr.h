#pragma once

#include <Python.h>
#include <stdint.h>
#include <vector>

struct datetime_event
{
	PyObject* py_callback;
	PyObject* py_param;
};

class GEPyDateTimeMgr {
public:
	GEPyDateTimeMgr();
	~GEPyDateTimeMgr() = default;
	GEPyDateTimeMgr(const GEPyDateTimeMgr&) = delete;
	GEPyDateTimeMgr& operator=(const GEPyDateTimeMgr&) = delete;
	
	void update();

public:
	void reg_per_second(PyObject* cb, PyObject* param)		{ reg_function(this->cb_functions_per_second, cb, param); }
	void reg_before_minute(PyObject* cb, PyObject* param)	{ reg_function(this->cb_functions_before_minute, cb, param); }
	void reg_after_minute(PyObject* cb, PyObject* param)	{ reg_function(this->cb_functions_after_minute, cb, param); }
	void reg_before_hour(PyObject* cb, PyObject* param)		{ reg_function(this->cb_functions_before_minute, cb, param); }
	void reg_after_hour(PyObject* cb, PyObject* param)		{ reg_function(this->cb_functions_after_hour, cb, param); }
	void reg_before_day(PyObject* cb, PyObject* param)		{ reg_function(this->cb_functions_before_minute, cb, param); }
	void reg_after_day(PyObject* cb, PyObject* param)		{ reg_function(this->cb_functions_after_day, cb, param); }

	void trigger_per_second()								{ trigger_function(this->cb_functions_per_second); }
	void trigger_before_minute()							{ trigger_function(this->cb_functions_before_minute); }
	void trigger_after_minute()								{ trigger_function(this->cb_functions_after_minute); }
	void trigger_before_hour()								{ trigger_function(this->cb_functions_before_hour); }
	void trigger_after_hour()								{ trigger_function(this->cb_functions_after_hour); }
	void trigger_before_day()								{ trigger_function(this->cb_functions_before_day); }
	void trigger_after_day()								{ trigger_function(this->cb_functions_after_day); }

private:
	void cache_clock();
	void cache_time();

	void reg_function(std::vector<struct datetime_event>&, PyObject* pyCallBack_BorrowRef, PyObject* pyParam_BorrowRef);
	void trigger_function(std::vector<struct datetime_event>&);
	void trigger_event();

public:
	int32_t year;
	int32_t month;
	int32_t day;
	int32_t hour;
	int32_t minute;
	int32_t second;
	int32_t weekday;
	int32_t yearday;
	int32_t unixtime;		//��ǰ��Unixʱ�������ϵͳʱ�䣬�ڲ�����ģ�
	uint64_t cpuclock;		//����CPU�����ڱ���Ľ���/ϵͳ�����ĺ�����
	uint64_t cumulation;	//�����ۼӺ�����ۼ���
	uint64_t timespeed;
	int32_t	timezone_second;//����ʱ���Լ���������Ӱ��
	int32_t dst_second;		//����ʱ��ʱ���Ӱ��

private:
	std::vector<struct datetime_event> cb_functions_per_second;
	std::vector<struct datetime_event> cb_functions_before_minute;
	std::vector<struct datetime_event> cb_functions_after_minute;
	std::vector<struct datetime_event> cb_functions_before_hour;
	std::vector<struct datetime_event> cb_functions_after_hour;
	std::vector<struct datetime_event> cb_functions_before_day;
	std::vector<struct datetime_event> cb_functions_after_day;
};