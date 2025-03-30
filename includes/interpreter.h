#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdint.h>

#include "instructions.h"

typedef struct
{
    const Instruction *const instructions;
    unsigned int instructionPointer;
    uint8_t *cells;
    unsigned int cellPointer;
} State;

Instruction getCurrentInstruction(State *state);
uint8_t getCurrentCell(State *state);
void setCurrentCell(State *state, uint8_t newValue);
void printState(State *state);

void doRight(State *state);
void doLeft(State *state);
void doIncrement(State *state);
void doDecrement(State *state);
void doOutput(State *state);
void doInput(State *state);
void doLoopStart(State *state);
void doLoopEnd(State *state);

#endif
