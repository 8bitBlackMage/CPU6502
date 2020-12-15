//
// Created by alice on 14/12/2020.
//

#ifndef INC_6502_CPU6502_H
#define INC_6502_CPU6502_H

using byte = unsigned char;
using word = unsigned short;

class RAM;


class cpu6502 {
enum instructions
{
    //jump instructions in both address modes
JMP_ABSOLUTE   = 0x4C,
JMP_INDIRECT   = 0x6C,

    //jump
JSR_ABSOLUTE   = 0x20,


    //LDA instructions and address modes
LDA_IMMEDIATE   = 0xA9,
LDA_ZEROPAGE    = 0xA5,
LDA_ZEROPAGEX   = 0xB5,
LDA_ABSOLUTE    = 0xAD,
LDA_ABSOLUTEX   = 0xBD,
LDA_ABSOLUTEY   = 0xB9,
LDA_INDIRECTX   = 0xA1,
LDA_INDIRECTY   = 0xB1,

    //LDX Instructions and address modes
LDX_IMMEDIATE   = 0xA2,
LDX_ZEROPAGE    = 0xA6,
LDX_ZEROPAGEY   = 0xB6,
LDX_ABSOLUTE    = 0xAE,
LDX_ABSOLUTEY   = 0xBE,

    //LDY Instructions and address modes
LDY_IMMEDIATE   = 0xA0,
LDY_ZEROPAGE    = 0xA4,
LDY_ZEROPAGEX   = 0xB4,
LDY_ABSOLUTE    = 0XAC,
LDY_ABSOLUTEX   = 0XBC,
};
public:
    explicit cpu6502(RAM* memoryOnBus);

    void log();
    void TestRun(int numCycles);
    void Reset();
    void Cycle();
    byte FetchByte();
    byte ReadByte(word address);
    void setFlags(byte register);
private:


    RAM * m_MemoryBus;
//registers
word PC; //program counter
byte SP; // stack pointer
byte A; //accumulator
byte x;// index X register
byte y;// index Y register

byte Carry :1;
byte Zero :1;
byte Interupt :1;
byte Decimal :1;
byte Break :1;
byte overflow :1;
byte Negative :1;

byte instruction;
byte Value;
word Address;
word IndirectAddress;
int CyclesInInstruction;
};


#endif //INC_6502_CPU6502_H
