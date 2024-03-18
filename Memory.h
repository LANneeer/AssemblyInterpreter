//
// Created by Laner on 16/03/2024.
//

#ifndef ASSEMBLY_MEMORY_H
#define ASSEMBLY_MEMORY_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip>

template<typename T>
class HexMap {
private:
    std::unordered_map<std::string, T> map;
    std::unordered_map<std::string, std::string> keyMap;
    unsigned long long nextKey = 1;

    std::string generateHexKey() {
        std::stringstream ss;
        ss << "0x" << std::setfill('0') << std::setw(5) << std::hex << nextKey++ << "h";
        return ss.str();
    }

public:
    void set(const std::string &originalKey, const T &value) {
        if (keyMap.find(originalKey) == keyMap.end()) {
            // Key does not exist, generate a new hex key
            keyMap[originalKey] = generateHexKey();
        }
        // Convert value to hex
        std::stringstream ss;
        ss << std::hex << value;

        map[keyMap[originalKey]] = ss.str();
    }

    bool get(const std::string &originalKey, T &value) {
        if (keyMap.find(originalKey) == keyMap.end()) {
            return false; // Original key does not exist
        }
        std::string hexKey = keyMap[originalKey];
        auto it = map.find(hexKey);
        if (it != map.end()) {
            value = it->second;
            return true;
        }
        return false;
    }

    bool remove(const std::string &originalKey) {
        if (keyMap.find(originalKey) == keyMap.end()) {
            return false; // Original key does not exist
        }
        std::string hexKey = keyMap[originalKey];
        keyMap.erase(originalKey); // Remove the key mapping
        return map.erase(hexKey) > 0; // Remove the actual value
    }

    void display() {
        for (const auto &pair: map) {
            std::cout << "Hex Key: " << pair.first << " Value: " << pair.second << std::endl;
        }
    }
};

#endif //ASSEMBLY_MEMORY_H