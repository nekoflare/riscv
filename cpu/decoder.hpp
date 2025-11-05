//
// Created by neko on 11/4/25.
//

#ifndef RV64_DECODER_HPP
#define RV64_DECODER_HPP
#include <cstdint>

constexpr uint32_t OPCODE_MASK  = 0x0000007F;
constexpr uint32_t RD_MASK      = 0x00000F80;
constexpr uint32_t RS1_MASK     = 0x000F8000;
constexpr uint32_t RS2_MASK     = 0x01F00000;
constexpr uint32_t FUNCT3_MASK  = 0x00007000;
constexpr uint32_t FUNCT5_MASK  = 0xF8000000;
constexpr uint32_t FUNCT7_MASK  = 0xFE000000;
constexpr uint32_t CSR_MASK     = 0xFFF00000;
constexpr uint32_t SHAMT_MASK   = 0x01F00000;
constexpr uint32_t AQ_MASK      = 0x04000000;
constexpr uint32_t RL_MASK      = 0x02000000;
constexpr uint32_t U_IMM_MASK   = 0xFFFFF000;

constexpr uint32_t OPCODE_SHIFT = 0;
constexpr uint32_t RD_SHIFT     = 7;
constexpr uint32_t FUNCT3_SHIFT = 12;
constexpr uint32_t RS1_SHIFT    = 15;
constexpr uint32_t RS2_SHIFT    = 20;
constexpr uint32_t FUNCT7_SHIFT = 25;
constexpr uint32_t FUNCT5_SHIFT = 27;
constexpr uint32_t CSR_SHIFT    = 20;
constexpr uint32_t SHAMT_SHIFT  = 20;
constexpr uint32_t AQ_SHIFT     = 26;
constexpr uint32_t RL_SHIFT     = 25;
constexpr uint32_t U_IMM_SHIFT  = 12;

constexpr uint32_t get_opcode(uint32_t instruction) {
    return (instruction & OPCODE_MASK) >> OPCODE_SHIFT;
}

constexpr uint32_t get_rd(uint32_t instruction) {
    return (instruction & RD_MASK) >> RD_SHIFT;
}

constexpr uint32_t get_rs1(uint32_t instruction) {
    return (instruction & RS1_MASK) >> RS1_SHIFT;
}

constexpr uint32_t get_rs2(uint32_t instruction) {
    return (instruction & RS2_MASK) >> RS2_SHIFT;
}

constexpr uint32_t get_funct3(uint32_t instruction) {
    return (instruction & FUNCT3_MASK) >> FUNCT3_SHIFT;
}

constexpr uint32_t get_funct5(uint32_t instruction) {
    return (instruction & FUNCT5_MASK) >> FUNCT5_SHIFT;
}

constexpr uint32_t get_funct7(uint32_t instruction) {
    return (instruction & FUNCT7_MASK) >> FUNCT7_SHIFT;
}

constexpr int32_t get_i_imm(uint32_t instruction) {
    return static_cast<int32_t>(instruction) >> 20;
}

constexpr int32_t get_s_imm(uint32_t instruction) {
    int32_t imm = ((instruction >> 25) << 5) | ((instruction >> 7) & 0x1F);
    return (imm << 20) >> 20;
}

constexpr int32_t get_b_imm(uint32_t instruction) {
    int32_t imm = (((instruction >> 31) & 0x1) << 12) |
                  (((instruction >> 7) & 0x1) << 11) |
                  (((instruction >> 25) & 0x3F) << 5) |
                  (((instruction >> 8) & 0xF) << 1);
    return (imm << 19) >> 19;
}

constexpr int32_t get_u_imm(uint32_t instruction) {
    return (instruction & U_IMM_MASK) >> U_IMM_SHIFT;
}

constexpr int32_t get_j_imm(uint32_t instruction) {
    int32_t imm = 0;
    imm |= ((instruction >> 31) & 0x1) << 20;
    imm |= ((instruction >> 21) & 0x3FF) << 1;
    imm |= ((instruction >> 20) & 0x1) << 11;
    imm |= ((instruction >> 12) & 0xFF) << 12;
    return (imm << 11) >> 11;
}

constexpr uint32_t get_shamt(uint32_t instruction) {
    return (instruction & SHAMT_MASK) >> SHAMT_SHIFT;
}

constexpr uint32_t get_aq(uint32_t instruction) {
    return (instruction & AQ_MASK) >> AQ_SHIFT;
}

constexpr uint32_t get_rl(uint32_t instruction) {
    return (instruction & RL_MASK) >> RL_SHIFT;
}

constexpr uint32_t get_csr(uint32_t instruction) {
    return (instruction & CSR_MASK) >> CSR_SHIFT;
}

constexpr uint32_t get_rm(uint32_t instruction) {
    return (instruction >> 12) & 0x7;
}

#endif // RV64_DECODER_HPP
