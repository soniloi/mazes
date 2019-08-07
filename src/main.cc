#include <iostream>

#include "game.h"

using namespace std;

int main(int argc, char ** argv) {
    Game game;
    int result = game.run();
    std::cout << "result: " << result << std::endl;
}
