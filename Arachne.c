/*
 * File: Arachne.c
 *
 * Code generated for Simulink model 'Arachne'.
 *
 * Model version                  : 1.759
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Sat Sep 22 16:10:05 2018
 *
 * Target selection: ert_linux.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Arachne.h"

/* Named constants for Chart: '<Root>/PacketParser' */
#define IN_GetHeader                   ((uint8_T)1U)
#define IN_ParsePayload                ((uint8_T)2U)

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

/* user code (top of source file) */
void DataEntry(char *data,int *count)
{
  int i;
  for (i=0;i<(*count-1);i++) {
    data[i]= data[i+1];
  }

  *count= *count-1;
}

int SumData(char *data,int start, int end)
{
  int i;
  int sumdata = 0;
  for (i = start; i <=end; i++) {
    sumdata^=data[i];
  }

  return sumdata;
}

/* Block signals and states (auto storage) */
DW rtDW;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void Arachne_step(uint8_T byte)
{
  /* local block i/o variables */
  uint8_T rtb_SerialReceive1;
  uint8_T CheckSum;
  boolean_T guard1 = false;
  uint32_T q0;
  uint32_T qY;

  rtb_SerialReceive1 = byte;

  /* Chart: '<Root>/PacketParser' */
  /* Gateway: PacketParser */
  /* During: PacketParser */
  if (rtDW.is_active_c2_Arachne == 0U) {
    /* Entry: PacketParser */
    rtDW.is_active_c2_Arachne = 1U;

    /* Entry Internal: PacketParser */
    /* Transition: '<S1>:761' */
    rtDW.is_c2_Arachne = IN_GetHeader;

    /* Entry 'GetHeader': '<S1>:296' */
    rtDW.data[rtDW.count] = rtb_SerialReceive1;
    q0 = rtDW.count;
    qY = q0 + 1U;
    if (qY < q0) {
      qY = MAX_uint32_T;
    }

    rtDW.count = qY;
  } else if (rtDW.is_c2_Arachne == IN_GetHeader) {
    /* During 'GetHeader': '<S1>:296' */
    if (rtDW.count >= 2U) {
      /* Transition: '<S1>:475' */
      if ((rtDW.data[0] == 0xeb) && ((rtDW.data[1] == 0x65) || (rtDW.data[1] ==
            0x66))) {
        /* Transition: '<S1>:760' */
        rtDW.is_c2_Arachne = IN_ParsePayload;

        /* Entry 'ParsePayload': '<S1>:297' */
        rtDW.data[rtDW.count] = rtb_SerialReceive1;
        q0 = rtDW.count;
        qY = q0 + 1U;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        rtDW.count = qY;
      } else {
        /* Transition: '<S1>:222' */
        /* Transition: '<S1>:208' */
        DataEntry(rtDW.data, &rtDW.count);
        rtDW.is_c2_Arachne = IN_GetHeader;

        /* Entry 'GetHeader': '<S1>:296' */
        rtDW.data[rtDW.count] = rtb_SerialReceive1;
        q0 = rtDW.count;
        qY = q0 + 1U;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        rtDW.count = qY;
      }
    } else {
      rtDW.data[rtDW.count] = rtb_SerialReceive1;
      q0 = rtDW.count;
      qY = q0 + 1U;
      if (qY < q0) {
        qY = MAX_uint32_T;
      }

      rtDW.count = qY;
    }
  } else {
    /* During 'ParsePayload': '<S1>:297' */
    if (rtDW.count >= 23U) {
      /* Transition: '<S1>:763' */
      rtDW.data[rtDW.count] = rtb_SerialReceive1;
      CheckSum = (uint8_T)SumData(rtDW.data, 0, 21);
      if (CheckSum == rtDW.data[23]) {
        /* Transition: '<S1>:765' */
        rtDW.message_id = rtDW.data[1];
        rtDW.video_switch = (uint8_T)(rtDW.data[2] >> 6);
        rtDW.Infrared_state = (uint8_T)(rtDW.data[2] >> 5 & 0x1);
        rtDW.Laser_state = (uint8_T)(rtDW.data[2] >> 4 & 0x1);
        rtDW.character_color = (uint8_T)(rtDW.data[2] >> 3 & 0x1);
        rtDW.Image_Enhance = (uint8_T)(rtDW.data[2] >> 2 & 0x1);
        rtDW.character_state = (uint8_T)(rtDW.data[2] & 0x3);
        rtDW.Sensor_Tv_Angle = (float)(rtDW.data[4] << 8 | rtDW.data[3])/10;
        rtDW.laser_state = (uint8_T)(rtDW.data[5] >> 5);
        rtDW.laser_mes_d = (uint8_T)(rtDW.data[5] >> 4 & 0x1);
        rtDW.laser_code = (uint8_T)(rtDW.data[5] & 0xf);
        rtDW.cur_mode = (uint8_T)(rtDW.data[6] >> 4);
        rtDW.Comp_SelfCheck = (uint8_T)(rtDW.data[6] >> 3 & 0x1);
        rtDW.LMC = (uint8_T)(rtDW.data[6] >> 2 & 0x1);
        rtDW.Shaft_Start = (uint8_T)(rtDW.data[6] >> 1 & 0x1);
        rtDW.Shart_Exit = (uint8_T)(rtDW.data[6] & 0x1);
        rtDW.HighOrder_Hor = (uint8_T)(rtDW.data[7] >> 5);
        rtDW.HighOrder_Ver = (uint8_T)(rtDW.data[7] >> 3 & 0x3);
        rtDW.MulTarget_Detect = (uint8_T)(rtDW.data[7] >> 2 & 0x1);
        rtDW.time_flag = (uint8_T)(rtDW.data[7] & 0x3);
        rtDW.LowOrder_Hor = rtDW.data[8];
        rtDW.LowOrder_Ver = rtDW.data[9];

        /* Transition: '<S1>:821' */
        rtDW.move_track_hor = (uint8_T)(rtDW.data[10] >> 6);
        rtDW.move_track_ver = (uint8_T)(rtDW.data[10] >> 4 & 0x3);
        rtDW.move_cross_hor = (uint8_T)(rtDW.data[10] >> 2 & 0x3);
        rtDW.move_cross_ver = (uint8_T)(rtDW.data[10] & 0x3);
        rtDW.Target_Distance = (uint32_T)(rtDW.data[12] << 8 | rtDW.data[11]);
        rtDW.TurretAngle_Hor = (float)(rtDW.data[14] << 8 | rtDW.data[13])/100;
        memset(&rtDW.sign_bit, 0xff * (rtDW.data[16] >> 7), 1);
        rtDW.TurretAngle_Ver =(float) (rtDW.sign_bit << 24 | rtDW.sign_bit << 16 |
          rtDW.data[16] << 8 | rtDW.data[15])/100;
        rtDW.time_date = rtDW.data[17];
        rtDW.Mul_Number = (uint8_T)(rtDW.data[18] >> 4);
        rtDW.TV_SizeChage = (uint8_T)(rtDW.data[18] >> 3 & 0x1);
        rtDW.bomen_size = (uint8_T)(rtDW.data[18] >> 1 & 0x3);
        rtDW.White_Black = (uint8_T)(rtDW.data[18] & 0x1);
        rtDW.Roam_Bomen_Switch = (uint8_T)(rtDW.data[19] >> 7);
        rtDW.track_grade = (uint8_T)(rtDW.data[19] >> 4 & 0x3);
        rtDW.En_AutoFocus = (uint8_T)(rtDW.data[19] >> 3 & 0x1);
        rtDW.Infrared_Change = (uint8_T)(rtDW.data[19] >> 2 & 0x1);
        rtDW.Sensor_Thermal = (uint8_T)(rtDW.data[19] >> 1 & 0x1);
        rtDW.Sensor_Tv_Enhance = (uint8_T)(rtDW.data[19] & 0x1);
        rtDW.interface_rate = (uint8_T)(rtDW.data[20] >> 6);
        rtDW.video_transfer = (uint8_T)(rtDW.data[20] >> 4 & 0x3);
        rtDW.video_frame = (uint8_T)(rtDW.data[20] >> 2 & 0x3);
        rtDW.Thermal_frame = (uint8_T)(rtDW.data[20] & 0x3);
        rtDW.Sensor_Thermal_Angle = (float)(rtDW.data[22] << 8 | rtDW.data[21])/10;

        /* Transition: '<S1>:770' */
        IPC_SendMeg(0, IPC_MSG_TYPE_STE_TO_AVT);
        rtDW.count = 0U;
        rtDW.is_c2_Arachne = IN_GetHeader;

        /* Entry 'GetHeader': '<S1>:296' */
        rtDW.data[rtDW.count] = rtb_SerialReceive1;
        q0 = rtDW.count;
        qY = q0 + 1U;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        rtDW.count = qY;
      } else if (CheckSum != rtDW.data[23]) {
        /* Transition: '<S1>:768' */
        /* Transition: '<S1>:208' */
        DataEntry(rtDW.data, &rtDW.count);
        rtDW.is_c2_Arachne = IN_GetHeader;

        /* Entry 'GetHeader': '<S1>:296' */
        rtDW.data[rtDW.count] = rtb_SerialReceive1;
        q0 = rtDW.count;
        qY = q0 + 1U;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        rtDW.count = qY;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      rtDW.data[rtDW.count] = rtb_SerialReceive1;
      q0 = rtDW.count;
      qY = q0 + 1U;
      if (qY < q0) {
        qY = MAX_uint32_T;
      }

      rtDW.count = qY;
    }
  }

  /* End of Chart: '<Root>/PacketParser' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  rtM->Timing.t[0] =
    (++rtM->Timing.clockTick0);

  {
    /* Update absolute timer for sample time: [5.0E-5s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 5.0E-5, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick1++;
  }
}

/* Model initialize function */
void Arachne_initialize(void)
{
  /* Registration code */
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
