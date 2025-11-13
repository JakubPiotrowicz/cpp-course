# Compile each .cpp into a .o file
g++ -std=c++23 -c main.cpp -o main.o
g++ -std=c++23 -c user1.cpp -o user1.o

# Now inspect the "symbols" (functions, variables) in each object file
# We are looking for the compiled code for performAction.
# The `| grep performAction` filters the output for the function we care about.
nm main.o | grep performAction
nm user1.o | grep performAction
