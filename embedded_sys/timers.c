#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_TIMER_IDS 100

typedef void (*timer_task)(void *);  // Task function pointer type

typedef struct {
    bool active;             // Is the timer active?
    uint32_t delay_ms;       // Delay for the timer in milliseconds
    uint32_t remaining_ms;   // Remaining time before the timer expires
    timer_task task_func;    // Task function to execute when the timer fires
    void *arg;               // Argument to pass to the task function
} TIMER_INFO;

// Static timer info array to store all timers
static TIMER_INFO s_timer_info[MAX_TIMER_IDS];

// Function to create a timer
void timer_create(timer_task task_func, void *arg, uint32_t delay_in_ms, uint32_t *allocated_timer_id) {
    TIMER_INFO new_timer = {false, delay_in_ms, delay_in_ms, task_func, arg};
    for(int i = 0; i < MAX_TIMER_IDS; i++){
        if(s_timer_info[i].active){
            continue;
        }
        s_timer_info[i] = new_timer;
    }
}

// get 1-ms timer interrupt-ISR
// ISR Address already setup in the interrupt vector table
void timer_check_and_fire(void) {
    for(int i = 0; i < MAX_TIMER_IDS; i++){
        if(!s_timer_info[i].active){
            continue;
        }
        if(s_timer_info[i].remaining_ms == 1){
            s_timer_info[i].task_func(s_timer_info[i].arg);
            s_timer_info[i].active = false;
        }
        s_timer_info[i].remaining_ms -= 1;
    }
}

int main() {
}

//how do you avoid checking every ms