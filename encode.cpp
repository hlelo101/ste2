#include <iostream>
#include <bitset>
#include <vector>
#include <string>

std::string stringToBinary(const std::string& text) {
    std::string binaryString = "";
    for(char c : text) {
        binaryString += std::bitset<8>(c).to_string();
    }

    return binaryString;
}

std::vector<std::string> split(const std::string& str) {
    std::vector<std::string> result;

    for (size_t i = 0; i < str.length(); i += 2) {
        result.push_back(str.substr(i, 2));
    }

    return result;
}

int main(int argc, char *argv[]) {
    std::string toEncode;

    if(argc == 1) {
        std::cout << "Enter the string to encode: ";
        std::getline(std::cin, toEncode);
    } else {
        std::string encodeFromArgs;
        for(int i = 1; i!=argc; i++) {
            encodeFromArgs += argv[i];
            encodeFromArgs += " ";
        }
        toEncode = encodeFromArgs;
    }

    std::string binary = stringToBinary(toEncode);

    std::vector<std::string> binPair = split(binary);
    std::vector<std::string> encodedString;

    for(const std::string& pair : binPair) {
        if(pair == "00") {
            encodedString.push_back("A");
        } else if(pair == "10") {
            encodedString.push_back("B");
        } else if(pair == "01") {
            encodedString.push_back("C");
        } else if(pair == "11") {
            encodedString.push_back("D");
        } else {
            std::cerr << "Well, something's screwed here" << std::endl;
            return 1;
        }
    }
    
    std::cout << "Encoded string: ";
    for(const std::string currentChar : encodedString) {
        std::cout << currentChar;
    }
    std::cout << std::endl;

    return 0;
}