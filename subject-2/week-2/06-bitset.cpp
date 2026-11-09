// std::bitset: zbiór flag o rozmiarze znanym w czasie kompilacji.
// Kontenery flat_set i flat_map (C++23) są opisane w README, ale nie ma ich w g++ 13.
#include <bitset>
#include <iostream>

enum class Permission {
    Read,
    Write,
    Execute
};

int main() {
    std::bitset<8> flags;
    flags.set(1);
    flags.set(3);
    flags[5] = true;
    std::cout << "flags = " << flags << ", ustawionych bitów: " << flags.count() << '\n';
    std::cout << std::boolalpha << "test(3): " << flags.test(3) << ", test(4): " << flags.test(4) << '\n';

    flags.flip();
    std::cout << "po flip() = " << flags << '\n';

    std::bitset<8> from_string("1011");
    std::bitset<8> from_number(0b1010);
    std::cout << "z napisu: " << from_string << ", z liczby: " << from_number << '\n';
    std::cout << "and: " << (from_string & from_number) << ", or: " << (from_string | from_number)
              << ", xor: " << (from_string ^ from_number) << ", << 2: " << (from_string << 2) << '\n';
    std::cout << "jako liczba: " << from_string.to_ulong() << '\n';

    std::bitset<3> permissions;
    permissions.set(static_cast<std::size_t>(Permission::Read));
    permissions.set(static_cast<std::size_t>(Permission::Execute));
    std::cout << "uprawnienia (Execute, Write, Read): " << permissions << '\n';
}
