#ifndef task_header_h

#define task_header_h

#include "common_header.h"

//������fpga��������
#define clr_menu_cnt         0x00 //�����ʾRAM����
#define write_menu_ram       0x02 //�˵�RAM��
#define write_dds_ram        0x03
#define write_data_command   0x01
#define clr_data_cnt         0x04 //����������ݼ���
#define clr_dds_add          0x05
#define clr_para_add         0x06
#define para_ram             0x07

#define FFT_CNT              256
#define FFT_LEN              8

#define Mutex_prio             12 //�����ź��� ��Ҫ�Ƿ�ֹ���ȼ���ת

#define data_process_prio       13  
#define data_process_size       8192 //�����ջ

//key_taskΪ��Ӧ�����жϣ����ȼ����Ǹߵ�ȽϺã��������ױ����ݴ����ִ�ϵò�����Ӧ��
#define Key_task_prio          11
#define Key_task_size          2000 //�����ջ


#define Init_task_prio         10
#define Init_task_size         64 

//������
#define uart4_task_prio         25
#define uart4_task_size         64 

//�˵������ʵʱ��Ҫ��ͣ������������ȼ�Ҫ��͡�
#define menu_task_prio         20
#define menu_task_size         1024

#define ddsCtrl_task_prio         19
#define ddsCtrl_task_size         1024

#define FirPara_task_prio         15
#define FirPara_task_size         500

#define Paradata_task_prio         16
#define Paradata_task_size         500

#define    Trigger_Num             2
#define    Trigger_Limin           1
#define    TriggerPoint            0xb0

#define    FirLength             21
#define    MidFre                8
#define    DataLength             512

#define    LcdLength              480


struct menu
{
    uint8 state;    //0������ʾ 1:չ��   0����չ��
    uint8 value;   //���õ�ֵ
    uint8 cursor;  //�����������ֵ
    uint8 value_num; //ֵ������
    uint8 menu_num; //�˵�λ��
    
    struct menu * next_menu; 
    struct menu * last_menu;
};

extern uint8 err;

extern struct menu trigger,kalman,fft_wave,freq_selc,trigger_lock,dds;
extern struct menu * menu_p;
extern struct menu * menu_head;

extern OS_FLAG_GRP *KeyFlag;

extern OS_FLAG_GRP *Menu;

extern OS_FLAG_GRP *Data_Process;
extern OS_FLAG_GRP *FirFlag;


extern OS_EVENT *MenuSem;
extern OS_EVENT *LCDdataSem;
extern OS_EVENT *ParaMbox;
extern OS_EVENT *FirParamSem;
extern OS_EVENT *FirMbox;

extern uint8 LCD_Command;

extern int32 FirParam[FirLength];

void key_menu(uint8 key_num);
void show_menu(void);

uint8 sample_algorithms(uint8 AD_data);

#endif

