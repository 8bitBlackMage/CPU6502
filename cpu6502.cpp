//
// Created by alice on 14/12/2020.
//

#include "cpu6502.h"
#include "RAM.h"
void cpu6502::Cycle() {
byte instruction = FetchByte();
switch(instruction)
{
    case(LDA_IMMEDIATE):
    {
       //2 cycles in instruction
       byte Value = FetchByte();
       A = Value;
       setFlags();
       CyclesInInstruction --;
    }break;
    case(LDA_ZEROPAGE):
    {
       //3 cycles in instruction
       byte ZeroPageAddress = FetchByte();
       byte Value = ReadByte(ZeroPageAddress);
       A = Value;
       setFlags();
       CyclesInInstruction --;
    }break;
    case(LDA_ZEROPAGEX):
    {
        //4 cycles in instruction
        byte ZeroPageAddress = FetchByte();
        ZeroPageAddress += x;
        CyclesInInstruction --;

        byte Value = ReadByte(ZeroPageAddress);
        A = Value;
        setFlags();
        CyclesInInstruction --;
    }break;
    case(LDA_ABSOLUTE):
        {
        //4 cycles in instruction
        byte loAdd = FetchByte();
        byte hiAdd = FetchByte();
        word Address = (loAdd & 0xFF) | (hiAdd << 8);
        CyclesInInstruction --;
        byte Value = ReadByte(Address);
        A = Value;
        setFlags();
        CyclesInInstruction --;
    }break;
    case(LDA_ABSOLUTEX):
    {
        //4 or 5 cycles in instruction
        byte loAdd = FetchByte();
        byte hiAdd = FetchByte();

        word Address = (loAdd & 0xFF) | (hiAdd << 8);
        if((Address ^ (Address + x ) >> 8 )== 1)
        {
            CyclesInInstruction--;
        }
        Address+= x;
        CyclesInInstruction --;
        byte Value = ReadByte(Address);
        A = Value;
        setFlags();
        CyclesInInstruction --;

    }break;
    case(LDA_ABSOLUTEY):
    {
        //4 or 5 cycles in instruction
        byte loAdd = FetchByte();
        byte hiAdd = FetchByte();
        if(loAdd + y > 255)
        {
            CyclesInInstruction--;
        }
        word Address = (loAdd & 0xFF) | (hiAdd << 8);
        Address+= y;
        CyclesInInstruction --;
        byte Value = ReadByte(Address);
        A = Value;
        setFlags();
        CyclesInInstruction --;

    }break;
    case(LDA_INDIRECTX):
    {
        byte ZeroPage = FetchByte();
        ZeroPage += x;
        CyclesInInstruction --;
        byte loAdd = ReadByte(ZeroPage);
        byte hiAdd = ReadByte(ZeroPage +1);
        word Address = (loAdd & 0xFF) | (hiAdd << 8);
        A = ReadByte(Address);
        setFlags();
        CyclesInInstruction --;
    }break;
    case(LDA_INDIRECTY):
    {
        byte ZeroPage = FetchByte();
        byte loAdd = ReadByte(ZeroPage);
        byte hiAdd = ReadByte(ZeroPage +1);

        word Address = (loAdd & 0xFF) | (hiAdd << 8);
        if((Address ^ (Address + y) >> 8 )== 1)
            CyclesInInstruction--;

        A = ReadByte(Address +y);
        CyclesInInstruction--;
    }break;
}


}

byte cpu6502::FetchByte() {
    byte data = m_MemoryBus->readByte(PC);
    PC++;
    CyclesInInstruction --;
    return data;
}
byte cpu6502::ReadByte(word address) {
byte data = m_MemoryBus->readByte(address);
CyclesInInstruction --;
return data;
}
void cpu6502::setFlags() {

    Zero = (A == 0);

    Negative = (A & 0b10000000);
}


