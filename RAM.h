//
// Created by alice on 14/12/2020.
//

#ifndef INC_6502_RAM_H
#define INC_6502_RAM_H
#include "vector"
#include "cpu6502.h"


class RAM {
public:
    RAM(int amountOfRam): ram(amountOfRam)
    {
    }

    byte readByte(word address)
    {
        return ram.at(address);
    }
    void writeByte(word address, byte data)
    {
        ram.at(address) = data;
    }
private:
    std::vector<byte> ram;

};


#endif //INC_6502_RAM_H
