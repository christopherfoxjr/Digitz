echo "Building . . ."
mkdir -p output
g++ src/main.cpp -o output/digitz -lncurses -lcurl -std=c++17
