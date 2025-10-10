echo "Building . . ."
mkdir output
g++ src/main.cpp -o output/digitz -lncurses -lcurl -std=c++11