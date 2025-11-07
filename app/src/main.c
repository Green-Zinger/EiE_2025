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

#define PASSWORD_LENGTH 4

int main(void){
    int password[PASSWORD_LENGTH] = {1, 2, 3, 1};
    int input[PASSWORD_LENGTH];
    if(0>BTN_init()){
        return 0;
    }

    if(0>LED_init()){
        return 0;
    }
    
    while(1){
        LED_toggle(LED0);
        for(int i = 0; i<PASSWORD_LENGTH; i++){
            while(1){
                if(BTN_check_clear_pressed(BTN0)){
                    input[i] = 0;
                    break;
                }
                else if(BTN_check_clear_pressed(BTN1)){
                    input[i] = 1;
                    break;
                }
                else if(BTN_check_clear_pressed(BTN2)){
                    input[i] = 2;
                    break;
                }
                else if(BTN_check_clear_pressed(BTN3)){
                    input[i] = 3;
                    break;
                }
                k_msleep(SLEEP_TIME_MS);
            }
            
        }
        int i;
        for(i = 0; i<PASSWORD_LENGTH; i++){
            if(password[i]!=input[i]){
                printk("Incorrect! You Suck!\n");
                LED_toggle(LED0);
                break;
            }
            printk(" The %dth thing is %d",i,input[i]);
        }
        if(i == 4){
            printk("Correct! You are the Goat!\n");
            LED_toggle(LED0);
        }
        while(!BTN_check_pressed(BTN0)&&!BTN_check_pressed(BTN1)&&!BTN_check_pressed(BTN2)&&!BTN_check_pressed(BTN3)){
            k_msleep(SLEEP_TIME_MS);
        }
        
    }
    return 0;
}
