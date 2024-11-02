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
using std::find;



// Blacksmith1 shop class
class Blacksmith1 {
public:
    string IronArmour;
    string IronSword;
    string IronDagger;

    vector<string> BlacksmithInventory; // shop1 inventory

    Blacksmith1(string IronArmour, string IronSword, string IronDagger) : IronArmour(), IronSword(), IronDagger() {
        for (int i = 0; i < 5; ++i) {
            BlacksmithInventory.push_back("IronArmour");
            BlacksmithInventory.push_back("IronSword");
            BlacksmithInventory.push_back("IronDagger");
        }
    }
    void DisplayShop2Menu() {
        cout << " \n";
        cout << "-Weapons/Armour-" << endl;
        cout << "-_________-_________-" << endl;
        cout << "[1]IronArmour-{$50} \n";
        cout << "[2]IronDagger-{$25} \n";
        cout << "[3]IronSword-{$75} \n";
        cout << "[4]-Exit_Shop- \n";
        cout << "_---------_---------_" << endl;
        cout << " \n";
    }
};

//Stat shop class
class StatShop1 { // still need to add the rest of the shop class like inv and add and sell/ display logic
public:
    int Str_Potion;
    int Spd_Potion;
    vector<string> Shop1Inventory; // shop1 inventory
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
    cout << "[1]+HP Potion-{$50} \n";
    cout << "[2]+10STR Potion-{$25} \n";
    cout << "[3]+10SPD Potion-{$25} \n";
    cout << "[4]-Exit_Shop- \n";
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
    int gold; // player starting gold
    // starting gold is (100) for now.
    int level;
    int xp;
    int xpToLevel;
    vector<string> inventory;
    vector<int> Wallet;

    //donning and doffing function
    vector<string> playerequip;

    Character(string n, int a) : name(n), age(a), Str(0), Mag(0), gold(100), Stm(0), Spd(0), Int(0), Wis(0), Con(0), Cha(0), health(100), level(1), xp(0), xpToLevel(100) {
        inventory.push_back("Sword"); // Adds sword to inv
        for (int i = 0; i < 5; ++i) { // Adds 5 health potions to inv
            inventory.push_back("Health Potion");
        }
    }

    //Function inventory use and remove hp potion
    void Use_Remove_HP(Character& player) {
        auto potionIt = find(player.inventory.begin(), player.inventory.end(), "Health Potion");
        if (potionIt != player.inventory.end()) {
            cout << "\n**CONSOLE:**" << endl;
            cout << "You use a Health Potion!\n";
            player.health += 80;
            cout << "\n**CONSOLE:**" << endl;
            cout << "You regain 80 health!\n";
            player.inventory.erase(potionIt); // Remove one potion per potion use
        }
        else {
            cout << "\n**CONSOLE:**" << endl;
            cout << "You have no Health Potions left!\n";
        }
    }

    //Function inventory sell and remove sword 
    void Use_Remove_Sword(Character& player) {
        auto weaponIt = find(player.inventory.begin(), player.inventory.end(), "Sword");
        if (weaponIt != player.inventory.end()) {
            cout << "\n**CONSOLE:**" << endl;
            cout << "You sold your sword!\n";
            player.gold += 200;
            cout << "\n**CONSOLE:**" << endl;
            cout << "You gained {200}$ gold!\n";
            player.inventory.erase(weaponIt); // Remove sword from players inventory
        }
        else if (weaponIt != player.playerequip.end()) {
            cout << "You cannot sell an item you have equipped. " << endl;
        }
        else {
            cout << "\n**CONSOLE:**" << endl;
            cout << "You dont own sword!\n";
        }
    }

    //Function inventory equip and remove sword 
    void Equip_Remove_Sword(Character& player) {
        auto weaponIt = find(player.inventory.begin(), player.inventory.end(), "Sword");
        if (weaponIt != player.inventory.end()) {
            cout << "\n**CONSOLE:**" << endl;
            cout << "You equipped your sword from inventory!\n";
            ;
            player.inventory.erase(weaponIt); // Remove sword from players inventory
        }
        else if (weaponIt != player.playerequip.end()) {
            cout << "You cannot equip an item you do not have equipped. " << endl;
        }
        else {
            cout << "\n**CONSOLE:**" << endl;
            cout << "You dont own sword!\n";
        }
    }

    //Function inventory unequip and remove sword 
    void Unequip_Remove_Sword(Character& player) {
        auto weaponIt = find(player.playerequip.begin(), player.playerequip.end(), "Sword");
        if (weaponIt != player.inventory.end()) {
            cout << "\n**CONSOLE:**" << endl;
            cout << "You unequipped your sword!\n";
            playerequip.erase(weaponIt); // Remove sword from players equip inventory
        }
        else if (weaponIt != player.inventory.end()) {
            cout << "You dont have this item equipped " << endl;
        }
        else {
            cout << "\n**CONSOLE:**" << endl;
            cout << "You cannot unequip an item you do not have equipped.!\n";
        }
    }

    
    // check inventory for equip 
    void CheckForEquip() {
        if (find(playerequip.begin(), playerequip.end(), "Sword") != playerequip.end() ){
            cout << "You have equipped an item." << endl;;
        }
        else {
            cout << "You do not have a weapon equipped. " << endl;
        }
    }
    
    void addGold(int amount) {
        Wallet.push_back(amount);
    }

    void AddHP_Potion() {
        if (gold >= 50) { // if equal or greater price
            cout << "Adding HP_Potion to inventory " << endl;
            inventory.push_back("Health Potion");
            gold -= 50;
        }
        else {
            cout << "Not enough gold to buy this item " << endl;
        }

    }

    void AddStr_Potion() {
        if (gold >= 25) { // if equal or greater price
            cout << "Adding Str_Potion to inventory " << endl;
            inventory.push_back("Str_Potion");
            gold -= 25;
           
        }
        else {
            cout << "Not enough gold to buy this item " << endl;
        }
    }

    void AddSpd_Potion() {
        if (gold >= 25) { // if equal or greater price
            cout << "Adding Spd_Potion to inventory " << endl;
            inventory.push_back("Spd_Potion");
            gold -= 25;
        }
        else {
            cout << "Not enough gold to buy this item " << endl;
        }
    }

    void levelUp() {
        while (xp >= xpToLevel) {
            xp -= xpToLevel;
            level++;
            xpToLevel += 50; // Increase XP required for the next level
            Str += 2; // Increase stats on level up
            health += 10; // Increase health on level up
            cout << "\n**CONSOLE:**" << endl;
            cout << "Congratulations! You leveled up to level " << level << "!\n";
            cout << "Your stats have increased!\n";
        }
    }
};

// equip weapon function
void EquipW(Character& player) {
    if (find(player.inventory.begin(), player.inventory.end(), "Sword") != player.inventory.end()) {
        player.playerequip.push_back("Sword");
        player.Equip_Remove_Sword(player);
    }
}

// unequip weapon function
void UnequipW(Character& player) {
    if (find(player.playerequip.begin(), player.playerequip.end(), "Sword") != player.playerequip.end()) {
        player.inventory.push_back("Sword");
        player.Unequip_Remove_Sword(player);
    }
}

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
        cout <<"|" << item << "| " << "\n";
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
        cout << "Choose an action: [1] Attack [2] Use Health Potion \n";
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
        NPC("Bandit", 50, 6, 40),
        NPC("BanditChief", 70, 4, 20),
        NPC("Lord Calum(Lord of Lag)", 90, 10, 40)
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
    cout << " \n";
    cout << "         | BOOSTS | " << endl;
    cout << "-_______________________________-" << endl;
    if (find(character.playerequip.begin(), character.playerequip.end(), "Sword") != character.playerequip.end()) {
        cout << "+10 Str boost from ['Sword'].\n ";
    }
    else {
        cout << "You have no boosts active. " << endl;
    }
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

// Inventory interaction menu for player
void InvinteractionMenu() {
    cout << "-_______________________________-" << endl;
    cout << "|[1] Use : [2] Exit Bag |\n";
    cout << "|[3] Equip : [4] Unequip |\n";
    cout << "_-------------------------------_" << endl;

}

//General Shop Option Menu
void GnrlShopOptionMenu() {
    cout << "-___________-___________________-" << endl;
    cout << " |[1] Buy : [2] Sell : [3] Exit | " << endl;
    cout << "_-----------_-------------------_" << endl;
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
//check bag option menu
void CheckBagOptionMenu() {
    cout << "-______________-___________________-" << endl;
    cout << "|[1] Check Bag : [2] Put Bag Away |\n";
    cout << "_--------------_-------------------_" << endl;

}

//combat exit option menu
void cExitOptionMenu() {
    cout << "     |What do you choose|" << endl;
    cout << "-______________-___________________-" << endl;
    cout << "|[1] Engage : [2] Run Away |\n";
    cout << "_-----------_-------------------_" << endl;
}

void Riddle1DisplayMenu() {
    cout << "     Q-| 1+1=?|" << endl;
    cout << "-______________-___________________-" << endl;
    cout << "|[1] 2 : [2] 5 : [3] 1 : [4] 0 |\n";
    cout << "_-----------_-------------------_" << endl;

    cout << "Choose your answer." << endl;
}
int main() {
    srand(static_cast<unsigned>(time(0))); // you have to seed for random number generation in main fnctn
    Character character("Player", 20); // Create a character
    int Exit_strat = 0;
    //checks for sword in inventory and if found adds +10 the the players damage (Str)
    character.CheckForEquip(); // should be used after every potential option that effects sword to check to make sure its still owned

    
    
    
    
    // Choices
    int choice = 0, choice2 = 0, Quest1Choice = 0;
    int Str_bonus = 0, Mag_bonus = 0, Stm_bonus = 0, Spd_bonus = 0, Int_bonus = 0, Wis_bonus = 0, Con_bonus = 0, Cha_bonus = 0;

    //Adds Basestats to player stats
    Str_bonus += 1;
    Mag_bonus += 1;
    Stm_bonus += 1;
    Spd_bonus += 1;
    Int_bonus += 1;
    Wis_bonus += 1;
    Con_bonus += 1;
    Cha_bonus += 1;
    

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
        
        



        do {
            ClassMenu();
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
        
        cout << "\n**YOU:**" << endl;
        cout << "Well, looks like im homeless and alone. " << endl;
        this_thread::sleep_for(seconds(2));
        
        cout << "\n**YOU:**" << endl;
        cout << "Lets try and focus on finding a place to call home and rebuild my legacy. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "|OBJECTIVE: FIND PLACE TO CALL HOME| " << endl;
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
        int AltChoice1 = 0;

        // Random Encounter
        // 1 = higher chance 2 = lower chance of encounter
        if (rand() % 1 == 0) { // 50% chance of encountering an NPC
            do {
                cout << "\n**NARRATOR:**" << endl;
                cout << "A SMALL BAND OF MOBS!!!\n\n";
                cout << "\n**CONSOLE:**" << endl;
                cExitOptionMenu();
                cin >> AltChoice1;
                
                switch (AltChoice1) {
                case 1:
                    encounter(character);
                    AltChoice1 = 2;
                    break;
                case 2:
                    cout << "You chose to run away. " << endl;
                    break;
                default:
                    cout << "\n**CONSOLE:**" << endl;
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            } while (AltChoice1 != 2);
        }
        else {
            cout << "\n**NARRATOR:**" << endl;
            cout << "It was nothing.\n";
            this_thread::sleep_for(seconds(2));

        }
        // check the players health, if 0 game ends
        if (character.health <= 0) {
            cout << "\nYou have died!\n";
            cout << "\n-Exiting Game-\n";
            return 0;
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
                do {
                    

                    DisplayShop1Menu();
                    cin >> choice2;
                    switch (choice2) {
                    case 1:  // adds HP Potion to inv
                        character.AddHP_Potion();
                        this_thread::sleep_for(seconds(1));
                        cout << "\n Anything else? \n";
                        break;
                    case 2:  // adds STR Potion to inv          
                        character.AddStr_Potion();
                        this_thread::sleep_for(seconds(1));
                        cout << "\n Anything else? \n";
                        break;
                    case 3:  // adds SPD Potion to inv
                        character.AddSpd_Potion();
                        this_thread::sleep_for(seconds(1));
                        cout << "\n Anything else? \n";
                        break;
                    case 4:
                        cout << "-Exiting shop, goodbye adventurer.- \n";
                        this_thread::sleep_for(seconds(1));
                        choice2 = 11;
                        break;
                    default:
                        cout << "\n**CONSOLE:**" << endl;
                        cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                } while (choice2 != 11);
                Quest1Choice = 11;
            break;
                
            case 2:
                cout << "\n**NARRATOR:**" << endl;
                cout << "You choose to ignore the mysterious shopcart dwarf and continue down the path on your journey." << endl;
                this_thread::sleep_for(seconds(3));
                choice = 11;
                Quest1Choice = 11;
                break;
            default:
                cout << "\n**CONSOLE:**" << endl;
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        } while (Quest1Choice != 11);
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
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**" << endl;
        cout << "You walk in and stand before the pouch, What should you do?\n\n";
        QuestOptionMenu();
        this_thread::sleep_for(seconds(2));
        choice = 0;
        cin >> choice;
        do {
            switch (choice) {
            case 1:
                cout << "\n**NARRATOR:**" << endl;
                cout << "You picked up the pouch and found a health potion inside." << endl;
                character.inventory.push_back("Health Potion");
                character.xp += 250;
                character.levelUp();
                choice2 = 11;
                break;
            case 2:
                cout << "\n**NARRATOR:**" << endl;
                cout << "You chose to ignore the pouch and leave the creepy build. " << endl;
                choice2 = 11;
                break;
            default:
                cout << "\n**CONSOLE:**" << endl;
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        } while (choice2 != 11);
        int choice3 = 0, choice4 = 0;
        StatsMenu(character);
        this_thread::sleep_for(seconds(5));

        cout << "While outside you decide to take a break and rest for the journey to come. " << endl;
        cout << "\n ";
        

        CheckBagOptionMenu();
        cin >> choice3;
        do {
            switch (choice3) {
            case 1:
                cout << "\n**NARRATOR:**" << endl;
                cout << "You decided to check your bag." << endl;
                displayInventory(character);
                this_thread::sleep_for(seconds(4));
                cout << "\n**NARRATOR:**" << endl;
                cout << "What would you like to do?. " << endl;
                
                choice = 0, choice2 = 0;

                do {
                    InvinteractionMenu();
                    cin >> choice; // Add this to get user input for choice
                    switch (choice) {
                    case 1:
                        character.Use_Remove_HP(character);
                        break;
                    case 2:
                        cout << "\n**NARRATOR:**" << endl;
                        cout << "You decided to exit your bag. " << endl;
                        this_thread::sleep_for(seconds(2));
                        cout << "Exiting bag." << endl;
                        choice2 = 13;
                        break;
                    case 3:
                        EquipW(character); // equip weapon
                        break;
                    case 4:
                        UnequipW(character); // unequip weapon
                        break;
                    default:
                        cout << "\n**CONSOLE:**" << endl;
                        cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                } while (choice2 != 13);

                
                choice4 = 12;
                break;
            case 2:
                cout << "\n**NARRATOR:**" << endl;
                cout << "You decided not to check your bag." << endl;
                this_thread::sleep_for(seconds(4));
               
                choice4 = 12;
                break;
            default:
                cout << "\n**CONSOLE:**" << endl;
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        } while (choice4 != 12);
        character.CheckForEquip();
        cout << "\n**NARRATOR:**" << endl;
        cout << "After taking a break you are well rested. " << endl;

        //get xp and health for resting
        cout << "\n**CONSOLE:**" << endl;
        cout << "+50xp for resting and full health regen." << endl;
        character.xp += 50;
        character.levelUp();
        if (character.health < 100) {
            character.health = 100;
        }
        else {
            cout << "\n**CONSOLE:**" << endl;
            cout << "\nYour health is full, +10xp instead. \n";
            character.xp += 10;
            character.levelUp();
        }
        cout << "\n**NARRATOR:**" << endl;
        cout << "After feeling well resting you continue your journey towards the distant white light at the end of the path. " << endl;
        this_thread::sleep_for(seconds(2));
        cout << "\n**NARRATOR:**" << endl;
        cout << "You come acrossed a fallen tree in the middle of your path." << endl;
        this_thread::sleep_for(seconds(2));
        int AltChoice2 = 0;

        // Random Encounter
        // 1 = 100% higher chance | 2 = 50% higher chance of encounter
        if (rand() % 2 == 0) { // 50% chance of encountering an NPC
            do {
                cout << "\n**NARRATOR:**" << endl;
                cout << "A SMALL BAND OF MOBS!!!\n\n";
                cout << "\n**CONSOLE:**" << endl;
                cExitOptionMenu();
                cin >> AltChoice1;

                switch (AltChoice1) {
                case 1:
                    encounter(character);
                    AltChoice1 = 2;
                    break;
                case 2:
                    cout << "You chose to run away. " << endl;
                    break;
                default:
                    cout << "\n**CONSOLE:**" << endl;
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            } while (AltChoice1 != 2);
        }
        else {
            cout << "\n**NARRATOR:**" << endl;
            cout << "Hm, weird place to put a tree.\n";
            this_thread::sleep_for(seconds(2));

        }
        // check the players health, if 0 game ends
        if (character.health <= 0) {
            cout << "\nYou have died!\n";
            cout << "\n-Exiting Game-\n";
            return 0;
        }

        cout << "\n**NARRATOR:**" << endl;
        cout << "You go around the tree and continue your walk for many miles." << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "As you approach the bright light at the end of the dirt pathyou grasp your sword. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "When you get to the source of the light, you see its just a lamp post at the enterance to a small remote village tucked away. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "Hm, maybe I can stop here for supplies, you say to yourself. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "You try to enter the town but get stopped by the gaurd at the gate. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**GUARD:**" << endl;
        cout << "HALT!, State your business stranger. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**YOU:**" << endl;
        cout << "I'm just passing through, here to get supplies and rest up than ill be on my way. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**GUARD:**" << endl;
        cout << "If you want to enter your going to have to answer a question. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**YOU:**" << endl;
        cout << "HM, ok try me im ready. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**GUARD:**" << endl;
        cout << "Alright, here it is,  " << endl;
        this_thread::sleep_for(seconds(2));
        AltChoice1 = 0;
        AltChoice2 = 0;

        do {
            Riddle1DisplayMenu();
            cout << "Your Answr: "; cin >> AltChoice1;
            switch (AltChoice1) {
            case 1:
                cout << "\n**GUARD:**" << endl;
                cout << "Hahaha " << endl;
                cout << "Incorrect! No entry, try again. " << endl;

                break;
            case 2:
                cout << "\n**GUARD:**" << endl;
                cout << "Correct! much smarter than I thought, you may enter, Welcome!. " << endl;
                AltChoice2 = 15;
                break;
            case 3:
                cout << "\n**GUARD:**" << endl;
                cout << "Hahaha " << endl;
                cout << "Incorrect! No entry, try again. " << endl;

                break;
            case 4:
                cout << "\n**GUARD:**" << endl;
                cout << "Hahaha " << endl;
                cout << "Incorrect! No entry, try again. " << endl;

                break;
            case 5:
                cout << "\n**GUARD:**" << endl;
                cout << "Hahaha " << endl;
                cout << "Incorrect! No entry, try again. " << endl;

                break;
            default:
                cout << "\n**CONSOLE:**" << endl;
                cout << "Invalid choice. Please try again.\n";

                break;
            }
                
        } while (AltChoice2 != 15);

        //gets xp for solving puzzle
        character.xp += 100;
        character.levelUp();
        choice = 0;
        choice2 = 0;
        int Bchoice1 = 0;
        int Bchoice2 = 0;
        int Pchoice1 = 0;
        int Pchoice2 = 0;

        // name of town 1 is gonna be -Argun- 
        cout << "\n**NARRATOR:**" << endl;
        cout << "You enter the town of Argun. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "There are not many buildings and the town is pretty small but the town looks very crowded and busy. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "You a potion shop and a blacksmith. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "Where do you visit?. " << endl;
        this_thread::sleep_for(seconds(2));
        
        do {
            cout << "-__________________-___________________-" << endl;
            cout << "|[1] PotionShop : [2] Blacksmith : [3] Exit |\n";
            cout << "_------------------_-------------------_" << endl;
            cout << "Choice:"; cin >> choice;

            switch (choice) {
            case 1:
                cout << "You chose to check out the PotionShop. " << endl;
                GnrlShopOptionMenu();
                do {


                    DisplayShop1Menu();
                    cin >> Pchoice2;
                    switch (Pchoice2) {
                    case 1:  // adds HP Potion to inv
                        character.AddHP_Potion();
                        this_thread::sleep_for(seconds(1));
                        cout << "\n Anything else? \n";
                        break;
                    case 2:  // adds STR Potion to inv          
                        character.AddStr_Potion();
                        this_thread::sleep_for(seconds(1));
                        cout << "\n Anything else? \n";
                        break;
                    case 3:  // adds SPD Potion to inv
                        character.AddSpd_Potion();
                        this_thread::sleep_for(seconds(1));
                        cout << "\n Anything else? \n";
                        break;
                    case 4:
                        cout << "-Exiting shop, goodbye adventurer.- \n";
                        this_thread::sleep_for(seconds(1));
                        Pchoice2 = 19;
                        break;
                    default:
                        cout << "\n**CONSOLE:**" << endl;
                        cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                } while (Pchoice2 != 19);
                choice = 18;
                break;
            case 2:
                cout << "You chose to check out the Blacksmith. " << endl;
                GnrlShopOptionMenu();

                choice = 18;
                break;
            case 3:
                cout << "\n**CONSOLE:**" << endl;
                cout << "You chose to exit and continue on.\n";
                choice = 18;
                break;
            default:
                cout << "\n**CONSOLE:**" << endl;
                cout << "Invalid choice. Please try again.\n";

                break;
            }
        } while (choice != 18);
        
        cout << "\n**NARRATOR:**" << endl;
        cout << "You decide to continue your search for a home and leave the small town. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "You leave the town and continue down your path " << endl;
        this_thread::sleep_for(seconds(2));

        // Random Encounter
        // 1 = higher chance 2 = lower chance of encounter
        if (rand() % 1 == 0) { // 50% chance of encountering an NPC
            do {
                cout << "\n**NARRATOR:**" << endl;
                cout << "A SMALL BAND OF MOBS!!!\n\n";
                cout << "\n**CONSOLE:**" << endl;
                cExitOptionMenu();
                cin >> AltChoice1;

                switch (AltChoice1) {
                case 1:
                    encounter(character);
                    AltChoice1 = 2;
                    break;
                case 2:
                    cout << "You chose to run away. " << endl;
                    break;
                default:
                    cout << "\n**CONSOLE:**" << endl;
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            } while (AltChoice1 != 2);
        }
        else {
            cout << "\n**NARRATOR:**" << endl;
            cout << "It was nothing.\n";
            this_thread::sleep_for(seconds(2));

        }
        // check the players health, if 0 game ends
        if (character.health <= 0) {
            cout << "\nYou have died!\n";
            cout << "\n-Exiting Game-\n";
            return 0;
        }

        cout << "\n**NARRATOR:**" << endl;
        cout << "After traveling very far, you find an abandoned house hidden in a tree infested valley. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "This looks like a good place to call home. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "You go inside, set down your bag and lay down to rest.... " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "You found your new home. " << endl;
        this_thread::sleep_for(seconds(2));

        cout << "\n**NARRATOR:**" << endl;
        cout << "YOU ACHIEVED YOUR GOAL!!! " << endl;
        this_thread::sleep_for(seconds(2));
        character.xp += 1000;
        character.levelUp();


        //End Of The Game//
        Exit_strat = 9;
    } while (Exit_strat != 9); // This keeps the game running

    return 0;
}