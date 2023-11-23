# SinePWM_Firmware
Code for frquency and amplitude modulated sine PWM signals.

## Description
This repository has C code to generate sine PWM signals with frequency and amplitude modulation on Tiva C series TM4C123GH6PM Cortex M4 Core as a part of a bigger project to build a bidirectional EV charging system.

## Project Structure
* README.md: This README file providing an overview and guide for the project.
* /Includes: Contains the header file of the microcontroller including registers and their addresses.
* /ProjectFiles: Contains the project specific configuration files to run this C code on Code Composer Studio v12.
* /Results: Contains the oscilloscope readings of the PWM signal, it's filtered output, amplitude modulation and frequency modulation.
* /Sources: Contains C file of the project.

## Logistics
* Hardware/Machine: Laptop, TM4C123GH6PM, Oscilloscope (to verify output), low pass RC filter.
* Repository: [Github](https://github.com/ShwetaKiranTotla/SinePWM_Firmware "Github Repository")

## Acknowledgements
Sincere thanks to Prof. Abhijit for helping throughout the project, explaining things I should've already known, and spending as much time on the project as I did. Sir's debugging and problem solving skills helped me understand and tackling them by the cause. He made me believe in the famous quote "Never Ask for a Lighter Rain but a Stronger Umbrella".  
Thanks to Karthik Sir for helping in testing these signals on hardware.

<br>

[Presentation](https://docs.google.com/presentation/d/1psUZHTPc9xYIChw90BaCJeNyP-WQW6ekRRW6uFMbo3s/edit?usp=sharing, "Slides")