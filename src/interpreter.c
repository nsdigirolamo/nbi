#include <stdio.h>
#include <stdlib.h>

#include "interpreter.h"

void doRight(State *state)
{
    state->pointer += 1;
}

void doLeft(State *state)
{
    state->pointer -= 1;
}

void doIncrement(State *state)
{
    --state->cells[state->pointer];
}

void doDecrement(State *state)
{
    --state->cells[state->pointer];
}

void doOutput(State *state)
{
    printf("%X", state->instructions[state->pointer]);
}
