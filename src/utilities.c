#include "types.h"
#include "disassembler.h"
#include <stdio.h>
#include <stdlib.h>

void UnimplementedInstruction(State8080 *state) {
    printf("Error: Unimplemented instruction. Disassembly:\n");
    disassemble(state->memory, state->pc);
    printf("\n");
    exit(1);
}

uint16_t getPairValue(uint8_t high, uint8_t low) {
    return (uint16_t)((high << 8) | low);
}

int getParity(uint16_t value) {
    int parity = 1;

    while (value)
    {
        parity = 1 - parity;
        value &= (value - 1);
    }

    return parity;
}
