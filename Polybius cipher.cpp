#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
// encryption fucntion
string encryptMessage(const string& message, const vector<int>& key) {
    string encryptedText = "";

    for (char ch : message) {
        if (isalpha(ch)) {
            char upperCh = toupper(ch);
            if (upperCh == 'J') {
                upperCh = 'I'; // Replace J with I
            }

            int index = upperCh - 'A';
            int row = index / 5;
            int col = index % 5;

            encryptedText += to_string(key[row]) + to_string(key[col]);
        }
    }

    return encryptedText;
}

// decryption function
string decryptMessage(const string& message, const vector<int>& key) {
    string decryptedText = "";

    for (size_t i = 0; i < message.length(); i += 2) {
        int row = message[i] - '0';
        int col = message[i + 1] - '0';

        // key positions
        auto position = find(key.begin(), key.end(), row);
        int rowIndex = distance(key.begin(), position) + 1;

        position = find(key.begin(), key.end(), col);
        int colIndex = distance(key.begin(), position) + 1;

        int index = (rowIndex - 1) * 5 + colIndex - 1;

        char decryptedChar = static_cast<char>(index) + 'A';
        if (decryptedChar == 'J') {
            //j and i are the same
            decryptedChar = 'I'; 
        }

        decryptedText += decryptedChar;
    }

    return decryptedText;
}





int main() {
    cout << "Enter the key (5 numbers separated by spaces) for encryption: ";
    vector<int> key(5);
    for (int i = 0; i < 5; ++i) {
        cin >> key[i];
    }

    cin.ignore(); // buffer control

    cout << "Enter the message to encrypt: ";
    string plainText;
    getline(cin, plainText);

    // remove spaces
    plainText.erase(remove_if(plainText.begin(), plainText.end(), ::isspace), plainText.end());

    // call and display encryption
    string cipherText = encryptMessage(plainText, key);
    cout << "Encrypted message: " << cipherText << endl;

    // decryption?
    cout << "Do you want to decrypt the message? (y/n): ";
    char choice;
    cin >> choice;

    if (tolower(choice) == 'y') {
        // key positions
        cout << "Enter the key for decryption (5 numbers separated by spaces): ";
        vector<int> decryptionKey(5);
        for (int i = 0; i < 5; ++i) {
            cin >> decryptionKey[i];
        }

        // decrypt and display message
        string decryptedText = decryptMessage(cipherText, decryptionKey);
        cout << "Decrypted message: " << decryptedText << endl;
    }

    return 0;
}
