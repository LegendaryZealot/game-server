#pragma once
#include <stdint.h>
#include <list>
#include <unordered_map>
#include <mutex>
#include <condition_variable>

#include "GESingleton.h"
#include "GEPyTimerMgr.h"
#include "GEPyEventMgr.h"
#include "GEPyMsgMgr.h"
#include "GEPyDateTimeMgr.h"

class GEGameServer : public GESingleton<GEGameServer> {

public:
	void run();

	//SocketServer����
	void socket_accept(uint16_t sock_id);
	void socket_data(uint16_t sock_id, uint16_t type, void* data, uint16_t size);
	void socket_connect(uint16_t sock_id);
	void socket_close(uint16_t sock_id);
	void socket_error(uint16_t sock_id);

	//����������Ϣ
	void send_obj(uint16_t sock_id, uint16_t msg_type, PyObject* pyobj_BorrowRef);
	void send_obj_and_back(uint16_t sock_id, uint16_t msg_type, PyObject* pyobj_BorrowRef, PyObject* pycb_BorrowRef, PyObject* pyparam_BorrowRef, uint32_t timeout);

	//�߼���ر�����
	void kick(uint16_t sock_id);

public:
	GEPyTimerMgr timer_mgr;
	GEPyEventMgr event_mgr;
	GEPyMsgMgr msg_mgr;
	GEPyDateTimeMgr datetime_mgr;

private:
	//SocketServer��Ϣ���
	void socket_message_push(struct socket_message* m);
	std::mutex mtx;
	std::condition_variable cv;
	std::list<struct socket_message*> socket_message_queue;

	PyGILState_STATE gstate;
};