#include <string>

void splitStringToInts(int result[2], std::string &str, char delimiter) {
    auto delimPos = str.find(delimiter);

    result[0] = std::stoi(str.substr(0, delimPos));
    result[1] = std::stoi(str.substr(delimPos + 1));
}
