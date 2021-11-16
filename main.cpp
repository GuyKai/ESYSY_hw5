/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <algorithm>

// Adjust pin name to your board specification.
// You can use LED1/LED2/LED3/LED4 if any is connected to PWM capable pin,
// or use any PWM capable pin, and see generated signal on logical analyzer.
// PwmOut led(PWM_OUT);

// int main()
// {
//     // specify period first
//     led.period(0.01f);     // 4 second period
//     led.write(0.25f);      // 50% duty cycle, relative to period
//     //led = 0.5f;          // shorthand for led.write()
//     //led.pulsewidth(2);   // alternative to led.write, set duty cycle time in seconds
//     while (1);
// }

#include <chrono>

Ticker ticker;
PwmOut motor(PWM_OUT);

// Using TowerPro SG90 servo motor
// PWM period of 50kHz (20ms period)
// 1ms   pulse   (5%) for -90 degrees
// 1.5ms pulse (7.5%) for   0 degrees (center)
// 2ms   pulse  (10%) for +90 degrees
static int pulseWidth = 1500;
static int direction = 2; // 1 or -1

const int MIN = 500;
const int MAX = 2500;
const int SPEED = 2;

void changeMotor() {
    pulseWidth += direction;
    if (pulseWidth == MAX) {
        direction = -SPEED;
    }
    if (pulseWidth == MIN) {
        direction = SPEED;
    }
    motor.pulsewidth_us(pulseWidth);
}

int main()
{
    motor.period_ms(20);
    motor.pulsewidth_us(2500);
    //ticker.attach(Callback<void(void)>(&changeMotor), std::chrono::milliseconds(1));

    while (1);
}
