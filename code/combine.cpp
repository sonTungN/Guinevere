#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using std::cout, std::cin;

static std::string file_input = "input.txt";

static int rescue = 1;

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown){
        
    cout << "HP: " << HP
        << ", level: " << level
        << ", remedy: " << remedy
        << ", maidenkiss: " << maidenkiss
        << ", phoenixdown: " << phoenixdown << '\n';
}

void adventureToKoopa(int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown) {

    display(HP, level, remedy, maidenkiss, phoenixdown);
    
}

bool validateInput(int HP, int level, int remedy, int maidenkiss, int phoenixdown){
    if(HP < 1 || HP > 999){

        return false;
    } else if (level < 1 || level > 10){

        return false;
    } else if ( (remedy < 0 || remedy > 10) || 
                (maidenkiss < 0 || maidenkiss > 10) ||
                (phoenixdown < 0 || phoenixdown > 10) ){

        return false;
                }
    return true;
}

void start(){
    int HP;
    int level;
    int remedy;
    int maidenkiss;
    int phoenixdown;

    std::ifstream file;
    file.open(file_input);
    if(!file.is_open()){
        std::cerr << "Error when opening input file!" << '\n';
        std::cerr << "Try again!" << '\n';
    }

    std::string line;
    getline(file, line, ',');

    std::stringstream ssData {line};

    ssData >> HP;
    ssData >> level;
    ssData >> remedy;
    ssData >> maidenkiss;
    ssData >> phoenixdown;

    if(validateInput(HP, level, remedy, maidenkiss, phoenixdown)){
        
        cout << "Game start!" << '\n';
        adventureToKoopa(HP, level, remedy, maidenkiss, phoenixdown);
    } else {

        std::cerr << "Invalid input! Thanks for playing!" << '\n';
        exit(1);
    }
}

int main() { 
    start();

    return 0;
}