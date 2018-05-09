//
// Created by gauth on 09-05-2018.
//

// WA

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <set>

using DecryptedStrings = std::set<std::string>;

class Decryptor {
public:
    Decryptor(std::string str, std::unordered_map<std::string, std::string> decryption) : str_(std::move(str)),
                                                                                          decryption_(std::move(
                                                                                                  decryption)) {}

    void Decrypt();

private:
    void Decrypt(std::size_t i_str, std::string &decryption, DecryptedStrings &decryptions);

    const std::string str_;
    std::unordered_map<std::string, std::string> decryption_;
};

void Decryptor::Decrypt(std::size_t i_str, std::string &decryption, DecryptedStrings &decryptions) {
    if (i_str >= str_.length()) {
        decryptions.insert(decryption);
        return;
    }

    std::string key;
    for (std::size_t i = i_str; i < str_.length(); ++i) {
        if (decryption_.find(key + str_[i]) == decryption_.end()) {
            if (str_[i] == '0') {
                continue;
            }

            break;
        }

        key += str_[i];
        decryption += decryption_[key];
        Decrypt(i + 1, decryption, decryptions);
        decryption.pop_back();
    }
}

void Decryptor::Decrypt() {
    std::string decrypted_str;
    DecryptedStrings decryptions;

    Decrypt(0, decrypted_str, decryptions);

    int count = 0;
    for (const auto &decryption : decryptions) {
        std::cout << decryption << std::endl;
        if (++count >= 100) {
            break;
        }
    }
}

int main() {
    std::string encrypted_str;
//            "123";
//            "01000010101";
    std::unordered_map<std::string, std::string> decryption{
            /*{"12", "a"},
            {"1",  "b"},
            {"2",  "c"},
            {"3",  "d"},
            {"23", "e"}*/

            /*{"10", "o"},
            {"1",  "x"}*/
    };

//    Decryptor(encrypted_str, decryption).Decrypt();

    int n_code, t = 1;
    std::string c, code;

    while (std::cin >> n_code, n_code) {
        decryption.clear();
        for (int i = 0; i < n_code; ++i) {
            std::cin >> c >> code;
            decryption[code] = c;
        }

        std::cin >> encrypted_str;

        printf("Case #%d\n", t++);
        Decryptor(encrypted_str, decryption).Decrypt();
        std::cout << std::endl;
    }

    return 0;
}
