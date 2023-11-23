/*
This file generates a sine PWM (50 Hz) with frequency modulation 
in the range of 50Hz - 1.5 kHz and amplitude variation from 0.1 - 1.
Author: Shweta Kiran
*/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include <stdbool.h>

#define MOD 1 //Amplitude modulation values from 0.1 -1
#define FDESIRED 50 //Desired frequency, values from 50Hz - 1.5kHz

int dutyCycles[320] = {
   500, 510, 520, 530, 539, 549, 559, 569, 578, 588, 598, 607, 617, 627, 636,
   646, 655, 664, 674, 683, 692, 701, 710, 719, 728, 736, 745, 754, 762, 770,
   779, 787, 795, 803, 810, 818, 826, 833, 840, 847, 854, 861, 868, 875, 881,
   887, 894, 900, 905, 911, 917, 922, 927, 932, 937, 942, 946, 951, 955, 959,
   963, 966, 970, 973, 976, 979, 982, 984, 987, 989, 991, 993, 994, 996, 997,
   998, 999, 999, 1000, 1000, 1000, 1000, 1000, 999, 998, 997, 996, 995, 993, 992, 990,
   988, 986, 983, 980, 978, 975, 971, 968, 964, 961, 957, 953, 948, 944, 939, 935,
   930, 925, 919, 914, 908, 902, 897, 890, 884, 878, 871, 865, 858, 851, 844, 837,
   829, 822, 814, 806, 799, 791, 783, 774, 766, 758, 749, 741, 732, 723, 714, 705,
   696, 687, 678, 669, 660, 650, 641, 631, 622, 612, 603, 593, 583, 574, 564, 554,
   544, 534, 525, 515, 505, 495, 485, 475, 466, 456, 446, 436, 426, 417, 407, 397,
   388, 378, 369, 359, 350, 340, 331, 322, 313, 304, 295, 286, 277, 268, 259, 251,
   242, 234, 226, 217, 209, 201, 194, 186, 178, 171, 163, 156, 149, 142, 135, 129,
   122, 116, 110, 103, 98, 92, 86, 81, 75, 70, 65, 61, 56, 52, 47, 43,
   39, 36, 32, 29, 25, 22, 20, 17, 14, 12, 10, 8, 7, 5, 4, 3, 2, 1,
   0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 6, 7, 9, 11, 13, 16, 18, 21,
   24, 27, 30, 34, 37, 41, 45, 49, 54, 58, 63, 68, 73, 78, 83, 89, 95,
   100, 106, 113, 119, 125, 132, 139, 146, 153, 160, 167, 174, 182, 190, 197, 205,
   213, 221, 230, 238, 246, 255, 264, 272, 281, 290, 299, 308, 317, 326, 336, 345,
   354, 364, 373, 383, 393, 402, 412, 422, 431, 441, 451, 461, 470, 480, 490
};


//float mod = 1;
int inc = FDESIRED / 50; 

int main(void) {

    // Enable the PWM0 and GPIOF peripherals.
    SYSCTL_RCGCPWM_R |= 0x00000002;  // Enable PWM1 clock
    SYSCTL_RCGCGPIO_R |= 0x00000020; // Enable GPIOF clock
    SYSCTL_RCC_R |= (1<<20); //Use System Clock with division
    //SYSCTL_RCC_R |= 0x000E0000; // Use pre divider of 64 and feed to PWM 1
    // SYSCTL_RCC_R |= 0x00020000; // Use pre divider of 4 and feed to PWM 1
    SYSCTL_RCC_R &= ~(0x00100000); //System clock

    GPIO_PORTF_AFSEL_R |= (1 << 2); // Enable alternate function
    GPIO_PORTF_PCTL_R &= ~0x00000F00; //Set PF2 as output
    GPIO_PORTF_PCTL_R |= 0x00000500; //Make PF2 as PWM output
    GPIO_PORTF_DEN_R |= (1 << 2); //Set PF2 as digital pin

    // Configure the PWM generator.
    PWM1_3_CTL_R &= ~(1<<0); // Disable PWM3 while configuring
    PWM1_3_CTL_R &= ~(1<<1); // Select Down count mode
    PWM1_3_GENA_R = 0x0000008C; // Set PWM3A to produce a symmetric down-counting PWM signal
    PWM1_3_LOAD_R = 1100;//1000
    PWM1_3_CMPA_R = 0;
    PWM1_3_CTL_R = 1; //Enable generator 3 counter
    PWM1_ENABLE_R |= 0x40; // Enable PWM1 channel 6 Output

    PWM1_INTEN_R = 8;
    PWM1_3_INTEN_R = 0x3;

    int dutyCycleIndex = 0;     // Index to cycle through duty cycle values

    while (1) {
        // Update duty cycle with the current value from the array
        while (! (PWM1_RIS_R & 0x8) ){};
            PWM1_3_ISC_R |= 0x2; //Clear Interrupt
            dutyCycles[dutyCycleIndex] = mod*dutyCycles[dutyCycleIndex];
            PWM1_3_CMPA_R = dutyCycles[dutyCycleIndex];
            // Increment the index and wrap around if necessary
            dutyCycleIndex = dutyCycleIndex + inc;
            //dutyCycleIndex++;
            if (dutyCycleIndex >= sizeof(dutyCycles) / sizeof(dutyCycles[0])) {
                dutyCycleIndex = 0;
                }
        }
}
