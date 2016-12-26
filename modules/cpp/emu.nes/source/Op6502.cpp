/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include <stdexcept>
#include <nyra/emu/nes/Op6502.h>

namespace nyra
{
namespace emu
{
namespace nes
{
//===========================================================================//
OpNUL::OpNUL(uint8_t opCode) :
    OpCode("NUL", "Null Opcode", opCode,
           0, 0, new ModeImplied())
{
}

//===========================================================================//
void OpNUL::op(CPURegisters& ,
               CPUInfo& ,
               MemoryMap& )
{
    throw std::runtime_error("Attempting to run null op");
}

//===========================================================================//
OpLSR<ModeAccumulator>::OpLSR(uint8_t opcode, uint8_t length, uint8_t time) :
    OpCode("LSR", "Logical shift right",
           opcode, length, time, new ModeAccumulator())
{
}

//===========================================================================//
OpASL<ModeAccumulator>::OpASL(uint8_t opcode, uint8_t length, uint8_t time) :
    OpCode("ASL", "Arithmetic shift left",
           opcode, length, time, new ModeAccumulator())
{
}

//===========================================================================//
OpROR<ModeAccumulator>::OpROR(uint8_t opcode, uint8_t length, uint8_t time) :
    OpCode("ROR", "Rotate right",
           opcode, length, time, new ModeAccumulator())
{
}

//===========================================================================//
OpROL<ModeAccumulator>::OpROL(uint8_t opcode, uint8_t length, uint8_t time) :
    OpCode("ROL", "Rotate left",
           opcode, length, time, new ModeAccumulator())
{
}

//===========================================================================//
OpJSR::OpJSR() :
    OpCode("JSR", "Jump to subroutine",
           0x20, 0, 6, new ModeAbsolute<false>())
{
}

//===========================================================================//
OpJMI::OpJMI() :
    OpCode("JMI", "Jump to interrupt, NYRA created",
           0x00, 0, 6, new ModeAbsolute<false>())
{
}

//===========================================================================//
OpNOP::OpNOP() :
    OpCode("NOP", "No operation",
           0xEA, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpRTI::OpRTI() :
    OpCode("RTI", "Return from interrupt",
           0x40, 0, 6, new ModeImplied())
{
}

//===========================================================================//
OpINY::OpINY() :
    OpCode("INY", "Increment Y",
           0xC8, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpINX::OpINX() :
    OpCode("INX", "Increment X",
           0xC8, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpDEY::OpDEY() :
    OpCode("DEY", "Decrement Y",
           0x88, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpDEX::OpDEX() :
    OpCode("DEX", "Decrement X",
           0xCA, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpTAX::OpTAX() :
    OpCode("TAX", "Transfer A to X",
           0xAA, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpTXA::OpTXA() :
    OpCode("TXA", "Transfer X to A",
           0x8A, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpTAY::OpTAY() :
    OpCode("TAY", "Transfer A to Y",
           0xA8, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpTYA::OpTYA() :
    OpCode("TYA", "Transfer Y to A",
           0x98, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpSEC::OpSEC() :
    OpCode("SEC", "Set carry",
           0x38, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpCLC::OpCLC() :
    OpCode("CLC", "Clear carry",
           0x18, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpCLV::OpCLV() :
    OpCode("CLV", "Clear overflow",
           0xB8, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpSEI::OpSEI() :
    OpCode("SEI", "Set interrupt",
           0x78, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpSED::OpSED() :
    OpCode("SED", "Set decimal",
           0xF8, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpCLD::OpCLD() :
    OpCode("CLD", "Clear decimal",
           0xD8, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpTSX::OpTSX() :
    OpCode("TSX", "Transfer stack ptr to X",
           0xBA, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpTXS::OpTXS() :
    OpCode("TXS", "Transfer X to stack ptr",
           0x9A, 1, 2, new ModeImplied())
{
}

//===========================================================================//
OpPLA::OpPLA() :
    OpCode("PLA", "Pull accumulator",
           0x68, 1, 4, new ModeImplied())
{
}

//===========================================================================//
OpPHA::OpPHA() :
    OpCode("PHA", "Push accumulator",
           0x48, 1, 3, new ModeImplied())
{
}

//===========================================================================//
OpPLP::OpPLP() :
    OpCode("PLP", "Pull processor status",
           0x28, 1, 4, new ModeImplied())
{
}

//===========================================================================//
OpPHP::OpPHP() :
    OpCode("PHP", "Push processor status",
           0x08, 1, 3, new ModeImplied())
{
}

//===========================================================================//
OpBCS::OpBCS() : OpBranch("BCS", "Branch on carry set", 0xB0)
{
}

//===========================================================================//
OpBEQ::OpBEQ() : OpBranch("BEQ", "Branch on equal", 0xF0)
{
}

//===========================================================================//
OpBNE::OpBNE() : OpBranch("BNE", "Branch on not equal", 0xD0)
{
}

//===========================================================================//
OpBCC::OpBCC() : OpBranch("BCC", "Branch on carry clear", 0x90)
{
}

//===========================================================================//
OpBVS::OpBVS() : OpBranch("BVS", "Branch on overflow set", 0x70)
{
}

//===========================================================================//
OpBVC::OpBVC() : OpBranch("BVC", "Branch on overflow clear",0x50)
{
}

//===========================================================================//
OpBPL::OpBPL() : OpBranch("BPL", "Branch on plus", 0x10)
{
}

//===========================================================================//
OpBMI::OpBMI() : OpBranch("BMI", "Branch on minus", 0x30)
{
}
}
}
}
