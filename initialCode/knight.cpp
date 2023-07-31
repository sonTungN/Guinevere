#include "knight.h"

static int maxHP {};
static int eventCount {0};

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

    cout << "---------------------------------------------------------------------------" << '\n';     
    cout << "| HP: " << HP
        << ", level: " << level
        << ", remedy: " << remedy
        << ", maidenkiss: " << maidenkiss
        << ", phoenixdown: " << phoenixdown
        << ", rescue: " << rescue << " |" << '\n';
    cout << "---------------------------------------------------------------------------" << '\n';
}

bool checkLevel(const int& level){
    return level < 10;
}

void fightCreep( 
        const int& eventCode,
        int& HP, 
        int& level, 
        int& remedy, 
        int& maidenkiss, 
        int& phoenixdown, 
        int& rescue){

    std::string creepName[] {"MadBear", "Bandit", "LordLupin", "Elf", "Troll"};
    double creepDamage[] {1, 1.5, 4.5, 7.5, 9.5};

    int b = (eventCount + 1) % 10;
    int levelO = (eventCount + 1)> 6 ? (b > 5 ? b : 5) : b;

    cout << "Meet " << creepName[eventCode - 1]
         << ", level: " << levelO << '\n';
    
    if(level > levelO){
        cout << "> Match-Up wins. Level up!" << '\n';
        if(checkLevel(level)){
            level++;
        }
        
    } else if (level < levelO){
        int damage = creepDamage[eventCode - 1] * levelO * 10;
        HP -= damage;
        cout << "> Match-Up loses. Inflicting " << damage << " damage!" << '\n';

    } else {
        cout << "> Match-Up draws. Continue the journey!" << '\n';
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

    // set event mode to 'continue'
    rescue = -1;
    // static const int maxHP = HP;
    maxHP = HP;
    // event order
    static const std::vector <int> eventOrder { readEventOrder(file_input) };
    int numberOfEvents = eventOrder.size();
    // int eventCount = 1;
    cout << "Starting the journey..." << '\n';

#if 1
    while (true){
        // check condition of 'rescue'
        if(rescue == 1 || eventCount == numberOfEvents){
            cout << "Rescue successfully!" << '\n';
            cout << "Game end..." << '\n';
            exit(0);
            
        } else if (rescue == 0){
            // heal by 'phoenixdown'
            if(phoenixdown > 0){
                cout << "*** Using phoenixdown to heal maxHP ***" << '\n';
                HP = maxHP;
                phoenixdown--;
                rescue = -1;

            } else {
                cout << "The character is dead!" << '\n';
                cout << "Can't rescue Guinevere. Game end..." << '\n';
                exit(0);
            }
        }
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        int eventCode { eventOrder.at(eventCount) };

        switch(eventCode){
            case 0:
                rescue = 1;
                break;
            
            case 1 ... 5:
                fightCreep(eventCode, HP, level, remedy, maidenkiss, phoenixdown, rescue);
                if(HP <= 0){
                    rescue = 0;
                }
                break;
        }

        eventCount++; // Move to next event
    } // while-loop end
#endif
}