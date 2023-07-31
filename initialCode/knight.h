#ifndef KNIGHT_H
#define KNIGHT_H

#include "main.h"

void display(
        int HP, 
        int level, 
        int remedy, 
        int maidenkiss, 
        int phoenixdown, 
        int rescue);

void adventureToKoopa(
        std::string file_input, 
        int& HP, 
        int& level, 
        int& remedy, 
        int& maidenkiss,
        int& phoenixdown,
        int& rescue);

#endif