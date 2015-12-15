#ifndef ELVIS_INIT_H
#define ELVIS_INIT_H

//--------------------------INCLUDE
#include <ros/ros.h>
#include <iostream>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Float64.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <tf/tf.h>
#include <tf/transform_datatypes.h>
#include <sensor_msgs/JointState.h>
#include <cmath>

//-------------------------NAMESPACE
using namespace std;
using namespace tf;
using namespace ros;


//-------------------JOYSTICK MACRO
// definitions for F710 in "direct input mode" (switch on 
// back side in "D" position), recognized as Logitech Cordless Rumblepad 2 

//sticks 
#define LR_stick_left   0
#define UD_stick_left   1
#define LR_stick_right  2
#define UD_stick_right  3
//cross
#define LR_cross_key    4
#define UD_cross_key    5

#define X               0
#define A               1
#define B               2
#define Y     	        3
#define LB    	        4
#define RB  	        5
#define LT              6
#define RT              7
#define BACK            8
#define START           9
#define L3              10
#define R3              11

//joystick sticks scale factor
#define scaleFacTrans  50
#define scaleFacRot    10



//----------------GLOBABEL VARIBALE
int mode = 0; 
int operation = 0;              
int ON = 1; 
int Counter_ = 0;
int Counter2_= 0;
int Vector_Length_ = 0;
float x_length = 0;
int iw = 1;
int fmode;
int rmode;
int laufen = 0;

//---------------------------STRUCT
//joypad
struct rumblePad2Struct{
	Vector3 speed; 
	Vector3 bdR;   
	Vector3 bdT;   
};
extern rumblePad2Struct rumblePad2;
//motoren
typedef struct{
	double m11;
	double m12;
	double m13;
	double m14;
	double m15;
	double m16;
	double m21;
	double m22;
	double m23;
	double m24;
	double m25;
	double m26;	
	double m31;
	double m32;
	double m33;
	double m41;
	double m42;
	double m43;
	double m51;
	double m61;
	double m62;
}structmotoren;


//----------------------------CLASS
class Elvis{

  private:
	    NodeHandle n;
	    Subscriber subJoy;          //subscriber of joy topic
	    Publisher jointPub;         //publisher (rviz)
	   
	  //L Bein
	    Publisher  pub_m11;	
	    Publisher  pub_m12;	
	    Publisher  pub_m13;
	   
	    Publisher  pub_m14;
	    Publisher  pub_m15;
	    Publisher  pub_m16;
	   
	  //R Bein
	    Publisher  pub_m21;
	    Publisher  pub_m22;
	    Publisher  pub_m23;

	    Publisher  pub_m24;
	    Publisher  pub_m25;
	    Publisher  pub_m26;
	   
	  //Becken
	    Publisher  pub_m51;

	  //Kopf
	    Publisher  pub_m61;
	    Publisher  pub_m62;
	    
	  //L Arm
	    Publisher  pub_m31;
	    Publisher  pub_m32;
	    Publisher  pub_m33;
	   
	  //R Arm
	    Publisher  pub_m41;
	    Publisher  pub_m42;
	    Publisher  pub_m43;     

  public:
    //constructor
    Elvis();
	void initElvis_move();
	void initElvis_stand_up();
	int moveMotors_neck_joint(double z);
	int moveMotors_left_shoulder_joint(double x, double y);
	int moveMotors_left_elbow_joint(double x);
	int moveMotors_right_shoulder_joint(double x, double y);
	int moveMotors_right_elbow_joint(double x);
	int moveMotors_right_hip_joint(double x, double y, double z);
	int moveMotors_right_knee_joint(double x);
	int moveMotors_right_ankle_joint(double x, double y, int i);	
	int moveMotors_left_hip_joint(double x, double y, double z);
	int moveMotors_left_knee_joint(double x);
	int moveMotors_left_ankle_joint(double x, double y, int i);	
	int moveMotors_camera_joint(double z);
	int moveMotors_trunk_joint(double x);
	void csv(const string &p);
	void moveElvis(int i);
	void callRumblePad2Back(const sensor_msgs::Joy::ConstPtr& joy);
};
double string_to_double(const string& s);
#endif
