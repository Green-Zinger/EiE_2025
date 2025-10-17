/*
 * main.c
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>
#include "BTN.h"
#include "LED.h"

#define SLEEP_TIME_MS 1

int main(void){
    int bit_0 = 0;
    int bit_1 = 0;
    int bit_2 = 0;
    int bit_3 = 0;
    if(0>BTN_init()){
        return 0;
    }

    if(0>LED_init()){
        return 0;
    }

    while(1){
        if(BTN_check_clear_pressed(BTN0)){
            if(bit_0 == 0){
                bit_0 = 1;
                LED_toggle(LED0);
            }else{
                bit_0 = 0;
                LED_toggle(LED0);
                if(bit_1 == 0){
                    bit_1 = 1;
                    LED_toggle(LED1);
                }else{
                    bit_1 = 0;
                    LED_toggle(LED1);
                    if(bit_2 == 0){
                        bit_2 = 1;
                        LED_toggle(LED2);
                    }else{
                        bit_2 = 0;
                        LED_toggle(LED2);
                        if(bit_3 == 0){
                            bit_3 = 1;
                            LED_toggle(LED3);
                        }else{
                            bit_0 = 0;
                            bit_1 = 0;
                            bit_2 = 0;
                            bit_3 = 0;
                            LED_toggle(LED3);
                        }
                    }
                }
            }
                 
        }
        
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}
