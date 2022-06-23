# ZephyrOS Thread demo
Zephyr example with ESP32 C3 mini devkit showing how to use kernel threads 

## What does this demo do?
This demo shows the use of Zephyr OS kernel threads to create tasks
**Specific topics:**
1) Create 2 threads,one statically and one dynamincally
2) The one thread has as start delay but both run at the same rate to demonstrate the delayed start feature
3) The tasks are created with kernel stacks due to  CONFIG_USERSPACE  not being enabled, the set of K_THREAD_STACK macros have an identical effect to the K_KERNEL_STACK macros.
4) The threads run in supervisor mode (kernel space)
5) The relation of main() to threads
 

## Hardware notes ##
This project uses the generic ESP32-C3-Devkit_M1. This unit is not identical to the official Espressif model. One difference is the RGB led, in the generic unit this is 3 LEDs but in the Espressif version its an LED driver module. The generic unit has a product marking "GOOUUU-ESP32-C3" on the underside.  The standard board **esp32c3_devkitm** is used

## How to use ##
It may be necssary to install the espressif project, do:

> west espressif install <br>
> west espressif update <br>


It may be necessary to add your username to the dialout group if you have communications issue when flashing the board
Steps
1. Clone the code
2. Init your zephyr environment 
> source ~/zephyrproject/zephyr/zephyr-env.sh
4. > west build -p -b esp32c3_devkitm
5. > west flash
6. Connect a termial emulator to the detected serial port set baud rate @ 115200
