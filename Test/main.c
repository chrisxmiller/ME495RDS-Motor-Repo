/*
 * Example commutation program for brushless motor project
 * Author: Bill Hunt
 */

#define MOTOR_PORT_PERIPH SYSCTL_PERIPH_GPIOA
#define MOTOR_PORT GPIO_PORTA_BASE
#define PHASE_A_STATE GPIO_PIN_2
#define PHASE_A_EN GPIO_PIN_3
#define PHASE_B_STATE GPIO_PIN_4
#define PHASE_B_EN GPIO_PIN_5
#define PHASE_C_STATE GPIO_PIN_6
#define PHASE_C_EN GPIO_PIN_7


// Create some LEDs for blinking
#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3
#define SLOW

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

/**
 * main.c
 */
int main(void)
{

    //
    // Setup the system clock to run at 50 Mhz from PLL with crystal reference
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|
                    SYSCTL_OSC_MAIN);

    //
    // Enable and wait for the port to be ready for access
    //
    SysCtlPeripheralEnable(MOTOR_PORT_PERIPH);
    while(!SysCtlPeripheralReady(MOTOR_PORT_PERIPH))
    {
    }

    // Port F for LEDs

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //
    // Set the outputs to OUTPUT mode
    //
    GPIOPinTypeGPIOOutput(MOTOR_PORT, PHASE_A_STATE | PHASE_B_STATE | PHASE_C_STATE |
                                      PHASE_A_EN | PHASE_B_EN | PHASE_C_EN);

    // LEDs output
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);

    //
    // State table for motor commutation
    //
    uint8_t stateTable[6] = {PHASE_A_EN | PHASE_B_EN | PHASE_B_STATE,
                             PHASE_A_EN | PHASE_C_EN | PHASE_C_STATE,
                             PHASE_B_EN | PHASE_C_EN | PHASE_C_STATE,
                             PHASE_A_EN | PHASE_B_EN | PHASE_A_STATE,
                             PHASE_A_EN | PHASE_C_EN | PHASE_A_STATE,
                             PHASE_B_EN | PHASE_C_EN | PHASE_B_STATE};

    // State table for state.
    uint8_t ledTable[6] = { RED_LED,
                            BLUE_LED,
                            GREEN_LED,
                            RED_LED+BLUE_LED,
                            GREEN_LED+BLUE_LED,
                            RED_LED+GREEN_LED};

    int j = 0;

    for (j = 1;j<10;j++){
        int i = 0;
        for(i = 0; i < 6; i++) {
                    HWREG(MOTOR_PORT+GPIO_O_DATA+((PHASE_A_STATE | PHASE_B_STATE | PHASE_C_STATE |
                            PHASE_A_EN | PHASE_B_EN | PHASE_C_EN) <<2)) = stateTable[i];
                    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, ledTable[i]);
                    SysCtlDelay(2000000-j*20*10000);
        }
        j++;

    }



    while(1) {
        // Commutation process: index into state table and apply that state to the motor port for a short time.
        // After the delay time, increment the state and repeat
        int i = 0;

        for(i = 0; i < 6; i++) {
            HWREG(MOTOR_PORT+GPIO_O_DATA+((PHASE_A_STATE | PHASE_B_STATE | PHASE_C_STATE |
                    PHASE_A_EN | PHASE_B_EN | PHASE_C_EN) <<2)) = stateTable[i];
            //bitmask to turn on LEDs
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, ledTable[i]);
            SysCtlDelay(100000); //100000 fast // 20000000 slow
        }
    }

    return 0;
}
