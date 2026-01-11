#include <iostream>
#include <fstream>
#include <bitset>  // for converting bytes to binary

int main() {
    // Open the binary file for reading
    std::ifstream file("output.bin", std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Read the file byte by byte
    char byte;
    while (file.read(&byte, sizeof(byte))) {
        // Convert byte to binary using bitset
        std::bitset<8> binary(byte);  // 8 bits per byte
        std::cout << binary << " ";  // Print binary value of the byte
    }

    file.close();  // Close the file
    std::cout << std::endl;

    return 0;
}

