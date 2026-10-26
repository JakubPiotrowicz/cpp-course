#include <string>
#include <iostream>

void print(std::string s) { std::cout << s; } // copy!

void print(const std::string& s) { std::cout << s; } // no copy!

// void print2(const std::string& s) { 
//     s += "abd";
//     std::cout << s;
// } // no copy!

// void print3(std::string& s) { 
//     s += "abd";
//     std::cout << s; 
// } // no copy!

int main() {
    // std::string str = "Hello";
    // print2(str);
    return 0;
}
