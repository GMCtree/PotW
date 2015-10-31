#include <iostream>
#include <set>
#include <string>
#include <vector>

bool valid_sentence(const std::set<std::string>& dictionary, const std::string& line, int pos) {
    bool ret;
    std::string word;
    for (unsigned i = pos; i != line.size(); ++i) {
        word += line[i];
        if (dictionary.find(word) != dictionary.end()) {
            ret = valid_sentence(dictionary, line, i+1);
            if (ret)
                return true;
        }
    }

    return dictionary.find(word) != dictionary.end();
}

int main() {
    int n;
    std::cin >> n;

    std::set<std::string> dictionary;
    for (int i = 0; i != n; ++i) {
        std::string s;
        std::cin >> s;
        dictionary.insert(s);
    }

    int m;
    std::cin >> m;
    for (int i = 0; i != m; ++i) {
        std::string s;
        std::cin >> s;
        std::cout << valid_sentence(dictionary, s, 0) << std::endl;
    }

    return 0;
}

