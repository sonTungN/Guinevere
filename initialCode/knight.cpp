#include "knight.h"

static int maxHP {};
static int eventCount {0};
const std::string creepName[] {"MadBear", "Bandit", "LordLupin", "Elf", "Troll"};
const double creepDamage[] {1, 1.5, 4.5, 7.5, 9.5};

int b;
int levelO;

static int tinyCountDown = 0;
static bool isTiny { false };

static int frogCountDown = 0;
static bool isFrog { false };
int previousLevel {};

//implement function declaration


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
    
    b = (eventCount + 1) % 10;
    levelO = (eventCount + 1)> 6 ? (b > 5 ? b : 5) : b;

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
    }
}

void cureTiny(bool& isTiny, int& HP, int& remedy){
    if(isTiny){
        if(remedy > 0){
            cout << "*** Using remedy to cure TINY ***" << '\n';
            HP *= 5;
            if(HP > maxHP){
                HP = maxHP;
            }
            remedy--;
        } else {
            tinyCountDown = 3;
        }
    }
}

void fightShaman(
        int& HP, 
        int& level, 
        int& remedy, 
        int& maidenkiss, 
        int& phoenixdown, 
        int& rescue){
    
    b = (eventCount + 1) % 10;
    levelO = (eventCount + 1)> 6 ? (b > 5 ? b : 5) : b;

    cout << "Meet Shaman" << ", level: " << levelO << '\n';
    if(isTiny || isFrog){
        cout << "Skip the match with Shaman." << '\n';
        return; 
    }

    if(level > levelO){
        cout << "> Match-Up wins. Level up!" << '\n';
        if(level <= 8){
            level += 2;
        } else {
            level = 10;
        }
        
    } else if (level < levelO){
        cout << "Match-Up loses. Becoming TINY..." << '\n'; 
        if(HP < 5){
            HP = 1;
        } else {
            HP = (int)(HP / 5);
        }
        isTiny = true;

    } else {
        cout << "> Match-Up draws. Continue the journey!" << '\n';
    }
}

void cureFrog(bool& isFrog, int& level, int& maidenkiss){
    if(isFrog){
        if(maidenkiss > 0){
            cout << "*** Using maidenkiss to cure FROG ***" << '\n';
            level = previousLevel;
            isFrog = false;
            maidenkiss--;

        } else {
            frogCountDown = 3;
        }
    }
}

void fightSiren(
        int& HP, 
        int& level, 
        int& remedy, 
        int& maidenkiss, 
        int& phoenixdown, 
        int& rescue){
    
    b = (eventCount + 1) % 10;
    levelO = (eventCount + 1)> 6 ? (b > 5 ? b : 5) : b;

    cout << "Meet Siren Vajsh" << ", level: " << levelO << '\n';
    if(isTiny || isFrog){
        cout << "Skip the match with Siren Vajsh." << '\n';
        return;
    }
    
    if(level > levelO){
        cout << "> Match-Up wins. Level up!" << '\n';
        if(level <= 8){
            level += 2;
        } else {
            level = 10;
        }
        
    } else if (level < levelO){
        cout << "Match-Up loses. Becoming a FROG..." << '\n'; 
        previousLevel = level;
        level = 1;
        isFrog = true;

    } else {
        cout << "> Match-Up draws. Continue the journey!" << '\n';
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
    
    cout << "Starting the journey..." << '\n';


#if 1
    while (true){
        // check TINY countdown
        if(tinyCountDown >= 0 && isTiny){
            cout << "Tiny expired in: " << tinyCountDown << '\n';
            if(tinyCountDown == 0){
                cout << "*** TINY expired ***" << '\n';
                isTiny = false;
                HP *= 5;
                if(HP > maxHP){
                    HP = maxHP;
                }
            }
            tinyCountDown--;
        }
        // check FROG countdown
        if(frogCountDown >= 0 && isFrog){
            cout << "Frog expired in: " << frogCountDown << '\n';
            if(frogCountDown == 0){
                cout << "*** FROG expired ***" << '\n';
                isFrog = false;
                level = previousLevel;
            }
            frogCountDown--;
        }

        // check 'rescue' & eventCount
        if (rescue == 0){
            // heal by 'phoenixdown'
            if(phoenixdown > 0){
                cout << "*** Using phoenixdown to heal maxHP ***" << '\n';
                HP = maxHP;
                phoenixdown--;
                rescue = -1;

                isTiny = false;
                tinyCountDown = 0;

            } else {
                cout << "The character is dead. (HP: " << HP << " )" << '\n';
                cout << "Can't rescue Guinevere. Game end..." << '\n';
                exit(0);
            }
        } else if (rescue == 1 || eventCount == numberOfEvents){
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            cout << "Rescue successfully!" << '\n';
            cout << "Game end..." << '\n';
            exit(0);
        }
        
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        int eventCode { eventOrder.at(eventCount) };

        // run event
        switch(eventCode){
            case 0:
                rescue = 1;
                break;
            
            case 1 ... 5:
                fightCreep(eventCode, HP, level, remedy, maidenkiss, phoenixdown, rescue);

                break;
            
            case 6:
                fightShaman(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                cureTiny(isTiny, HP, remedy);

                break;
            
            case 7:
                fightSiren(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                cureFrog(isFrog, level, maidenkiss);

                break;
        }

        if(HP <= 0){
            rescue = 0;
        }

        eventCount++; // Move to next event
    } // while-loop end
#endif
}

