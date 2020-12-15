//
// Created by alice on 14/12/2020.
//

#include "cpu6502.h"
#include "RAM.h"
#include <iostream>
cpu6502::cpu6502(RAM* memoryOnBus): m_MemoryBus(memoryOnBus) {

}

void cpu6502::Cycle() {
    Address = 0;
    Value  = 0;
    instruction = FetchByte();
switch(instruction)
{
    case(JMP_ABSOLUTE):
    {
        //3 cycles to perform
      byte loAdd = FetchByte();
      byte hiAdd = FetchByte();
      Address = (loAdd & 0xFF) | (hiAdd <<8);
      PC = Address;
      CyclesInInstruction --;
    }break;
    case(JMP_INDIRECT):
    {
        byte loAdd = FetchByte();
        byte hiAdd = FetchByte();
        if(loAdd == 0xFF)
        {
            hiAdd = 0x00;
        }
        word ResultAddress = (loAdd & 0xFF) | (hiAdd <<8);

        loAdd = ReadByte(ResultAddress);
        hiAdd = ReadByte(ResultAddress + 1);

        Address = (loAdd & 0xFF) | (hiAdd <<8);
        PC = Address;
        CyclesInInstruction--;

    }break;



    case(LDA_IMMEDIATE):
    {
       //2 cycles in instruction
       Value = FetchByte();
       A = Value;
       setFlags(A);
       CyclesInInstruction --;
    }break;
    case(LDA_ZEROPAGE):
    {
       //3 cycles in instruction
       byte ZeroPageAddress = FetchByte();
       Value = ReadByte(ZeroPageAddress);
       A = Value;
       setFlags(A);
       CyclesInInstruction --;
    }break;
    case(LDA_ZEROPAGEX):
    {
        //4 cycles in instruction
        byte ZeroPageAddress = FetchByte();
        ZeroPageAddress += x;
        CyclesInInstruction --;

        Value = ReadByte(ZeroPageAddress);
        A = Value;
        setFlags(A);
        CyclesInInstruction --;
    }break;
    case(LDA_ABSOLUTE):
        {
        //4 cycles in instruction
        byte loAdd = FetchByte();
        byte hiAdd = FetchByte();
        Address = (loAdd & 0xFF) | (hiAdd << 8);
        CyclesInInstruction --;
        Value = ReadByte(Address);
        A = Value;
        setFlags(A);
        CyclesInInstruction --;
    }break;
    case(LDA_ABSOLUTEX):
    {
        //4 or 5 cycles in instruction
        byte loAdd = FetchByte();
        byte hiAdd = FetchByte();
        Address = (loAdd & 0xFF) | (hiAdd << 8);
        if((Address ^ (Address + x ) >> 8 )== 1)
        {
            CyclesInInstruction--;
        }
        Address+= x;
        CyclesInInstruction --;
        Value = ReadByte(Address);
        A = Value;
        setFlags(A);
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
        Address = (loAdd & 0xFF) | (hiAdd << 8);
        Address+= y;
        CyclesInInstruction --;
        Value = ReadByte(Address);
        A = Value;
        setFlags(A);
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
        Value = ReadByte(Address);
        A = Value;
        setFlags(A);
        CyclesInInstruction --;
    }break;
    case(LDA_INDIRECTY):
    {
        byte ZeroPage = FetchByte();
        byte loAdd = ReadByte(ZeroPage);
        byte hiAdd = ReadByte(ZeroPage +1);

        Address = (loAdd & 0xFF) | (hiAdd << 8);
        if((Address ^ (Address + y) >> 8 )== 1)
            CyclesInInstruction--;
        Value = ReadByte(Address +y);
        A = Value;
        setFlags(A);
        CyclesInInstruction--;
    }break;


    case(LDX_IMMEDIATE):
    {
        //2 cycles in instruction
        Value = FetchByte();
        x = Value;
        setFlags(x);
        CyclesInInstruction--;
    } break;
    case(LDX_ZEROPAGE):
    {
        //3 cycles in instruction
        byte ZeroPageAddress = FetchByte();
        Value = ReadByte(ZeroPageAddress);
        x = Value;
        setFlags(x);
        CyclesInInstruction --;
    }break;
    case(LDX_ZEROPAGEY):
    {
        //4 cycles in instruction
        byte ZeroPageAddress = FetchByte();
        ZeroPageAddress += y;
        CyclesInInstruction --;

        Value = ReadByte(ZeroPageAddress);
        x = Value;
        setFlags(x);
        CyclesInInstruction --;


    }break;
    case(LDX_ABSOLUTE):
    {
        //4 cycles in instruction
        byte loAdd = FetchByte();
        byte hiAdd = FetchByte();
        Address = (loAdd & 0xFF) | (hiAdd << 8);
        CyclesInInstruction --;
        Value = ReadByte(Address);
        x = Value;
        setFlags(x);
        CyclesInInstruction --;
    }break;
    case(LDX_ABSOLUTEY):
    {
        //4 or 5 cycles in instruction
        byte loAdd = FetchByte();
        byte hiAdd = FetchByte();
        Address = (loAdd & 0xFF) | (hiAdd << 8);
        if((Address ^ (Address + y) >> 8 )== 1)
        {
            CyclesInInstruction--;
        }
        Address+= y;
        CyclesInInstruction --;
        Value = ReadByte(Address);
        x = Value;
        setFlags(x);
        CyclesInInstruction --;
    }break;


    case(LDY_IMMEDIATE):
    {
        //2 cycles in instruction
        Value = FetchByte();
        y = Value;
        setFlags(y);
        CyclesInInstruction--;
    } break;
    case(LDY_ZEROPAGE):
    {
        //3 cycles in instruction
        byte ZeroPageAddress = FetchByte();
        Value = ReadByte(ZeroPageAddress);
        y = Value;
        setFlags(y);
        CyclesInInstruction --;
    }break;
    case(LDY_ZEROPAGEX):
    {
        //4 cycles in instruction
        byte ZeroPageAddress = FetchByte();
        ZeroPageAddress += x;
        CyclesInInstruction --;

        byte Value = ReadByte(ZeroPageAddress);
        y = Value;
        setFlags(y);
        CyclesInInstruction --;


    }break;
    case(LDY_ABSOLUTE):
    {
        //4 cycles in instruction
        byte loAdd = FetchByte();
        byte hiAdd = FetchByte();
        Address = (loAdd & 0xFF) | (hiAdd << 8);
        CyclesInInstruction --;
        Value = ReadByte(Address);
        y = Value;
        setFlags(y);
        CyclesInInstruction --;
    }break;
    case(LDY_ABSOLUTEX):
    {
        //4 or 5 cycles in instruction
        byte loAdd = FetchByte();
        byte hiAdd = FetchByte();
        Address = (loAdd & 0xFF) | (hiAdd << 8);
        if((Address ^ (Address + x) >> 8 )== 1)
        {
            CyclesInInstruction--;
        }
        Address+= x;
        CyclesInInstruction --;
        Value = ReadByte(Address);
        y = Value;
        setFlags(y);
        CyclesInInstruction --;
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
void cpu6502::setFlags(byte reg)
{
    Zero = (reg == 0);

    Negative = (reg & 0b10000000);
}

void cpu6502::Reset() {
  A = x = y = 0;
  SP = 0;

  PC = 0xFFFC;
}

void cpu6502::TestRun(int numCycles) {
    CyclesInInstruction = numCycles;
    while(CyclesInInstruction > 0)
    {
        Cycle();
        log();
    }
}

void cpu6502::log()
{

    switch(instruction)
    {
        case(JMP_INDIRECT):
        case(JMP_ABSOLUTE):
        {
            std::cout <<"JMP " << std::hex << Address << std::endl ;
        }break;

        case(LDA_IMMEDIATE):
        case(LDA_ZEROPAGE ):
        case(LDA_ZEROPAGEX):
        case(LDA_ABSOLUTE ):
        case(LDA_ABSOLUTEX):
        case(LDA_ABSOLUTEY):
        case(LDA_INDIRECTX):
        case(LDA_INDIRECTY):
        {
            std::cout <<"LDA " << std::hex <<(int) Value << std::endl ;
        }break;


        case(LDX_IMMEDIATE):
        case(LDX_ZEROPAGE ):
        case(LDX_ZEROPAGEY):
        case(LDX_ABSOLUTE ):
        case(LDX_ABSOLUTEY):
        {
            std::cout <<"LDX " << std::hex <<(int) Value << std::endl;
        }break;
        case(LDY_IMMEDIATE):
        case(LDY_ZEROPAGE ):
        case(LDY_ZEROPAGEX):
        case(LDY_ABSOLUTE ):
        case(LDY_ABSOLUTEX):
        {
            std::cout <<"LDY " << std::hex <<(int) Value << std::endl;
        }break;
    }
    std::cout << "address used: " << std::hex << Address << std::endl;
    std::cout << "registers" <<std::endl
    << "A: " << std::hex << (int)A << " "
    << "X: " << std::hex << (int)x << " "
    << "y: " << std::hex << (int)y << std::endl;
}



