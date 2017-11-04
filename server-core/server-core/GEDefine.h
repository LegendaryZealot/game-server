#pragma once
#include <stdint.h>

struct game_message {
	uint16_t sock_id;
	uint16_t size;
	uint16_t type;
	void* data;
};

enum CMsgType {
	Ping = 1,
	PingReply,
	Echo,
	EchoReply,
	ChatString,
};

//�����˿�
#define PORT_STRING "9995"
#define PORT		9995

//pythonģ��Ŀ¼
#define PYTHON_PACKAGE_DIR	"../py-lib/site-packages/"
#define PYTHON_MAIN_DIR		"../py-lib/python36/"
#define PYTHON_DLL_DIR		"../py-lib/dlls/"
#define PYTHON_MODULE_DIR	"../../server-py/"

//�����ű�����ʼ����������ֹ����
#define PYTHON_INIT_SCRIPT		"init_script"
#define PYTHON_INIT_FUNCTION	"init"
#define PYTHON_FINAL_FUNCTION	"final"

#define SocketEvent_Accept		1
#define SocketEvent_Connect		2
#define SocketEvent_Close		3
#define SocketEvent_Error		4
#define SocketEvent_Data		5
