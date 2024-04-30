#ifndef UTILITIES_H
#define UTILITIES_H

void UnimplementedInstruction(State8080 *state);

uint16_t getPairValue(uint8_t high, uint8_t low);

int getParity(uint16_t value);

#endif // UTILITIES_H
