#include "opcodes.h"
#include "utilities.h"

//TODO: Once things are working, have a function here to build a function pointer jump table in the order
//      of the opcode values. This will greatly simplify the emulator source file.

// ==============================================================
// ========================= Data group =========================
// ==============================================================
// Move register
void MOV_r_r(State8080 *state, uint8_t *r1, uint8_t *r2) {
    *r1 = *r2;

    state->cycles += 1;
    state->pc += 1;
}

// Move from memory
void MOV_r_M(State8080 *state, uint8_t *r) {
    *r = state->memory[getPairValue(state->h, state->l)];

    state->cycles += 2;
    state->pc += 1;
}

// Move to memory
void MOV_M_r(State8080 *state, uint8_t *r) {
    state->memory[getPairValue(state->h, state->l)] = *r;

    state->cycles += 2;
    state->pc += 1;
}

// Move immediate
void MVI_r_data(State8080 *state, uint8_t *r, uint8_t data) {
    *r = data;

    state->cycles += 2;
    state->pc += 2;
}

// Move to memory immediate
void MVI_M_data(State8080 *state, uint8_t data) {
    state->memory[getPairValue(state->h, state->l)] = data;

    state->cycles += 3;
    state->pc += 2;
}

// Load register pair immediate
void LXI_rp_data16(State8080 *state, uint8_t *rh, uint8_t *rl, uint8_t high, uint8_t low) {
    *rh = high;
    *rl = low;

    state->cycles += 3;
    state->pc += 3;
}

void LXI_sp_data16(State8080 *state, uint8_t high, uint8_t low) {
    state->sp = getPairValue(high, low);

    state->cycles += 3;
    state->pc += 3;
}

// Load accumulator direct
void LDA_addr(State8080 *state, uint8_t high, uint8_t low) {
    state->a = state->memory[getPairValue(high, low)];

    state->cycles += 4;
    state->pc += 3;
}

// Store accumulator direct
void STA_addr(State8080 *state, uint8_t high, uint8_t low) {
    state->memory[getPairValue(high, low)] = state->a;

    state->cycles += 4;
    state->pc += 3;
}

// Load H and L direct
void LHLD_addr(State8080 *state, uint8_t high, uint8_t low) {
    state->l = state->memory[getPairValue(high, low)];
    state->h = state->memory[getPairValue(high, low) + 1];

    state->cycles += 5;
    state->pc += 3;
}

// Store H and L direct
void SHLD_addr(State8080 *state, uint8_t high, uint8_t low) {
    state->memory[getPairValue(high, low)] = state->l;
    state->memory[getPairValue(high, low) + 1] = state->h;

    state->cycles += 5;
    state->pc += 3;
}

// Load accumulator indirect
void LDAX_rp(State8080 *state, uint8_t *rh, uint8_t *rl) {
    state->a = state->memory[getPairValue(*rh, *rl)];

    state->cycles += 2;
    state->pc += 1;
}

// Store accumulator indirect
void STAX_rp(State8080 *state, uint8_t *rh, uint8_t *rl) {
    state->memory[getPairValue(*rh, *rl)] = state->a;

    state->cycles += 2;
    state->pc += 1;
}

// Exchange H and L with D and E
void XCHG(State8080 *state) {
    uint8_t swap = state->h;
    state->h = state->d;
    state->d = swap;
    swap = state->l;
    state->l = state->e;
    state->e = swap;

    state->cycles += 1;
    state->pc += 1;
}

// ====================================================================
// ========================= Arithmetic group =========================
// ====================================================================
// Add register
void ADD_r(State8080 *state, uint8_t *r) {
    uint16_t result16 = (uint16_t)state->a + (uint16_t)*r;
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 1;
    state->pc += 1;
}

// Add memory
void ADD_M(State8080 *state) {
    uint16_t result16 = (uint16_t)state->a + (uint16_t)state->memory[getPairValue(state->h, state->l)];
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 2;
    state->pc += 1;
}

// Add immediate
void ADI_data(State8080 *state, uint8_t data) {
    uint16_t result16 = (uint16_t)state->a + (uint16_t)data;
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 2;
    state->pc += 2;
}

// Add register with carry
void ADC_r(State8080 *state, uint8_t *r) {
    uint16_t result16 = (uint16_t)state->a + (uint16_t)*r + (uint16_t)state->cc.cy;
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 1;
    state->pc += 1;
}

// Add memory with carry
void ADC_M(State8080 *state) {
    uint16_t result16 = (uint16_t)state->a + (uint16_t)state->memory[getPairValue(state->h, state->l)] + (uint16_t)state->cc.cy;
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 2;
    state->pc += 1;
}

// Add immediate with carry
void ACI_data(State8080 *state, uint8_t data) {
    uint16_t result16 = (uint16_t)state->a + (uint16_t)data + (uint16_t)state->cc.cy;
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 2;
    state->pc += 2;
}

// Subtract register
void SUB_r(State8080 *state, uint8_t *r) {
    uint16_t result16 = (uint16_t)state->a - (uint16_t)*r;
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 1;
    state->pc += 1;
}

// Subtract memory
void SUB_M(State8080 *state) {
    uint16_t result16 = (uint16_t)state->a - (uint16_t)state->memory[getPairValue(state->h, state->l)];
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 2;
    state->pc += 1;
}

// Subtract immediate
void SUI_data(State8080 *state, uint8_t data) {
    uint16_t result16 = (uint16_t)state->a - (uint16_t)data;
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 2;
    state->pc += 2;
}

// Subtract register with borrow
void SBB_r(State8080 *state, uint8_t *r) {
    uint16_t result16 = (uint16_t)state->a - (uint16_t)*r - (uint16_t)state->cc.cy;
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 1;
    state->pc += 1;
}

// Subtract memory with borrow
void SBB_M(State8080 *state) {
    uint16_t result16 = (uint16_t)state->a - (uint16_t)state->memory[getPairValue(state->h, state->l)] - (uint16_t)state->cc.cy;
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 2;
    state->pc += 1;
}

// Subtract immediate with borrow
void SBI_data(State8080 *state, uint8_t data) {
    uint16_t result16 = (uint16_t)state->a - (uint16_t)data - (uint16_t)state->cc.cy;
    state->cc.z = ((result16 & 0xff) == 0);
    state->cc.s = ((result16 & 0x80) != 0);
    state->cc.cy = (result16 > 0xff);
    state->cc.p = getParity(result16 & 0xff);
    state->a = result16 & 0xff;

    state->cycles += 2;
    state->pc += 2;
}

// Increment register
void INR_r(State8080 *state, uint8_t *r) {
    *r += 1;
    state->cc.z = ((state->b & 0xff) == 0);
    state->cc.s = ((state->b & 0x80) != 0);
    state->cc.p = getParity(state->b & 0xff);

    state->cycles += 1;
    state->pc += 1;
}

// Increment memory
void INR_M(State8080 *state) {
    state->memory[getPairValue(state->h, state->l)] += 1;
    state->cc.z = ((state->b & 0xff) == 0);
    state->cc.s = ((state->b & 0x80) != 0);
    state->cc.p = getParity(state->b & 0xff);

    state->cycles += 3;
    state->pc += 1;
}

// Decrement register
void DCR_r(State8080 *state, uint8_t *r) {
    *r -= 1;
    state->cc.z = ((state->b & 0xff) == 0);
    state->cc.s = ((state->b & 0x80) != 0);
    state->cc.p = getParity(state->b & 0xff);

    state->cycles += 1;
    state->pc += 1;
}

// Decrement memory
void DCR_M(State8080 *state) {
    state->memory[getPairValue(state->h, state->l)] -= 1;
    state->cc.z = ((state->b & 0xff) == 0);
    state->cc.s = ((state->b & 0x80) != 0);
    state->cc.p = getParity(state->b & 0xff);

    state->cycles += 3;
    state->pc += 1;
}

// Increment register pair
void INX_rp(State8080 *state, uint8_t *rh, uint8_t *rl) {
    uint16_t value = getPairValue(*rh, *rl) + 1;
    *rh = value >> 8;
    *rl = value & 0xff;

    state->cycles += 1;
    state->pc += 1;
}

// Dccrement register pair
void DCX_rp(State8080 *state, uint8_t *rh, uint8_t *rl) {
    uint16_t value = getPairValue(*rh, *rl) - 1;
    *rh = value >> 8;
    *rl = value & 0xff;

    state->cycles += 1;
    state->pc += 1;
}

// Add register pair to H and L
void DAD_rp(State8080 *state, uint8_t *rh, uint8_t *rl) {
    uint32_t value = (uint32_t)getPairValue(state->h, state->l) + (uint32_t)getPairValue(*rh, *rl);
    state->h = (value >> 8) & 0xff;
    state->l = value & 0xff;
    state->cc.cy = ((value & 0x10000) > 1);

    state->cycles += 3;
    state->pc += 1;
}

// Decimal adjust accumulator
void DAA(State8080 *state) {
    uint16_t value = (uint16_t)state->a;
    if (value & 0xf > 9 || state->cc.ac) {
        value += 6;
    } // TODO: We might have to set the carry flag between these IF statements
    if ((value >> 4) > 9 || state->cc.cy) {
        value += (6 << 4);
    }
    state->cc.z = ((value & 0xff) == 0);
    state->cc.s = ((value & 0x80) != 0);
    state->cc.p = getParity(value & 0xff);
    state->cc.cy = (value > 0xff);
    state->a = value & 0xff;

    state->cycles += 1;
    state->pc += 1;
}

// =================================================================
// ========================= Logical group =========================
// =================================================================
// AND register
void ANA_r(State8080 *state) {
    UnimplementedInstruction(state);
}

// AND memory
void ANA_M(State8080 *state) {
    UnimplementedInstruction(state);
}

// AND immediate
void ANI_data(State8080 *state) {
    UnimplementedInstruction(state);
}

// Exclusive OR register
void XRA_r(State8080 *state) {
    UnimplementedInstruction(state);
}

// Exclusive OR memory
void XRA_M(State8080 *state) {
    UnimplementedInstruction(state);
}

// Exclusive OR immediate
void XRI_data(State8080 *state) {
    UnimplementedInstruction(state);
}

// OR register
void ORA_r(State8080 *state) {
    UnimplementedInstruction(state);
}

// OR memory
void ORA_M(State8080 *state) {
    UnimplementedInstruction(state);
}

// OR immediate
void ORI_data(State8080 *state) {
    UnimplementedInstruction(state);
}

// Compare register
void CMP_r(State8080 *state) {
    UnimplementedInstruction(state);
}

// Compare memory
void CMP_M(State8080 *state) {
    UnimplementedInstruction(state);
}

// Compare immediate
void CPI_data(State8080 *state) {
    UnimplementedInstruction(state);
}

// Rotate left
void RLC(State8080 *state) {
    UnimplementedInstruction(state);
}

// Rotate right
void RRC(State8080 *state) {
    UnimplementedInstruction(state);
}

// Rotate left through carry
void RAL(State8080 *state) {
    UnimplementedInstruction(state);
}

// Rotate right through carry
void RAR(State8080 *state) {
    UnimplementedInstruction(state);
}

// Complement accumulator
void CMA(State8080 *state) {
    UnimplementedInstruction(state);
}

// Complement carry
void CMC(State8080 *state) {
    state->cc.cy = (uint8_t)~(state->cc.cy);

    state->cycles += 1;
    state->pc += 1;
}

// Set carry
void STC(State8080 *state) {
    state->cc.cy = 1;

    state->cycles += 1;
    state->pc += 1;
}


// ================================================================
// ========================= Branch group =========================
// ================================================================
// (Conditional) jump
void JMP(State8080 *state, uint8_t high, uint8_t low, bool jmp) {
    if (jmp) {
        state->pc = getPairValue(high, low);
    } else {
        state->pc += 3;
    }

    state->cycles += 3;
}

// (Conditional) call
void CALL(State8080 *state, uint8_t high, uint8_t low, bool call) {
    if (call) {
        state->memory[state->sp - 1] = state->pc >> 8;
        state->memory[state->sp - 2] = state->pc & 0xff;
        state->sp -= 2;
        state->pc = getPairValue(high, low);
        state->cycles += 5;
    } else {
        state->cycles += 3;
        state->pc += 3;
    }
}

// (Conditional) return
void RET(State8080 *state, bool ret) {
    if (ret) {
        state->pc = (uint16_t)(state->memory[state->sp + 1] << 8) | (state->memory[state->sp]);
        state->sp += 2;
        state->cycles += 3;
    } else {
        state->cycles += 1;
        state->pc += 1;
    }
}

// Restart
void RST_n(State8080 *state, int n) {
    state->memory[state->sp - 1] = state->pc >> 8;
    state->memory[state->sp - 2] = state->pc & 0xff;
    state->sp -= 2;
    state->pc = 8 * n;

    state->cycles += 3;
}

// Jump H and L indirect - move H and L to PC
void PCHL(State8080 *state) {
    state->pc = getPairValue(state->h, state->l);

    state->cycles += 1;
}

// =========================================================================================
// ========================= Stack, I/O, and Machine Control group =========================
// =========================================================================================
// Push
void PUSH_rp(State8080 *state) {
    UnimplementedInstruction(state);
}

// Push processor status word
void PUSH_PSW(State8080 *state) {
    UnimplementedInstruction(state);
}

// Pop
void POP_rp(State8080 *state) {
    UnimplementedInstruction(state);
}

// Pop processor status word
void POP_PSW(State8080 *state) {
    UnimplementedInstruction(state);
}

// Exchange stack top with H and L
void XTHL(State8080 *state) {
    UnimplementedInstruction(state);
}

// Move HL to SP
void SPHL(State8080 *state) {
    UnimplementedInstruction(state);
}

// Input
void IN_port(State8080 *state) {
    UnimplementedInstruction(state);
}

// Output
void OUT_port(State8080 *state) {
    UnimplementedInstruction(state);
}

// Enable interrupts
void EI(State8080 *state) {
    UnimplementedInstruction(state);
}

// Disable interrupts
void DI(State8080 *state) {
    UnimplementedInstruction(state);
}

// Halt
void HLT(State8080 *state) {
    UnimplementedInstruction(state);
}

// No op
void NOP(State8080 *state) {
    state->cycles += 4;
    state->pc += 1;
}
