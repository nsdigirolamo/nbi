#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

typedef enum
{
    RIGHT,
    LEFT,
    INCREMENT,
    DECREMENT,
    OUTPUT,
    INPUT,
    LOOP_START,
    LOOP_END,
    NOP,
} Instruction;

Instruction getNextInstruction(char symbol);
char *InstructionToString(Instruction instruction);

#endif