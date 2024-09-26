#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>

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

void writeToFile(std::string binaryData, std::string output) {
    std::ofstream outFile(output, std::ios::binary);
    if(!outFile) {
        std::cerr << "Error: failed to write file\n";
    } else {
        outFile.write(binaryData.c_str(), binaryData.size());

        outFile.close();
    }
}

void printHelp() {
    std::cout << "Syntax: decode <arguments>(optional) <encoded text> <output file>(only if the -f argument has been used)\n";
    std::cout << "Arguments:\n-f: File. Decodes a string to a file, ex: decode -f \"$(cat encoded.txt)\" decodedFile\n-t Text. The default argument, decodes to test. Ex: decode -t CBBACBBCABACABAA\n";
    std::cout << "Example usage: decode CBBACBBCABACABAA" << std::endl;
}

int main(int argc, char *argv[]) {
    std::string encoded;
    char to = 't';
    if(argc == 1) {
        std::cout << "Enter the string to decode: ";
        std::getline(std::cin, encoded);
    } else {
        bool argumentsDone = false;
            if(argv[1][0] == '-' && strlen(argv[1]) >= 2) {
                char arg = argv[1][1];

                switch(arg) {
                    case 't':
                        std::cout << "Decode to text.\n";
                        to = 't';
                        break;
                    case 'f':
                        std::cout << "Decode to file.\n";
                        to = 'f';
                        break;
                    case 'h':
                        printHelp();
                        return 0;
                    default:
                        std::cout << "Unrecognized option\n";
                        return 1;
                }
                encoded = argv[2];
            } else {
                encoded = argv[1];
            }
    }

    std::vector<std::string> binary = encodedToBinary(encoded);
    std::vector<std::string> binary8bit = split(vectorToString(binary));

    std::string decoded = binaryToString(vectorToString(binary8bit));

    if(!error) {
        if(to == 't') {
            std::cout << "Decoded: " << decoded << std::endl;
        } else {
            if(argc == 3) {
                writeToFile(decoded, "decoded.bin");
            } else if(argc == 4) {
                writeToFile(decoded, argv[3]);
            } else {
                std::cerr << "Error: Too many arguments, arguments: " << argc << std::endl;
                return 1;
            }
        }
    }
    
    return 0;
}