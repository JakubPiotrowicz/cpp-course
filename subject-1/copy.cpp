#include <string>
#include <iostream>

void print(std::string s) { std::cout << s; } // copy!

void print(const std::string& s) { std::cout << s; } // no copy!

int main(){
    return 0;
}
