CXX       = g++-14
CXXFLAGS  = -std=c++23 -fmodules-ts -Wall -Wextra -g
GCM       = gcm.cache/MathEngine.gcm

.PHONY: all clean run
all: app

# 1) Interfejs: generuje math_engine.o i gcm.cache/MathEngine.gcm
math_engine.o $(GCM): math_engine.ixx
	$(CXX) $(CXXFLAGS) -x c++-module -c $< -o math_engine.o

# 2) Implementacja modułu
math_engine_impl.o: math_engine.cpp $(GCM)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -fmodule-file=MathEngine=$(GCM)

# 3) Konsument modułu
main.o: main.cpp $(GCM)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -fmodule-file=MathEngine=$(GCM)

# 4) Link
app: math_engine.o math_engine_impl.o main.o
	$(CXX) $^ -o $@

run: app
	./app

clean:
	rm -rf app *.o gcm.cache
