#include <iostream>
#include <string>

char *rle(std::string text)
{
    char encoded_text[1000]; 
    int count = 1;
    int j = 0;

    for (int i = 0; i < text.length(); i++) {
        if (text[i] == text[i + 1]) {
            count++;
        } else {

            std::string countStr = std::to_string(count);
            for (char digit : countStr) {
                encoded_text[j] = digit;
                j++;
            }

            encoded_text[j] = text[i];
            j++;

            count = 1;
        }
    }
    encoded_text[j] = '\0';
    return (encoded_text);
}
int main() {
    std::string line = "WWWWWWWWWWWWWBBBBWWWWBWWBBBBBBBBW";
    printf("%s\n", rle(line));

    return 0;
}
