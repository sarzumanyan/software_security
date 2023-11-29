#include <iostream>
using namespace std;

string generateKey(string str, string key)
{
    int x = str.size();

    for (int i = 0; ; i++)
    {
        if (x == i)
            i = 0;
        if (key.size() == str.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}

string cipherText(string str, string key)
{
    string cipher_text;

    for (int i = 0; i < str.size(); i++)
    {
        // converting in range 0-25 or 0-127
        char x = (str[i] + key[i]) % 26;
        //char x = (str[i] + key[i]) % 128;

        // convert into alphabets(ASCII)
        x += 'A';

        cipher_text.push_back(x);
    }
    return cipher_text;
}
int main()
{
    string str = "BANANATREE";
    string keyword = "LEMON";

    string key = generateKey(str, keyword);
    string cipher_text = cipherText(str, key);

    cout << "Ciphertext : " << cipher_text << "\n";
    return 0;
}