CXX := g++
CC := gcc
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -O0

PROGRAMS := build/01-build-demo build/02-state-demo build/03-macros build/04-using \
            build/05-initialization build/06-c-linkage-demo build/07-forward
OBJECTS := build/01-build/main.o build/01-build/math.o \
           build/02-state/main.o build/02-state/counter.o \
           build/06-c-linkage/main.o build/06-c-linkage/api.o

.PHONY: all run clean
all: $(PROGRAMS)

build/01-build-demo: build/01-build/main.o build/01-build/math.o

build/02-state-demo: build/02-state/main.o build/02-state/counter.o

build/06-c-linkage-demo: build/06-c-linkage/main.o build/06-c-linkage/api.o

# The three multi-file programs share the same linking command.
build/01-build-demo build/02-state-demo build/06-c-linkage-demo:
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

# -c creates an object file; -MMD -MP records header dependencies in a .d file.
build/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Compile actual C code with the C compiler, then link using the C++ driver.
build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# The remaining examples each fit in one source file.
build/%: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

-include $(OBJECTS:.o=.d)

run: all
	@set -e; for program in $(PROGRAMS); do \
	    printf '\n>>> %s\n' "$$program"; "./$$program"; \
	done

clean:
	$(RM) -r build
