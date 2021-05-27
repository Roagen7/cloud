#include "src/Game.h"


int main(int argc, char *argv[]){
    Game game(400,20,3);

    while(game.running()){


        game.update();
        game.render();



    }



}
