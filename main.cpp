/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "mbed_events.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

DigitalOut led(LED1);
InterruptIn btn(PA_5);
bool var = true;

// create an event queue
EventQueue queue;

void interrupt_handler() {
    led = !led;
    printf("Button pressed\n");
}

int main()
{
    // create a thread that'll run the event queue's dispatch function
    Thread eventThread;
    eventThread.start(callback(&queue, &EventQueue::dispatch_forever));
    
    btn.fall(queue.event(&interrupt_handler));
    
   while(1);
}
