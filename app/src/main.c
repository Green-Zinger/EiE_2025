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
    if(0>BTN_init()){
        printk("Failure setting up BTN");
        return 0;
    }

    if(0>LED_init()){
        printk("Failure setting up LED");
        return 0;
    }
    
    //Setting up intial condition for locked password state.
    int input_cap;
    int input_length;

    int password[PASSWORD_LENGTH] = {0, 1, 1, 2};
    int *input;
    int locked = 1;
    
    //The main loop
    while(1){
        //Gotta enable dynamic memory to use value the way it is being used.
        input_cap = PASSWORD_LENGTH;
        input_length = 0;
        input = k_malloc(input_cap*sizeof(int));
        printk("Startup success\n");
        if(input == NULL){
            printk("Memory error.\n");
            return 0;
        }
 
        LED_toggle(LED0);
        //locked state loop
        while(locked){
            if(input_length==input_cap){
                int *old = input;
                input = k_malloc(input_cap*2*sizeof(int));

                if(input == NULL)
                    return 0;

                for(int i =0; i<input_cap; i++)
                    input[i] = old[i];
                input_cap*=2;
                k_free(old);
            }
            while(1){
                if(BTN_check_clear_pressed(BTN0)){
                    input[input_length] = 0;
                    input_length++;
                    break;
                }else if(BTN_check_clear_pressed(BTN1)){
                    input[input_length] = 1;
                    input_length++;
                    break;
                }else if(BTN_check_clear_pressed(BTN2)){
                    input[input_length] = 2;
                    input_length++;
                    break;
                }else if(BTN_check_clear_pressed(BTN3)){
                    locked = 0;
                    break;
                }
                k_msleep(SLEEP_TIME_MS);
            }
            
        }
        //
        LED_toggle(LED0);
        
        if(input_length != PASSWORD_LENGTH){
            printk("Incorrect! You Suck!\n");   
        }else{
            int i;
            for(i = 0; i<PASSWORD_LENGTH; i++){
                if(input[i] != password[i]){
                    printk("Incorrect! You Suck!\n");
                    break;
                }
            }
            if(i == PASSWORD_LENGTH)
                printk("Correct! You are the Goat!\n");
        }
        
        k_free(input);
        //This is the waiting state.
        while(!locked){
            if(BTN_check_clear_pressed(BTN0)){
                locked = 1;
            }else if(BTN_check_clear_pressed(BTN1)){
                locked = 1;
            }else if(BTN_check_clear_pressed(BTN2)){
                locked = 1;
            }else if(BTN_check_clear_pressed(BTN3)){
                locked = 1;
            }
            k_msleep(SLEEP_TIME_MS);
        }
    }
    return 0;
}
