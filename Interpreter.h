//
// Created by Laner on 16/03/2024.
//

#ifndef ASSEMBLY_INTERPRETER_H
#define ASSEMBLY_INTERPRETER_H

#include "Memory.h"
#include <string>
#include <vector>
#include <sstream>
#include <exception>
#include <string>


class AssemblerInterpreterException : public std::exception {
public:
    AssemblerInterpreterException(const std::string &message) : msg_(message) {}

    virtual const char *what() const noexcept override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

class AssemblerInterpreter {
public:
    AssemblerInterpreter();

    void execute(const std::string &instruction);

    void run(const std::vector<std::string> &instructions);

private:
    HexMap<std::string> memory;

    void parseAndExecute(const std::string &instruction);

    bool isPseudoOp(const std::string &opcode);

    bool isInstruction(const std::string &opcode);

    void handleDataDeclaration(const std::string &opcode, std::vector<std::string> &tokens);

    void handleInstruction(const std::string &opcode, std::vector<std::string> &tokens);

    void asmMOV(const std::string &dest, const std::string &src);

    void asmXCHG(const std::string &dest, const std::string &src);

    void asmADD(const std::string &dest, const std::string &src);

    void asmSUB(const std::string &dest, const std::string &src);

    void asmDIV(const std::string &dest, const std::string &src);

    void asmMUL(const std::string &dest, const std::string &src);

    void asmAND(const std::string &dest, const std::string &src);

    void asmOR(const std::string &dest, const std::string &src);

    void asmXOR(const std::string &dest, const std::string &src);

    void asmINC(const std::string &dest);

    void asmDEC(const std::string &dest);

    void asmDB(const std::string &varName, const std::string &value);

    void asmDW(const std::string &varName, const std::string &size);

    void asmDD(const std::string &varName, const std::string &size);
// Existing methods...

};

#endif // ASSEMBLY_INTERPRETER_H
