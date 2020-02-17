#include "common_header.h"
#include "task_header.h"



OS_STK Key_store[Key_task_size];         //�����ջ
OS_STK System_store[Init_task_size];    
OS_STK uart_store[uart4_task_size];
OS_STK menu_srore[menu_task_size];
OS_STK data_process_store[data_process_size];
OS_STK dds_ctrl_store[ddsCtrl_task_size];
OS_STK FirPara_store[FirPara_task_size];

OS_STK Paradata_store[Paradata_task_size];
void main()
{

    OSInit();                                               //��ʼ��uC/OS
    //���ݴ���
    OSTaskCreate(data_process_task,(void *)0,
                 &data_process_store[data_process_size-1],data_process_prio); 
    //dds����
    OSTaskCreate(dds_ctrl_task,(void *)0,
                 &dds_ctrl_store[ddsCtrl_task_size-1],ddsCtrl_task_prio); 
    //������Ӧ
    OSTaskCreate(key_task,(void *)0,
                 &Key_store[Key_task_size-1],Key_task_prio); 
    //ϵͳ��ʼ��
    OSTaskCreate(system_init_task,(void *)0,
                 &System_store[Init_task_size-1],Init_task_prio); 
    //���ڣ������ã�
    //OSTaskCreate(uart4_task,(void *)0,
                 //&uart_store[0],uart4_task_prio); 
    //�˵���ʾ
    OSTaskCreate(menu_task,(void *)0,
                 &menu_srore[menu_task_size-1],menu_task_prio); 
	//FIR��������
    OSTaskCreate(FirPara_task,(void *)0,
                 &FirPara_store[FirPara_task_size-1],FirPara_task_prio); 
 
    //ʾ������������
    OSTaskCreate(Paradata_task,(void *)0,
                 &Paradata_store[Paradata_task_size-1],Paradata_task_prio); 
    
    OSStart();                                              //�������������
}
