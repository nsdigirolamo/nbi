#include <stdio.h>
#include <stdlib.h>

#include "interpreter.h"

void advanceToNextLoopEnd(State *state);
void retreatToPreviousLoopStart(State *state);

Instruction getCurrentInstruction(State *state)
{
    return state->instructions[state->instructionPointer];
}

uint8_t getCurrentCell(State *state)
{
    return state->cells[state->cellPointer];
}

void setCurrentCell(State *state, uint8_t newValue)
{
    state->cells[state->cellPointer] = newValue;
}

void printState(State *state)
{
    Instruction currentInstruction = getCurrentInstruction(state);
    uint8_t currentCellValue = getCurrentCell(state);
    printf("Instruction: %9s %d\n", instructionToString(currentInstruction), state->instructionPointer);
    printf("Cell       : %9d %d\n", currentCellValue, state->cellPointer);
    fflush(stdout);
}

void doRight(State *state)
{
    state->cellPointer += 1;
}

void doLeft(State *state)
{
    state->cellPointer -= 1;
}

void doIncrement(State *state)
{
    uint8_t currentValue = getCurrentCell(state);
    setCurrentCell(state, currentValue + 1);
}

void doDecrement(State *state)
{
    uint8_t currentValue = getCurrentCell(state);
    setCurrentCell(state, currentValue - 1);
}

void doOutput(State *state)
{
    printf("%c", (char)(getCurrentCell(state)));
}

void doInput(State *state)
{
    uint8_t input = (uint8_t)(getchar());
    setCurrentCell(state, input);
}

void doLoopStart(State *state)
{
    if (state->cells[state->cellPointer] == 0)
    {
        advanceToNextLoopEnd(state);
    }
}

void doLoopEnd(State *state)
{
    if (state->cells[state->cellPointer] != 0)
    {
        retreatToPreviousLoopStart(state);
    }
}

/**
 * Advances the state's `instructionPointer` to the first unpaired `LOOP_END`
 * it can find.
 */
void advanceToNextLoopEnd(State *state)
{
    int loopStartCount = 1;
    while (0 < loopStartCount)
    {
        state->instructionPointer += 1;
        Instruction instruction = getCurrentInstruction(state);

        if (instruction == LOOP_START)
        {
            loopStartCount += 1;
        }
        else if (instruction == LOOP_END)
        {
            loopStartCount -= 1;
        }
    }
}

/**
 * Retreats the state's `instructionPointer` to the first unpaired `LOOP_START`
 * it can find.
 */
void retreatToPreviousLoopStart(State *state)
{
    int loopEndCount = 1;
    while (0 < loopEndCount)
    {
        state->instructionPointer -= 1;
        Instruction instruction = getCurrentInstruction(state);

        if (instruction == LOOP_END)
        {
            loopEndCount += 1;
        }
        else if (instruction == LOOP_START)
        {
            loopEndCount -= 1;
        }
    }
}
