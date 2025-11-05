//
// Created by neko on 11/4/25.
//

#include <iostream>


#include "../cpu.hpp"
#include "../decoder.hpp"

enum class ITypeFunct3 : uint32_t {
    ADDI = 0x0,
    GRP1 = 0x1,
    ANDI = 0x7
};

enum class ITypeFunct3Funct6 : uint32_t {
    SLLI = 0x0
};

enum class StoreTypeFunct3 : uint32_t {
    SB = 0x0,
    SH = 0x1,
    SW = 0x2,
    SD = 0x3
};

enum class SystemTypeFunct3 : uint32_t {
    WFI = 0x0
};

constexpr uint32_t FUNCT12_MASK  = 0xFFF00000u;
constexpr uint32_t FUNCT12_SHIFT = 20;
constexpr uint32_t FUNCT6_MASK   = 0xFC000000u;
constexpr uint32_t FUNCT6_SHIFT  = 26;

void CPU::execute_auipc(uint32_t instruction) {
    auto rd = get_rd(instruction);
    auto imm = get_u_imm(instruction);

    int32_t value = imm << 12;
    uint64_t result = registers.pc + value;

    registers[rd] = result;
}

void CPU::execute_i_type(uint32_t instruction) {
    auto funct3 = get_funct3(instruction);

    auto execute_addi = [&]() {
        uint32_t value_a = registers[get_rs1(instruction)];
        int64_t value_b = get_i_imm(instruction);
        int64_t result = static_cast<int64_t>(value_a + value_b);
        registers[get_rd(instruction)] = result;
    };

    auto execute_andi = [&]() {
        uint64_t value_a = registers[get_rs1(instruction)];
        uint64_t value_b = get_i_imm(instruction);
        uint64_t result = value_a & value_b;
        registers[get_rd(instruction)] = result;
    };

    auto execute_slli = [&]() {
        auto shamt = static_cast<uint64_t>(get_i_imm(instruction)) & 0x3f;
        registers[get_rd(instruction)] = registers[get_rs1(instruction)] << shamt;
    };

    auto execute_sub_group_1 = [&]() {
        auto funct12 = (instruction & FUNCT12_MASK) >> FUNCT12_SHIFT;
        auto funct6 = (instruction & FUNCT6_MASK) >> FUNCT6_SHIFT;

        // funct12 has: sext.h, clz, sext.b, cpop and ctz
        // funct6 has: bseti, binvi and blcri.
        // ill implement them once i work in Zbb stuff

        switch (static_cast<ITypeFunct3Funct6>(funct6)) {
            case ITypeFunct3Funct6::SLLI:
                execute_slli(); break;
            default:
                throw std::runtime_error(std::format("Exceptions are not supported. (Unknown funct6 in execute_sub_group_1(\"{}\"): {:04x})", disas(instruction), funct6));
        }
    };

    switch (static_cast<ITypeFunct3>(funct3)) {
        case ITypeFunct3::ADDI:
            execute_addi(); break;
        case ITypeFunct3::ANDI:
            execute_andi(); break;
        case ITypeFunct3::GRP1:
            execute_sub_group_1(); break;
        default:
            throw std::runtime_error(std::format("Exceptions are not supported. (Unknown funct3 in execute_imm(\"{}\"): {:04x})", disas(instruction), funct3));
    }
}

void CPU::execute_jal(uint32_t instruction) {
    auto rd = get_rd(instruction);
    int32_t immediate = get_j_imm(instruction);
    uint64_t next_address = registers.pc + immediate;
    registers[rd] = registers.pc + 4;
    registers.pc = next_address;
}

void CPU::execute_store(uint32_t instruction) {
    auto funct3 = get_funct3(instruction);

    auto execute_sd = [&]() {
        auto rs1 = get_rs1(instruction);
        auto rs2 = get_rs2(instruction);
        auto s_imm = get_s_imm(instruction);

        uint64_t address = registers[rs1] + static_cast<int64_t>(s_imm);
        uint64_t value   = registers[rs2];

        if (!memory->write_value<uint64_t>(address, value)) {
            throw std::runtime_error(std::format(
                "Memory write failed in SD at address 0x{:016x}", address));
        }
    };

    auto execute_sw = [&]() {
        auto rs1 = get_rs1(instruction);
        auto rs2 = get_rs2(instruction);
        auto s_imm = get_s_imm(instruction);

        uint64_t address = registers[rs1] + static_cast<int64_t>(s_imm);
        uint32_t value   = static_cast<uint32_t>(registers[rs2]);

        if (!memory->write_value<uint32_t>(address, value)) {
            throw std::runtime_error(std::format(
                "Memory write failed in SW at address 0x{:016x}", address));
        }
    };

    auto execute_sh = [&]() {
        auto rs1 = get_rs1(instruction);
        auto rs2 = get_rs2(instruction);
        auto s_imm = get_s_imm(instruction);

        uint64_t address = registers[rs1] + static_cast<int64_t>(s_imm);
        uint16_t value   = static_cast<uint16_t>(registers[rs2]);

        if (!memory->write_value<uint16_t>(address, value)) {
            throw std::runtime_error(std::format(
                "Memory write failed in SH at address 0x{:016x}", address));
        }
    };

    auto execute_sb = [&]() {
        auto rs1 = get_rs1(instruction);
        auto rs2 = get_rs2(instruction);
        auto s_imm = get_s_imm(instruction);

        uint64_t address = registers[rs1] + static_cast<int64_t>(s_imm);
        uint8_t value    = static_cast<uint8_t>(registers[rs2]);

        if (!memory->write_value<uint8_t>(address, value)) {
            throw std::runtime_error(std::format(
                "Memory write failed in SB at address 0x{:016x}", address));
        }
    };

    switch (static_cast<StoreTypeFunct3>(funct3)) {
        case StoreTypeFunct3::SB: execute_sb(); break;
        case StoreTypeFunct3::SH: execute_sh(); break;
        case StoreTypeFunct3::SW: execute_sw(); break;
        case StoreTypeFunct3::SD: execute_sd(); break;
        default:
            throw std::runtime_error(std::format(
                "Exceptions are not supported. (Unknown funct3 in execute_store(\"{}\"): {:04x})",
                disas(instruction), funct3));
    }
}

void CPU::execute_system(uint32_t instruction) {
    auto funct3 = get_funct3(instruction);

    switch (static_cast<SystemTypeFunct3>(funct3)) {
        case SystemTypeFunct3::WFI:
            stopped = true; return;
    }

    std::cout << "Unimplemented: " << disas(instruction) << std::endl;
}