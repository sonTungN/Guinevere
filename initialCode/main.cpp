#include "knight.h"

int main(int argc, char ** argv) {

    std::string file_input(argv[1]);

    int HP;
    int level;
    int remedy;
    int maidenkiss;
    int phoenixdown;
    int rescue;
    
    adventureToKoopa(file_input, HP, level, remedy, maidenkiss, phoenixdown, rescue);

    return 0;
}