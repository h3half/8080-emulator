#ifndef OPCODES_H
#define OPCODES_H

#include "types.h"
#include <stdbool.h>

// Data Transfer group
void MOV_r_r(State8080 *state, uint8_t *r1, uint8_t *r2);
void MOV_r_M(State8080 *state, uint8_t *r);
void MOV_M_r(State8080 *state, uint8_t *r);
void MVI_r_data(State8080 *state, uint8_t *r, uint8_t data);
void MVI_M_data(State8080 *state, uint8_t data);
void LXI_rp_data16(State8080 *state, uint8_t *rh, uint8_t *rl, uint8_t high, uint8_t low);
void LXI_sp_data16(State8080 *state, uint8_t high, uint8_t low);
void LDA_addr(State8080 *state, uint8_t high, uint8_t low);
void STA_addr(State8080 *state, uint8_t high, uint8_t low);
void LHLD_addr(State8080 *state, uint8_t high, uint8_t low);
void SHLD_addr(State8080 *state, uint8_t high, uint8_t low);
void LDAX_rp(State8080 *state, uint8_t *rh, uint8_t *rl);
void STAX_rp(State8080 *state, uint8_t *rh, uint8_t *rl);
void XCHG(State8080 *state);

// Arithmetic group
void ADD_r(State8080 *state, uint8_t *r);
void ADD_M(State8080 *state);
void ADI_data(State8080 *state, uint8_t data);
void ADC_r(State8080 *state, uint8_t *r);
void ADC_M(State8080 *state);
void ACI_data(State8080 *state, uint8_t data);
void SUB_r(State8080 *state, uint8_t *r);
void SUB_M(State8080 *state);
void SUI_data(State8080 *state, uint8_t data);
void SBB_r(State8080 *state, uint8_t *r);
void SBB_M(State8080 *state);
void SBI_data(State8080 *state, uint8_t data);
void INR_r(State8080 *state, uint8_t *r);
void INR_M(State8080 *state);
void DCR_r(State8080 *state, uint8_t *r);
void DCR_M(State8080 *state);
void INX_rp(State8080 *state, uint8_t *rh, uint8_t *rl);
void DCX_rp(State8080 *state, uint8_t *rh, uint8_t *rl);
void DAD_rp(State8080 *state, uint8_t *rh, uint8_t *rl);
void DAA(State8080 *state);

// Logical group
void ANA_r(State8080 *state);
void ANA_M(State8080 *state);
void ANI_data(State8080 *state);
void XRA_r(State8080 *state);
void XRA_M(State8080 *state);
void XRI_data(State8080 *state);
void ORA_r(State8080 *state);
void ORA_M(State8080 *state);
void ORI_data(State8080 *state);
void CMP_r(State8080 *state);
void CMP_M(State8080 *state);
void CPI_data(State8080 *state);
void RLC(State8080 *state);
void RRC(State8080 *state);
void RAL(State8080 *state);
void RAR(State8080 *state);
void CMA(State8080 *state);
void CMC(State8080 *state);
void STC(State8080 *state);

// Branch group
void JMP(State8080 *state, uint8_t high, uint8_t low, bool jmp);
void CALL(State8080 *state, uint8_t high, uint8_t low, bool call);
void RET(State8080 *state, bool ret);
void RST_n(State8080 *state, int n);
void PCHL(State8080 *state);

// Stack, I/O, and Machine Control group
void PUSH_rp(State8080 *state);
void PUSH_PSW(State8080 *state);
void POP_rp(State8080 *state);
void POP_PSW(State8080 *state);
void XTHL(State8080 *state);
void SPHL(State8080 *state);
void IN_port(State8080 *state);
void OUT_port(State8080 *state);
void EI(State8080 *state);
void DI(State8080 *state);
void HLT(State8080 *state);
void NOP(State8080 *state);

#endif // OPCODES_H
