#include <Game.h>
#include <iostream>
#include <application.h>

int main()
{
    try {
        /*
        Game game;
        game.run();
         */
        application app;
        app.run();
    }
    catch (std::exception& e)
    {
        std::cout << "\nException: " << e.what() << std::endl;
    }

}