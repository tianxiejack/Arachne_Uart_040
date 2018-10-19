/*
 * IPC_Sender.c
 *
 *  Created on: Apr 15, 2017
 *      Author: hoover
 */

/*IPC_sender.c*/
#include <stdio.h>
#include "Arachne_Message.h"

extern DW rtDW;
char IPC_ftok_path[64] = "/home/";

void IPC_Init(int num) {
	ipc_port[num] = IPC_PORT_NUM + num;
	ipc_key[num] = ftok(IPC_ftok_path, ipc_port[num]);
	if (ipc_key[num] == -1) {
		printf(" port %d ftok key failed erro:  \n", ipc_port[num]);
		perror(IPC_ftok_path);
		exit(-1);
	}

	ipc_qid[num] = msgget(ipc_key[num], IPC_EXCL); /*检查消息队列是否存在*/
	if (ipc_qid[num] < 0) {
		ipc_qid[num] = msgget(ipc_key[num], IPC_CREAT | 0666);/*创建消息队列*/
		if (ipc_qid[num] < 0) {
			printf("failed to create msq | errno=%d \n", errno);
			perror(" ");
			exit(-1);
		}
	} else {
		printf("port %d already create! \n", ipc_port[num]);
	}
}
void IPC_Destroy(int num) {
	msgctl(ipc_qid[num], IPC_RMID, 0); //删除消息队列
}
void IPC_SendMeg(int num, IPC_MSG_TYPE n) {
	IPC_msg msgs;
	memset(&msgs, 0, sizeof(IPC_msg));
	switch (n) {
	case IPC_MSG_TYPE_STE_TO_AVT:
		msgs.msg_type = IPC_MSG_TYPE_STE_TO_AVT;
		msgs.payload.message_id = rtDW.message_id;
		msgs.payload.sen_mes.video_switch = rtDW.video_switch;
		msgs.payload.sen_mes.Infrared_state = rtDW.Infrared_state;
		msgs.payload.sen_mes.Laser_state = rtDW.Laser_state;
		msgs.payload.sen_mes.character_color = rtDW.character_color;
		msgs.payload.sen_mes.Image_Enhance = rtDW.Image_Enhance;
		msgs.payload.sen_mes.character_state = rtDW.character_state;
		msgs.payload.Sensor_Tv_Angle = rtDW.Sensor_Tv_Angle;
		msgs.payload.Laser_Mes.laser_state = rtDW.laser_state;
		msgs.payload.Laser_Mes.laser_mes_d = rtDW.laser_mes_d;
		msgs.payload.Laser_Mes.laser_code = rtDW.laser_code;
		msgs.payload.Work_Pattern.cur_mode = rtDW.cur_mode;
		msgs.payload.Work_Pattern.Comp_SelfCheck = rtDW.Comp_SelfCheck;
		msgs.payload.Work_Pattern.LMC = rtDW.LMC;
		msgs.payload.Work_Pattern.Shaft_Start = rtDW.Shaft_Start;
		msgs.payload.Work_Pattern.Shart_Exit = rtDW.Shart_Exit;
		msgs.payload.Track_Search.HighOrder_Hor = rtDW.HighOrder_Hor;
		msgs.payload.Track_Search.HighOrder_Ver = rtDW.HighOrder_Ver;
		msgs.payload.Track_Search.MulTarget_Detect = rtDW.MulTarget_Detect;
		msgs.payload.Track_Search.LowOrder_Hor = rtDW.LowOrder_Hor;
		msgs.payload.Track_Search.LowOrder_Ver = rtDW.LowOrder_Ver;
		msgs.payload.Track_Trim.move_track_hor = rtDW.move_track_hor;
		msgs.payload.Track_Trim.move_track_ver = rtDW.move_track_ver;
		msgs.payload.Track_Trim.move_cross_hor = rtDW.move_cross_hor;
		msgs.payload.Track_Trim.move_cross_ver = rtDW.move_cross_ver;
		msgs.payload.Target_Distance = rtDW.Target_Distance;
		msgs.payload.TurretAngle_Hor = rtDW.TurretAngle_Hor;
		msgs.payload.TurretAngle_Ver = rtDW.TurretAngle_Ver;
		msgs.payload.Td.time_flag = rtDW.time_flag;
		msgs.payload.Td.time_date = rtDW.time_date;
		msgs.payload.MulTarget_Num.Mul_Number = rtDW.Mul_Number;
		msgs.payload.MulTarget_Num.TV_SizeChage = rtDW.TV_SizeChage;
		msgs.payload.MulTarget_Num.bomen_size = rtDW.bomen_size;
		msgs.payload.MulTarget_Num.White_Black = rtDW.White_Black;
		msgs.payload.Sensor_Image_EN.Roam_Bomen_Switch = rtDW.Roam_Bomen_Switch;
		msgs.payload.Sensor_Image_EN.track_grade = rtDW.track_grade;
		msgs.payload.Sensor_Image_EN.En_AutoFocus = rtDW.En_AutoFocus;
		msgs.payload.Sensor_Image_EN.Infrared_Change = rtDW.Infrared_Change;
		msgs.payload.Sensor_Image_EN.Sensor_Thermal = rtDW.Sensor_Thermal;
		msgs.payload.Sensor_Image_EN.Sensor_Tv_Enhance = rtDW.Sensor_Tv_Enhance;
		msgs.payload.Video_C.interface_rate = rtDW.interface_rate;
		msgs.payload.Video_C.video_transfer = rtDW.video_transfer;
		msgs.payload.Video_C.video_frame = rtDW.video_frame;
		msgs.payload.Video_C.Thermal_frame = rtDW.Thermal_frame;
		msgs.payload.Sensor_Thermal_Angle = rtDW.Sensor_Thermal_Angle;
		break;
	default:
		printf("n is error!\n");
	}
	/* 发送消息队列 */
	ret_value = msgsnd(ipc_qid[num], &msgs, sizeof(msgs.payload),
	IPC_NOWAIT);
	if (ret_value < 0) {
		printf("msgsnd() write msg failed,errno=%d \n", errno);
		perror(" ");
	}
#if Debug_Test
	printf("\nipc_qid[%d]:%d", num, ipc_qid[num]);
	printf("\nSend Success !\n");
#endif
}
