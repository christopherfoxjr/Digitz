echo "Building . . ."
mkdir output
g++ stc/main.cpp -o output/digitz -lncurses -lcurl -std=c++11