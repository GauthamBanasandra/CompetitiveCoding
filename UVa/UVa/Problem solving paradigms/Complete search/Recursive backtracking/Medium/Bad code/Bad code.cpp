//
// Created by gauth on 09-05-2018.
//

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <set>
#include <cassert>

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
    for (std::size_t i = i_str, n_relax = 2; n_relax && (i < str_.length()); ++i, --n_relax) {
        key += str_[i];
        if (decryption_.find(key) == decryption_.end()) {
            if (key[0] == '0') {
                assert(key.length() == 1);
                key.pop_back();
                ++n_relax;
            }

            continue;
        }

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
    std::unordered_map<std::string, std::string> decryption{};

    int n_code, t = 1;
    std::string c, code, line;

    while (std::cin >> n_code, n_code) {
        decryption.clear();
        std::cin.ignore();
        for (int i = 0; i < n_code; ++i) {
            std::getline(std::cin, line);
            std::istringstream tokenizer(line);
            tokenizer >> c >> code;
            decryption[code] = c;
        }

        std::getline(std::cin, encrypted_str);

        printf("Case #%d\n", t++);
        Decryptor(encrypted_str, decryption).Decrypt();
        std::cout << std::endl;
    }

    return 0;
}
