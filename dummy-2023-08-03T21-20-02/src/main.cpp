/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Student                                          */
/*    Created:      Thu Jul 13 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// l1                   motor         5               
// l2                   motor         20              
// l3                   motor         17              
// r1                   motor         3               
// r2                   motor         12              
// r3                   motor         14              
// Inertial4            inertial      18              
// lr                   rotation      11              
// rr                   rotation      21              
// Controller1          controller                    
// Intake               motor         4               
// cata                 motor         8               
// LimitSwitchA         limit         A               
// Arm                  motor         19              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;


int i = 0;
int prev=0;
void reset() {
  i=0;
  prev=0;
}


int li(){
  return (l1.position(degrees)+l2.position(degrees)+l3.position(degrees))/3;
}
int ri(){
  return (r1.position(degrees)+r2.position(degrees)+r3.position(degrees))/3;
}


void sl(int speed) {
  l1.spin(forward,speed,pct);
  l2.spin(forward,speed,pct);
  l3.spin(forward,speed,pct);
}
void sr(int speed) {
  r1.spin(forward,speed,pct);
  r2.spin(forward,speed,pct);
  r3.spin(forward,speed,pct);
}
void sl1(int speed) {
  l2.spin(forward,speed,pct);
  l3.spin(forward,speed,pct);
}
void sr1(int speed) {
  r1.spin(forward,speed,pct);
  r2.spin(forward,speed,pct);
}

void wings(int i) {
  if(i==1) {
    wingL.set(true);
    wingR.set(false);
  }
  else if (i==2) {
  wingR.set(true);
  wingL.set(false);
  }
  else if(i==3){
    wingL.set(true);
    wingR.set(true);
  }
  else if(i==0){
    wingL.set(false);
    wingR.set(false);
  }

}

void pid(int ang) {
  float p = ang-inert.rotation();
  float i = 0;
  float d = ang;
  float kp;
  
  kp = .35;
  
  float ki=0;//.000000000000001;
  float kd=.12;
  while(fabs(d)>.3||fabs(p)>.6) {
    float prev = p;
    p=ang-inert.rotation();
    d=p-prev;
    if(fabs(p)<10){
    i+=p;
    }
    l1.spin(forward,p*kp+d*kd+i*ki,pct);
    l2.spin(forward,p*kp+d*kd+i*ki,pct);
    l3.spin(forward,p*kp+d*kd+i*ki,pct);
    r1.spin(reverse,p*kp+d*kd+i*ki,pct);
    r2.spin(reverse,p*kp+d*kd+i*ki,pct);
    r3.spin(reverse,p*kp+d*kd+i*ki,pct);

    //sl(p*kp+d*kd);
    //sr(-p*kp+-d*kd);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print(p);
    wait(10,msec);
  }
  sl(0);
  sr(0);
}

void pid(int ang,int timeout) {
  float p = ang-inert.rotation();
  float i = 0.000001;
  float d = ang;
  float kp=.35;
  
  float kd=.12;
  int t=0;
  while((fabs(d)>.3||fabs(p)>.3)&&t<timeout) {
    t+=10;
    float prev = p;
    p=ang-inert.rotation();
    d=p-prev;

    l1.spin(forward,p*kp+d*kd,pct);
    l2.spin(forward,p*kp+d*kd,pct);
    l3.spin(forward,p*kp+d*kd,pct);
    r1.spin(reverse,p*kp+d*kd,pct);
    r2.spin(reverse,p*kp+d*kd,pct);
    r3.spin(reverse,p*kp+d*kd,pct);

    //sl(p*kp+d*kd);
    //sr(-p*kp+-d*kd);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(inert.rotation());
    wait(10,msec);
  }
  sl(0);
  sr(0);
}

void intout() {
  Intake.spin(reverse,100,pct);
  wait(1,sec);
  Intake.stop();
}

void pidswingr(int ang) {
  float p = ang;
  float i = 0;
  float d = ang;

  float kp = .6;
  float kd=0.05;
  while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5) {
    float prev = p;
    p=ang-inert.rotation();
    d=p-prev;

    //sl(p*kp+d*kd);
    r1.spin(reverse,p*kp+d*kd,pct);
    r2.spin(reverse,p*kp+d*kd,pct);
    r3.spin(forward,p*kp+d*kd,pct);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(inert.rotation());
    wait(10,msec);
  }
  
  sl(0);
  sr(0);
}

void pidswingl(int ang) {
  float p = ang;
  float i = 0;
  float d = ang;

  float kp = .45;
  float kd=.05;
  float t=0;
  while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5&&t<800) {
    float prev = p;
    p=ang-inert.rotation();
    d=p-prev;

    l1.spin(forward,p*kp+d*kd,pct);
    l2.spin(forward,p*kp+d*kd,pct);
    l3.spin(forward,p*kp+d*kd,pct);
    sr(-p*.05);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(inert.rotation());
    wait(10,msec);
    t+=10;
  }
  
  sl(0);
  sr(0);
}

void pidswingl2(int ang) {
  float p = ang;
  float i = 0;
  float d = ang;

  float kp = .6;
  float kd=0.05;
  float t=0;
  while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5&&t<500) {
    float prev = p;
    p=ang-inert.rotation();
    d=p-prev;
    float inp=p*kp+d*kd;
    if(inp>50) {
      inp=50;
    }
    l1.spin(reverse,inp,pct);
    l2.spin(forward,inp,pct);
    l3.spin(forward,inp,pct);
    //sr(-p*kp+-d*kd);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(inert.rotation());
    wait(10,msec);
    t+=10;
  }
  pid(ang);
  sl(0);
  sr(0);
}

void pidd(int dist, int ang) {
  l1.resetPosition();
  l2.resetPosition();
  l3.resetPosition();
  r1.resetPosition();
  r2.resetPosition();
  r3.resetPosition();
double kp=.08;


double kd = 0.11;
//dist=dist*4*3.25*3.14159/(5*360);
float p = dist;
float d=dist;

double kap = .03;

while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5) {
    float prev = p;
    p=dist-(li()+ri())/2;
    d=p-prev;

    float ap = ang-inert.rotation();

    sl(p*kp+d*kd+ap*kap);
    sr(p*kp+d*kd-ap*kap);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(kp);
    wait(10,msec);
  }
  sl(0);
  sr(0);
}

void pidd(int dist, int ang,int timeout) {
  l1.resetPosition();
  l2.resetPosition();
  l3.resetPosition();
  r1.resetPosition();
  r2.resetPosition();
  r3.resetPosition();
double kp=.08;


double kd = 0.11;
//dist=dist*4*3.25*3.14159/(5*360);
float p = dist;
float d=dist;

double kap = .03;
double t =0;
while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5&&t<timeout) {
    float prev = p;
    p=dist-(li()+ri())/2;
    d=p-prev;
    t+=10;
    float ap = ang-inert.rotation();
    int pow = p*kp+d*kd;
    
    sl(pow+ap*kap);
    sr(pow-ap*kap);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(kp);
    wait(10,msec);
  }
  sl(0);
  sr(0);
}


int dist2=0;
int max1;

int actmax=0;
int change1(){
  while(abs((li()+ri())/2)<dist2){
    wait(10,msec);
  }
  actmax=max1;
  return 0;
}

void changemax(int dist,int max){
max1= max;
dist2=dist;
thread m(change1);
}

int ang1=0;
int dist1=0;

int actang;
int change(){
  while(abs((li()+ri())/2)<dist1){
    wait(10,msec);
  }
  actang=ang1;
  return 0;
}

void changeangle(int dist,int ang){
ang1= ang;
dist1=dist;
thread m(change);
}

void pidd(int dist, int ang,int timeout,int maxspeed) {
  l1.resetPosition();
  l2.resetPosition();
  l3.resetPosition();
  r1.resetPosition();
  r2.resetPosition();
  r3.resetPosition();
double kp=.2;

actang=ang;
double kd = 0.15;
//dist=dist*4*3.25*3.14159/(5*360);
float p = dist;
float d=dist;
actmax=maxspeed;

double kap = .2;
double t =0;
while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5&&t<timeout) {
    float prev = p;
    p=dist-(li()+ri())/2;
    d=p-prev;
    t+=10;
    float ap = actang-inert.rotation();
    int pow = p*kp+d*kd;
    if(fabs(ap)>5&&pow>maxspeed&&pow>0){
      pow=maxspeed;
    }
    if(fabs(ap)>5&&pow<maxspeed&&pow<0){
      pow=-maxspeed;
    }
    
    if(pow>70&&pow>0){
      pow=70;
    }
    if(pow<-70&&pow<0){
      pow=-70;
    }
    sl(pow+ap*kap);
    sr(pow-ap*kap);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(kp);
    wait(10,msec);
  }
  sl(0);
  sr(0);
}

void arc(int dist, int ang) {
  l1.resetPosition();
  l2.resetPosition();
  l3.resetPosition();
  r1.resetPosition();
  r2.resetPosition();
  r3.resetPosition();
double kp=.09;


double kd = 0.05;
//dist=dist*4*3.25*3.14159/(5*360);
float p = dist;
float d=dist;

double kap = 2;

while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5) {
    float prev = p;
    p=dist-(li()+ri())/2;
    d=p-prev;

    float ap = ang-inert.rotation();

    sl(p*kp+d*kd+ap*kap);
    sr(p*kp+d*kd-ap*kap);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(kp);
    wait(10,msec);
  }
  sl(0);
  sr(0);
}
competition Comp;
int select=1;
int catathing(){
  bool skillsthing=false;
  while(true) {
    if(Comp.isDriverControl()&&(select!=5||skillsthing)){
    if(Controller1.ButtonL2.pressing()&&(!Controller1.ButtonR2.pressing()&&!Controller1.ButtonL1.pressing()&&!Controller1.ButtonR1.pressing())) {
      cata.spin(forward,95,pct);
      cata2.spin(forward,95,pct);
    }
    else {
    cata.stop();
    cata2.stop();
    }
    }
    else if(select==5&&!skillsthing){
      if(Controller1.ButtonL2.pressing()){
        while(Controller1.ButtonL2.pressing()){
          wait(10,msec);
        }
        skillsthing=true;
        bwing.set(false);
      }
    }
    
    /*if(cata.torque()>.1) {
      cata.setPosition(0, deg);
      cata.spin(forward,100,pct);
      while(cata.position(deg)<400) {
        wait(10,msec);
      }
      if(di.objectDistance(inches)>2) {
      cata.stop();
      waitUntil(di.objectDistance(inches)<2);
      }
      cata.spin(forward,100,pct);
    }
    else{
      cata.spin(forward,100,pct);
    }
    */
  }
  return 0;
}

void cataauto() {
  int times=0;
  int tim=0;
  cata.spin(forward,95,pct);
  cata2.spin(forward,95,pct);
  while(times<44&&tim<24000){
  if(di.hue()>=90) {
      times++;
      while(di.hue()>=90){
      wait(10,msec);
      tim+=10;
      }
      

  }
  wait(10,msec);
  tim+=10;
  }
  cata.stop();
  cata2.stop();
}


void driver_auto(){
  pidd(-600,0);
  pid(-61,1400);
  pidd(-50,-61,400);
  pid(-61,400);
  bwing.set(true);
  cata.spin(forward,100,pct);
  wait(5,seconds);
}

int timething=0;
int timerend(){
  while(timething<800) {
    timething+=10;
    wait(10,msec);
  }
  return 0;
}


void driver() {
  thread th(catathing);
  bool n = false;
  bool t= false;
  bool m = false;
  bool z = false;
  bool l = false;
  bool r = false;
  bool rr = false;
  bool lr = false;
  bool inta = false;
  bool inta2 = false;
  bool tank = false;
  bool test=false;
  
  int toggle= 0;
  bool end=false;
  bool lifttog=false;
  bool side=false;
  bool enddone=false;
  bool inta3=false;
  if(select==5){
    pidd(-2000,45,1000,50);
  
  pid(20,400);
  pidd(790,20,700);
  pid(-60,700);
  cata.spin(forward,95,pct);
  cata2.spin(forward,95,pct);
  pidd(- 200,-60,800);
  pid(-60,200);
  bwing.set(true);
  }
  while(true) {
    

    if(!Controller1.ButtonX.pressing()&&!Controller1.ButtonB.pressing()){
      lifttog=false;
    }
    
    
    if(!tank){
    l1.spin(forward,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    l2.spin(forward,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    l3.spin(forward,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    r1.spin(forward,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    r2.spin(forward,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    r3.spin(forward,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    }
    else{
      l1.spin(forward,Controller1.Axis3.position(),pct);
      l2.spin(forward,Controller1.Axis3.position(),pct);
      l3.spin(forward,Controller1.Axis3.position(),pct);
      r1.spin(forward,Controller1.Axis2.position(),pct);
      r2.spin(forward,Controller1.Axis2.position(),pct);
      r3.spin(forward,Controller1.Axis2.position(),pct);
    }
    
    if(Controller1.ButtonX.pressing()){
      
      
      end=true;
      
      
        release.set(true);
        
      
      
    }
    
    if(Controller1.ButtonL1.pressing()&&Controller1.ButtonL2.pressing()&&Controller1.ButtonR1.pressing()&&Controller1.ButtonR2.pressing()){
    
        pto.set(true);
        wingR.set(false);
        wingL.set(false);
        release.set(false);
        bwingl.set(false);
        bwing.set(false);
        end=true;
        
        
          
        
        
        
      }

    
    

    
    
    if(Controller1.ButtonRight.pressing()&&Controller1.ButtonLeft.pressing()&&Controller1.ButtonDown.pressing()&&Controller1.ButtonUp.pressing()&&Controller1.ButtonA.pressing()&&Controller1.ButtonB.pressing()&&Controller1.ButtonX.pressing()&&Controller1.ButtonY.pressing()){
      tank = true;
    }
    
      
    if(Controller1.ButtonA.pressing()&&Controller1.ButtonB.pressing()&&Controller1.ButtonX.pressing()&&Controller1.ButtonY.pressing()){
      test=true;
    }
      
    
    
    if(!end&&Controller1.ButtonL1.pressing()&&Controller1.ButtonR1.pressing()&&inta==false&&!(Controller1.ButtonL2.pressing()&&Controller1.ButtonR2.pressing())) {
        bwing.set(!bwing.value());
        
        inta=true;
      }
      else if(!Controller1.ButtonL1.pressing()&&!Controller1.ButtonR1.pressing()){
        inta=false;
      }

    if(Controller1.ButtonRight.pressing()) {
        bwingl.set(!bwingl.value());
        
        inta3=true;
      }
      else if(!Controller1.ButtonRight.pressing()){
        inta3=false;
      }
    
    
    else{
      inta2=false;
    }
    
    if(!toggle){
    if(Controller1.ButtonL1.pressing()&&!Controller1.ButtonR1.pressing()) {
      Intake.spin(forward,100,pct);
    }
    else if(Controller1.ButtonR1.pressing()&&!Controller1.ButtonL1.pressing()) {
      Intake.spin(reverse,100,pct);
    }
    else{
      Intake.stop(hold);
    }
    }
    

    
    if(Controller1.ButtonB.pressing()){
      pto.set(false);
    }
    

    if(Controller1.ButtonR2.pressing()&&!Controller1.ButtonR1.pressing()&&!Controller1.ButtonL2.pressing()&&!Controller1.ButtonL1.pressing()&&!toggle) {
      
      if(t&&m==false) {
        t=false;
      }
      else if(!t&&m==false) {
        t=true;
      }
      if(m==false&&(wingL.value()||wingR.value())){
        t=false;
      }
      wingL.set(t);
      wingR.set(t);
      m=true;
      
    }
    if(!Controller1.ButtonR2.pressing()) {
      m=false;
    }

     if(Controller1.ButtonY.pressing()) {
      
      
      if(lr==false){
        wingL.set(!wingL.value());
      }
      
      
      lr=true;
    }
    if(!Controller1.ButtonY.pressing()) {
      lr=false;
    }
    if(Controller1.ButtonA.pressing()) {
      
      

      if(rr==false){
      wingR.set(!wingR.value());
      }
      
      rr=true;
    }
    if(!Controller1.ButtonA.pressing()) {
      rr=false;
    }
    
  }
}

void intin(){
  Intake.spin(forward,100,pct);
}
void inout() {
  Intake.spin(reverse,100,pct);
}
int distin() {
  while(li()<200){
    wait(10,msec);
  }
  intout();
  return 0;
}
void intstop() {
  Intake.stop(hold);
}


int psel;
void pre() {
  inert.calibrate();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Defense awp");

  while(true){//!Comp.isAutonomous()) {

  if(selector.pressing()){
    select++;
    if(select>5){
      select=1;
    }
    while(selector.pressing()){
      wait(.1,sec);
      Brain.Screen.clearScreen();
    }
  
  
  
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  
  if(select == 1) {
    Brain.Screen.print("Defense awp");
  }
  if(select == 2) {
    Brain.Screen.print("Defense Elims");
  }
  if(select == 3) {
    Brain.Screen.print("Offense Elims");
  }
  if(select==4) {
    Brain.Screen.print("offense awp");
  }
  if(select==5) {
    Brain.Screen.print("skills");
  
  }
  
}}
}
void db(int degs){
  double ang= inert.rotation();
  l1.resetPosition();
  l2.resetPosition();
  l3.resetPosition();
  r1.resetPosition();
  r2.resetPosition();
  r3.resetPosition();
  
  while(li()+ri()>-degs*2) {
    float ap = ang-inert.rotation();
    sl(-70+ap*.05);
    sr(-70-ap*.05);
    wait(20,msec);
  }
  sl(0);
  sr(0);
}


void drive(int lspeed,int rspeed) {

}


int wingin() {
  wait(.4,sec);
  wingL.set(false);
  wingR.set(false);
  return 0;
}


void autodefensewp(){
  bwing.set(true);
  pid(-40,500);
  bwing.set(false);
  pidd(1800,-40);
  
}

void autooffenseawp1(){
  intin();
  pidd(400,0,500);
  intstop();
  changeangle(1000,-45);
  pidd(-2150,0,2000,20);
  bwingl.set(true);
  pid(-90,500);
  bwingl.set(false);
  pid(-45,500);
  pidd(-1000,-90,800,40);
  pidd(400,-90,500);
  pid(90,700);
  inout();
  wingR.set(true);
  pidd(800,90,600);
  pidd(-500,90);
  pidd(1000,90,500);
  wingR.set(false);
  pidd(-600,90);
  pid(-45,600);
  pidd(1200,-45);
  pid(0,600);
  pidd(1300,0);
}

void autooffenseawp(){
  pidd(-1000,0,600);
  pidd(800,-10);
  pid(100,600);
  intin();
  pidd(2300,100);
  pid(160,700);
  pidd(800,160);
  pid(250,600);
  wingL.set(true);
  inout();
  pidd(5000,180,800);
  pidd(-1200,180);
  pid(110,800);
  intin();
  pidd(400,110,500);
  inout();
  pidd(5000,250);
}

void autooffenseelim(){
  intin();
  pidd(400,0,600);
  intstop();
  changeangle(1000,-45);
  pidd(-2150,0,2000,40);
  bwingl.set(true);
  pid(-90,500);
  bwingl.set(false);
  pid(-45,500);
  pidd(-1000,-90,800,40);
  pidd(700,-90,500);
  pid(90,700);
  inout();
  pidd(1500,90,700);
  pidd(-1000,90);
  pid(25,600);
  intin();
  pidd(2300,10);
  pid(90,700);
  pidd(800,110);
  pid(180,600);
  wingL.set(true);
  inout();
  pidd(5000,180,800);
  pidd(-1200,180);
  pid(20,800);
  intin();
  pidd(400,20,500);
  inout();
  pidd(5000,180);
}

int wingout(){
  while(l1.position(degrees)<1500){
    wait(10,msec);
  }
  wingR.set(true);
  return(0);
}

void skills(){
  
  
  pidd(-2000,45,1000,50);
  
  pid(20,400);
  pidd(790,20,700);
  pid(-60,700);
  cata.spin(forward,95,pct);
  cata2.spin(forward,95,pct);
  pidd(- 200,-60,800);
  pid(-60,200);
  bwing.set(true);
  cataauto();
  bwing.set(false);
  
  thread l(wingout);
  pidd(2300,-45,2000,20);
  
  pidd(-400,-45,500);
  pid(-128,600);
  wingL.set(true);
  wingR.set(true);
  pidd(3600,-135);
  wingL.set(false);
  wingR.set(false);
  pidd(-200,-135,400);
  pid(-225,600);
  pidd(1500,-160,1000,40);
  pid(-90,500);
  pidd(1600,-90,800);
  
  pid(-47,500);
  wingR.set(true);
  wingL.set(true);
  pidd(2950,-45);
  wingL.set(false);
  pid(0,500);
  pidd(1900,45,900,60);
  
  wingR.set(false);
  
  pidd(-100,45);
  pid(128,700);
  pidd(1800,128,800);
  pid(45,700);
  wingL.set(true);
  wingR.set(true);
  pidd(1600,-45,1000,40);
  pidd(-600,-45);
  pidd(2000,-45,600);
  wingL.set(false);
  wingR.set(false);
  changeangle(800, -135);
  pidd(-4000,-90,2200,30);
  pidd(-1000,-135);
  pid(-90,600);
  wingL.set(true);
  wingR.set(true);
  pidd(2000,-45,1000,40);
  pidd(-600,-45);
  pidd(2000,-45,600);
  wingL.set(false);
  wingR.set(false);
  pid(-135,600);
  
  pidd(-1000,-135,600);
  pidd(-3000,-315,1600,50);
  pidd(400,-315);
  pid(-270,500);
  pidd(1200,-450);
  pid(-225,600);
  pto.set(true);
  pidd(2000,-225,1000);
  pto.set(false);
}

void disrupt(){
  wingL.set(true);
  thread d(wingin);
  intin();
  pidd(2300,0);
  pidd(-200,0);
  pid(70,600);
  wingL.set(true);
  inout();
  pidd(1000,80);
  wingL.set(false);
  pidd(-200,80);
  pid(29,500);
  pidd(-2800,30);
  pid(80,600);
  inout();
  pidd(1600,80);
  
  pidd(-2000,110);
  
  // pid(50);
  // bwing.set(true);
}

int brainread(){
  while (true){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print(inert.rotation());
    wait(.1,sec);
  }
  return 0;
}

void skills2(){
  //thread t(brainread);
  bwingl.set(true);
  pidd(-600,45);
  // pid(40,600);
  // pidd(-300,40);
  // pidd(300,45);
  bwingl.set(false);
  pid(-61,1500);
  pid(-61,200);
  
  bwing.set(true);
  cata.spin(forward,85,pct);
  cata2.spin(forward,85,pct);

  wait(25.5,sec);

  cata.stop();
  cata2.stop();
  
  cata.stop();
  bwing.set(false);
  pidd(200,-60);
  pid(30,700);
  pidd(-1000,45,700);
  pidd(100,45);
  pid(0,700);
  pidd(1800,0);
  pid(-45,700);
  pidd(3600,-45);
  pid(-90,500);
  pidd(500,-90);
  pidd(-500,-90);
  pid(90,500);
  pidd(-800,90);
  pid(52,500);
  
  pidd(-1000,45,800);
  pid(45,200);
  pidd(500,45);
  pidd(-500,45);
  pidd(300,45);
  pid(135,700);
  pidd(2000,135);
  pid(225,700);
  pidd(700,225);
  pid(300,600);
  wingL.set(true);
  wingR.set(true);
  
  pidd(1200,270,1000);
  wingL.set(false);
  wingR.set(false);
  pid(315,500);
  pidd(-1000,315);
  pid(225,500);
  pidd(1500,225);
  pid(315,700);
  wingL.set(true);
  wingR.set(true);
  pidd(1600,315,1000);
  
  wingL.set(false);
  wingR.set(false);
  pid(290,500);
  pidd(-900,300);
  pid(315,300);
  wingL.set(true);
  wingR.set(true);
  pidd(1600,315,1000);
}



void autonomousprogram() {
  
  if(select==1){
    disrupt();//autodefensewp();
  }
  if(select==2){
    disrupt();
  }
  if(select==3){
    autooffenseelim();
    //pidswingl(-45);
    //pidd(500,-45);
  }
  if(select==5){
    skills();
  }
  if(select==4){
    autooffenseawp();
  }
}



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
   Comp.autonomous(autonomousprogram);
   Comp.drivercontrol(driver);

  pre();
  
  
  
  

  while(1){
    wait(100,msec);
    
  }

}