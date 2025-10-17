template <typename Container>
void print_reverse(const Container& c) {
    for (auto it = c.rbegin(); it != c.rend(); ++it)
        std::cout << *it << " ";
}
