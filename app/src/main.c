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

#define INPUT_BASE_LENGTH 4

int* variable_int_input(int *length);
//REQUIRES:
//BUTTON and LED input are set up. Length point to a valid memory address of integer type.
//PROMISES:
//the return value is a pointer to array of ints that represent a sequence of button presses,
//inputed by the user.

int main(void){
    if(0>BTN_init()){
        printk("Failure setting up BTN");
        return 0;
    }

    if(0>LED_init()){
        printk("Failure setting up LED");
        return 0;
    }
    
    //Setting up intial conditions for input.
    int input_length;
    int *input;
    int sleep; 

    //Setting up the initial conditions for password setting.
    int password_length;
    int default_password[INPUT_BASE_LENGTH] = {0, 1, 1, 2};
    int *password = default_password;

    LED_toggle(LED3);
    for(int i = 0; i<3000; i++){
        if(BTN_check_clear_pressed(BTN3)){
                LED_toggle(LED3);
                printk("Choose a password.\n");
                password = variable_int_input(&password_length);
                break;
        }
        k_msleep(SLEEP_TIME_MS);
    }
    //The main loop
    while(1){
        sleep = 1;
        printk("What is the password?\n");
        input = variable_int_input(&input_length);

        if(input_length != password_length){
            printk("Incorrect! You Suck! Wrong length! %d is not equal to %d\n", password_length, input_length);   
        }else{
            int i;
            for(i = 0; i<INPUT_BASE_LENGTH; i++){
                if(input[i] != password[i]){
                    printk("Incorrect! You Suck! Only got the length right!\n");
                    break;
                }
            }
            if(i == INPUT_BASE_LENGTH)
                printk("Correct! You are the Goat!\n");
        }
        
        k_free(input);
        //This is the waiting state.
        while(sleep){
            if(BTN_check_clear_pressed(BTN0)){
                sleep = 0;
            }else if(BTN_check_clear_pressed(BTN1)){
                sleep = 0;
            }else if(BTN_check_clear_pressed(BTN2)){
                sleep = 0;
            }else if(BTN_check_clear_pressed(BTN3)){
                sleep = 0;
            }
            k_msleep(SLEEP_TIME_MS);
        }
    }

    return 0;
}
int* variable_int_input(int *length){
    //Gotta enable dynamic memory to use value the way it is being used.
    int cap = INPUT_BASE_LENGTH;
    *length = 0;
    int *arr = k_malloc(cap*sizeof(int));
    int entry = 1;
    if(arr == NULL){
        printk("Memory error.\n");
        return 0;
    }
    printk("Please input your button sequence now:\n\n\n");
    LED_toggle(LED0);
    //locked state loop
    while(entry){
        if(*length==cap){
            int *old = arr;
            arr = k_malloc(cap*2*sizeof(int));

            if(arr == NULL)
                return 0;

            for(int i =0; i<cap; i++)
                arr[i] = old[i];

            cap*=2;
            k_free(old);
            }
        while(1){
            if(BTN_check_clear_pressed(BTN0)){
                arr[*length] = 0;
                (*length)++;
                break;
            }else if(BTN_check_clear_pressed(BTN1)){
                arr[*length] = 1;
                (*length)++;
                break;
            }else if(BTN_check_clear_pressed(BTN2)){
                arr[*length] = 2;
                (*length)++;
                break;
            }else if(BTN_check_clear_pressed(BTN3)){
                entry = 0;
                break;
            }
            k_msleep(SLEEP_TIME_MS);
        }
            
    }
    LED_toggle(LED0);
    return arr;
}

