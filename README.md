# ZephyrOS Timers demo
Zephyr example with ESP32 C3 mini devkit showing how to use kernel timers 

## What does this demo do?
This demo shows the use of Zephyr OS kernel timers and work queues.
**Specific topics:**
* Creation of timers at compile time or run time
* Avoidance of processing in timer interupt using work queues


## Hardware notes ##
This project uses the generic ESP32-C3-Devkit_M1. This unit is not identical to the official Espressif model. One difference is the RGB led, in the generic unit this is 3 LEDs but in the Espressif version its an LED driver module. The generic unit has a product marking "GOOUUU-ESP32-C3" on the underside.  The standard board **esp32c3_devkitm** is used

## How to use ##
It may be ncessary to install the espressif project, do:

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
