CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0

SOURCES := $(wildcard [0-9][0-9]-*.cpp)
PROGRAMS := $(SOURCES:%.cpp=build/%)

# Celowo błędne warianty z katalogu broken/ nie wchodzą do all ani run. Buduje je osobny cel.
BROKEN := $(patsubst %.cpp,build/%,$(wildcard broken/*.cpp))

.PHONY: all run broken clean
all: $(PROGRAMS)

# Każdy przykład to jeden plik, więc wystarczy jedna reguła.
build/%: %.cpp alloc_counter.hpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

# Przykład 01 czyta dane, więc dostaje je z potoku. Pozostałe nie czytają nic.
run: all
	@set -e; for program in $(PROGRAMS); do \
	    printf '\n>>> %s\n' "$$program"; \
	    case "$$program" in \
	        build/01-io) printf 'Ala 3\nAla ma kota\nostatni wiersz\n' | "./$$program" ;; \
	        *) "./$$program" < /dev/null ;; \
	    esac; \
	done

broken: $(BROKEN)

clean:
	$(RM) -r build
