# Compile all cpp files.
CPP_FILES := $(wildcard subject-4/*.cpp)
TARGETS := $(CPP_FILES:.cpp=)
CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra
LDFLAGS :=
.PHONY: all clean
all: $(TARGETS)
$(TARGETS): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)
clean:
	rm -f $(TARGETS)
