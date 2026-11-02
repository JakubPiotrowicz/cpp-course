CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0

SOURCES := $(wildcard [0-9][0-9]-*.cpp)
PROGRAMS := $(SOURCES:%.cpp=build/%)
BROKEN := $(wildcard broken/*.cpp)

.PHONY: all run broken clean
all: $(PROGRAMS)

# Każdy przykład to jeden plik, więc wystarczy jedna reguła.
build/%: %.cpp ../noisy.hpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

run: all
	@set -e; for program in $(PROGRAMS); do \
	    printf '\n>>> %s\n' "$$program"; "./$$program"; \
	done

# Celowo błędne warianty z katalogu broken/ nie wchodzą do all ani run. Błędy kompilacji są tu
# oczekiwane, więc pętla nie przerywa pracy po pierwszym z nich. Programy, które się skompilują,
# trafiają do build/broken/ (z AddressSanitizer, żeby widać było błędy pamięci).
broken:
	@mkdir -p build/broken
	@for source in $(BROKEN); do \
	    printf '\n>>> %s\n' "$$source"; \
	    $(CXX) $(CXXFLAGS) -g -fsanitize=address $$source -o build/$${source%.cpp} || true; \
	done

clean:
	$(RM) -r build
