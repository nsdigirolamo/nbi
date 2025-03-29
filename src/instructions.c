#include "instructions.h"

Instruction charToInstruction(char character)
{
    switch (character)
    {
    case '>':
        return RIGHT;
    case '<':
        return LEFT;
    case '+':
        return INCREMENT;
    case '-':
        return DECREMENT;
    case '.':
        return OUTPUT;
    case ',':
        return INPUT;
    case '[':
        return LOOP_START;
    case ']':
        return LOOP_END;
    default:
        return NOP;
    }
}

char *instructionToString(Instruction instruction)
{
    switch (instruction)
    {
    case RIGHT:
        return "RIGHT";
    case LEFT:
        return "LEFT";
    case INCREMENT:
        return "INCREMENT";
    case DECREMENT:
        return "DECREMENT";
    case OUTPUT:
        return "OUTPUT";
    case INPUT:
        return "INPUT";
    case LOOP_START:
        return "LOOP_START";
    case LOOP_END:
        return "LOOP_END";
    case NOP:
        return "NOP";
    default:
        return "INVALID_INSTRUCTION";
    }
}