/*
 * File: Arachne.h
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

#ifndef RTW_HEADER_Arachne_h_
#define RTW_HEADER_Arachne_h_
#ifndef Arachne_COMMON_INCLUDES_
# define Arachne_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#endif                                 /* Arachne_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#define Arachne_M                      (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* user code (top of header file) */
#include "UartInterface.h"
#include "Arachne_Message.h"

void DataEntry();
int SumData(char *data,int start, int end);

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  float TurretAngle_Ver;             /* '<Root>/PacketParser' */
  float Sensor_Tv_Angle;            /* '<Root>/PacketParser' */
  uint32_T Target_Distance;            /* '<Root>/PacketParser' */
  float TurretAngle_Hor;            /* '<Root>/PacketParser' */
  float Sensor_Thermal_Angle;       /* '<Root>/PacketParser' */
  uint32_T count;                      /* '<Root>/PacketParser' */
  uint8_T data[512];                   /* '<Root>/PacketParser' */
  uint8_T message_id;                  /* '<Root>/PacketParser' */
  uint8_T video_switch;                /* '<Root>/PacketParser' */
  uint8_T Infrared_state;              /* '<Root>/PacketParser' */
  uint8_T Laser_state;                 /* '<Root>/PacketParser' */
  uint8_T character_color;             /* '<Root>/PacketParser' */
  uint8_T Image_Enhance;               /* '<Root>/PacketParser' */
  uint8_T laser_state;                 /* '<Root>/PacketParser' */
  uint8_T laser_mes_d;                 /* '<Root>/PacketParser' */
  uint8_T laser_code;                  /* '<Root>/PacketParser' */
  uint8_T cur_mode;                    /* '<Root>/PacketParser' */
  uint8_T Comp_SelfCheck;              /* '<Root>/PacketParser' */
  uint8_T LMC;                         /* '<Root>/PacketParser' */
  uint8_T Shaft_Start;                 /* '<Root>/PacketParser' */
  uint8_T Shart_Exit;                  /* '<Root>/PacketParser' */
  uint8_T HighOrder_Hor;               /* '<Root>/PacketParser' */
  uint8_T HighOrder_Ver;               /* '<Root>/PacketParser' */
  uint8_T MulTarget_Detect;            /* '<Root>/PacketParser' */
  uint8_T LowOrder_Hor;                /* '<Root>/PacketParser' */
  uint8_T LowOrder_Ver;                /* '<Root>/PacketParser' */
  uint8_T move_track_hor;              /* '<Root>/PacketParser' */
  uint8_T move_track_ver;              /* '<Root>/PacketParser' */
  uint8_T move_cross_hor;              /* '<Root>/PacketParser' */
  uint8_T move_cross_ver;              /* '<Root>/PacketParser' */
  uint8_T time_flag;                   /* '<Root>/PacketParser' */
  uint8_T time_date;                   /* '<Root>/PacketParser' */
  uint8_T Mul_Number;                  /* '<Root>/PacketParser' */
  uint8_T TV_SizeChage;                /* '<Root>/PacketParser' */
  uint8_T bomen_size;                  /* '<Root>/PacketParser' */
  uint8_T White_Black;                 /* '<Root>/PacketParser' */
  uint8_T Roam_Bomen_Switch;           /* '<Root>/PacketParser' */
  uint8_T track_grade;                 /* '<Root>/PacketParser' */
  uint8_T En_AutoFocus;                /* '<Root>/PacketParser' */
  uint8_T Infrared_Change;             /* '<Root>/PacketParser' */
  uint8_T Sensor_Thermal;              /* '<Root>/PacketParser' */
  uint8_T Sensor_Tv_Enhance;           /* '<Root>/PacketParser' */
  uint8_T interface_rate;              /* '<Root>/PacketParser' */
  uint8_T video_transfer;              /* '<Root>/PacketParser' */
  uint8_T video_frame;                 /* '<Root>/PacketParser' */
  uint8_T Thermal_frame;               /* '<Root>/PacketParser' */
  uint8_T character_state;             /* '<Root>/PacketParser' */
  uint8_T SerialReceive1_CustomOutValue;/* '<Root>/Serial Receive1' */
  uint8_T is_active_c2_Arachne;        /* '<Root>/PacketParser' */
  uint8_T is_c2_Arachne;               /* '<Root>/PacketParser' */
  uint8_T sign_bit;                    /* '<Root>/PacketParser' */
} DW;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    uint32_T *t;
    uint32_T tArray[2];
  } Timing;
};

/* Block signals and states (auto storage) */
extern DW rtDW;

/* Model entry point functions */
extern void Arachne_initialize(void);
extern void Arachne_step(uint8_T byte);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Display1' : Unused code path elimination
 * Block '<Root>/Display10' : Unused code path elimination
 * Block '<Root>/Display11' : Unused code path elimination
 * Block '<Root>/Display12' : Unused code path elimination
 * Block '<Root>/Display13' : Unused code path elimination
 * Block '<Root>/Display14' : Unused code path elimination
 * Block '<Root>/Display15' : Unused code path elimination
 * Block '<Root>/Display16' : Unused code path elimination
 * Block '<Root>/Display17' : Unused code path elimination
 * Block '<Root>/Display18' : Unused code path elimination
 * Block '<Root>/Display19' : Unused code path elimination
 * Block '<Root>/Display2' : Unused code path elimination
 * Block '<Root>/Display20' : Unused code path elimination
 * Block '<Root>/Display21' : Unused code path elimination
 * Block '<Root>/Display22' : Unused code path elimination
 * Block '<Root>/Display23' : Unused code path elimination
 * Block '<Root>/Display24' : Unused code path elimination
 * Block '<Root>/Display25' : Unused code path elimination
 * Block '<Root>/Display26' : Unused code path elimination
 * Block '<Root>/Display27' : Unused code path elimination
 * Block '<Root>/Display28' : Unused code path elimination
 * Block '<Root>/Display29' : Unused code path elimination
 * Block '<Root>/Display3' : Unused code path elimination
 * Block '<Root>/Display30' : Unused code path elimination
 * Block '<Root>/Display31' : Unused code path elimination
 * Block '<Root>/Display32' : Unused code path elimination
 * Block '<Root>/Display33' : Unused code path elimination
 * Block '<Root>/Display34' : Unused code path elimination
 * Block '<Root>/Display35' : Unused code path elimination
 * Block '<Root>/Display36' : Unused code path elimination
 * Block '<Root>/Display37' : Unused code path elimination
 * Block '<Root>/Display38' : Unused code path elimination
 * Block '<Root>/Display39' : Unused code path elimination
 * Block '<Root>/Display4' : Unused code path elimination
 * Block '<Root>/Display40' : Unused code path elimination
 * Block '<Root>/Display41' : Unused code path elimination
 * Block '<Root>/Display42' : Unused code path elimination
 * Block '<Root>/Display43' : Unused code path elimination
 * Block '<Root>/Display44' : Unused code path elimination
 * Block '<Root>/Display45' : Unused code path elimination
 * Block '<Root>/Display46' : Unused code path elimination
 * Block '<Root>/Display5' : Unused code path elimination
 * Block '<Root>/Display6' : Unused code path elimination
 * Block '<Root>/Display7' : Unused code path elimination
 * Block '<Root>/Display8' : Unused code path elimination
 * Block '<Root>/Display9' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Arachne'
 * '<S1>'   : 'Arachne/PacketParser'
 */
#endif                                 /* RTW_HEADER_Arachne_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
