/*基于扫描式拼接项目*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UartInterface.h"

/*下面都是该项目的变量跟相关函数*/
int fd;
typedef struct {
	char serial_tty[64];
	int baud_rate;
} SerialSet;
SerialSet Serial[1] = { "/dev/ttyTHS2", 115200 };

/*空的，什么都不做，必需*/
void NothingToDo(void *p) {
}

/*函数名不可改，作用就是初始化，此处为读取串口设置文件中的设备号*/
void interface_uart_set() {
}

/*下面直到interface_ipc_destroy函数，都是该项目相关函数，非固定*/
void interface_uart_init(void* p) {
	int err;
	fd = UART0_Open(fd, Serial[0].serial_tty);
	do {
		err = UART0_Init(fd, Serial[0].baud_rate, 0, 8, 1, 'N');
		printf("%d  %d\n", fd, err);
	} while (-1 == err || -1 == fd);
}

/*下面三个*recv*函数参数都是函数指针，将函数地址传输过来，执行传输的函数*/
void interface_uart_recv(void *step_Fun) {
	int j, len;
	int bufsize = 512;
	unsigned char rcv_buf[bufsize];
	PFUNCSTUB_UC p = (PFUNCSTUB_UC) step_Fun;
	memset(rcv_buf, 0, sizeof(rcv_buf));
	len = UART0_Recv(fd, rcv_buf, bufsize);
	if (len > 0) {
#if Debug_Test
		printf("recive data: ");
#endif
		for (j = 0; j < len; j++) {
			p(rcv_buf[j]);
#if Debug_Test
			printf("%0.2x ", rcv_buf[j]);
#endif
		}
#if Debug_Test
		printf("\n");
#endif
	}
}

void interface_ipc_destroy(void *p) {
	IPC_Destroy(0);
}

/*关键处，绑定函数指针跟需要执行的函数*/
void interface_bind_func(void *p) {
	IPC_Init(0);

	pfuncStub[0] = interface_uart_init;
	pfuncStub[1] = NothingToDo;
	pfuncStub[2] = interface_uart_recv;
	pfuncStub[3] = NothingToDo;
	pfuncStub[4] = NothingToDo;

	funcFinish = interface_ipc_destroy;
}
