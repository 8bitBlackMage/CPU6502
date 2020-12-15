#include <iostream>
#include "cpu6502.h"
#include "RAM.h"

RAM MainRam(1024 * 64);
cpu6502 CPU(&MainRam);
int main() {
    MainRam.writeByte(0xFFFC, 0x4c);
    MainRam.writeByte(0xFFFD, 0x00);
    MainRam.writeByte(0xFFFE, 0x01);
    MainRam.writeByte(0x0100, 0xA9);
    MainRam.writeByte(0x0101, 0x42);
    CPU.Reset();
    CPU.TestRun(5);
}
