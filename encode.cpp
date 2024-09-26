#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

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

std::vector<std::string> encodeFromBinary(std::string binary) {
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
            // be vector return vector
            std::vector<std::string> errReturn;
            errReturn.push_back("An error occured");
            return errReturn;
        }
    }

    return encodedString;
}

int encodeFromText(std::string toEncode) {
    std::string binary = stringToBinary(toEncode);
    
    std::vector<std::string> result = encodeFromBinary(binary);
    
    for(const std::string currentChar : result) {
        std::cout << currentChar;
    }
    std::cout << std::endl;

    return 0;
}

std::string getTextFromFile(std::string fileName) {
        std::ifstream inputFile(fileName, std::ios::binary);

    if (!inputFile) {
        std::cerr << "File could not be opened!" << std::endl;
        return "err";
    }

    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);

    inputFile.read(buffer.data(), fileSize);

    inputFile.close();

    std::string binary(buffer.begin(), buffer.end());

    return binary;
}

void printHelp() {
    std::cout << "Syntax: encode <argument>(optional) <text or file to encode>\n";
    std::cout << "Arguments:\n-f file. Encodes from a file. Ex: encode file\n-t text. The default argument, encodes from a string. Ex: encode hello!" << std::endl;
}

int main(int argc, char *argv[]) {
    std::string toEncode;
    int returnCode = 0;

    if(argc == 1) {
        std::cout << "Enter the string to encode: ";
        std::getline(std::cin, toEncode);

        returnCode = encodeFromText(toEncode);
    } else {
        std::string encodeFromArgs;
        bool argsDone = false;
        char type = 't';

        for(int i = 1; i!=argc; i++) {
            if(!argsDone) {
                if(argv[i][0] == '-' && strlen(argv[i]) >= 2) {
                    char arg = argv[i][1];
                    switch(arg) {
                        case 'f':
                            type = 'f';
                            break;
                        case 't':
                            type = 't';
                            break;
                        case 'h':
                            printHelp();
                            return 0;
                        default:
                            if(i >= 2) {
                                argsDone = true;

                                encodeFromArgs += argv[i];
                                encodeFromArgs += " ";
                            } else {
                                std::cout << "Unrecognized option\n";
                                return 1;
                            }
                    }
                    continue;
                }
            }

            encodeFromArgs += argv[i];
            encodeFromArgs += " ";
        }
        toEncode = encodeFromArgs;

        if(type == 't') {
            returnCode = encodeFromText(toEncode);
        } else {
            std::string binaryResult = getTextFromFile(argv[2]);

            if(binaryResult!="err") {
                returnCode = encodeFromText(binaryResult);

                std::cout << std::endl;
            } else {;
                std::cout << "An error occured while reading the file.\n";
                returnCode = 1;
            }
        }
    }

    return returnCode;
}