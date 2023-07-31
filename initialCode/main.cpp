#include "knight.h"

bool validateValue(
        int HP, 
        int level, 
        int remedy, 
        int maidenkiss, 
        int pheonixdown){

            if(HP < 1 || HP > 999){
                return false;
            } else if (level < 1 || level > 10){
                return false;
            } else if (
                    (remedy < 0 || remedy > 99) ||
                    (maidenkiss < 0 || maidenkiss > 99) ||
                    (pheonixdown < 0 || maidenkiss > 99) ){
                
                return false;
            }
        return true;
}

int main(int argc, char** argv) {

    std::string file_input { argv[1] };

    int HP;
    int level;
    int remedy;
    int maidenkiss;
    int phoenixdown;
    int rescue;

    std::ifstream file;
    file.open(file_input);
    if(!file.is_open()){
        std::cerr << "Error when opeing 'input.dat'!" << '\n';
        return -1;
    }    
    
    file >> HP >> level >> remedy >> maidenkiss >> phoenixdown;
    file.close();

    if(validateValue(HP, level, remedy, maidenkiss, phoenixdown)){

        adventureToKoopa(file_input, HP, level, remedy, maidenkiss, phoenixdown, rescue);
    }

    return 0;
}