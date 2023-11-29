#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>

// Function to generate a random key of given length
std::string rand_key(int length) {
    std::string key;
    for (int i = 0; i < length; ++i) {
        key += (rand() % 2) + '0';
    }
    return key;
}

// Function to perform bitwise XOR of two strings
std::string exor(const std::string& a, const std::string& b) {
    std::string result;
    for (std::size_t i = 0; i < a.length(); ++i) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Function to convert binary to decimal
int binaryToDecimal(const std::string& binary) {
    return std::bitset<8>(binary).to_ulong();
}

int main() {
    // Plaintext
    std::string PT = "Hello";
    std::cout << "Plain Text is: " << PT << std::endl;

    // Convert plaintext to ASCII and then to binary
    std::string PT_Bin;
    for (char c : PT) {
        PT_Bin += std::bitset<8>(c).to_string();
    }

    std::size_t n = PT_Bin.length() / 2;
    std::string L1 = PT_Bin.substr(0, n);
    std::string R1 = PT_Bin.substr(n);

    std::size_t m = R1.length();

    // Generate Keys K1 and K2
    std::string K1 = rand_key(m);
    std::string K2 = rand_key(m);

    // First round of Feistel
    std::string f1 = exor(R1, K1);
    std::string R2 = exor(f1, L1);
    std::string L2 = R1;

    // Second round of Feistel
    std::string f2 = exor(R2, K2);
    std::string R3 = exor(f2, L2);
    std::string L3 = R2;

    // Cipher text
    std::string bin_data = L3 + R3;
    std::string str_data;

    for (std::size_t i = 0; i < bin_data.length(); i += 7) {
        std::string temp_data = bin_data.substr(i, 7);
        int decimal_data = binaryToDecimal(temp_data);
        str_data += static_cast<char>(decimal_data);
    }

    std::cout << "Cipher Text: " << str_data << std::endl;

    // Decryption
    std::string L4 = L3;
    std::string R4 = R3;

    std::string f3 = exor(L4, K2);
    std::string L5 = exor(R4, f3);
    std::string R5 = L4;

    std::string f4 = exor(L5, K1);
    std::string L6 = exor(R5, f4);
    std::string R6 = L5;

    std::string PT1 = L6 + R6;

    int PT1_int = std::bitset<32>(PT1).to_ulong();
    std::string RPT(reinterpret_cast<char*>(&PT1_int), sizeof(PT1_int));
    std::cout << "Retrieved Plain Text is: " << RPT << std::endl;

    return 0;
}
