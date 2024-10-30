#include <iostream> // standard library
#include <string> // also storage
#include <vector> // for storage
#include <cstdlib> // same thing as below
#include <ctime> // for random
#include <chrono> // for wait function
#include <thread> // for chrono
#include <algorithm> // I use this for std::remove

using namespace std;
using namespace std::chrono;
using std::cout;
using std::endl;
using std::cin;
using std::thread;

//Stat shop class
class StatShop1 {  //still need to add the rest of the shop class like inv and add and sell/ display logic
public:

    int Str_Potion;
    int Spd_Potion;
    vector <string> Shop1Inventory; //shop1 inventory

     StatShop1(int Str_Potion, int Spd_Potion) : Str_Potion(0), Spd_Potion(0) {
         for (int i = 0; i < 5; ++i) {
             Shop1Inventory.push_back("Str_Potion");
             Shop1Inventory.push_back("Spd_Potion");
             Shop1Inventory.push_back("Health Potion");
         }
    }


};

void DisplayShop1Menu() {
    cout << " \n";
    cout << "-Potions/Consumables-" << endl;
    cout << "-_________-_________-" << endl;
    cout << "[1]+HP Potion \n";
    cout << "[2]+10STR Potion \n";
    cout << "[3]+10SPD Potion \n";
    cout << "_---------_---------_" << endl;
    cout << " \n";
}
// Function to display StatShop1 inventory
void displayStatShop1Inventory(const StatShop1& StatShop1) {
    cout << "\n**CONSOLE:**" << endl;
    cout << "Your Inventory: \n";
    cout << "-_____-_____-" << endl;
    for (const auto& item : StatShop1.Shop1Inventory) {
        cout << item << " \n";
    }
    cout << endl;
    cout << "_-----_-----_" << endl;
}

// Character class
class Character {
public:
    string name;
    int age;
    int Str, Mag, Stm, Spd, Int, Wis, Con, Cha;
    int health;
    int level;
    int xp;
    int xpToLevel;
    vector<string> inventory;
    vector<int> Wallet;
    
    void addGold(int amount) {
        Wallet.push_back(amount);
    }

    Character(string n, int a) : name(n), age(a), Str(0), Mag(0), Stm(0), Spd(0), Int(0), Wis(0), Con(0), Cha(0), health(100), level(1), xp(0), xpToLevel(100) {
        inventory.push_back("Sword"); // Adds sword to inv
        for (int i = 0; i < 5; ++i) { // Adds 5 health potions to inv
            inventory.push_back("Health Potion");
        }
    }

    void levelUp() {
        while (xp >= xpToLevel) {
            xp -= xpToLevel;
            level++;
            xpToLevel += 50; // Increase XP require for the next level
            Str += 2; // Increase stats on level up
            Mag += 1;
            health += 10; // Increase health on level up
            cout << "\n**CONSOLE:**" << endl;
            cout << "Congratulations! You leveled up to level " << level << "!\n";
            cout << "Your stats have increased!\n";
        }
    }
};

// NPC class for encounters
class NPC {
public:
    string type;
    int health;
    int Str;
    int xpReward;

    NPC(string t, int h, int s, int xp) : type(t), health(h), Str(s), xpReward(xp) {}
};

// Function to display inventory
void displayInventory(const Character& character) {
    cout << "\n**CONSOLE:**" << endl;
    cout << "Your Inventory: \n";
    cout << "-_____-_____-" << endl;
    for (const auto& item : character.inventory) {
        cout << item << " \n";
    }
    cout << endl;
    cout << "_-----_-----_" << endl;
}

// Fight function
void fight(Character& player, NPC& npc) {
    cout << "\n**CONSOLE:**" << endl;
    cout << "A wild " << npc.type << " appears with " << npc.health << " health!\n";

    while (player.health > 0 && npc.health > 0) {
        cout << "\n**CONSOLE:**" << endl;
        cout << "Your health: " << player.health << ", " << npc.type << " health: " << npc.health << endl;
        cout << "\n**CONSOLE:**" << endl;
        cout << "Choose an action: [1] Attack [2] Use Health Potion\n";
        int action;
        cin >> action;

        if (action == 1) {
            cout << "\n**CONSOLE:**" << endl;
            cout << "You attack the " << npc.type << "!\n";
            npc.health -= player.Str;
            cout << "You deal " << player.Str << " damage!\n";
        }
        else if (action == 2) {
            auto potionIt = find(player.inventory.begin(), player.inventory.end(), "Health Potion");
            if (potionIt != player.inventory.end()) {
                cout << "\n**CONSOLE:**" << endl;
                cout << "You use a Health Potion!\n";
                player.health += 80;
                cout << "\n**CONSOLE:**" << endl;
                cout << "You regain 80 health!\n";
                player.inventory.erase(potionIt); // Remove one potion
            }
            else {
                cout << "\n**CONSOLE:**" << endl;
                cout << "You have no Health Potions left!\n";
            }
        }
        else {
            cout << "\n**CONSOLE:**" << endl;
            cout << "Invalid action!\n";
            continue;
        }

        if (npc.health > 0) {
            player.health -= npc.Str;
            cout << "\n**CONSOLE:**" << endl;
            cout << "The " << npc.type << " attacks you for " << npc.Str << " damage!\n";
        }
    }

    if (player.health <= 0) {
        cout << "\n**CONSOLE:**" << endl;
        cout << "You have been defeated by the " << npc.type << "!\n";
    }
    else {
        cout << "\n**CONSOLE:**" << endl;
        cout << "You defeated the " << npc.type << "!\n";
        player.xp += npc.xpReward; // Award XP for defeating the NPC
        cout << "You gain " << npc.xpReward << " XP!\n";
        player.levelUp(); // Check for level up
    }
}

// Encounter function
void encounter(Character& character) {
    vector<NPC> npcs = {
        NPC("Goblin", 30, 5, 25),
        NPC("Orc", 40, 7, 50),
        NPC("Bandit", 50, 6, 40),
        NPC("BanditChief", 70, 4, 20),
        NPC("Lord Calum(BOSS of Lag)", 90, 10, 40)
    };

    // Calum boss is a little easter egg, there is random chance of encountering him...I thought this would be funny


    for (auto& npc : npcs) {
        if (character.health > 0) {
            fight(character, npc);
        }
        else {
            break;
        }
    }
}

// Main Menu Function
void LineageMenu() {
    cout << "-______________________________-" << endl;
    cout << "[1] Bagger " << endl; // ++2 Wis
    cout << "[2] Noble " << endl; // ++3 CHA
    cout << "[3] Monster " << endl; // ++5 STM
    cout << "[4] Assassin " << endl; // ++3 SPD
    cout << "[5] Samurai " << endl; // ++1 CON
    cout << "[6] -Exit- " << endl;
    cout << "_-------------------------------_" << endl;
}

// Sub Menu Function
void ClassMenu() {
    cout << "-______________________________-" << endl;
    cout << "[1] Wizard " << endl; // ++3 MAG
    cout << "[2] Barbarian " << endl; // ++4 STR
    cout << "[3] Monk " << endl; // ++2 CHA
    cout << "[4] Rogue " << endl; // ++2 MAG
    cout << "[5] Wraith " << endl; // ++6 STM
    cout << "[6] -Exit- " << endl;
    cout << "_------------------------------_" << endl;
}

// Character Stats Menu
void StatsMenu(const Character& character) {
    cout << "-_______________________________-" << endl;
    cout << "Str: " << character.Str << " Mag: " << character.Mag << endl;
    cout << "Stm: " << character.Stm << " Spd: " << character.Spd << endl;
    cout << "Int: " << character.Int << " Wis: " << character.Wis << endl;
    cout << "Con: " << character.Con << " Cha: " << character.Cha << endl;
    cout << "Health: " << character.health << endl;
    cout << "Level: " << character.level << endl;
    cout << "_-------------------------------_" << endl;
}

// Sub Character Information Menu
void SubStatsMenu(const string& name, const string& Lineage_choice, const string& Class_choice, int age) {
    cout << "-_______________________________-" << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Lineage: " << Lineage_choice << endl;
    cout << "Class: " << Class_choice << endl;
    cout << "_-------------------------------_" << endl;
}

// Object Option Menu
void ObjectOptionMenu() {
    cout << "-___________-___________________-" << endl;
    cout << "|[1] Inspect : [2] Touch|\n";
    cout << "|[3] Pick Up : [4] Leave|\n";
    cout << "_-----------_-------------------_" << endl;
}
// Quest Option Menu
void QuestOptionMenu() {
    cout << "-___________-___________________-" << endl;
    cout << "|[1] Interact : [2] Ignore |\n";
    cout << "_-----------_-------------------_" << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0))); // you have to seed for random number generation in main fnctn
    Character character("Player", 20); // Create a character
    int Exit_strat = 0;

    // player starting gold
    int gold = 100;
    character.addGold(gold);
    
    
    
    
    // Choices
    int choice = 0, choice2 = 0, Quest1Choice = 0;
    int Str_bonus = 0, Mag_bonus = 0, Stm_bonus = 0, Spd_bonus = 0, Int_bonus = 0, Wis_bonus = 0, Con_bonus = 0, Cha_bonus = 0;

    //Adds Basestats to player stats
    Str_bonus += 5;
    Mag_bonus += 5;
    Stm_bonus += 5;
    Spd_bonus += 5;
    Int_bonus += 5;
    Wis_bonus += 5;
    Con_bonus += 5;
    Cha_bonus += 5;

    do {
        cout << "RPG_Chrctr_Creator v1.0\n\n";
        cout << "\n**CONSOLE:**" << endl;
        cout << "Welcome Adventurer,\n" << endl;
        this_thread::sleep_for(milliseconds(1500));
        cout << "\n**CONSOLE:**" << endl;
        cout << "What is your name?: " << endl;


        string name;
        string Class_choice;
        string Lineage_choice;
        int age;
        cin >> name;
        cout << "\n**CONSOLE:**" << endl;
        cout << "What is your age?: " << endl;
        cin >> age;

        character.name = name;
        character.age = age;
        cout << "\n**CONSOLE:**" << endl;
        cout << "\nHello there! " << character.name << endl;

        cout << "\n**CONSOLE:**" << endl;
        cout << "\n| Choose Your Lineage |\n";
        LineageMenu();

        do {


            //choice start
            cin >> choice;
            switch (choice) {
            case 1:
                cout << "\n**CONSOLE:**" << endl;
                cout << "\nAh yes, a poor Bagger indeed" << "(+2 Wis)\n";
                Wis_bonus += 2;
                Lineage_choice = "Bagger";
                choice = 9;
                continue;
            case 2:
                cout << "\n**CONSOLE:**" << endl;
                cout << "\nNoble indeed, great things are to be expected of you" << "(+3 Cha)\n";
                Cha_bonus += 3;
                Lineage_choice = "Noble";
                choice = 9;
                continue;
            case 3:
                cout << "\n**CONSOLE:**" << endl;
                cout << "\nYou're a Monster!, selfish and ugly yet dangerous!" << "(+5 Stm)\n";
                Stm_bonus += 5;
                Lineage_choice = "Monster";
                choice = 9;
                continue;
            case 4:
                cout << "\n**CONSOLE:**" << endl;
                cout << "\nAn Assassin is sneaky and agile, use this info wisely" << "(+3 Spd)\n";
                Spd_bonus += 3;
                Lineage_choice = "Assassin";
                choice = 9;
                continue;
            case 5:
                cout << "\n**CONSOLE:**" << endl;
                cout << "\nA Samurai, honorable yet deadly!" << "(+1 Con)\n";
                Con_bonus += 1;
                Lineage_choice = "Samurai";
                choice = 9;
                continue;
            case 6:
                cout << "Exitng game, goodbye! " << endl;
                cout << "\n:)\n";
                this_thread::sleep_for(seconds(3));
                return 0; // this exits the menu
            default:
                cout << "\n**CONSOLE:**" << endl;
                cout << "Invalid choice. Please try again.\n";
                LineageMenu();
            }
        } while (choice != 9);

        // Class Selection
        cout << "\n**CONSOLE:**" << endl;
        cout << "\n| Choose Your Class |\n";
        ClassMenu();
        



        do {
            cin >> choice2;
            switch (choice2) {
            case 1:
                cout << "\n**CONSOLE:**" << endl;
                cout << "\nWizard, a master of magic arts" << "(+3 Mag)\n";
                Mag_bonus += 3;
                Class_choice = "Wizard";
                choice2 = 9;
                continue;
            case 2:
                cout << "\n**CONSOLE:**" << endl;
                cout << "\nBarbarian, strong and fierce" << "(+4 Str)\n";
                Str_bonus += 4;
                Class_choice = "Barbarian";
                choice2 = 9;
                continue;
            case 3:
                cout << "\n**CONSOLE:**" << endl;
                cout << "\nMonk, a master of self control" << "(+2 Cha)\n";
                Cha_bonus += 2;
                Class_choice = "Monk";
                choice2 = 9;
                continue;
            case 4:
                cout << "\n**CONSOLE:**" << endl;
                cout << "\nRogue, sneaky and clever" << "(+2 Mag)\n";
                Mag_bonus += 2;
                Class_choice = "Rogue";
                choice2 = 9;
                continue;
            case 5:
                cout << "\n**CONSOLE:**" << endl;
                cout << "\nWraith, a magical ghostly being" << "(+6 Stm)\n";
                Stm_bonus += 6;
                Class_choice = "Wraith";
                choice2 = 9;
                continue;
            case 6:
                cout << "Exitng game, goodbye! " << endl;
                cout << "\n:)\n";
                this_thread::sleep_for(seconds(3));
                return 0; // this exit the menu
            default:
                cout << "\n**CONSOLE:**" << endl;
                cout << "Invalid choice. Please try again.\n";
                ClassMenu();
            }
        } while (choice2 != 9);

        // Apply bonuses to character stats
        character.Str += Str_bonus;
        character.Mag += Mag_bonus;
        character.Stm += Stm_bonus;
        character.Spd += Spd_bonus;
        character.Int += Int_bonus;
        character.Wis += Wis_bonus;
        character.Con += Con_bonus;
        character.Cha += Cha_bonus;

        // Display player stats and inventory
        SubStatsMenu(character.name, Lineage_choice, Class_choice, character.age);
        StatsMenu(character);
        displayInventory(character);
        for (int money : character.Wallet) {
            std::cout << "Wallet contains: " << money << " gold." << std::endl;
        }
        this_thread::sleep_for(seconds(6));
        // Start Encounter Journy
        cout << "\n**NARRATOR:**" << endl;
        cout << "\nYour journey begins in a dark shack in a clearing in the forest...\n";
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**" << endl;
        cout << "You wander into a forest unknowing of what is in there...\n";
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**" << endl;
        cout << "\nYou come across a dirt path leading to a distant white light.\n";
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**" << endl;
        cout << "You decide to follow this dirt path toward the white light.\n";
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**" << endl;
        cout << "\nAfter following the dirt path for a while you hear a noise,...\n";
        this_thread::sleep_for(milliseconds(2500));

        // Random Encounter
        if (rand() % 2 == 0) { // 50% chance of encountering an NPC
            cout << "\n**NARRATOR:**" << endl;
            cout << "A SMALL GROUP OF MOBS!!!\n\n";
            encounter(character);
        }
        else {
            cout << "\n**NARRATOR:**" << endl;
            cout << "It was nothing.\n";
            this_thread::sleep_for(seconds(2));

        }

        cout << "\n**NARRATOR:**" << endl;
        cout << "You continue your journey down the path.\n";
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**" << endl;
        cout << "You hear another noise coming from the bushes up ahead...\n\n";
        cout << "\n**NARRATOR:**" << endl;
        cout << "When you get to the bushes you see a small tiny man with a small shopcart. " << endl;
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**\n" << endl;
        cout << "Hmmm.. must be a dawf, ive heard storys of these tiny little people." << endl;

        cout << "\n**CONSOLE:**" << endl;
        cout << "|What would you like to do?|" << endl;
        QuestOptionMenu();
        cin >> Quest1Choice;
        //setting this to 0 incase it already holds value above so i can reuese this integer
        choice = 0;
        choice2 = 0;
        do {
            switch (Quest1Choice) {
            case 1:
                cout << "\n**NARRATOR:**" << endl;
                cout << "You decided to talk to the mysterious shopcart dwarf. \n";
                this_thread::sleep_for(seconds(2));
                cout << "\n**YOU:**" << endl;
                cout << "Hey you, who are you?, you say to the mysterious dwarf. \n";
                this_thread::sleep_for(seconds(3));
                cout << "\n**MysteriousDwarf:**" << endl;
                cout << "I am a traveling dawrf, wondering these woods with things to sell" << endl;
                this_thread::sleep_for(seconds(2));
                cout << "\n**MysteriousDwarf:**" << endl;
                cout << "\nWould you like to see what I have, maybe you might find something you need. " << endl;
                this_thread::sleep_for(seconds(2));
                cout << "\n**YOU:**" << endl;
                cout << "Yes please." << endl;
                DisplayShop1Menu();
                cin >> choice2;
                do {
                    switch (choice2) {
                    case 1:  // adds HP Potion to inv
                        if {
                            character.Wallet(amount) = < 50;
                            cout << "Adding item to inventory " << endl;
                            inventory.push_back("Health Potion");

                        }
                        break;
                    case 2:  // adds 10 STR Potion to inv          // yet to be done
                        break;
                    case 3:  // adds 10 SPD Potion to inv
                        break;
                    default:
                        cout << "\n**CONSOLE:**" << endl;
                        cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                } while (choice2 != 11);

                break;
            case 2:
                cout << "\n**NARRATOR:**" << endl;
                cout << "You choose to ignore the mysterious shopcart dwarf and continue down the path on your journey." << endl;
                this_thread::sleep_for(seconds(3));
                choice = 11;
                break;
            default:
                cout << "\n**CONSOLE:**" << endl;
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        } while (choice != 11);
        // putting these back to 0 so it can be used again
        choice = 0;
        choice2 = 0;
        cout << "\n**NARRATOR:**" << endl;
        cout << "As you continue to walk, you think to yourself, 'I feel like I have been walking forever'\n";
        this_thread::sleep_for(seconds(4));
        cout << "\n**NARRATOR:**" << endl;
        cout << "You see a building up ahead, off to the side of the path.\n";
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**" << endl;
        cout << "Once at the door, you decide to enter the mysterious building.\n";
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**" << endl;
        cout << "When you open the door, inside you see...\n\n";
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**" << endl;
        cout << "...a pouch on the floor inside. " << endl;




        //End Of The Game//
        Exit_strat = 9;
    } while (Exit_strat != 9); // This keeps the game running

    return 0;
}