#include "isr.h"
#include "bsp.h"


//�����ж�
void PORTD_IRQHandler(void)
{
  
    if(PORTD_ISFR & (1<<8))             //PTd8�����ж�
    {
        OSFlagPost(KeyFlag,(OS_FLAGS)0x01,OS_FLAG_SET,NULL);
        PORTD_ISFR  |= (1<<8);          //д1���жϱ�־λ 
      
    }     
    else if(PORTD_ISFR & (1<<10))             
    {
        OSFlagPost(KeyFlag,(OS_FLAGS)0x02,OS_FLAG_SET,NULL);
        PORTD_ISFR  |= (1<<10);        
   
    }    
    else if(PORTD_ISFR & (1<<12))           
    {
        OSFlagPost(KeyFlag,(OS_FLAGS)0x04,OS_FLAG_SET,NULL);
        PORTD_ISFR  |= (1<<12);         
    
    }    
    else if(PORTD_ISFR & (1<<14))          
    {
        OSFlagPost(KeyFlag,(OS_FLAGS)0x08,OS_FLAG_SET,NULL);
        PORTD_ISFR  |= (1<<14);         
    
    }    
    else;
}

void PIT0_IRQHandler(void)
{
    OSFlagPost(Data_Process,(OS_FLAGS)0x01,OS_FLAG_SET,NULL);
    
    PIT_TFLG0 |= PIT_TFLG_TIF_MASK;   //���жϱ�־
    PIT_MCR = 0;     
}

