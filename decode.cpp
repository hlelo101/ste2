#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <sstream>

bool error = false;

std::vector<std::string> split(const std::string& str) {
    std::vector<std::string> result;

    for (size_t i = 0; i < str.length(); i += 8) {
        result.push_back(str.substr(i, 8));
    }

    return result;
}

std::string vectorToString(const std::vector<std::string>& vec) {
    std::ostringstream oss;
    for (const auto& str : vec) {
        oss << str;
    }
    return oss.str();
}

std::string binaryToString(const std::string& binary) {
    std::string result;
    
    for (size_t i = 0; i < binary.length(); i += 8) {
        std::string byteString = binary.substr(i, 8);
        char character = static_cast<char>(std::bitset<8>(byteString).to_ulong());
        result.push_back(character);
    }

    return result;
}

std::vector<std::string> encodedToBinary(std::string encoded) {
    std::vector<std::string> binary;

    for(int i = 0; i!=encoded.size(); i++) {
        if(encoded[i] == 'A') {
            binary.push_back("00");
        } else if(encoded[i] == 'B') {
            binary.push_back("10");
        } else if(encoded[i] == 'C') {
            binary.push_back("01");
        } else if(encoded[i] == 'D') {
            binary.push_back("11");
        } else {
            std::cerr << "An error occured." << std::endl;
            error = true;
            break;
        }
    }

    return binary;
}

int main() {
    std::string encoded;
    std::cout << "Enter the string to decode: ";
    std::getline(std::cin, encoded);

    std::vector<std::string> binary = encodedToBinary(encoded);
    std::vector<std::string> binary8bit = split(vectorToString(binary));

    std::string decoded = binaryToString(vectorToString(binary8bit));

    if(!error) {
        std::cout << "Decoded: " << decoded << std::endl;
    }
    
    return 0;
}