#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utilities.h"
#include "disassembler.h"
#include "opcodes.h"

#define FILESIZE 8192

int Emulate8080Op(State8080 *state) {
    unsigned char *opcode = &(state->memory[state->pc]);

    switch (*opcode) {
        case 0x00: // NOP
            NOP(state);
            break;
        case 0x01: // LXI B, D16
            LXI_rp_data16(state, &(state->b), &(state->c), opcode[2], opcode[1]);
            break;
        case 0x02: // STAX B
            STAX_rp(state, &(state->b), &(state->c));
            break;
        case 0x03: // INX B
            INX_rp(state, &(state->b), &(state->c));
            break;
        case 0x04: // INR B
            INR_r(state, &(state->b));
            break;
        case 0x05: // DCR B
            DCR_r(state, &(state->b));
            break;
        case 0x06: // MVI B, D8
            MVI_r_data(state, &(state->b), opcode[1]);
            break;
        case 0x07: // RLC
            RLC(state);
            break;
        case 0x09: // DAD B
            DAD_rp(state, &(state->b), &(state->c));
            break;
        case 0x0a: // LDAX B
            LDAX_rp(state, &(state->b), &(state->c));
            break;
        case 0x0b: // DCX B
            DCX_rp(state, &(state->b), &(state->c));
            break;
        case 0x0c: // INR C
            INR_r(state, &(state->c));
            break;
        case 0x0d: // DCR C
            DCR_r(state, &(state->c));
            break;
        case 0x0e: // MVI C, D8
            MVI_r_data(state, &(state->c), opcode[1]);
            break;
        case 0x0f: // RRC
            RRC(state);
            break;
        case 0x11: // LXI D, D16
            LXI_rp_data16(state, &(state->d), &(state->e), opcode[2], opcode[1]);
            break;
        case 0x12: // STAX D
            STAX_rp(state, &(state->d), &(state->e));
            break;
        case 0x13: // INX D
            INX_rp(state, &(state->d), &(state->e));
            break;
        case 0x14: // INR D
            INR_r(state, &(state->d));
            break;
        case 0x15: // DCR D
            DCR_r(state, &(state->d));
            break;
        case 0x16: // MVI D, D8
            MVI_r_data(state, &(state->d), opcode[1]);
            break;
        case 0x17: // RAL
            RAL(state);
            break;
        case 0x19: // DAD D
            DAD_rp(state, &(state->d), &(state->e));
            break;
        case 0x1a: // LDAX D
            LDAX_rp(state, &(state->d), &(state->e));
            break;
        case 0x1b: // DCX D
            DCX_rp(state, &(state->d), &(state->e));
            break;
        case 0x1c: // INR E
            INR_r(state, &(state->e));
            break;
        case 0x1d: // DCR E
            DCR_r(state, &(state->e));
            break;
        case 0x1e: // MVI E, D8
            MVI_r_data(state, &(state->e), opcode[1]);
            break;
        case 0x1f: // RAR
            RAR(state);
            break;
        case 0x21: // LXI H, D16
            LXI_rp_data16(state, &(state->h), &(state->l), opcode[2], opcode[1]);
            break;
        case 0x22: // SHLD adr
            SHLD_addr(state, opcode[2], opcode[1]);
            break;
        case 0x23: // INX H
            INX_rp(state, &(state->h), &(state->l));
            break;
        case 0x24: // INR H
            INR_r(state, &(state->h));
            break;
        case 0x25: // DCR H
            DCR_r(state, &(state->h));
            break;
        case 0x26: // MVI H, D8
            MVI_r_data(state, &(state->h), opcode[1]);
            break;
        case 0x27: // DAA
            DAA(state);
            break;
        case 0x29: // DAD H
            DAD_rp(state, &(state->h), &(state->l));
            break;
        case 0x2a: // LHLD adr
            LHLD_addr(state, opcode[2], opcode[1]);
            break;
        case 0x2b: // DCX H
            DCX_rp(state, &(state->h), &(state->l));
            break;
        case 0x2c: // INR L
            INR_r(state, &(state->l));
            break;
        case 0x2d: // DCR L
            DCR_r(state, &(state->l));
            break;
        case 0x2e: // MVI L, D8
            MVI_r_data(state, &(state->l), opcode[1]);
            break;
        case 0x2f: // CMA
            CMA(state);
            break;
        case 0x31: // LXI SP, D16
            LXI_sp_data16(state, opcode[2], opcode[1]);
            break;
        case 0x32: // STA adr
            STA_addr(state, opcode[2], opcode[1]);
            break;
        case 0x33: // INX SP
            UnimplementedInstruction(state);
            break;
        case 0x34: // INR M
            INR_M(state);
            break;
        case 0x35: // DCR M
            DCR_M(state);
            break;
        case 0x36: // MVI M, D8
            MVI_M_data(state, opcode[1]);
            break;
        case 0x37: // STC
            STC(state);
            break;
        case 0x39: // DAD SP
            UnimplementedInstruction(state);
            break;
        case 0x3a: // LDA adr
            LDA_addr(state, opcode[2], opcode[1]);
            break;
        case 0x3b: // DCX SP
            UnimplementedInstruction(state);
            break;
        case 0x3c: // INR A
            INR_r(state, &(state->a));
            break;
        case 0x3d: // DCR A
            DCR_r(state, &(state->a));
            break;
        case 0x3e: // MVI A, D8
            MVI_r_data(state, &(state->a), opcode[1]);
            break;
        case 0x3f: // CMC
            CMC(state);
            break;
        case 0x40: // MOV B, B
            MOV_r_r(state, &(state->b), &(state->b));
            break;
        case 0x41: // MOV B, C
            MOV_r_r(state, &(state->b), &(state->c));
            break;
        case 0x42: // MOV B, D
            MOV_r_r(state, &(state->b), &(state->d));
            break;
        case 0x43: // MOV B, E
            MOV_r_r(state, &(state->b), &(state->e));
            break;
        case 0x44: // MOV B, H
            MOV_r_r(state, &(state->b), &(state->h));
            break;
        case 0x45: // MOV B, L
            MOV_r_r(state, &(state->b), &(state->l));
            break;
        case 0x46: // MOV B, M
            MOV_r_M(state, &(state->b));
            break;
        case 0x47: // MOV B, A
            MOV_r_r(state, &(state->b), &(state->a));
            break;
        case 0x48: // MOV C, B
            MOV_r_r(state, &(state->c), &(state->b));
            break;
        case 0x49: // MOV C, C
            MOV_r_r(state, &(state->c), &(state->c));
            break;
        case 0x4a: // MOV C, D
            MOV_r_r(state, &(state->c), &(state->d));
            break;
        case 0x4b: // MOV C, E
            MOV_r_r(state, &(state->c), &(state->e));
            break;
        case 0x4c: // MOV C, H
            MOV_r_r(state, &(state->c), &(state->h));
            break;
        case 0x4d: // MOV C, L
            MOV_r_r(state, &(state->c), &(state->l));
            break;
        case 0x4e: // MOV C, M
            MOV_r_M(state, &(state->c));
            break;
        case 0x4f: // MOV C, A
            MOV_r_r(state, &(state->c), &(state->a));
            break;
        case 0x50: // MOV D, B
            MOV_r_r(state, &(state->d), &(state->b));
            break;
        case 0x51: // MOV D, C
            MOV_r_r(state, &(state->d), &(state->c));
            break;
        case 0x52: // MOV D, D
            MOV_r_r(state, &(state->d), &(state->d));
            break;
        case 0x53: // MOV D, E
            MOV_r_r(state, &(state->d), &(state->e));
            break;
        case 0x54: // MOV D, H
            MOV_r_r(state, &(state->d), &(state->h));
            break;
        case 0x55: // MOV D, L
            MOV_r_r(state, &(state->d), &(state->l));
            break;
        case 0x56: // MOV D, M
            MOV_r_M(state, &(state->d));
            break;
        case 0x57: // MOV D, A
            MOV_r_r(state, &(state->d), &(state->a));
            break;
        case 0x58: // MOV E, B
            MOV_r_r(state, &(state->e), &(state->b));
            break;
        case 0x59: // MOV E, C
            MOV_r_r(state, &(state->e), &(state->c));
            break;
        case 0x5a: // MOV E, D
            MOV_r_r(state, &(state->e), &(state->d));
            break;
        case 0x5b: // MOV E, E
            MOV_r_r(state, &(state->e), &(state->e));
            break;
        case 0x5c: // MOV E, H
            MOV_r_r(state, &(state->e), &(state->h));
            break;
        case 0x5d: // MOV E, L
            MOV_r_r(state, &(state->e), &(state->l));
            break;
        case 0x5e: // MOV E, M
            MOV_r_M(state, &(state->e));
            break;
        case 0x5f: // MOV E, A
            MOV_r_r(state, &(state->e), &(state->a));
            break;
        case 0x60: // MOV H, B
            MOV_r_r(state, &(state->h), &(state->b));
            break;
        case 0x61: // MOV H, C
            MOV_r_r(state, &(state->h), &(state->c));
            break;
        case 0x62: // MOV H, D
            MOV_r_r(state, &(state->h), &(state->d));
            break;
        case 0x63: // MOV H, E
            MOV_r_r(state, &(state->h), &(state->e));
            break;
        case 0x64: // MOV H, H
            MOV_r_r(state, &(state->h), &(state->h));
            break;
        case 0x65: // MOV H, L
            MOV_r_r(state, &(state->h), &(state->l));
            break;
        case 0x66: // MOV H, M
            MOV_r_M(state, &(state->h));
            break;
        case 0x67: // MOV H, A
            MOV_r_r(state, &(state->h), &(state->a));
            break;
        case 0x68: // MOV L, B
            MOV_r_r(state, &(state->l), &(state->b));
            break;
        case 0x69: // MOV L, C
            MOV_r_r(state, &(state->l), &(state->c));
            break;
        case 0x6a: // MOV L, D
            MOV_r_r(state, &(state->l), &(state->d));
            break;
        case 0x6b: // MOV L, E
            MOV_r_r(state, &(state->l), &(state->e));
            break;
        case 0x6c: // MOV L, H
            MOV_r_r(state, &(state->l), &(state->h));
            break;
        case 0x6d: // MOV L, L
            MOV_r_r(state, &(state->l), &(state->l));
            break;
        case 0x6e: // MOV L, M
            MOV_r_M(state, &(state->l));
            break;
        case 0x6f: // MOV L, A
            MOV_r_r(state, &(state->l), &(state->a));
            break;
        case 0x70: // MOV M, B
            MOV_M_r(state, &(state->b));
            break;
        case 0x71: // MOV M, C
            MOV_M_r(state, &(state->c));
            break;
        case 0x72: // MOV M, D
            MOV_M_r(state, &(state->d));
            break;
        case 0x73: // MOV M, E
            MOV_M_r(state, &(state->e));
            break;
        case 0x74: // MOV M, H
            MOV_M_r(state, &(state->h));
            break;
        case 0x75: // MOV M, L
            MOV_M_r(state, &(state->l));
            break;
        case 0x76: // HLT
            HLT(state);
            break;
        case 0x77: // MOV M, A
            MOV_M_r(state, &(state->a));
            break;
        case 0x78: // MOV A, B
            MOV_r_r(state, &(state->a), &(state->b));
            break;
        case 0x79: // MOV A, C
            MOV_r_r(state, &(state->a), &(state->c));
            break;
        case 0x7a: // MOV A, D
            MOV_r_r(state, &(state->a), &(state->d));
            break;
        case 0x7b: // MOV A, E
            MOV_r_r(state, &(state->a), &(state->e));
            break;
        case 0x7c: // MOV A, H
            MOV_r_r(state, &(state->a), &(state->h));
            break;
        case 0x7d: // MOV A, L
            MOV_r_r(state, &(state->a), &(state->l));
            break;
        case 0x7e: // MOV A, M
            MOV_r_M(state, &(state->a));
            break;
        case 0x7f: // MOV A, A
            MOV_r_r(state, &(state->a), &(state->a));
            break;
        case 0x80: // ADD B
            ADD_r(state, &(state->b));
            break;
        case 0x81: // ADD C
            ADD_r(state, &(state->c));
            break;
        case 0x82: // ADD D
            ADD_r(state, &(state->d));
            break;
        case 0x83: // ADD E
            ADD_r(state, &(state->e));
            break;
        case 0x84: // ADD H
            ADD_r(state, &(state->h));
            break;
        case 0x85: // ADD L
            ADD_r(state, &(state->l));
            break;
        case 0x86: // ADD M
            ADD_M(state);
            break;
        case 0x87: // ADD A
            ADD_r(state, &(state->a));
            break;
        case 0x88: // ADC B
            ADC_r(state, &(state->b));
            break;
        case 0x89: // ADC C
            ADC_r(state, &(state->c));
            break;
        case 0x8a: // ADC D
            ADC_r(state, &(state->d));
            break;
        case 0x8b: // ADC E
            ADC_r(state, &(state->e));
            break;
        case 0x8c: // ADC H
            ADC_r(state, &(state->h));
            break;
        case 0x8d: // ADC L
            ADC_r(state, &(state->l));
            break;
        case 0x8e: // ADC M
            ADC_M(state);
            break;
        case 0x8f: // ADC A
            ADC_r(state, &(state->a));
            break;
        case 0x90: // SUB B
            SUB_r(state, &(state->b));
            break;
        case 0x91: // SUB C
            SUB_r(state, &(state->c));
            break;
        case 0x92: // SUB D
            SUB_r(state, &(state->d));
            break;
        case 0x93: // SUB E
            SUB_r(state, &(state->e));
            break;
        case 0x94: // SUB H
            SUB_r(state, &(state->h));
            break;
        case 0x95: // SUB L
            SUB_r(state, &(state->l));
            break;
        case 0x96: // SUB M
            SUB_M(state);
            break;
        case 0x97: // SUB A
            SUB_r(state, &(state->a));
            break;
        case 0x98: // SBB B
            SBB_r(state, &(state->b));
            break;
        case 0x99: // SBB C
            SBB_r(state, &(state->c));
            break;
        case 0x9a: // SBB D
            SBB_r(state, &(state->d));
            break;
        case 0x9b: // SBB E
            SBB_r(state, &(state->e));
            break;
        case 0x9c: // SBB H
            SBB_r(state, &(state->h));
            break;
        case 0x9d: // SBB L
            SBB_r(state, &(state->l));
            break;
        case 0x9e: // SBB M
            SBB_M(state);
            break;
        case 0x9f: // SBB A
            SBB_r(state, &(state->a));
            break;
        case 0xa0: // ANA B
            ANA_r(state);
            break;
        case 0xa1: // ANA C
            ANA_r(state);
            break;
        case 0xa2: // ANA D
            ANA_r(state);
            break;
        case 0xa3: // ANA E
            ANA_r(state);
            break;
        case 0xa4: // ANA H
            ANA_r(state);
            break;
        case 0xa5: // ANA L
            ANA_r(state);
            break;
        case 0xa6: // ANA M
            ANA_M(state);
            break;
        case 0xa7: // ANA A
            ANA_r(state);
            break;
        case 0xa8: // XRA B
            XRA_r(state);
            break;
        case 0xa9: // XRA C
            XRA_r(state);
            break;
        case 0xaa: // XRA D
            XRA_r(state);
            break;
        case 0xab: // XRA E
            XRA_r(state);
            break;
        case 0xac: // XRA H
            XRA_r(state);
            break;
        case 0xad: // XRA L
            XRA_r(state);
            break;
        case 0xae: // XRA M
            XRA_M(state);
            break;
        case 0xaf: // XRA A
            XRA_r(state);
            break;
        case 0xb0: // ORA B
            ORA_r(state);
            break;
        case 0xb1: // ORA C
            ORA_r(state);
            break;
        case 0xb2: // ORA D
            ORA_r(state);
            break;
        case 0xb3: // ORA E
            ORA_r(state);
            break;
        case 0xb4: // ORA H
            ORA_r(state);
            break;
        case 0xb5: // ORA L
            ORA_r(state);
            break;
        case 0xb6: // ORA M
            ORA_M(state);
            break;
        case 0xb7: // ORA A
            ORA_r(state);
            break;
        case 0xb8: // CMP B
            CMP_r(state);
            break;
        case 0xb9: // CMP C
            CMP_r(state);
            break;
        case 0xba: // CMP D
            CMP_r(state);
            break;
        case 0xbb: // CMP E
            CMP_r(state);
            break;
        case 0xbc: // CMP H
            CMP_r(state);
            break;
        case 0xbd: // CMP L
            CMP_r(state);
            break;
        case 0xbe: // CMP M
            CMP_M(state);
            break;
        case 0xbf: // CMP A
            CMP_r(state);
            break;
        case 0xc0: // RNZ
            RET(state, state->cc.z == 0);
            break;
        case 0xc1: // POP B
            POP_rp(state);
            break;
        case 0xc2: // JNZ adr
            JMP(state, opcode[2], opcode[1], state->cc.z == 0);
            break;
        case 0xc3: // JMP adr
            JMP(state, opcode[2], opcode[1], true);
            break;
        case 0xc4: // CNZ adr
            CALL(state, opcode[2], opcode[1], state->cc.z == 0);
            break;
        case 0xc5: // PUSH B
            PUSH_rp(state);
            break;
        case 0xc6: // ADI D8
            ADI_data(state, opcode[1]);
            break;
        case 0xc7: // RST 0
            RST_n(state, 0);
            break;
        case 0xc8: // RZ
            RET(state, state->cc.z == 1);
            break;
        case 0xc9: // RET
            RET(state, true);
            break;
        case 0xca: // JZ adr
            JMP(state, opcode[2], opcode[1], state->cc.z == 1);
            break;
        case 0xcc: // CZ adr
            CALL(state, opcode[2], opcode[1], state->cc.z == 1);
            break;
        case 0xcd: // CALL adr
            CALL(state, opcode[2], opcode[1], true);
            break;
        case 0xce: // ACI D8
            ACI_data(state, opcode[1]);
            break;
        case 0xcf: // RST 1
            RST_n(state, 1);
            break;
        case 0xd0: // RNC
            RET(state, state->cc.cy == 0);
            break;
        case 0xd1: // POP D
            POP_rp(state);
            break;
        case 0xd2: // JNC adr
            JMP(state, opcode[2], opcode[1], state->cc.cy == 0);
            break;
        case 0xd3: // OUT D8
            OUT_port(state);
            break;
        case 0xd4: // CNC adr
            CALL(state, opcode[2], opcode[1], state->cc.cy == 0);
            break;
        case 0xd5: // PUSH D
            PUSH_rp(state);
            break;
        case 0xd6: // SUI D8
            SUI_data(state, opcode[1]);
            break;
        case 0xd7: // RST 2
            RST_n(state, 2);
            break;
        case 0xd8: // RC
            RET(state, state->cc.cy == 1);
            break;
        case 0xda: // JC adr
            JMP(state, opcode[2], opcode[1], state->cc.cy == 1);
            break;
        case 0xdb: // IN D8
            IN_port(state);
            break;
        case 0xdc: // CC adr
            CALL(state, opcode[2], opcode[1], state->cc.cy == 1);
            break;
        case 0xde: // SBI D8
            SBI_data(state, opcode[1]);
            break;
        case 0xdf: // RST 3
            RST_n(state, 3);
            break;
        case 0xe0: // RPO
            RET(state, state->cc.p == 0);
            break;
        case 0xe1: // POP H
            POP_rp(state);
            break;
        case 0xe2: // JPO adr
            JMP(state, opcode[2], opcode[1], state->cc.p == 0);
            break;
        case 0xe3: // XTHL
            XTHL(state);
            break;
        case 0xe4: // CPO adr
            CALL(state, opcode[2], opcode[1], state->cc.p == 0);
            break;
        case 0xe5: // PUSH H
            PUSH_rp(state);
            break;
        case 0xe6: // ANI D8
            ANI_data(state);
            break;
        case 0xe7: // RST 4
            RST_n(state, 4);
            break;
        case 0xe8: // RPE
            RET(state, state->cc.p == 1);
            break;
        case 0xe9: // PCHL
            PCHL(state);
            break;
        case 0xea: // JPE adr
            JMP(state, opcode[2], opcode[1], state->cc.p == 1);
            break;
        case 0xeb: // XCHG
            XCHG(state);
            break;
        case 0xec: // CPE adr
            CALL(state, opcode[2], opcode[1], state->cc.p == 1);
            break;
        case 0xee: // XRI D8
            XRI_data(state);
            break;
        case 0xef: // RST 5
            RST_n(state, 5);
            break;
        case 0xf0: // RP
            RET(state, state->cc.s == 0);
            break;
        case 0xf1: // POP PSW
            POP_PSW(state);
            break;
        case 0xf2: // JP adr
            JMP(state, opcode[2], opcode[1], state->cc.s == 0);
            break;
        case 0xf3: // DI
            DI(state);
            break;
        case 0xf4: // CP adr
            CALL(state, opcode[2], opcode[1], state->cc.s == 0);
            break;
        case 0xf5: // PUSH PSW
            PUSH_PSW(state);
            break;
        case 0xf6: // ORI D8
            ORI_data(state);
            break;
        case 0xf7: // RST 6
            RST_n(state, 6);
            break;
        case 0xf8: // RM
            RET(state, state->cc.s == 1);
            break;
        case 0xf9: // SPHL
            SPHL(state);
            break;
        case 0xfa: // JM adr
            JMP(state, opcode[2], opcode[1], state->cc.s == 1);
            break;
        case 0xfb: // EI
            EI(state);
            break;
        case 0xfc: // CM adr
            CALL(state, opcode[2], opcode[1], state->cc.s == 1);
            break;
        case 0xfe: // CPI D8
            CPI_data(state);
            break;
        case 0xff: // RST 7
            RST_n(state, 7);
            break;
        default:
            printf("ERROR: UNKNOWN OPCODE %x\n\n", *opcode);
            exit(1);
    }
}

void displayState(State8080 *state) {
    // TODO need to condense flags into the "f" register for display
    uint8_t flagsRegister = 0;

    printf(" af   bc   de   hl   pc   sp   flags cycles\n");
    printf("%02x%02x %02x%02x %02x%02x %02x%02x %04x %04x  ", state->a, flagsRegister, state->b, state->c, state->d, state->e, state->h, state->l, state->pc, state->sp);

    if (state->cc.ac == 1) {
        printf("a");
    } else {
        printf(".");
    }

    if (state->cc.cy == 1)     {
        printf("c");
    } else     {
        printf(".");
    }

    if (state->cc.p == 1)     {
        printf("p");
    } else {
        printf(".");
    }

    if (state->cc.s == 1)
    {
        printf("s");
    } else {
        printf(".");
    }

    if (state->cc.z == 1)
    {
        printf("z");
    } else {
        printf(".");
    }

    printf(" %lli\n\n", state->cycles);
}

int main() {
    State8080 *state = calloc(1, sizeof(State8080));
    state->memory = malloc(0x10000); // 16 KB
    state->sp = 0xf000;
    FILE* filePointer = fopen("invaders", "rb");
    fread(state->memory, 1, FILESIZE, filePointer);
    long long int counter = 0;

    while (1) {
        printf("%lli ", counter);
        disassemble(state->memory, state->pc);
        Emulate8080Op(state);
        displayState(state);
        ++counter;
    }
}
