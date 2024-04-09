#include "sample_ms12.h"

#ifndef __SAMPLE_IR_H__
#define __SAMPLE_IR_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    IR_KEY_type_UP=0,/*向上*/
    IR_KEY_type_DOWN,/*向下*/
    IR_KEY_type_RIGHT,/*向右*/
    IR_KEY_type_LEFT,/*向左*/
    IR_KEY_type_ENTER,/*确认*/
    IR_KEY_type_BACK,/*Back*/
    IR_KEY_type_EPG,/*EPG*/
    IR_KEY_type_POWER,/*Power*/
    IR_KEY_type_HOME,/*-/--*/
    IR_KEY_type_VOLUMEUP,/*VOL +*/
    IR_KEY_type_VOLUMEDOWN,/*VOL -*/
    IR_KEY_type_MUTE,/*Mute*/
    IR_KEY_type_1,
    IR_KEY_type_2,
    IR_KEY_type_3,
    IR_KEY_type_4,
    IR_KEY_type_5,
    IR_KEY_type_6,
    IR_KEY_type_7,
    IR_KEY_type_8,
    IR_KEY_type_9,
    IR_KEY_type_0,
    IR_KEY_type_F1,/*Green F1*/
    IR_KEY_type_F2,/*Red F2*/
    IR_KEY_type_F3,/*Yellow F3*/
    IR_KEY_type_F4,/*Blue F4*/
    IR_KEY_type_SEARCH,/*Search*/
    IR_KEY_type_REWIND,/*REW*/
    IR_KEY_type_FF,/*FF*/
    IR_KEY_type_STOP,/*Stop*/
    IR_KEY_type_SET,/*Set*/
    IR_KEY_type_INFO,/*INFO*/
    IR_KEY_type_AUDIO,/*Audio*/
    IR_KEY_type_SUB,/*SUB*/
    IR_KEY_type_BACKSPACE,/*BackSpace DEL*/
    IR_KEY_type_PLAYPAUSE,/*Play/Pause*/
    IR_KEY_type_FAVORITES,/*FAV*/
    IR_KEY_type_CHANNELUP,/*CH +*/
    IR_KEY_type_CHANNELDOWN,/*CH -*/
    IR_KEY_type_PAGEDOWN,/*PgDown*/
    IR_KEY_type_PAGEUP,/*PgUp*/
    IR_KEY_type_FN_1,/*IME*/
    IR_KEY_type_FN_2,/*More*/
    IR_KEY_type_FN_D,/*BTV*/
    IR_KEY_type_FN_E,/*VOD*/
    IR_KEY_type_FN_F,/*NVOD*/
    IR_KEY_type_FN_S,/*nPVR*/
    IR_KEY_type_FN_B,/*SEEK*/
    IR_KEY_type_RECALL,
    IR_KEY_type_BUTT
}IR_KEY_TYPE_E;

typedef struct tagIR_KEY_INFO_S
{
    HI_U32  u32KeyValue;
    IR_KEY_TYPE_E enKeyType;
}IR_KEY_INFO_S;
typedef HI_S32 (*Sample_Ir_ProcFn)(IR_KEY_TYPE_E enKeyType);
HI_S32 Sample_Ir_Init(HI_VOID);
HI_S32 Sample_Ir_DeInit(HI_VOID);
HI_VOID *Sample_Ir_ProcessRoutine(HI_VOID *pArgs);

HI_S32 Sample_Ir_RegKeyProcessFn(Sample_Ir_ProcFn pKeyProcFn);
#ifdef __cplusplus
}
#endif

#endif

