MRTOS - Michigan Real Time Operating System
===========================================
* Matt Schulte (mttschult@umich.edu)
* Mark Brehob (brehob@umich.edu)

[Source Code](https://github.com/schultetwin1/MRTOS.git)

Overview
--------
MRTOS is the result of my EECS 499 independent study with Mark Brehob (brehob@umich.edu) for my last semester of 
undergrad at the University of Michigan (Winter 2015). MRTOS was meant to be an educational project to learn the 
basics of real time system design. All the code for this project was written from scratch (no library dependencies) in
order to fulfill this goal. MRTOS is currently written in C, though future projects could port it to C++, D, Rust, or
other languages of choice.

MRTOS was designed to be platform independent (see the porting guide below) however all my development happen on the
STM32L0, which has a Cortex-M0+ running on it. Development was done on the STM32L0 Discovery Board using the arm gnu 
build tools. OpenOCD was used to flash the board. 

MRTOS is a static library which will be compiled with your project. The user will be able to use the threading
library, 3rd party drivers, and virtual hardware abstractions by linking them against their source. Currently, the 
Makefile is setup such that whatevery files are in the prj/ directory are assumed to be the users source and are
compiled against MRTOS.

List of Hardware
----------------
* [STM32L0 Discovery Board] (http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/LN1848/PF260319?sc=stm32l0-discovery)
* [Adafruit nRF8001 BLE Breakout](http://www.adafruit.com/products/1697)

List of Sofware
---------------
* [GNU Arm Embedded Build Tools](https://launchpad.net/gcc-arm-embedded/+download)
* [OpenOCD](http://openocd.org/)

Getting Started
---------------
The following are steps to be able to build MRTOS on a linux machine. This can be extended to run on a Mac or Windows
machine as well.

1. Install GNU Arm Embedded Build tools
2. Try compiling MRTOS using the provided example (just run make in the top directory)
3. Install OpenOCD
4. Run "make flash" from the top level directory to flash the board

Once the compilation is successful you can start using MRTOS for your own projects, or hack on MRTOS yourself. The 
majority of future work currently needs to happen in the src/ folder. This is where all the platform independent RTOS
code exists.

### queue.c ###
This contains template queue for MRTOS. queue.h contains the interface. The queue uses dynamic memory the is allocated
from the custom (and currently extremely simple) allocator found in utils.c. 

### task.c ###
This contains the logic for creating and running multiple threads. The switch\_context function can be changed allowing
for different types of scheduling. Interrupts must be setup on a board by board basis and so are configured in the
port section.

### vtimer.c ###
This contains logic to create a virtual timer in your code. This code has since been integrated with task scheduling,
but can also be used as a standalone virtual timer.

All the port specific code is driver related, though most of them implement a generic interface found in the include 
folder.

Folder Layout
-------------
```
-MRTOS/
  -prj/
    +All the users source will go here
  -src/
    +The main RTOS code is here. All platfrom independent code for MRTOS is found here
  -include/
    +MRTOS headers to include in your project
  -port/
    +All the platform dependent code, see porting guide for more information
```


Porting Guide
=============
Currently can only port to ARM

Step To Port
============
1. Take the port/gcc/m0+ folder and make a copy.
2. Rewrite startup.c which should:
  * Setup interrupt table
  * Define the reset_handler
  * Setup any global variables in the reset_handler
  * Call main in the reset_handler
3. Rewrite port.c which should
  * Define crtical start and end function calls
  * Setup interrupts for task switching
  * Setup yield functionality, and starting scheduler
4. Rewrite the drivers as needed
5. Rewrite main.ld for the ports memory layout
