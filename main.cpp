

#include "mbed.h"
#include "uLCD_4DGL.h"
using namespace std::chrono;

InterruptIn button_up(D13);
InterruptIn button_down(D12);
InterruptIn button_sel(D11);
uLCD_4DGL uLCD(D1, D0, D2);
AnalogOut  aout(D7);
//AnalogIn ain(A0);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;


void ulcd_display(int);
int rate_int[] = {8, 4, 2, 1};
int i = 0;
float value = 0.0;
void wavegenerate(){
    int count = 0;
    int a = 80/rate_int[i];
    while(count <= 240){
        if(count <= 80){
            if(value < 1.0){
                value += 1/a;
                aout = value/1.1;
                wait_us(1000);
            }
        }
        else if (count > 80 && count <= 160){
            value = 1;
            aout = value/1.1;
            wait_us(1000);
        }
        else if(count > 160 && count <= 240){
            if(count <= 240-a){
                value = 1;
                aout = value/1.1;
                wait_us(1000);    
            }
            else{
                value -= 1/a;
                aout = value/1.1;
                wait_us(1000);
            }
        }
        count++;
    }
}
void upcount()
{
    printf("26126516");
    if(i == 3)
        ulcd_display(rate_int[i]);
    else{
        i ++;
        ulcd_display(rate_int[i]);
    }
    return;
}
void downcount()
{
    if(i == 0)
        ulcd_display(rate_int[i]);
    else{
        i --;
        ulcd_display(rate_int[i]);
    }
    return;
}
void select_()
{
    value = 0.0;
    ulcd_display(rate_int[i]);
    wavegenerate();
    //queue.call(sampling)
    return;
}


int main()
{
    
    //float ADCdata[100];
    //float cycle = 0.0;
    //int flag_prt = 0;
    //int flag = 1;
    ulcd_display(rate_int[i]);
    //t.start(callback(&queue, &EventQueue::dispatch_forever));
    while(1){
        button_up.rise(&upcount);
        button_down.rise(&downcount);
        button_sel.rise(&select_);
       
        /*if(count_ == 100){
            flag_prt = 0;
            count_ = 0;
            printf("%d\r\n", frequency);
            for (int i = 0; i < 100; i++){
                printf("%f\r\n",ADCdata[i]);
            }
        }
        else if(flag_prt == 1){
            ADCdata[count_] = ain;
            count_ ++;
        }*/
        /*
        if (flag_prt == 1){
            ADCdata[count_] = ain;
            if (count_ == 99){
                flag_prt = 0;
                count_ = 0;
                printf("%d\r\n", frequency);
                for (int i = 0; i < 100; i++){
                    printf("%f\r\n",ADCdata[i]);
                }
            } else {
                count_++;
            }
        }*/
    }
}

void ulcd_display(int rate_int){
    uLCD.cls();
    uLCD.locate(1,2);
    uLCD.text_width(4); //4X size text
    uLCD.text_height(4);
    uLCD.printf("%d", 1);
    uLCD.printf("%c", '/');
    uLCD.printf("%d", rate_int);
}
