#include "scop.hpp"

std::vector<std::string> split (const std::string &s, std::string delim) {
    std::vector<std::string> r;
    std::string tmp;

    for (std::string::size_type i = 0; i < s.length(); i++) {
        char c = s[i];

        if (delim.find(c) == std::string::npos)
            tmp += c;
        
        if ((delim.find(c) != std::string::npos || i + 1 == s.length()) && tmp.length() > 0) {
            r.push_back(tmp);
            tmp.clear();
        }
    }

    return r;
}

void printCwd() {
    char tmp[512];
    getcwd(tmp, 512) ;
    std::cout << "currentPath : " << tmp << "\n";
}