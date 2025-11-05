//
// Created by neko on 11/4/25.
//

#ifndef RV64_CPU_HPP
#define RV64_CPU_HPP

#include <memory>

#include "state.hpp"
#include "../memory/base_memory.hpp"

constexpr size_t INSTRUCTION64_LEN_BYTES = 4;

constexpr uint32_t OPCODE_AUIPC  = 0x17;
constexpr uint32_t OPCODE_I_TYPE = 0x13;
constexpr uint32_t OPCODE_JAL    = 0x6f;
constexpr uint32_t OPCODE_STORE  = 0x23;
constexpr uint32_t OPCODE_SYSTEM = 0x73;

class CPU {
public:
    explicit CPU(const std::shared_ptr<base_memory> &flat_memory);

    void step_instruction();

    void execute_auipc(uint32_t instruction);
    void execute_i_type(uint32_t instruction);
    void execute_jal(uint32_t instruction);
    void execute_store(uint32_t instruction);
    void execute_system(uint32_t instruction);

    std::string disas(uint32_t instruction);

    [[nodiscard]] bool is_stopped() const;
private:
    Registers registers;
    std::shared_ptr<base_memory> memory;
    bool stopped = false;
};

#endif //RV64_CPU_HPP
