#include <iostream>
#include <fstream>
#include <vector>
#include <format>
#include <nlohmann/json.hpp>

#include "config.hpp"
#include "cpu/cpu.hpp"
#include "memory/flat_memory.hpp"
#include "memory/flat_test_memory.hpp"

int main() {
    ConfigParser cf("../config.json");

    auto loads = cf.getLoadSections();
    auto mems = cf.getMemoryRegions();

    for (const auto& [file, address, maxSize] : loads) {
        std::cout << std::format("file: {} address: {} maxSize: {}", file, address, maxSize) << std::endl;
    }

    for (const auto& [start, length, permissions] : mems) {
        std::cout << std::format("start: {} length: {} permissions: {:x}", start, length, static_cast<std::uint64_t>(permissions)) << std::endl;
    }

    auto memory = std::make_shared<flat_test_memory>(2 * 1024 * 1024);

    const std::string path = "../binary.bin";
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file) {
        std::cerr << "Failed to open " << path << "\n";
        return 1;
    }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    if (fileSize > static_cast<std::streamsize>(memory->size())) {
        std::cerr << "binary.bin too large for memory (" << fileSize << " bytes)\n";
        return 1;
    }

    std::vector<std::byte> buffer(fileSize);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
        std::cerr << "Failed to read binary file\n";
        return 1;
    }

    if (!memory->write(0x0, buffer)) {
        std::cerr << "Failed to write to memory\n";
        return 1;
    }

    std::cout << std::format("Loaded {} bytes from {} into address 0x0\n",
                             fileSize, path);


    CPU cpu(memory);

    while (!cpu.is_stopped())
        cpu.step_instruction();

    return 0;
}
