#include QMK_KEYBOARD_H

/* Copyright 2018 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// #include ".h"

bool i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;


void matrix_init_kb(void) {
  // Turn status LED on
  setPinOutput(C13);
  writePinHigh(C13);

  matrix_init_user();
}

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();

    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        // TODO: Removed delay, could cause issues 
        // _delay_ms(1000);
    }
    // i2c_init(); // on pins D(1,0)
    // _delay_ms(1000);

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    // mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    // mcp23018_status = i2c_write(IODIRA, ERGODOX_EZ_I2C_TIMEOUT);            if (mcp23018_status) goto out;
    // mcp23018_status = i2c_write(0b00000000, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    // mcp23018_status = i2c_write(0b00111111, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_writeReg(
        I2C_ADDR_WRITE,
        IODIRA,
        (uint8_t[]){0b00000000, 0b00111111},
        2,
        ERGODOX_EZ_I2C_TIMEOUT
    );
    if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    // mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    // mcp23018_status = i2c_write(GPPUA, ERGODOX_EZ_I2C_TIMEOUT);             if (mcp23018_status) goto out;
    // mcp23018_status = i2c_write(0b00000000, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    // mcp23018_status = i2c_write(0b00111111, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;

    mcp23018_status = i2c_writeReg(
        I2C_ADDR_WRITE,
        GPPUA,
        (uint8_t[]){0b00000000, 0b00111111},
        2,
        ERGODOX_EZ_I2C_TIMEOUT
    );

out:
    i2c_stop();


    return mcp23018_status;
}

