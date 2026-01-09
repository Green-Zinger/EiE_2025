/**
 * @file my_state_machine.c
 */

 #include <zephyr/smf.h>

 #include "LED.h"
 #include "BTN.h"
 #include "my_state_machine.h"

/*----------------------------------------
* Function Prototypes
------------------------------------------*/
static void state_0_entry(void* o);
static enum smf_state_result state_0_run(void* o);
static void state_1_entry(void* o);
static enum smf_state_result state_1_run(void* o);
static void state_2_entry(void* o);
static enum smf_state_result state_2_run(void* o);
static void state_3_entry(void* o);
static enum smf_state_result state_3_run(void* o);
static void state_4_entry(void* o);
static enum smf_state_result state_4_run(void* o);
/*--------------------------------------
* Typedefs
------------------------------------------*/
enum state_machine_states{
    STATE_0,
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4
};

typedef struct {
    //Context variable used by zephyr to track state machine state. Must be first
    struct smf_ctx ctx;

    uint16_t count;
} state_object_t;
/*--------------------------------------
* Local Variables
------------------------------------------*/
static const struct smf_state states[] = {
    [STATE_0] = SMF_CREATE_STATE(state_0_run, ,state_0_exit, NULL, NULL, NULL),
    [STATE_1] = SMF_CREATE_STATE(state_1_run, ,state_1_exit, NULL, NULL, NULL),
    [STATE_2] = SMF_CREATE_STATE(state_2_run, ,state_2_exit, NULL, NULL, NULL),
    [STATE_3] = SMF_CREATE_STATE(state_3_run, ,state_3_exit, NULL, NULL, NULL),
    [STATE_4] = SMF_CREATE_STATE(state_4_run, ,state_4_exit, NULL, NULL, NULL),
};
static state_object_t state_object;

 void state_machine_init(){
    state_object.count = 0;
    smf_set_initial(SMF_CTX(&state_object), &states[STATE_0]);
 }

 int state_machine_run(){
    return smf_run_state(SMF_CTX(&state_object));
 }
 
 static void state_0_entry(void* o){
    LED_set(LED0, LED_OFF);
    LED_set(LED1, LED_OFF);
    LED_set(LED2, LED_OFF);
    LED_set(LED3, LED_OFF);
 }
 
 static enum smf_state_result led_on_state_run(void* o){
    if(BTN_check_clear_pressed(BTN0)){
        smf_set_state(SMF_CTX(&state_object), &states[STATE_1]);
    } 
    return SMF_EVENT_HANDLED;
 }
 
 static void state_1_entry(void* o){
    LED_blink(LED0,1)
 }
 static enum smf_state_result state_1_run(void* o){
    if(BTN_check_clear_pressed(BTN1)){
        smf_set_state(SMF_CTX(&state_object), &states[STATE_2]);
    }else if(BTN_check_clear_pressed(BTN2)){
        smf_set_state(SMF_CTX(&state_object), &state[STATE_3]);
    }
    return SMF_EVENT_HANDLED
 }
 static void state_2_entry(void* o){
    LED_set(LED0, LED_ON);
    LED_set(LED2, LED_ON);
    LED_set(LED1, LED_OFF);
    LED_set(LED3, LED_OFF);
 }
 static enum smf_state_result state_2_run(void* o){
    if(state_object.count >)
 }

 