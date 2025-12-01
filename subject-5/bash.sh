# Compiling and running:
g++ -o task1a task1a.cpp
valgrind --leak-check=full ./task1a

g++ -o task1b task1b.cpp
valgrind --leak-check=full ./task1b

g++ -o task1c task1c.cpp
valgrind --leak-check=full ./task1c
