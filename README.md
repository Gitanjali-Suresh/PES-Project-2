# PES-Project-2
Project By: Gitanjali Suresh and Rucha Borwankar

The project consists of a C code with four versions - two running on the NXP freedom board KL25Z and two running on the computer - FB_Run, FB_Debug, PC_Run and PC_Debug.
In the first part, we focus on the FB_Run function i.e., we write a code to drive the multicolor LED through multiple timing cycles in lookup table on board and after every 3 on and off cycles the LED color will change.
In the second part, we focus on FB_Debug function i.e., we send LED on or off status messages on the serial port and print the time for which the LED was on or off.
In the third part, we focus on PC_Run function which runs on the PC. In this, we code to print output LED on or LED off instead of glowing LED On the board on the MCUXpresso depending on the timing cycles.
In the fourth part of the code, we focus on PC_Debug that runs on the PC and prints the output of LED status along with a timing stamp. 

Installation and Execution notes:

For the above project, we used Freedom Board KL25Z and MCUXpresso IDE v11. We used arm-gcc and gcc compiler for the two different platforms. Make files were manually generated on the same IDE.
