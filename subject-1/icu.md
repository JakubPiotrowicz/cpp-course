# UTF-8 operations

std::string is a sequence of bytes, not UTF-8 characters

I recommend using libraries like ICU for UTF-8 characters. There is also possibility to use std::wstring or char32_t.
