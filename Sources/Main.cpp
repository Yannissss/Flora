#include "Utils.h"
#include "Game.h"

using namespace std;

Config defaultConfig {
    1024,        // Window width
    768,         // Window height
    60,          // Window framerate cap
    250,         // Default view distance
    125,         // Travel speed in pixel/second
    65*PI/180,   // Angular speed in rad/second
    15.5,        // Scale sensitivity
};

int main(int argc, char const *argv[])
{
    Game game(defaultConfig);
    if( !game.init() )
    {
        cout << ERR << "Quiting due to error ..." << endl;
        return 1;
    } else {
        game.loop();
    }
    cout << INFO << "Successfully closed the program" << endl;
    return 0;
}
