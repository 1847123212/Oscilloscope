#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

#include "common.h"




/***************** ucos ר�� *****************/
#define USOC_EN 1u
#include  "ucos_ii.h"               //uC/OS-IIϵͳ����ͷ�ļ�

#include  "app.h"           //�û�������


#define EnableInterrupts asm(" CPSIE i");  //�����ж�

#define DisableInterrupts asm(" CPSID i");  //�����ж�

#define CPU_frequency   100000000


//typedef unsigned short    uint16;
//typedef unsigned long     uint32;
//typedef unsigned char     uint8;

#define      uint16            unsigned short
#define      uint32            unsigned long
#define      uint8             unsigned char 

#define    ARM_MATH_CM4           4 

#endif
