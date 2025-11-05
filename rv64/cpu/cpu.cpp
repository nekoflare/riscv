//
// Created by neko on 11/4/25.
//

#include "cpu.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <memory>
#include <regex>

#include "decoder.hpp"

CPU::CPU(const std::shared_ptr<base_memory> &memory) : memory(memory) {
    registers.pc = 0;
}

void CPU::step_instruction() {
    auto old_pc = registers.pc;
    auto instruction_maybe = memory->read_value<uint32_t>(registers.pc);

    if (!instruction_maybe.has_value()) {
        throw std::runtime_error("Exceptions aren't supported yet. (Failed to load instruction)");
    }

    auto instruction = instruction_maybe.value();
    auto opcode = get_opcode(instruction);

    if ((instruction & 0x3) != 0x3) {
        // its compressed
        throw std::runtime_error("Exceptions aren't supported yet (compressed instructions not supported).");
    }

    auto unsupported_opcode = [&]() {
        std::cerr << std::format("Unknown instruction {:08x}.", instruction) << std::endl;
        std::cerr << std::format("Opcode: {:02x}", opcode) << std::endl;

        exit(1); // ugly ass
    };

    switch (opcode) {
        case OPCODE_AUIPC: execute_auipc(instruction); break;
        case OPCODE_I_TYPE: execute_i_type(instruction); break;
        case OPCODE_JAL: execute_jal(instruction); break;
        case OPCODE_STORE: execute_store(instruction); break;
        case OPCODE_SYSTEM: execute_system(instruction); break;
        default:
            unsupported_opcode(); break;
    }

    // Increment program counter if previous instruction didnt modify the program counter.
    if (old_pc == registers.pc)
        registers.pc += INSTRUCTION64_LEN_BYTES;
}


std::string CPU::disas(uint32_t instruction) {
    const std::string binFile = "/tmp/tmp_instr.bin";
    {
        std::ofstream ofs(binFile, std::ios::binary | std::ios::trunc);
        ofs.write(reinterpret_cast<const char*>(&instruction), sizeof(instruction));
    }

    std::ostringstream cmd;
    cmd << "riscv64-unknown-elf-objdump -D -b binary -m riscv:rv64 "
        << binFile << " 2>/dev/null";

    std::array<char, 256> buffer{};
    std::string output;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.str().c_str(), "r"), pclose);
    if (!pipe) return "objdump error";

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        output += buffer.data();

    std::remove(binFile.c_str());

    std::regex instr_regex(R"(\b0:.*?\b([a-z][a-z0-9_.]+(?:\s+[^\n\r]*)?))", std::regex::icase);
    std::smatch match;

    if (std::regex_search(output, match, instr_regex)) {
        std::string line = match[1];
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        return line;
    }

    return "unknown";
}

bool CPU::is_stopped() const{
    return stopped;
}