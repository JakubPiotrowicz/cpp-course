# Compile each .cpp into a .o file
g++ -std=c++23 -c main.cpp -o main.o
g++ -std=c++23 -c user1.cpp -o user1.o
g++ -std=c++23 -c heavy_template.cpp -o heavy_template.o

# Inspect the user object files first
echo "--- Symbols in main.o ---"
nm main.o | grep performAction

echo "--- Symbols in user1.o ---"
nm user1.o | grep performAction

# Now inspect the template's own object file
echo "--- Symbols in heavy_template.o ---"
nm heavy_template.o | grep performAction
