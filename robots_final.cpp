//robots_final.cpp
//Shreya Gowda, CISP 400
//12/19/19

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

typedef enum {NORTH, SOUTH, EAST, WEST, RAND} direction;
typedef enum {NO_OBJ, WALL, BATTERY, IDC, ROBOT} sensor_and_tile;

class Robot{
  private:
  static const int NUM_ROWS=12;
  static const int NUM_COLS=12;
  static const int NUM_GENES=16;
  static const int NUM_CODES=5; 
  static const int BATTERIES=40;
  int map[NUM_ROWS][NUM_COLS];
  int sensor[4];
  int genes[NUM_GENES][NUM_CODES];
  int turns_survived;
  int turns_left;
  int x_pos;
  int y_pos;

  public:
  Robot(){
    turns_survived=0;
    turns_left=5;
    setMap();
    setGenes();
    checkSensor();
  }

  void setMap(){
    //sets robot's map

    int rand_row=0;
    int rand_col=0;

    //sets wall surrounding map
    for(int i=0; i<NUM_ROWS; i++){
      map[i][0]=WALL;
    }
    for(int i=0; i<NUM_ROWS; i++){
      map[i][NUM_COLS-1]=WALL;
    }
    for(int j=0; j<NUM_COLS; j++){
      map[0][j]=WALL;
    }
    for(int j=0; j<NUM_COLS; j++){
      map[NUM_ROWS-1][j]=WALL;
    }
    for(int i=1; i<NUM_ROWS-1; i++){
      for(int j=1; j<NUM_COLS-1; j++){
        map[i][j]=NO_OBJ;
      }
    }

    //sets robot's position randomly
    x_pos=1+rand()%(NUM_ROWS-2);
    y_pos=1+rand()%(NUM_COLS-2);
    map[y_pos][x_pos]=ROBOT;

    //sets battery positions randomly
    int i=0;
    while(i<BATTERIES){
      rand_row=1+rand()%(NUM_ROWS-2);
      rand_col=1+rand()%(NUM_COLS-2);
      //checks to make sure there isn't a robot or battery in a space before placing a battery
      if((map[rand_row][rand_col]!=5)&&(map[rand_row][rand_col]!=BATTERY)){
        map[rand_row][rand_col]=BATTERY;
        i++;
      }
    }
  }

  void setGenes(){
    //sets random genes for the first generation of robots
    for(int i=0; i<NUM_GENES; i++){
      for(int j=0; j<NUM_CODES-1; j++){
        genes[i][j]=rand()%4;
      }
    }

    //sets random action codes too
    for(int i=0; i<NUM_GENES; i++){
      genes[i][NUM_CODES-1]=rand()%5;
    }
  }

  void checkSensor(){
    //checks what type of block is surrounding the robot in each cardinal direction
    sensor[NORTH]=map[y_pos-1][x_pos];
    sensor[SOUTH]=map[y_pos+1][x_pos];
    sensor[EAST]=map[y_pos][x_pos+1];
    sensor[WEST]=map[y_pos][x_pos-1];
  }

  int decision(){
    //decides where to move on map based on genes

    for(int i=0; i<NUM_GENES; i++){
      //match is initially set to true
      bool match=true;
      for(int j=0; j<NUM_CODES-1; j++){
        //if one of the genes does not match the sensor reading, match is set to false
        if(!(genes[i][j]==sensor[j]||genes[i][j]==IDC)){
          match=false;
        }
      }
      //if match is true (which can only happen if the sensor reading matched a gene row), returns the action code for that gene
      if(match==true){
        return genes[i][NUM_CODES-1];
      }
    }
    //if none matched, returns action code of last gene
    return genes[NUM_GENES-1][NUM_CODES-1];
  }

  void action(){
    //makes robot move on map
    int move=decision();
    map[y_pos][x_pos]=NO_OBJ;

    turns_left--;
    turns_survived++;

    //if random move, sets move to a random direction
    if(move==RAND){
      move=rand()%4;
    }

    //for moving North
    if(move==NORTH){
      //if there is a wall, don't move robot
      if(sensor[NORTH]==WALL){
        map[y_pos][x_pos]=ROBOT;
      }
      //if it is an empty space, move to space
      if(sensor[NORTH]==NO_OBJ){
        y_pos-=1;
        map[y_pos][x_pos]=ROBOT;
      }
      //if there is a battery there, move to space and add more turns
      if(sensor[NORTH]==BATTERY){
        y_pos-=1;
        map[y_pos][x_pos]=ROBOT;
        turns_left+=5;
      }
    }

    //all directions follow the same pattern previously mentioned (see North)
    if(move==SOUTH){
      if(sensor[SOUTH]==WALL){
        map[y_pos][x_pos]=ROBOT;
      }
      if(sensor[SOUTH]==NO_OBJ){
        y_pos+=1;
        map[y_pos][x_pos]=ROBOT;
      }
      if(sensor[SOUTH]==BATTERY){
        y_pos+=1;
        map[y_pos][x_pos]=ROBOT;
        turns_left+=5;
      }
    }

    if(move==EAST){
      if(sensor[EAST]==WALL){
        map[y_pos][x_pos]=ROBOT;
      }
      if(sensor[EAST]==NO_OBJ){
        x_pos+=1;
        map[y_pos][x_pos]=ROBOT;
      }
      if(sensor[EAST]==BATTERY){
        x_pos+=1;
        map[y_pos][x_pos]=ROBOT;
        turns_left+=5;
      }
    }

    if(move==WEST){
      if(sensor[WEST]==WALL){
        map[y_pos][x_pos]=ROBOT;
      }
      if(sensor[WEST]==NO_OBJ){
        x_pos-=1;
        map[y_pos][x_pos]=ROBOT;
      }
      if(sensor[WEST]==BATTERY){
        x_pos-=1;
        map[y_pos][x_pos]=ROBOT;
        turns_left+=5;
      }
    }

    checkSensor();
  }

  int getTurnsLeft(){
    return turns_left;
  }

  int getTurnsSurvived(){
    return turns_survived;
  }
  
  void printMap(){
    //prints robot's map. for debugging and aesthetic purposes.
    //numbers are replaced with characters for better readability on console

    for(int i=0; i<NUM_ROWS; i++){
      for(int j=0; j<NUM_COLS; j++){
        if(map[i][j]==ROBOT){
          //robot is displayed as a square w/ a dot on console
          cout<<"▣ ";
        }
        if(map[i][j]==BATTERY){
          //battery is displayed as a dashed square on console
          cout<<"▨ ";
        }
        if(map[i][j]==WALL){
          //wall is displayed as a solid colored square on console
          cout<<"⯀ ";
        }
        if(map[i][j]==NO_OBJ){
          //empty space is displayed as a hollow dotted square on console
          cout<<"⬚ ";
        }
      }
      cout<<endl;
    }
  }

  Robot operator + (Robot const& R){
    //overloaded addition operator for robots. used in creating child from two parent robots. adds two parents genes to make new robot

    Robot child;

    //child gets half of the genes from one robot 
    for(int i=0; i<(NUM_GENES/2); i++){
      for(int j=0; j<NUM_CODES; j++){
        child.genes[i][j]=genes[i][j];
      }
    }
    //and the other half from another robot
    for(int i=NUM_GENES/2; i<NUM_GENES; i++){
      for(int j=0; j<NUM_CODES; j++){
        child.genes[i][j]=R.genes[i][j];
      }
    }

    //mutates random gene 
    int mutation=rand()%4;
    int i=rand()%NUM_GENES;   //random row
    int j=rand()%(NUM_CODES-1);   //random column
    child.genes[i][j]=mutation;

    return child;
  }
};



//Function Prototypes
void sorter(Robot* robot, const int POP);
void makingChildren(Robot* robot, const int POP);

int main() {
  const int POPULATION=200;   //number of robots per generation
  const int GENERATIONS=100;   //cluster of robots (parent to child)
  long int avg_score=0;       //average turns survived in one generation

  srand(time(0));
  Robot rob[POPULATION];

  //Program Greeting
  cout<<"Testing Robots"<<endl;
  cout<<"Program made to test robot fitness"<<endl;
 
 //loops through each generation of robots
  for(int i=0; i<GENERATIONS; i++){
    avg_score=0;
    cout<<"Gen "<<i<<": ";
    //runs through each robot in generation
    for(int j=0; j<POPULATION; j++){
      while(rob[j].getTurnsLeft()>0){
        rob[j].action();
     }
     //averages turns survived for each generation
     avg_score+=rob[j].getTurnsSurvived();
    }
    avg_score/=POPULATION;
    cout<<(avg_score)<<endl;

    sorter(rob, POPULATION);
    makingChildren(rob, POPULATION);
  }

}

void sorter(Robot* robot, const int POP){
  //sorts robots from highest to lowest using bubble sort
  Robot temp; 
  bool swapped; 
  do { 
    swapped = false; 
    for (int i= 0; i<(POP - 1); i++) { 
      if (robot[i].getTurnsSurvived() < robot[i+1].getTurnsSurvived()) { 
        temp= robot[i]; 
        robot[i] = robot[i+1]; 
        robot[i+1] = temp; 
        swapped = true; 
      } 
    } 
  } while (swapped);
}

void makingChildren(Robot* robot, const int POP){
  //makes new robots from top 100 old robots. replaces lower robots with new robots.

  for(int i=0; i<(POP/2); i=i+2){
    for(int j=POP/2; j<POP; j++){
      robot[j]=robot[i]+robot[i+1];
    }
  }
}
