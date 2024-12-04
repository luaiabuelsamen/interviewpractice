#include <stdio.h>
#include <stdlib.h>


typedef enum {
    STATE_IDLE = 0,
    STATE_READY = 1,
    STATE_VENDING = 2,
    STATE_FAULT = 9,
} eGumBallState;

typedef enum {
    COIN = 0,
    BUTTON = 1,
    COIN_RETURN = 2,
    VENDING_COMPLETE = 3,
    GENERIC_FAULT = 9,
} eGumBallInput;

eGumBallState update_state(eGumBallInput input){
    static eGumBallState currentState = STATE_IDLE;
    switch(input){
        case COIN:
            if (currentState == STATE_IDLE){
                printf("Moving from Idle to Ready\n");
                currentState = STATE_READY;
            } else{
                printf("Invalid transition, ignoring\n");
            }
            break;
        case BUTTON:
            if (currentState == STATE_READY){
                printf("Moving from ready to vending\n");
                currentState = STATE_VENDING;
            } else{
                printf("Invalid transition, ignoring\n");
            }
            break;
        case COIN_RETURN:
            if (currentState == STATE_READY){
                printf("Moving from ready to idle\n");
                currentState = STATE_IDLE;
            } else{
                printf("Invalid transition, ignoring\n");
            }
            break;
        case VENDING_COMPLETE:
            if (currentState == STATE_VENDING){
                printf("Moving from vending to idle\n");
                currentState = STATE_IDLE;
            } else{
                printf("Invalid transition, ignoring\n");
            }
            break;
        case GENERIC_FAULT:
            printf("Faulting...\n");
            currentState = STATE_FAULT;
            break;
        default:
            printf("Not a valid input\n");

    }
    return currentState;
}
int main(){
    update_state(COIN);
    update_state(COIN_RETURN);
    update_state(COIN);
    update_state(BUTTON);
    update_state(VENDING_COMPLETE);
    update_state(BUTTON);
    update_state(GENERIC_FAULT);
    update_state(COIN);
}