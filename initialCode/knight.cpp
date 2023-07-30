#include "knight.h"

static int maxHP {};

std::vector<int> readEventOrder(std::string file_input){
    std::vector<int> events;

    std::ifstream file;
    file.open(file_input);
    if(file.fail()){
        std::cerr << "Fail to read 'eventOrder'" << '\n';
        exit(0);
    }
    
    std::string line;
    getline(file, line);

    int eventNumber;
    while(file >> eventNumber){
        events.push_back(eventNumber);
    }
    file.close();
    
    return events;
}

void display(
        int HP, 
        int level, 
        int remedy, 
        int maidenkiss,
        int phoenixdown, 
        int rescue) {
            
    cout << "Knight's Stats: " << '\n';
    cout << "HP: " << HP
        << ", level: " << level
        << ", remedy: " << remedy
        << ", maidenkiss: " << maidenkiss
        << ", phoenixdown: " << phoenixdown
        << ", rescue: " << rescue << '\n';
}

bool checkLevel(const int& level){
    return level < 10;
}

// bool checkHP(const int& HP, const int& phoenixdown){ // isAlive()
//     if(HP <= 0){
//         if(phoenixdown <= 0){
//             return false;
//         }
//         return true;
//     }
// }

void fightCreep( 
        const int& eventCount,
        int& HP, 
        int& level, 
        int& remedy, 
        int& maidenkiss, 
        int& phoenixdown, 
        int& rescue){

    double creepDamage[5] {1, 1.5, 4.5, 7.5, 9.5};

    int b = eventCount % 10;
    int levelO = eventCount > 6 ? (b > 5 ? b : 5) : b;
            
    if(level > levelO){
        cout << "Match wins. Level up!" << '\n';
        if(checkLevel(level)){
            level++;
        }
        
    } else if (level < levelO){
        cout << "Match-Up loses. Inflicting damage!" << '\n';
        int damage = creepDamage[eventCount - 1] * levelO * 10;
        HP -= damage;

    } else {

        return;
    }
}

void adventureToKoopa(
        std::string file_input, 
        int& HP, 
        int& level, 
        int& remedy, 
        int& maidenkiss, 
        int& phoenixdown, 
        int& rescue) {
    
    maxHP = HP;
    // static const int maxHP = HP;
    static const std::vector <int> eventOrder { readEventOrder(file_input) };

    int numberOfEvents = eventOrder.size();
    int eventCount = 0;

    while(eventCount < numberOfEvents){
        cout << "Starting the journey..." << '\n';
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        cout << rescue << '\n';

        // check condition of 'rescue'
        if(rescue = 1){
            cout << "Rescue successfully!" << '\n';
            cout << "Game end..." << '\n';
            exit(0);

        } else if (rescue = 0){
            // heal by 'phoenixdown'
            if(phoenixdown > 0){
                HP = maxHP;
                phoenixdown--;
                rescue = -1;

            } else {
                cout << "The character is dead!" << '\n';
                cout << "Can't rescue Guinevere. Game end..." << '\n';
                exit(0);
            }

        }

        switch(eventOrder.at(eventCount)){
            case 0:
                rescue = 1;
                break;
            
            case 1 ... 5:
                fightCreep(eventCount, HP, level, remedy, maidenkiss, phoenixdown, rescue);
                if(HP <= 0){
                    rescue = 0;
                }

                break;
        }

        eventCount++; // Move to next event
    } // while-loop end
}