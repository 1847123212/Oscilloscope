#ifndef __ISR_H
#define __ISR_H 

#include  "common_header.h"
#include "task_header.h"

#if     USOC_EN > 0u    //�����������ucosϵͳ  ��ucos�ĵδ�ʱ���жϷ�����
#undef  VECTOR_014
#undef  VECTOR_015
#define VECTOR_014    OS_CPU_PendSVHandler
#define VECTOR_015    OS_CPU_SysTickHandler
#endif  //if     USOC_EN > 0u  


#undef  VECTOR_106                        //ȡ���жϺŵĶ���
#define VECTOR_106    PORTD_IRQHandler    //���¶���Ӳ���Ϸ��жϷ�����

#undef  VECTOR_084                        //ȡ���жϺŵĶ���
#define VECTOR_084    PIT0_IRQHandler    //���¶���Ӳ���Ϸ��жϷ�����

void PORTD_IRQHandler(void);           //PORTD�жϷ�����
void PIT0_IRQHandler(void);
#endif  