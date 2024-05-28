#include <Braccio.h>
#include <servo.h>
//#include "InverseK.h"


Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot; 
Servo gripper;

void setup() { 
   Serial.begin(9600);
       Serial.print("start setup");


  // put your setup code here, to run once:
  Braccio.begin();
  //Braccio.ServoMovement(0, 130, 180, 120, 90, 90, 73);
  /*
  //heavy thing grabbing animation
  Braccio.ServoMovement(0, 100, 180, 100, 100, 0, 0);
  delay(1000);
  Braccio.ServoMovement(0, 100, 180, 100, 100, 45, 0);
  delay(1000);
  Braccio.ServoMovement(0, 50, 130, 100, 100, 45, 0);
  */

  /*
  Link base, upperarm, forearm, hand;

  base.init(0,b2a(0.0),b2a(180.0));
  upperarm.init(200,b2a(15.0),b2a(165.0));
  forearm.init(200,b2a(0.0),b2a(180.0));
  hand.init(270,b2a(0.0),b2a(180.0));

  InverseK.attach(base, upperarm, forearm, hand);
  float a0, a1, a2, a3;

  if(InverseK.solve(400, 0, 50, a0, a1, a2, a3)){
      Serial.print(a2b(a0)); Serial.print(',');
      Serial.print(a2b(a1)); Serial.print(',');
      Serial.print(a2b(a2)); Serial.print(',');
      Serial.println(a2b(a3));
      delay(100);
      Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 90, 0);
      delay(1000);
      Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 90, 73);
  } else {
    Serial.print("No solution found!");
  }
  */
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  // InverseK.solve(x, y, z, a0, a1, a2, a3, phi)
    Serial.println("Done");
}

//turning system

int jointnames[] = {"base", "shoulder", "elbow", "wrist"};
int joints[] = {90, 90, 90, 90};
int jointchange[] = {0,0,0,0};
int jointnum = 1;
//gripper
int grip1 = 50;
//selection(?)
int options[] = {0,0};

bool game = true;
int round = 1;
int goal[] = {0,0,0,0};

void loop() {
  goal = {random(60, 120), random(60, 120), random(60, 120), random(60, 120)}
  while (game = true){

    
    //Serial.begin(9600);
    //read botton status
    int button = digitalRead(4);
    int choice = digitalRead(2);
    if (button == 0){
      
      if (choice == 1){

        Serial.print(choice);
        jointchange[jointnum] += options[0];
        joints[jointnum] += jointchange[jointnum];
        if (joints[jointnum] > 180){
          joints[jointnum] = joints[jointnum] - 180;
        }
        Serial.print("Joint:");
        Serial.println(jointnames[1]);
        Serial.print("Angle:");
        Serial.println(joints[jointnum]);
        Braccio.ServoMovement(0, joints[0], joints[1], joints[2], joints[3], grip1, 0);
      }
      else{
        //add 
        Serial.print(choice);
        jointchange[jointnum] += options[0];
        joints[jointnum] += jointchange[jointnum];
        if (joints[jointnum] < 0){
          joints[jointnum] = joints[jointnum] + 180;
        }
        Serial.print("Joint:");
        Serial.println(jointnames[1]);
        Serial.print("Angle:");
        Serial.println(joints[jointnum]);
        Braccio.ServoMovement(0, joints[0], joints[1], joints[2], joints[3], grip1, 0);
      }
      while (digitalRead(4) == 0){
        int button = digitalRead(4);
      }
      if (jointnum < 3){
          jointnum++;
        }
      else{
        jointnum = 0;
      }
      for (int i = 0; i <= 3; i++){
        if (joints[i] > goal[i] - 20 && joints[i] < goal[i] + 20);
      }
      Serial.println(" Joint change: ");
      Serial.print("Base change: ");
      Serial.println(jointchange[0]);
      Serial.print("Shoulder change: ");
      Serial.println(jointchange[1]); 
      Serial.print("Elbow change: ");
      Serial.println(jointchange[2]); 
      Serial.print("Wrist change: ");
      Serial.println(jointchange[3]);
      options[0] = random(5, 50);
      options[1] = random(-50, -5);
      Serial.print("Cahnge moter ");
      Serial.print(jointnum);
      Serial.println(" by:");
      Serial.print(options[0]);
      Serial.print(" or ");
      Serial.println(options[1]);
      Serial.print("Base goal: ");
      Serial.println(goal[0]);
      Serial.print("Shoulder goal: ");
      Serial.println(goal[1]);
      Serial.print("Elbow goal: ");
      Serial.println(goal[2]);
      Serial.print("Wrist goal: ");
      Serial.println(goal[3]);

    }
  }
}


// Quick conversion from the Braccio angle system to radians
float b2a(float b){
  return b / 180.0 * PI - HALF_PI;
}

// Quick conversion from radians to the Braccio angle system
float a2b(float a) {
  return (a + HALF_PI) * 180 / PI;
}

