/*
 * UartInterface.h
 *
 *  Created on: Dec 20, 2017
 *      Author: wang
 */

#ifndef UARTINTERFACE_H_
#define UARTINTERFACE_H_

#include "Serial_port.h"//串口函数头文件
#include "Arachne_Message.h"//进程间通信实现函数头文件


typedef void (*PFUNCSTUB_V)(void *a);
typedef void (*PFUNCSTUB_UC)(unsigned char b);

/*模板生成的代码中，有以下函数指针*/
PFUNCSTUB_V funcFinish;
PFUNCSTUB_V pfuncStub[5];

void interface_bind_func(void*);

#endif /* UARTINTERFACE_H_ */
