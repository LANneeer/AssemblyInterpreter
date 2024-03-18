#include <iostream>
#include <vector>
#include "Interpreter.h"


int main() {
    AssemblerInterpreter interpreter;
    std::vector<std::string> instructions = {};
    int n;
    std::cin >> n;
    for(int i = 0; i <= n; i++) {
        std::string instruction;
        std::getline(std::cin, instruction);
        if (!instruction.empty()) {
            instructions.push_back(instruction);
        }
    }
    interpreter.run(instructions);

    return 0;
}
