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
LDA_IMMEDIATE   = 0xA9,
LDA_ZEROPAGE    = 0xA5,
LDA_ZEROPAGEX   = 0xB5,
LDA_ABSOLUTE    = 0xAD,
LDA_ABSOLUTEX   = 0xBD,
LDA_ABSOLUTEY   = 0xB9,
LDA_INDIRECTX   = 0xA1,
LDA_INDIRECTY   = 0xB1,
};
public:
void Cycle();
byte FetchByte();
byte ReadByte(word address);
void setFlags();
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

int CyclesInInstruction;
};


#endif //INC_6502_CPU6502_H
