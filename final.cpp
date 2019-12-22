//final.cpp
//Shreya Gowda, CISP 360
//8/9/18

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

//each direction corresponds to a number
enum Direction{
  SOUTH,
  EAST,
  WEST,
  NORTH
};

//each room corresponds to a number
enum RoomNum{
  EXIT=-2,
  NONE=-1,
  DOCKS=0,
  EMPTY_VILLAGE=1,
  FIELDS=2,
  FOREST=3,
  CITY_HALL=4,
  RUINED_TEMPLE=5,
};

const int NUM_ROOMS=6;    //number of rooms 

//Each direction object corresponds to a word (ex: North-> 'N') and number (*see direction enum)
struct DirectionObj{
  string word;
  int num;
};

//A room construct consists of its name, description, id, and where it exits to based on direction
struct Room{
  string room_name; 
  string room_description;
  int room_id;
  int path[4];
};

//Specification B1 - Monster class
/*
Put all the monsters in a monster class. Monster is picked randomly in constructor.
*/
class Monster{
  public: 
  Monster(int* health){
    srand(time(0));
   int rand_num = (rand()%5)+1;

    //Specification B2 - Combat
    /*
    When monster is created, you are forced to attack or die
    */
    if(rand_num==1){
      int a=0;
      char attack='x';
      cout<<endl<<"Forgotten Ghost (Lvl.1)"<<endl;
      while((a!=3)&&(*health>0)){
        cout<<endl<<"Your Health: "<<*health<<endl;
        cout<<endl<<"Monster attacked you!"<<endl;
        int rand_num2=(rand()%3)+1;
        *health-=rand_num2;
        cout<<"Now it's your turn! Attack (A) it!";
        cin>>attack;
        attack=toupper(attack);
        while(attack!='A'){
          cout<<endl<<"You can only attack (A) when cornered by a monster: ";
          cin>>attack;
          attack=toupper(attack);
        }
        a++;
      }
      if(a==3){
        cout<<endl<<"Monster is dead"<<endl;
        cout<<endl<<"Your health: "<<*health<<endl;
      }
    }

    if(rand_num==2){
      int a=0;
      char attack='x';
      cout<<endl<<"Dismembered Mummy (Lvl.2)"<<endl;
      while((a!=3)&&(*health>0)){
        cout<<endl<<"Your Health: "<<*health<<endl;
        cout<<endl<<"Monster attacked you!"<<endl;
        int rand_num2=(rand()%5)+1;
        *health-=rand_num2;
        cout<<"Now it's your turn! Attack (A) it!";
        cin>>attack;
        attack=toupper(attack);
        while(attack!='A'){
          cout<<endl<<"You can only attack (A) when cornered by a monster.";
          cin>>attack;
          attack=toupper(attack);
        }
        a++;
      }
      if(a==3){
        cout<<endl<<"Monster is dead"<<endl;
        cout<<endl<<"Your health: "<<*health<<endl;
      }
    }

    if(rand_num==3){
      int a=0;
      char attack='x';
      cout<<endl<<"Red Fiend (Lvl.3)"<<endl;
      while((a!=4)&&(*health>0)){
        cout<<endl<<"Your Health: "<<*health<<endl;
        cout<<endl<<"Monster attacked you!"<<endl;
        int rand_num2=(rand()%8)+2;
        *health-=rand_num2;
        cout<<"Now it's your turn! Attack (A) it!";
        cin>>attack;
        attack=toupper(attack);
        while(attack!='A'){
          cout<<endl<<"You can only attack (A) when cornered by a monster.";
          cin>>attack;
          attack=toupper(attack);
        }
        a++;
      }
      if(a==4){
        cout<<endl<<"Monster is dead"<<endl;
        cout<<endl<<"Your health: "<<*health<<endl;
      }
    }

    if(rand_num==4){
      int a=0;
      char attack='x';
      cout<<endl<<"BloodSucker (Lvl.4)"<<endl;
      while((a!=4)&&(*health>0)){
        cout<<endl<<"Your Health: "<<*health<<endl;
        cout<<endl<<"Monster attacked you!"<<endl;
        int rand_num2=(rand()%15)+5;
        *health-=rand_num2;
        cout<<"Now it's your turn! Attack (A) it!";
        cin>>attack;
        attack=toupper(attack);
        while(attack!='A'){
          cout<<endl<<"You can only attack (A) when cornered by a monster.";
          cin>>attack;
          attack=toupper(attack);
        }
        a++;
      }
      if(a==4){
        cout<<endl<<"Monster is dead"<<endl;
        cout<<endl<<"Your health: "<<*health<<endl;
      }
    }

    //Specification B3 - More monsters
    /*
    One more monster created called "treacherous serpent"
    */
    if(rand_num==5){
      int a=0;
      char attack='x';
      cout<<endl<<"Treacherous Serpent (Lvl.5)"<<endl;
      while((a!=5)&&(*health>0)){
        cout<<endl<<"Your Health: "<<*health<<endl;
        cout<<endl<<"Monster attacked you!"<<endl;
        int rand_num2=(rand()%10)+10;
        *health-=rand_num2;
        cout<<"Now it's your turn! Attack (A) it!";
        cin>>attack;
        attack=toupper(attack);
        while(attack!='A'){
          cout<<endl<<"You can only attack (A) when cornered by a monster.";
          cin>>attack;
          attack=toupper(attack);
        }
        a++;
      }
      if(a==5){
        cout<<endl<<"Monster is dead"<<endl;
        cout<<endl<<"Your health: "<<*health<<endl;
      }
    }

  }
};

//Function Prototypes
void guide();
void playGame(string username, int start_health);
void setRooms(Room rm[]);
bool validInput(Room* room, string input, int* health, bool* exit, bool objs[]);
bool checkTreasure(bool objs[]);
string upperCase(string word);
string description1();
string description2();
string description3();
string description4();
string description5();
string description6();

int main(){
  string player_name="";   //user input for their name
  int full_health=100;    //starting health
  char opt='x';    //menu option chosen

  //Program Greeting
  cout<<"Ivory Island Adventure"<<endl;
  cout<<"This is a text-based adventure game. \nAdventure through rooms, battle monsters, and find treasure!"<<endl;
  cout<<"Creator: Shreya Gowda"<<endl;
  cout<<endl<<"Press ENTER to begin";
  cin.get();

  //Menu
  system("clear");
  cout<<"Ivory Island Adventure"<<endl;
  cout<<endl<<"  Menu"<<endl;
  cout<<"---------"<<endl;
  cout<<"Guide (G)"<<endl;
  cout<<"Play  (P)"<<endl;
  cout<<"Quit  (Q)"<<endl;
  cout<<endl<<"Enter here: ";

  cin>>opt;
  opt=toupper(opt);

  //Check if valid menu option
  while(opt!='G'&&opt!='P'&&opt!='Q'){
    cout<<"Invalid Input. Please try again: ";
    cin>>opt;
    opt=toupper(opt);
  }

  //If menu option 'guide' chosen
  if(opt=='G'){
    guide();

    cout<<endl<<"  Menu"<<endl;
    cout<<"---------"<<endl;
    cout<<"Play  (P)"<<endl;
    cout<<"Quit  (Q)"<<endl;
    cout<<endl<<"Enter here: ";

    cin>>opt;
    opt=toupper(opt);

    while(opt!='P'&&opt!='Q'){
      cout<<"Invalid Input. Please try again: ";
      cin>>opt;
      opt=toupper(opt);
    }
  }

  cin.ignore();

  system("clear");
  // Specification C2 - Player Name
  cout<<"What is your name? ";
  getline(cin, player_name);
  while(opt=='P'){
    playGame(player_name, full_health);
    cout<<endl<<"Play Again? (Y/N)";
    cin>>opt;
    opt=toupper(opt);
    if(opt=='Y'){
      opt='P';
    }
  }

  cout<<endl<<"Thanks for playing!"<<endl;
  return 0;
}

//instructions
void guide(){
  system("clear");
  cout<<"Ivory Island Adventure"<<endl<<endl;
  cout<<"Instructions"<<endl;
  cout<<"Press 'L' to LOOK at the room description again.\n";
  cout<<"Press 'A' to ATTACK a monster.\n";
  cout<<"Press 'H' to HUNT for treasures in a room.\n";
  cout<<"Press 'I' to see your INVENTORY.\n";
  cout<<"Move throughout the adventure with the N,S, E, W keys \n";
  cout<<"   (moving you in the four cardinal directions.)"<<endl<<endl;
}

//actual game
void playGame(string username, int start_health){
  system("clear");

  int health=start_health;    //player's health throughout game
  int* ptr_health=&health;    //pointer to health
  bool treasure_objs[3]={false, false, false};    //if player has treasure or not
  bool exit=false;    //if player went to exit
  bool* ptr_exit=&exit;    //pointer to exit
  bool win=false;    //if player won
  string choice="";    //user input
  int count=0;    //'win' message is only displayed once
  Room all_rooms[NUM_ROOMS];    //array of all the rooms and their settings
  Room curr_room;    //room player is currently in
  Room* ptr_room=&curr_room;    //pointer to current room

  setRooms(all_rooms);

  //intro
  cout<<"Ivory Island Adventure"<<endl;
  cout<<"Greetings "<<username<<", my name is Kizara. I am the guardian of Ivory island. I have heard a lot about you. Your many daring exploits have brought you fame as a legendary explorer. But I must warn you, the monsters in these parts are especially dangerous. \nDo you think you can handle it? (Y/N)"<<endl;
  cin>>choice;
  choice=upperCase(choice);

  cout<<endl;
  if(choice=="Y"){
    cout<<"I admire your bravery. Search for treasures that you may take back to the museum and preserve. And if you ever change your mind, your ship is right behind (South) you to take you home."<<endl;
  }
  else if(choice=="N"){
    cout<<"If you truly wish to leave, your ship is right behind (South) you to take you home. Otherwise, you may explore the rooms and search for treasures."<<endl;
  }
  else{
    cout<<"I do not know what that means. You are free to do as you please. Explore and search for treasures. Or leave the island the way you came (South)."<<endl;
  }
  cout<<"I will be leaving now."<<endl<<endl;

  //starting room
  curr_room=all_rooms[DOCKS];
  cout<<curr_room.room_name<<endl;
  cout<<curr_room.room_description<<endl;

  cin.ignore();
  while((!exit)&&(health>0)){
    if((curr_room.room_id==RUINED_TEMPLE)&&(checkTreasure(treasure_objs))&&count==0){
      cout<<endl<<"Your treasures gravitate towards the pedestals. The ground opens up to reveal an underground cavern filled with valuable treasures. You will call archaelogists here later to safely excavate the area and bring the treasures to a museum. For now, your work here is done. Good job " <<username<<". Head back to the exit."<<endl;
      win=true;
      count++;
    }
    cout<<endl<<"Input: ";
    getline(cin, choice);
    choice=upperCase(choice);
    // Specification C3 - Input Validation
    validInput(ptr_room, choice, ptr_health, ptr_exit, treasure_objs);
  }

  if(win==true&&exit==true){
    cout<<endl<<"You won. Good Job!"<<endl;
  }
  if(health<=0){
    cout<<endl<<"You died"<<endl;
  }
  cout<<"Game is over.";
}

bool validInput(Room* curr_room, string input, int* health, bool* exit, bool objs[]){
  Room rm[NUM_ROOMS];    //array of all the rooms
  bool went[NUM_ROOMS];    //if player already went to room

  //treasure corresponds to a number
  enum TREASURES{
    AMULET,
    GOLD_LEAF,
    BIG_COIN,
  };

  setRooms(rm);

  //player has not gone to any room except the docks
  for(int i=0; i<NUM_ROOMS; i++){
    went[i]=false;
  }
  went[DOCKS]=true;

  //Specification A1 - Array of structs
  /*
  Array of structs was created for the four cardinal directions. Each direction object has a corressponding letter and number. Makes looping through easier.
  */
  DirectionObj dir[4];
  dir[SOUTH].word="S";
  dir[SOUTH].num=SOUTH;
  dir[EAST].word="E";
  dir[EAST].num=EAST;
  dir[WEST].word="W";
  dir[WEST].num=WEST;
  dir[NORTH].word="N";
  dir[NORTH].num=NORTH;

  //checks if user input matches a word in direction object array
  for(int i=0; i<4; i++){
  if(input==dir[i].word){
    int new_room=(*curr_room).path[dir[i].num];
    if(new_room==NONE){
      cout<<endl<<"No room there."<<endl;
      return true;
    }
    else if(new_room==EXIT){
      *exit=true;
      return true;
    }
    else{
      *curr_room=rm[new_room];
      cout<<endl<<(*curr_room).room_name<<endl;

      // Specification C4 – Abbreviated Room Description
      if(went[new_room]==false){
        cout<<(*curr_room).room_description;
      }
      cout<<endl;

      went[new_room]=true;

      Monster new_monster(health);

      //village and temple regenerate health
      if(new_room==EMPTY_VILLAGE){
        if(*health>0){
        cout<<endl<<"You feel a surge of energy come from the fountain."<<endl;
        if(*health>80){
          cout<<"Your health regenerates 0."<<endl;
        }
        else if(*health>55){
          *health+=30;
          cout<<"Your health is restored by 30."<<endl;
        }
        else{
          *health+=50;
          cout<<"Health is restored by 50"<<endl;
        }
        }
      }
      if(new_room==RUINED_TEMPLE){
      if(*health>0){
        cout<<endl<<"You feel a surge of energy come from the runes."<<endl;
          *health+=30;
          cout<<"Your health is restored by 30."<<endl;
      }
      }

      cin.ignore();
      return true;
    }
  }
  }

  // Specification C5 - Detailed Look
  if(input=="L"){
    cout<<endl<<(*curr_room).room_name<<endl;
    cout<<(*curr_room).room_description<<endl;
    return true;
  }

  //Specification A2 - Treasure
  /*
  If you hunt for treasure in certain rooms, you will find treasure
  */
  if(input=="H"){
    if((*curr_room).room_id==FIELDS){
      if(objs[AMULET]==false){
        objs[AMULET]=true;
        cout<<endl<<"You found an amulet!"<<endl;
      }
      else{
        cout<<endl<<"You already found treasure here."<<endl;
      }
    }
    else if((*curr_room).room_id==FOREST){
      if(objs[GOLD_LEAF]==false){
        objs[GOLD_LEAF]=true;
        cout<<endl<<"You found an intricate gold leaf!"<<endl;
      }
      else{
        cout<<endl<<"You already found treasure here."<<endl;
      }
    }
    else if((*curr_room).room_id==CITY_HALL){
      if(objs[BIG_COIN]==false){
        objs[BIG_COIN]=true;
        cout<<endl<<"You found a coin the size of your palm!"<<endl;
      }
      else{
        cout<<endl<<"You already found treasure here."<<endl;
      }
    }
    else {
      cout<<endl<<"No treasure here!"<<endl;
    }
    return true;
  }

  //Specification A3 - More Command Options
  /*
  Pressing 'I' allows you to see all the treasures you already have in your inventory.
  */
  if(input=="I"){
    cout<<endl<<"Inventory"<<endl;
    cout<<"---------"<<endl;
    if(objs[AMULET]){
      cout<<"AMULET"<<endl;
    }
    if(objs[GOLD_LEAF]){
      cout<<"GOLD LEAF"<<endl;
    }
    if(objs[BIG_COIN]){
      cout<<"BIG COIN"<<endl;
    }
    cout<<endl;
    return true;
  }

  cout<<endl<<"Invalid Input"<<endl;
  return false;
}

//creates the rooms
void setRooms(Room rm[]){

  rm[DOCKS].room_name="The Docks";
  rm[DOCKS].room_description=description1();
  rm[DOCKS].room_id=DOCKS;
  rm[DOCKS].path[SOUTH]=EXIT;
  rm[DOCKS].path[EAST]=NONE;
  rm[DOCKS].path[WEST]=NONE;
  rm[DOCKS].path[NORTH]=EMPTY_VILLAGE;

  rm[EMPTY_VILLAGE].room_name="The Abandoned Village";
  rm[EMPTY_VILLAGE].room_description=description2();
  rm[EMPTY_VILLAGE].room_id=EMPTY_VILLAGE;
  rm[EMPTY_VILLAGE].path[SOUTH]=DOCKS;
  rm[EMPTY_VILLAGE].path[EAST]=FOREST;
  rm[EMPTY_VILLAGE].path[WEST]=FIELDS;
  rm[EMPTY_VILLAGE].path[NORTH]=CITY_HALL;
  
  rm[FIELDS].room_name="The Fields";
  rm[FIELDS].room_description=description3();
  rm[FIELDS].room_id=FIELDS;
  rm[FIELDS].path[SOUTH]=NONE;
  rm[FIELDS].path[EAST]=EMPTY_VILLAGE;
  rm[FIELDS].path[WEST]=NONE;
  rm[FIELDS].path[NORTH]=NONE;

  rm[FOREST].room_name="The Forest";
  rm[FOREST].room_description=description4();
  rm[FOREST].room_id=FOREST;
  rm[FOREST].path[SOUTH]=NONE;
  rm[FOREST].path[EAST]=NONE;
  rm[FOREST].path[WEST]=EMPTY_VILLAGE;
  rm[FOREST].path[NORTH]=RUINED_TEMPLE;

  // Specification C1 - Five Rooms
  rm[CITY_HALL].room_name="City Hall";
  rm[CITY_HALL].room_description=description5();
  rm[CITY_HALL].room_id=CITY_HALL;
  rm[CITY_HALL].path[SOUTH]=EMPTY_VILLAGE;
  rm[CITY_HALL].path[EAST]=RUINED_TEMPLE;
  rm[CITY_HALL].path[WEST]=NONE;
  rm[CITY_HALL].path[NORTH]=NONE;
  
  //Specification A4 - More Rooms
  /*
  One more room called 'temple ruins'
  */
  rm[RUINED_TEMPLE].room_name="The Temple Ruins";
  rm[RUINED_TEMPLE].room_description=description6();
  rm[RUINED_TEMPLE].room_id=RUINED_TEMPLE;
  rm[RUINED_TEMPLE].path[SOUTH]=FOREST;
  rm[RUINED_TEMPLE].path[EAST]=NONE;
  rm[RUINED_TEMPLE].path[WEST]=CITY_HALL;
  rm[RUINED_TEMPLE].path[NORTH]=NONE;
  
}

//descriptions of the rooms
string description1(){
  return "Many centuries ago. Ivory Island was famous for its import and export of magical runes and treasures. This was before the monsters appeared. Now the docks are a memory of what once was.A huge, rusty, arched gateway in front of you welcomes you to Haven Town. Behind you is your ship, in case you want to leave.";
}

string description2(){
  return "This is the abandoned village once called Haven Town. Empty houses surround a fountain flowing purple liquid. The houses look like they could've been abandoned yesterday, and not centuries ago, with how impeccably clean they look. In front of you, you see the menacingly large city hall, crushing you under its shadow. To your far right is a beautiful forest. To your far left is a golden meadow. ";
}

string description3(){
  return "How beautiful! Truly a wonder of nature. Golden grass as far as the eye can see, speckled with yellow, orange, and purple wildflowers. All perspectives lead to a magestic, but distant mountain range. Maybe one day you will have the opportunity to come back and traverse those mountains. But sadly, not in this adventure. On your right, you see the village that you just left.";
}

string description4(){
  return "This is a forest. With leaves and sap and mosquitos and other nature-y stuffs. And you like this. Because you are an explorer and this is what you do. Still you feel an uncomfortable aura in this particular forest. No matter. Through the openings in the trees, you see the village on the left. A path in front of you leads to the ruins of a once great temple.";
}

string description5(){
  return "Despite your observations on the structural integrity of this building, you go in to see if you can find anything. Any trace of rich colors had faded to brown by now. Still the vast space and immense height were enough to tell you that this had once been a lobby to be reckoned with. Glass doors to your right show trees and the ruins of a once great temple. Behind you, you can go back to the village.";
}

string description6(){
  return "The first thing you notice are three pedestals at the center of the ruins. Looks like something goes there. Huge broken runestones surround the three pedestals. Far to your left through the trees, you see city hall. Behind you is more forest.";
}

//checks if player has all three treasures
bool checkTreasure(bool objs[]){
  for(int i=0; i<3; i++){
    if(objs[i]==false){
      return false;
    }
  }
  return true;
}

//makes a string all uppercase letters
string upperCase(string word){
  for(unsigned int i=0; i<word.length(); i++){
    word[i]=toupper(word[i]);
  }
  return word;
}
