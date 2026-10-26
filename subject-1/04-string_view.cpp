#include <string>
#include <iostream>

void print(std::string_view s) { std::cout << s << '\n'; }

int main(){
    print("Hello, World!");
    std::string str = "Goodbye, World!";
    print(str);
    return 0;
}
