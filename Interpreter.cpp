#include "Interpreter.h"
#include <iostream>
#include <vector>


bool isValidVariableName(const std::string &name) {
    if (name.empty() || !isalpha(name[0])) {
        return false;
    }
    return std::all_of(name.begin(), name.end(), [](char c) {
        return isalnum(c) || c == '_';
    });
}

std::string toHexString(int value) {
    std::stringstream ss;
    ss << std::hex << value;
    return ss.str();
}

std::vector<std::string> istringstreamToVector(const std::string &line) {
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;

    while (getline(iss, token, ' ')) {
        size_t pos = 0;
        std::string delimiter = ",";
        while ((pos = token.find(delimiter)) != std::string::npos) {
            tokens.push_back(token.substr(0, pos));
            token.erase(0, pos + delimiter.length());
        }
        if (!token.empty()) tokens.push_back(token);
    }

    return tokens;
}


AssemblerInterpreter::AssemblerInterpreter() {}

void AssemblerInterpreter::execute(const std::string &instruction) {
    try {
        parseAndExecute(instruction);
    } catch (const AssemblerInterpreterException &e) {
        std::cerr << "Error executing instruction: " << e.what() << std::endl;
    }
}

void AssemblerInterpreter::run(const std::vector<std::string> &instructions) {
    for (const auto &instruction: instructions) {
        execute(instruction);
    }
}

bool AssemblerInterpreter::isPseudoOp(const std::string &opcode) {
    return opcode == "DB" || opcode == "DW" || opcode == "DD";
}

bool AssemblerInterpreter::isInstruction(const std::string &opcode) {
    return opcode == "MOV" || opcode == "XCHG" || opcode == "ADD" || opcode == "SUB" || opcode == "DIV" ||
           opcode == "MUL" || opcode == "AND" || opcode == "OR" || opcode == "XOR" || opcode == "INC" ||
           opcode == "DEC";
}

void AssemblerInterpreter::parseAndExecute(const std::string &line) {

    std::vector<std::string> tokens = istringstreamToVector(line);
    if (tokens.empty()) {
        throw AssemblerInterpreterException("Empty line");
    }
    std::string firstWord = tokens[0];
    std::string secondWord = tokens.size() > 1 ? tokens[1] : "";

    if (isPseudoOp(secondWord)) {
        handleDataDeclaration(firstWord, tokens);
    } else if (isInstruction(firstWord)) {
        handleInstruction(firstWord, tokens);
    } else {
        throw AssemblerInterpreterException("Unsupported or unrecognized line: " + line);
    }
}

void AssemblerInterpreter::handleInstruction(const std::string &opcode, std::vector<std::string> &tokens) {
    if (opcode == "MOV") {
        std::string arg1, arg2;
        if (tokens.size() < 3) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        arg2 = tokens[2];
        if (!isValidVariableName(arg1)) {
            throw AssemblerInterpreterException("Invalid variable name: " + arg1);
        }
        asmMOV(arg1, arg2);
    } else if (opcode == "XCHG") {
        std::string arg1, arg2;
        if (tokens.size() < 3) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        arg2 = tokens[2];
        asmXCHG(arg1, arg2);
    } else if (opcode == "ADD") {
        std::string arg1, arg2;
        if (tokens.size() < 3) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        arg2 = tokens[2];
        asmADD(arg1, arg2);
    } else if (opcode == "SUB") {
        std::string arg1, arg2;
        if (tokens.size() < 3) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        arg2 = tokens[2];
        asmSUB(arg1, arg2);
    } else if (opcode == "DIV") {
        std::string arg1, arg2;
        if (tokens.size() < 3) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        arg2 = tokens[2];
        asmDIV(arg1, arg2);
    } else if (opcode == "MUL") {
        std::string arg1, arg2;
        if (tokens.size() < 3) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        arg2 = tokens[2];
        asmMUL(arg1, arg2);
    } else if (opcode == "AND") {
        std::string arg1, arg2;
        if (tokens.size() < 3) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        arg2 = tokens[2];
        asmAND(arg1, arg2);
    } else if (opcode == "OR") {
        std::string arg1, arg2;
        if (tokens.size() < 3) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        arg2 = tokens[2];
        asmOR(arg1, arg2);
    } else if (opcode == "XOR") {
        std::string arg1, arg2;
        if (tokens.size() < 3) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        arg2 = tokens[2];
        asmXOR(arg1, arg2);
    } else if (opcode == "INC") {
        std::string arg1;
        if (tokens.size() < 2) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        asmINC(arg1);
    } else if (opcode == "DEC") {
        std::string arg1;
        if (tokens.size() < 2) {
            throw AssemblerInterpreterException("MOV instruction requires two arguments");
        }
        arg1 = tokens[1];
        asmINC(arg1);
        asmDEC(arg1);
    } else {
        throw AssemblerInterpreterException("Unsupported instruction: " + opcode);
    }
}

void AssemblerInterpreter::handleDataDeclaration(const std::string &varName, std::vector<std::string> &tokens) {
    std::string pseudoOp, value;
    if (tokens.size() < 3) {
        throw AssemblerInterpreterException("Data declaration requires two arguments");
    }
    pseudoOp = tokens[1];
    value = tokens[2];
    if (pseudoOp == "DB") asmDB(varName, value);
    else if (pseudoOp == "DW") asmDW(varName, value);
    else if (pseudoOp == "DD") asmDD(varName, value);
    else throw AssemblerInterpreterException("Unsupported data declaration: " + pseudoOp);
}

void AssemblerInterpreter::asmMOV(const std::string &dest, const std::string &src) {
    std::string destValue, srcValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    if (!memory.get(src, srcValue)) {
        throw AssemblerInterpreterException("Source register not found: " + src);
    }
    try {
        int sum = std::stoi(destValue, nullptr, 16) + std::stoi(srcValue, nullptr, 16);
        memory.set(dest, toHexString(sum));
    } catch (const std::invalid_argument &) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    memory.set(dest, srcValue);
    memory.display();
}

void AssemblerInterpreter::asmXCHG(const std::string &dest, const std::string &src) {
    std::string destValue, srcValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    if (!memory.get(src, srcValue)) {
        throw AssemblerInterpreterException("Source register not found: " + src);
    }
    try {
        int sum = std::stoi(destValue, nullptr, 16) + std::stoi(srcValue, nullptr, 16);
        memory.set(dest, toHexString(sum));
    } catch (const std::invalid_argument &) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    memory.set(dest, srcValue);
    memory.set(src, destValue);
    memory.display();

}

void AssemblerInterpreter::asmADD(const std::string &dest, const std::string &src) {
    std::string destValue, srcValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    if (!memory.get(src, srcValue)) {
        throw AssemblerInterpreterException("Source register not found: " + src);
    }
    long destVal = 0, srcVal = 0;
    try {
        destVal = std::stol(destValue, nullptr, 16);
        srcVal = std::stol(srcValue, nullptr, 16);
    } catch (const std::invalid_argument &e) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    long sum = destVal + srcVal;
    memory.set(dest, toHexString(sum));
    memory.display();
}

void AssemblerInterpreter::asmSUB(const std::string &dest, const std::string &src) {
    std::string destValue, srcValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    if (!memory.get(src, srcValue)) {
        throw AssemblerInterpreterException("Source register not found: " + src);
    }
    long destVal = 0, srcVal = 0;
    try {
        destVal = std::stol(destValue, nullptr, 16);
        srcVal = std::stol(srcValue, nullptr, 16);
    } catch (const std::invalid_argument &e) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    long sub = destVal - srcVal;
    memory.set(dest, toHexString(sub));
    memory.display();
}

void AssemblerInterpreter::asmDIV(const std::string &dest, const std::string &src) {
    std::string destValue, srcValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    if (!memory.get(src, srcValue)) {
        throw AssemblerInterpreterException("Source register not found: " + src);
    }
    long destVal = 0, srcVal = 0;
    try {
        destVal = std::stol(destValue, nullptr, 16);
        srcVal = std::stol(srcValue, nullptr, 16);
    } catch (const std::invalid_argument &e) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    long div = destVal / srcVal;
    memory.set(dest, toHexString(div));
    memory.display();

}

void AssemblerInterpreter::asmMUL(const std::string &dest, const std::string &src) {
    std::string destValue, srcValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    if (!memory.get(src, srcValue)) {
        throw AssemblerInterpreterException("Source register not found: " + src);
    }

    long destVal = 0, srcVal = 0;
    try {
        destVal = std::stol(destValue, nullptr, 16);
        srcVal = std::stol(srcValue, nullptr, 16);
    } catch (const std::invalid_argument &e) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    long mul = destVal * srcVal;
    memory.set(dest, toHexString(mul));
    memory.display();
}

void AssemblerInterpreter::asmAND(const std::string &dest, const std::string &src) {
    std::string destValue, srcValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    if (!memory.get(src, srcValue)) {
        throw AssemblerInterpreterException("Source register not found: " + src);
    }
    long destVal = 0, srcVal = 0;
    try {
        destVal = std::stol(destValue, nullptr, 16);
        srcVal = std::stol(srcValue, nullptr, 16);
    } catch (const std::invalid_argument &e) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    long _and = destVal & srcVal;
    memory.set(dest, toHexString(_and));
    memory.display();
}

void AssemblerInterpreter::asmOR(const std::string &dest, const std::string &src) {
    std::string destValue, srcValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    if (!memory.get(src, srcValue)) {
        throw AssemblerInterpreterException("Source register not found: " + src);
    }
    long destVal = 0, srcVal = 0;
    try {
        destVal = std::stol(destValue, nullptr, 16);
        srcVal = std::stol(srcValue, nullptr, 16);
    } catch (const std::invalid_argument &e) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    long _or = destVal | srcVal;
    memory.set(dest, toHexString(_or));
    memory.display();
}

void AssemblerInterpreter::asmXOR(const std::string &dest, const std::string &src) {
    std::string destValue, srcValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    if (!memory.get(src, srcValue)) {
        throw AssemblerInterpreterException("Source register not found: " + src);
    }
    long destVal = 0, srcVal = 0;
    try {
        destVal = std::stol(destValue, nullptr, 16);
        srcVal = std::stol(srcValue, nullptr, 16);
    } catch (const std::invalid_argument &e) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    long _xor = destVal ^ srcVal;
    memory.set(dest, toHexString(_xor));
    memory.display();

}

void AssemblerInterpreter::asmINC(const std::string &dest) {
    std::string destValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    long destVal = 0;
    try {
        destVal = std::stol(destValue, nullptr, 16);
    } catch (const std::invalid_argument &e) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    long inc = destVal + 1;
    memory.set(dest, toHexString(inc));
    memory.display();
}

void AssemblerInterpreter::asmDEC(const std::string &dest) {
    std::string destValue;
    if (!memory.get(dest, destValue)) {
        throw AssemblerInterpreterException("Destination register not found: " + dest);
    }
    long destVal = 0;
    try {
        destVal = std::stol(destValue, nullptr, 16);
    } catch (const std::invalid_argument &e) {
        throw AssemblerInterpreterException("Invalid numeric conversion");
    }
    long dec = destVal + 1;
    memory.set(dest, toHexString(dec));
    memory.display();
}

void AssemblerInterpreter::asmDB(const std::string &varName, const std::string &value) {
    if (!isValidVariableName(varName)) {
        throw AssemblerInterpreterException("Invalid variable name: " + varName);
    }
    memory.set(varName, value);
    memory.display();

}

void AssemblerInterpreter::asmDW(const std::string &varName, const std::string &size) {
    if (!isValidVariableName(varName)) {
        throw AssemblerInterpreterException("Invalid variable name: " + varName);
    }
    memory.set(varName, size);
    memory.display();

}

void AssemblerInterpreter::asmDD(const std::string &varName, const std::string &size) {
    if (!isValidVariableName(varName)) {
        throw AssemblerInterpreterException("Invalid variable name: " + varName);
    }
    memory.set(varName, size);
    memory.display();

}
