/*
 * Copyright (c) 2020, Putu Darmayasa
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *
 *  3. Neither the name of Majenko Technologies nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <Mb1501.h>

Mb1501::Mb1501(uint8_t data, uint8_t le, uint8_t sck) {
    _data = data;
    _le = le;
    _sck = sck;
    _delay = 16;

}

void Mb1501::begin() {
    pinMode(_data, OUTPUT);
    pinMode(_le, OUTPUT);
    pinMode(_sck, OUTPUT);

    digitalWrite(_data, LOW);
    digitalWrite(_le, LOW);
    digitalWrite(_sck, LOW);

}

void Mb1501::end() {
    pinMode(_data, INPUT);
    pinMode(_le, INPUT);
    pinMode(_sck, INPUT);
}

void Mb1501::pulse_clock() {

  uint8_t del = _delay >> 1;
  wait(del);
  digitalWrite(_sck, HIGH);
  wait(del);
  digitalWrite(_sck, LOW);
  wait(del);

}

void Mb1501::pulse_le() {

  uint8_t del = _delay >> 1;
  wait(del);
  digitalWrite(_le, HIGH);
  wait(del);
  digitalWrite(_le, LOW);
  wait(del);

}


void Mb1501::wait(uint_fast8_t del) {
    for (uint_fast8_t i = 0; i < del; i++) {
        asm volatile("nop");
    }
}


void Mb1501::transferRef(uint16_t val, uint8_t pre) {


        uint16_t v2 =
            ((val & 0x0001) << 15) |
            ((val & 0x0002) << 13) |
            ((val & 0x0004) << 11) |
            ((val & 0x0008) << 9) |
            ((val & 0x0010) << 7) |
            ((val & 0x0020) << 5) |
            ((val & 0x0040) << 3) |
            ((val & 0x0080) << 1) |
            ((val & 0x0100) >> 1) |
            ((val & 0x0200) >> 3) |
            ((val & 0x0400) >> 5) |
            ((val & 0x0800) >> 7) |
            ((val & 0x1000) >> 9) |
            ((val & 0x2000) >> 11) |
            ((val & 0x4000) >> 13) |
            ((val & 0x8000) >> 15) ;


        val = v2;

// Transfer Prescaler
    digitalWrite(_data, (pre & 1) ? HIGH : LOW);
    pulse_clock();

// Transfer reference divider
    for (uint8_t bit = 0u; bit < 14u; bit++)
    {

        digitalWrite(_data, ((val & (1<<bit)) ? HIGH : LOW));
        pulse_clock();
    }
// Transfer Command Bit
    digitalWrite(_data, HIGH);
    pulse_clock();

    pulse_le();


}



void Mb1501::transferDiv(uint16_t val,uint8_t swa) {


        uint16_t v2 =
            ((val & 0x0001) << 15) |
            ((val & 0x0002) << 13) |
            ((val & 0x0004) << 11) |
            ((val & 0x0008) << 9) |
            ((val & 0x0010) << 7) |
            ((val & 0x0020) << 5) |
            ((val & 0x0040) << 3) |
            ((val & 0x0080) << 1) |
            ((val & 0x0100) >> 1) |
            ((val & 0x0200) >> 3) |
            ((val & 0x0400) >> 5) |
            ((val & 0x0800) >> 7) |
            ((val & 0x1000) >> 9) |
            ((val & 0x2000) >> 11) |
            ((val & 0x4000) >> 13) |
            ((val & 0x8000) >> 15) ;


        val = v2;

        uint8_t v3 =
            ((swa & 0x01) << 7) |
            ((swa & 0x02) << 5) |
            ((swa & 0x04) << 3) |
            ((swa & 0x08) << 1) |
            ((swa & 0x10) >> 1) |
            ((swa & 0x20) >> 3) |
            ((swa & 0x40) >> 5) |
            ((swa & 0x80) >> 7);
        swa = v3;

    for (uint8_t bit = 0u; bit < 11u; bit++)
    {
        digitalWrite(_data, ((val & (1<<bit)) ? HIGH : LOW));
        pulse_clock();
    }

    /// Swallow Counter

    for (uint8_t bit = 0u; bit <7u; bit++)
    {

        digitalWrite(_data, ((swa & (1<<bit)) ? HIGH : LOW));
        pulse_clock();


    }
   // Write Command
    digitalWrite(_data,  LOW);
    pulse_clock();
    pulse_le();



}
