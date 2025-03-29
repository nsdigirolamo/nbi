#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdint.h>

#include "instructions.h"

typedef struct
{
    const Instruction *const instructions;
    uint8_t *cells;
    size_t pointer;
} State;

void doRight(State *state);
void doLeft(State *state);
void doIncrement(State *state);
void doDecrement(State *state);
void doOutput(State *state);
void doInput(State *state);
void doLoopStart(State *state);
void doLoopEnd(State *state);

#endif