#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <openssl/aes.h>
using namespace std;
#pragma warning(disable: 4996)


const int BLOCK_SIZE = AES_BLOCK_SIZE;


void encrypt(const unsigned char* plaintext, const unsigned char* key, unsigned char* ciphertext) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    AES_encrypt(plaintext, ciphertext, &aesKey);
}


void decrypt(const unsigned char* ciphertext, const unsigned char* key, unsigned char* decryptedtext) {
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 128, &aesKey);
    AES_decrypt(ciphertext, decryptedtext, &aesKey);
}

int main() {
    setlocale(0, "");
    unsigned char key[] = "0123456789dabcdef";
    while(true){
        int punkt = 0;
        cout << "1. Зашифровать текст"<<endl;
        cout << "2. Расшифровать текст" << endl;
        cout << "3. Поменять ключ шифрования" << endl;
        cout << "4. Выход" << endl;
        cout << "############################" << endl;
        cout << "Выберите пункт:" << endl;
        cin >> punkt;
        switch (punkt)
        {
            case 1:{
                unsigned char plaintext[128];
                unsigned char ciphertext[128];

                cout << "Введите текст для шифрования: ";
                cin.ignore();
                cin.getline((char*)plaintext, 128);
                //cout << key << endl;
                int plaintext_len = strlen((char*)plaintext);
                int ciphertext_len = (plaintext_len / BLOCK_SIZE + 1) * BLOCK_SIZE;
                encrypt(plaintext, key, ciphertext);

                cout << "Зашифрованный текст: ";
                for (int i = 0; i < ciphertext_len; i++) {
                    cout << hex << (int)ciphertext[i];
                }
                cout << endl;
                break;
            }
            case 2: {
                unsigned char ciphertext[128];
                unsigned char decryptedtext[128];

                cout << "Введите зашифрованный текст: ";
                string ciphertext_str;
                cin.ignore();
                getline(cin, ciphertext_str);

                int ciphertext_len = ciphertext_str.length() / 2;
                for (int i = 0; i < ciphertext_len; i++) {
                    sscanf(ciphertext_str.substr(i * 2, 2).c_str(), "%02x", &ciphertext[i]);
                }
                decrypt(ciphertext, key, decryptedtext);

                cout << "Расшифрованный текст: " << decryptedtext << endl;
                break;
            }
            case 3: {
                cout << "Введите ключ: ";
                cin >> hex >> key;
                cout << key << endl;
                break;
            }
            case 4: {
                return 0;
            }
        default:
            break;
        }
    }
  
    return 0;
}