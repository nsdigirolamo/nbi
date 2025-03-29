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
    HALT,
    NOP,
} Instruction;

Instruction charToInstruction(char symbol);
char *instructionToString(Instruction instruction);

#endif