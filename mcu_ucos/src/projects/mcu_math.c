#include"mcu_math.h"



struct complex_num complex_mul(struct complex_num a,struct complex_num b)
{
    struct complex_num c;
    c.real=a.real*b.real-a.imag*b.imag;
    c.imag=a.real*b.imag+a.imag*b.real;
    return(c);
}

struct complex_num  wn_calculate(int n,int N)
{
    struct complex_num wnn;
    float degree;
    degree = 2*pi*n/N;
    wnn.real = arm_cos_f32(degree);
    wnn.imag = -1*arm_sin_f32(degree);
    return(wnn);

};
struct complex_num complex_add(struct complex_num a,struct complex_num b)
{
    struct complex_num c;
    c.imag = a.imag + b.imag;
    c.real = b.real + a.real;
    return(c);
};

struct complex_num complex_sub (struct complex_num a,struct complex_num b)
{
    struct complex_num c;
    c.imag = a.imag - b.imag;
    c.real = a.real - b.real;
    return(c);
};


void fft(uint8* data,struct complex_num* data_out,uint8 fft_length,uint16 FFT_count)
{
  
    uint16 i,k,j,length;
    uint16 point_1,point_2;
    uint8 tem;
    struct complex_num fft_tem,wn;

    //�׵��㷨
    for(j=0,i=0;i<FFT_count-1;i++)
    {
        if(i<j) //���i<j,�����б�ַ
        {
            tem=data[j];
            data[j]=data[i];
            data[i]=tem;
        }
        k=FFT_count/2; //��j����һ����λ��
        while(k<=j) //���k<=j,��ʾj�����λΪ1
        {
            j=j-k; //�����λ���0
            k=k/2; //k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
        }
        j=j+k; //��0��Ϊ1
    }


    for(i=0;i<FFT_count;i++)
    {
        data_out[i].real = data[i];
        data_out[i].imag = 0;
    }


    for(length=0;length<fft_length;length++)    //����Ҷ�׼���
    {
        for(i=0;i<FFT_count;i +=(2<<length))  //ÿ��������������
        {

            for(j=0;j<(1<<length);j++) //ÿ����������
            {
                point_2 = i+j+(1<<length);
                point_1 = i+j;
                wn = wn_calculate(j,(2<<length));
                fft_tem = complex_mul(wn,data_out[point_2]);
                //fft_tem.imag = fft_tem.imag/400;
                //fft_tem.real = fft_tem.real/400;

                data_out[point_2] = complex_sub(data_out[point_1],fft_tem);
                data_out[point_1] = complex_add(data_out[point_1],fft_tem);
            }

        }

    }

}
void absfft(struct complex_num * fft_result,uint8 * absdata,uint32 cnt)
{
    uint32 i,tem;

    for(i=0;i<cnt;i++)
    {
        //absdata[i]=((int32)fft_result[i].real*(int32)fft_result[i].real+(int32)fft_result[i].imag*(int32)fft_result[i].imag)>>15;
        tem=((int32)fft_result[i].real*(int32)fft_result[i].real+(int32)fft_result[i].imag*(int32)fft_result[i].imag);
        if(tem<1048576)
           absdata[i] = tem>>10;
        else if(tem<4194304)
           absdata[i] = ((tem-1048576)/3072)+1024;
        else 
           absdata[i] = ((tem-4194304)/5120)+2048;
          
          
    }
}

    
    
    
    
    


void FirPara(uint8 H,uint8 L, uint16 N,int32 * fir_c,uint8 len)
{
    OSSemPend(FirParamSem,0,&err);
    int32 s0;
    uint8 i;
    uint8 mid;
    s0 = (int32)(H-L)*1024/(N-1);
    mid = (len-1)>>1;
    fir_c[mid] = s0;
    //window[mid]= 1;
    for(i=1;i<mid+1;i++)
    {
        fir_c[mid+i]=1024*(arm_sin_f32((double)i*2*pi*H/(N-1))-arm_sin_f32((double)i*2*pi*L/(N-1)))/i/pi;
        fir_c[mid-i]=1024*(arm_sin_f32((double)i*2*pi*H/(N-1))-arm_sin_f32((double)i*2*pi*L/(N-1)))/i/pi;

        //window[mid-i]=0.5+0.5*cos(i*2*pi/(len-1));
        //window[mid+i]=0.5+0.5*cos(i*2*pi/(len-1));
        //window[mid+i]=1;
        //window[mid+i]=1;
    }
    OSSemPost(FirParamSem);
}


//��ʼЭ������� ����Э������� ����Э������� ��ʼԤ��ֵ��
void KalmanFilter(uint8 * NoiseSig,uint8 InitX,uint8 InitP)
{
    uint16 i;
    float OptimX[KalmanLength+1],Optimp[KalmanLength+1];
    float PreX,PreP,kg;
    uint8 Ux=0; //�޿�����

    //��ֵ
    OptimX[0] = InitX;
    Optimp[0] = InitP;
    //printf("%f,%f\n",OptimX[0],Optimp[0]);
    for(i=0;i<KalmanLength;i++)
    {
        PreX = OptimX[i]+Ux;         //Ԥ��ֵ
        PreP = Optimp[i]+KalmanQ;       //Ԥ��Э����
        kg = PreP/(PreP+KalmanR);   //����������
        //printf("%f\t",kg);
        OptimX[i+1] = PreX+kg*(NoiseSig[i]-PreX);
        //printf("%d\t",NoiseSig[i]);
        Optimp[i+1] = (1-kg)*PreP;
        //printf("%f,%f\n",OptimX[i+1],Optimp[i+1]);
        NoiseSig[i]= OptimX[i+1];
    }
}



