CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0

SOURCES := $(wildcard [0-9][0-9]-*.cpp)
PROGRAMS := $(SOURCES:%.cpp=build/%)

# Celowo błędne warianty z katalogu broken/ nie wchodzą do all ani run. Buduje je osobny cel.
BROKEN := $(patsubst %.cpp,build/%,$(wildcard broken/*.cpp))

.PHONY: all run broken clean
all: $(PROGRAMS)

# Każdy przykład to jeden plik, więc wystarczy jedna reguła.
build/%: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

run: all
	@set -e; for program in $(PROGRAMS); do \
	    printf '\n>>> %s\n' "$$program"; "./$$program"; \
	done

broken: $(BROKEN)

clean:
	$(RM) -r build

# AddressSanitizer pokazuje błąd, który bez niego mógłby przejść niezauważony.
build/broken/copy-to-empty: CXXFLAGS += -g -fsanitize=address
