#include<ros/ros.h>
#include<std_msgs/Float64.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<fstream>
#include<elvis/elvis_init.h>
#include<tf/tf.h>
#include<tf/transform_datatypes.h>
#include<tf/transform_broadcaster.h>
#include<geometry_msgs/TransformStamped.h>
#include<sensor_msgs/JointState.h>
#include<cmath>

using namespace std;
using namespace tf;
rumblePad2Struct pad;
sensor_msgs::JointState js;

/* ------------------------------------------------------------------*/ 
	/* Here is read the angles parameters from a .csv file,
	then the info is located in a structure and the structrure 
	is located in a Vector. */
	structmotoren winkelstruktur;
	/* Here is defined the structures in a vector, each line is
	   a structure and each structure a position in a vector */	
	vector<structmotoren> wv; /* wv = winkelvektoren */
	/*-----------------------------------------------------------*/

/* ------------------------------------------------------------------*/ 
// Elvis() Constructor
/* ------------------------------------------------------------------*/ 
Elvis::Elvis(){

	//[SUBCRIBER]	-- subJoy:  subscribe the topic(joy)
  	//		-- subMots: subscribe the topic(/motorState/pan_tilt_port/)
  	subJoy = n.subscribe<sensor_msgs::Joy>("joy", 10, &Elvis::callRumblePad2Back, this);
  	jointPub = n.advertise<sensor_msgs::JointState>("/joint_states",1);	

	pub_m11 = n.advertise<std_msgs::Float64>("/m11/command",1);
	pub_m12 = n.advertise<std_msgs::Float64>("/m12/command",1);
	pub_m13 = n.advertise<std_msgs::Float64>("/m13/command",1);
	pub_m14 = n.advertise<std_msgs::Float64>("/m14/command",1);
	pub_m15 = n.advertise<std_msgs::Float64>("/m15/command",1);
	pub_m16 = n.advertise<std_msgs::Float64>("/m16/command",1);
	pub_m21 = n.advertise<std_msgs::Float64>("/m21/command",1);
	pub_m22 = n.advertise<std_msgs::Float64>("/m22/command",1);
	pub_m23 = n.advertise<std_msgs::Float64>("/m23/command",1);
	pub_m24 = n.advertise<std_msgs::Float64>("/m24/command",1);
    	pub_m25 = n.advertise<std_msgs::Float64>("/m25/command",1);
	pub_m26 = n.advertise<std_msgs::Float64>("/m26/command",1);
	pub_m31 = n.advertise<std_msgs::Float64>("/m31/command",1);
	pub_m32 = n.advertise<std_msgs::Float64>("/m32/command",1);
	pub_m33 = n.advertise<std_msgs::Float64>("/m33/command",1);
	pub_m41 = n.advertise<std_msgs::Float64>("/m41/command",1);
	pub_m42 = n.advertise<std_msgs::Float64>("/m42/command",1);
	pub_m43 = n.advertise<std_msgs::Float64>("/m43/command",1);
	pub_m51 = n.advertise<std_msgs::Float64>("/m51/command",1);
	pub_m61 = n.advertise<std_msgs::Float64>("/m61/command",1);
	pub_m62 = n.advertise<std_msgs::Float64>("/m62/command",1);

	js.name.resize(21);
	js.position.resize(21);
  	js.velocity.resize(21);
  	js.effort.resize(21);
}


/* ------------------------------------------------------------------*/ 
// String to Double Function
/* ------------------------------------------------------------------*/ 

double string_to_double(const string& s){
	istringstream i(s);
	double x;
	if (!(i>>x))
	  return 0;
	return x; 
}

/* ------------------------------------------------------------------*/ 
// Joint Functions for the Head and Trunk
/* ------------------------------------------------------------------*/ 
// Neck Horizontal Movement
/* ------------------------------------------------------------------*/ 

int Elvis::moveMotors_neck_joint(double z){
	std_msgs::Float64 aux;
	aux.data = z*3.14/180;
	pub_m61.publish(aux);
	js.name[19] = "m61";
        js.position[19] = aux.data;
        js.velocity[19] = 0.0;
        js.effort[19] = 0.0; 

	return 1;
}
/* ------------------------------------------------------------------*/ 
// Camera Head Movement (Up-Down)
/* ------------------------------------------------------------------*/ 
int Elvis::moveMotors_camera_joint(double z){
	std_msgs::Float64 aux;
	aux.data = z*3.14/180;
	pub_m62.publish(aux);
	js.name[20] = "m62";
        js.position[20] = aux.data;
        js.velocity[20] = 0.0;
        js.effort[20] = 0.0;
	return 1;
}
/* ------------------------------------------------------------------*/ 
// Trunk
/* ------------------------------------------------------------------*/ 
int Elvis::moveMotors_trunk_joint(double x){
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m51.publish(aux);
	js.name[18] = "m51";
        js.position[18] = aux.data;
        js.velocity[18] = 0.0;
        js.effort[18] = 0.0; 
	return 1;
}

/* ------------------------------------------------------------------*/ 
// Joint Functions for the Arms 
/* ------------------------------------------------------------------*/ 
// Left Arm 
/* ------------------------------------------------------------------*/ 
// Left Shoulder Joint
int Elvis::moveMotors_left_shoulder_joint(double x, double y){
	std_msgs::Float64 aux;
	
	aux.data = x*3.14/180;
	pub_m31.publish(aux);
	js.name[12] = "m31";
        js.position[12] = aux.data;
        js.velocity[12] = 0.0;
        js.effort[12] = 0.0;

	aux.data = y*3.14/180;
	pub_m32.publish(aux);
	js.name[13] = "m32";
        js.position[13] = aux.data;
        js.velocity[13] = 0.0;
        js.effort[13] = 0.0;
	return 1;
}

// Left Elbow Joint
int Elvis::moveMotors_left_elbow_joint(double x){
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m33.publish(aux);
	js.name[14] = "m33";
        js.position[14] = aux.data;
        js.velocity[14] = 0.0;
        js.effort[14] = 0.0; 
	return 1;
}
/* ------------------------------------------------------------------*/ 
// Right Arm 
/* ------------------------------------------------------------------*/ 
// Right Shoulder Joint
int Elvis::moveMotors_right_shoulder_joint(double x, double y){
	std_msgs::Float64 aux;

	aux.data = x*3.14/180;
	pub_m41.publish(aux);
	js.name[15] = "m41";
        js.position[15] = aux.data;
        js.velocity[15] = 0.0;
        js.effort[15] = 0.0;

	aux.data = y*3.14/180;
	pub_m42.publish(aux);
	js.name[16] = "m42";
        js.position[16] = aux.data;
        js.velocity[16] = 0.0;
        js.effort[16] = 0.0;
	return 1;
}

// Right Elbow Joint
int Elvis::moveMotors_right_elbow_joint(double x){
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m43.publish(aux);
	js.name[17] = "m43";
        js.position[17] = aux.data;
        js.velocity[17] = 0.0;
        js.effort[17] = 0.0; 
	return 1;
}

/* ------------------------------------------------------------------*/ 
// Joint Functions for the Legs 
/* ------------------------------------------------------------------*/ 
// Left Leg 
/* ------------------------------------------------------------------*/ 
// Left Hip Joint
int Elvis::moveMotors_left_hip_joint(double x, double y, double z){
	std_msgs::Float64 aux;

	aux.data = x*3.14/180;
	pub_m12.publish(aux);
	js.name[1] = "m12";
        js.position[1] = aux.data;
        js.velocity[1] = 0.0;
        js.effort[1] = 0.0;

	aux.data = y*3.14/180;
	pub_m13.publish(aux);
	js.name[2] = "m13";
        js.position[2] = aux.data;
        js.velocity[2] = 0.0;
        js.effort[2] = 0.0;

	aux.data = z*3.14/180;
	pub_m11.publish(aux);
	js.name[0] = "m11";
        js.position[0] = aux.data;
        js.velocity[0] = 0.0;
        js.effort[0] = 0.0;

	return 1;
}
// Left Knee Joint
int Elvis::moveMotors_left_knee_joint(double x){
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m14.publish(aux);
	js.name[3] = "m14";
        js.position[3] = aux.data;
        js.velocity[3] = 0.0;
        js.effort[3] = 0.0; 
	return 1;
}
// Left Ankle Joint
int Elvis::moveMotors_left_ankle_joint(double x, double y, int i){
	std_msgs::Float64 aux;
	//Vector3 m16_trans; Vector3 m16_rot;
	
	aux.data = x*3.14/180;
	pub_m15.publish(aux);
	js.name[4] = "m15";
        js.position[4] = aux.data;
        js.velocity[4] = 0.0;
        js.effort[4] = 0.0;

	aux.data = y*3.14/180;
	pub_m16.publish(aux);
	js.name[5] = "m16";
        js.position[5] = aux.data;
        js.velocity[5] = 0.0;
        js.effort[5] = 0.0;
	
	return 1;
}


/* ------------------------------------------------------------------*/ 
// Right Leg 
/* ------------------------------------------------------------------*/ 
// Right Hip Joint
int Elvis::moveMotors_right_hip_joint(double x, double y, double z){
	std_msgs::Float64 aux;

	aux.data = x*3.14/180;
	pub_m22.publish(aux);
	js.name[7] = "m22";
        js.position[7] = aux.data;
        js.velocity[7] = 0.0;
        js.effort[7] = 0.0;

	aux.data = y*3.14/180;
	pub_m23.publish(aux);
	js.name[8] = "m23";
        js.position[8] = aux.data;
        js.velocity[8] = 0.0;
        js.effort[8] = 0.0;

	aux.data = z*3.14/180;
	pub_m21.publish(aux);
	js.name[6] = "m21";
        js.position[6] = aux.data;
        js.velocity[6] = 0.0;
        js.effort[6] = 0.0;

	return 1;
}
// Right Knee Joint
int Elvis::moveMotors_right_knee_joint(double x){
	std_msgs::Float64 aux;

	aux.data = x*3.14/180;
	pub_m24.publish(aux);
	js.name[9] = "m24";
        js.position[9] = aux.data;
        js.velocity[9] = 0.0;
        js.effort[9] = 0.0;

	return 1;
}
// Right Ankle Joint
int Elvis::moveMotors_right_ankle_joint(double x, double y, int i){
	std_msgs::Float64 aux;
	//Vector3 m26_trans; Vector3 m26_rot;

	aux.data = x*3.14/180;
	pub_m25.publish(aux);
	js.name[10] = "m25";
        js.position[10] = aux.data;
        js.velocity[10] = 0.0;
        js.effort[10] = 0.0;

	aux.data = y*3.14/180;
	pub_m26.publish(aux);
	js.name[11] = "m26";
        js.position[11] = aux.data;
        js.velocity[11] = 0.0;
        js.effort[11] = 0.0;
	
	return 1;
}
/* ------------------------------------------------------------------*/
void Elvis::initElvis_stand_up(){ 
        std_msgs::Float64 aux;
	js.header.stamp = ros::Time::now();
	aux.data = 0.0;

	pub_m11.publish(aux);
	js.name[0] = "m11";
        js.position[0] = aux.data;
        js.velocity[0] = 0.0;
        js.effort[0] = 0.0;

	pub_m12.publish(aux);
	js.name[1] = "m12";
        js.position[1] = aux.data;
        js.velocity[1] = 0.0;
        js.effort[1] = 0.0;

	pub_m13.publish(aux);
	js.name[2] = "m13";
        js.position[2] = aux.data;
        js.velocity[2] = 0.0;
        js.effort[2] = 0.0;

	pub_m14.publish(aux);
	js.name[3] = "m14";
        js.position[3] = aux.data;
        js.velocity[3] = 0.0;
        js.effort[3] = 0.0;

	pub_m15.publish(aux);
	js.name[4] = "m15";
        js.position[4] = aux.data;
        js.velocity[4] = 0.0;
        js.effort[4] = 0.0;

	pub_m16.publish(aux);
	js.name[5] = "m16";
        js.position[5] = aux.data;
        js.velocity[5] = 0.0;
        js.effort[5] = 0.0;

	pub_m21.publish(aux);
	js.name[6] = "m21";
        js.position[6] = aux.data;
        js.velocity[6] = 0.0;
        js.effort[6] = 0.0;

	pub_m22.publish(aux);
	js.name[7] = "m22";
        js.position[7] = aux.data;
        js.velocity[7] = 0.0;
        js.effort[7] = 0.0;

	pub_m23.publish(aux);
	js.name[8] = "m23";
        js.position[8] = aux.data;
        js.velocity[8] = 0.0;
        js.effort[8] = 0.0;

	pub_m24.publish(aux);
	js.name[9] = "m24";
        js.position[9] = aux.data;
        js.velocity[9] = 0.0;
        js.effort[9] = 0.0;

	pub_m25.publish(aux);
	js.name[10] = "m25";
        js.position[10] = aux.data;
        js.velocity[10] = 0.0;
        js.effort[10] = 0.0;

	pub_m26.publish(aux);
	js.name[11] = "m26";
        js.position[11] = aux.data;
        js.velocity[11] = 0.0;
        js.effort[11] = 0.0;

	pub_m31.publish(aux);
	js.name[12] = "m31";
        js.position[12] = aux.data;
        js.velocity[12] = 0.0;
        js.effort[12] = 0.0;

	pub_m32.publish(aux);
	js.name[13] = "m32";
        js.position[13] = aux.data;
        js.velocity[13] = 0.0;
        js.effort[13] = 0.0;
	
	pub_m33.publish(aux);
	js.name[14] = "m33";
        js.position[14] = aux.data;
        js.velocity[14] = 0.0;
        js.effort[14] = 0.0;

	pub_m41.publish(aux);
	js.name[15] = "m41";
        js.position[15] = aux.data;
        js.velocity[15] = 0.0;
        js.effort[15] = 0.0;

	pub_m42.publish(aux);
	js.name[16] = "m42";
        js.position[16] = aux.data;
        js.velocity[16] = 0.0;
        js.effort[16] = 0.0;

	pub_m43.publish(aux);
	js.name[17] = "m43";
        js.position[17] = aux.data;
        js.velocity[17] = 0.0;
        js.effort[17] = 0.0;

	pub_m51.publish(aux);
	js.name[18] = "m51";
        js.position[18] = aux.data;
        js.velocity[18] = 0.0;
        js.effort[18] = 0.0;

	pub_m61.publish(aux);
	js.name[19] = "m61";
        js.position[19] = aux.data;
        js.velocity[19] = 0.0;
        js.effort[19] = 0.0;	
	
	pub_m62.publish(aux);
	js.name[20] = "m62";
        js.position[20] = aux.data;
        js.velocity[20] = 0.0;
        js.effort[20] = 0.0;

	jointPub.publish(js);
}

void Elvis::initElvis_move(){ 
        std_msgs::Float64 aux;
	js.header.stamp = ros::Time::now();
	aux.data = 0.0;

	pub_m11.publish(aux);
	js.name[0] = "m11";
        js.position[0] = aux.data;
        js.velocity[0] = 0.0;
        js.effort[0] = 0.0;

	pub_m12.publish(aux);
	js.name[1] = "m12";
        js.position[1] = aux.data;
        js.velocity[1] = 0.0;
        js.effort[1] = 0.0;

	pub_m13.publish(aux);
	js.name[2] = "m13";
        js.position[2] = aux.data;
        js.velocity[2] = 0.0;
        js.effort[2] = 0.0;

	pub_m14.publish(aux);
	js.name[3] = "m14";
        js.position[3] = aux.data;
        js.velocity[3] = 0.0;
        js.effort[3] = 0.0;

	pub_m15.publish(aux);
	js.name[4] = "m15";
        js.position[4] = aux.data;
        js.velocity[4] = 0.0;
        js.effort[4] = 0.0;

	pub_m16.publish(aux);
	js.name[5] = "m16";
        js.position[5] = aux.data;
        js.velocity[5] = 0.0;
        js.effort[5] = 0.0;

	pub_m21.publish(aux);
	js.name[6] = "m21";
        js.position[6] = aux.data;
        js.velocity[6] = 0.0;
        js.effort[6] = 0.0;

	pub_m22.publish(aux);
	js.name[7] = "m22";
        js.position[7] = aux.data;
        js.velocity[7] = 0.0;
        js.effort[7] = 0.0;

	pub_m23.publish(aux);
	js.name[8] = "m23";
        js.position[8] = aux.data;
        js.velocity[8] = 0.0;
        js.effort[8] = 0.0;

	pub_m24.publish(aux);
	js.name[9] = "m24";
        js.position[9] = aux.data;
        js.velocity[9] = 0.0;
        js.effort[9] = 0.0;

	pub_m25.publish(aux);
	js.name[10] = "m25";
        js.position[10] = aux.data;
        js.velocity[10] = 0.0;
        js.effort[10] = 0.0;

	pub_m26.publish(aux);
	js.name[11] = "m26";
        js.position[11] = aux.data;
        js.velocity[11] = 0.0;
        js.effort[11] = 0.0;

	pub_m31.publish(aux);
	js.name[12] = "m31";
        js.position[12] = aux.data;
        js.velocity[12] = 0.0;
        js.effort[12] = 0.0;
	
	pub_m51.publish(aux);
	js.name[18] = "m51";
        js.position[18] = aux.data;
        js.velocity[18] = 0.0;
        js.effort[18] = 0.0;

	pub_m61.publish(aux);
	js.name[19] = "m61";
        js.position[19] = aux.data;
        js.velocity[19] = 0.0;
        js.effort[19] = 0.0;

	pub_m41.publish(aux);
	js.name[15] = "m41";
        js.position[15] = aux.data;
        js.velocity[15] = 0.0;
        js.effort[15] = 0.0;
	
	pub_m62.publish(aux);
	js.name[20] = "m62";
        js.position[20] = aux.data;
        js.velocity[20] = 0.0;
        js.effort[20] = 0.0;

	aux.data = 30*3.14/180;	
	pub_m32.publish(aux);
	js.name[13] = "m32";
        js.position[13] = aux.data;
        js.velocity[13] = 0.0;
        js.effort[13] = 0.0;

	aux.data = -30*3.14/180;
	pub_m42.publish(aux);
	js.name[16] = "m42";
        js.position[16] = aux.data;
        js.velocity[16] = 0.0;
        js.effort[16] = 0.0;

	aux.data = 90*3.14/180;	   	        
	pub_m33.publish(aux);
	js.name[14] = "m33";
        js.position[14] = aux.data;
        js.velocity[14] = 0.0;
        js.effort[14] = 0.0;

	aux.data = -90*3.14/180;	           
	pub_m43.publish(aux);
	js.name[17] = "m43";
        js.position[17] = aux.data;
        js.velocity[17] = 0.0;
        js.effort[17] = 0.0;

	jointPub.publish(js);
}

/* ------------------------------------------------------------------*/ 
/* Csv Function */
/* ------------------------------------------------------------------*/ 
void Elvis::csv(const string& p){
	string StringValue_;
	const char *pp = p.c_str();
	ifstream file(pp);
	string line;
	getline(file,line); 
	/*Here is read the first line of the parameters file. 
	The first line of the file has the ID of the Motors*/
	while(getline(file,line) && ON && ros::ok())
	{
		Vector_Length_ ++;
		stringstream iss(line);
		getline(iss,StringValue_,','); winkelstruktur.m11 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m12 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m13 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m14 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m15 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m16 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m21 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m22 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m23 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m24 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m25 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m26 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m31 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m32 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m33 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m41 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m42 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m43 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m51 = string_to_double(StringValue_);
		getline(iss,StringValue_,','); winkelstruktur.m61 = string_to_double(StringValue_);
		getline(iss,StringValue_);     winkelstruktur.m62 = string_to_double(StringValue_);
	/* ---- Here is included the structure in a vector ----- */
	wv.push_back(winkelstruktur);
	/*-------------------------------------------------------*/
			
	}//while
	file.close();	
	
/* ------------------------------------------------------------------*/ 
}

/* ------------------------------------------------------------------*/ 
/* Move Elvis Function */
/* ------------------------------------------------------------------*/ 
void Elvis::moveElvis(int i){

	cout<<"VLength: "<<Vector_Length_<<endl;
		js.header.stamp = ros::Time::now();
		Elvis::moveMotors_neck_joint(wv[i-1].m61);
		Elvis::moveMotors_camera_joint(wv[i-1].m62);
		Elvis::moveMotors_left_shoulder_joint(wv[i-1].m31,wv[i-1].m32);
		Elvis::moveMotors_right_shoulder_joint(wv[i-1].m41,wv[i-1].m42);
		Elvis::moveMotors_right_hip_joint(wv[i-1].m22,wv[i-1].m23,wv[i-1].m21);
		Elvis::moveMotors_right_knee_joint(wv[i-1].m24);
		Elvis::moveMotors_right_ankle_joint(wv[i-1].m25,wv[i-1].m26, i);
		Elvis::moveMotors_left_hip_joint(wv[i-1].m12,wv[i-1].m13,wv[i-1].m11);
		Elvis::moveMotors_left_knee_joint(wv[i-1].m14);
		Elvis::moveMotors_left_ankle_joint(wv[i-1].m15,wv[i-1].m16, i);
		Elvis::moveMotors_left_elbow_joint(wv[i-1].m33);
		Elvis::moveMotors_right_elbow_joint(wv[i-1].m43);
		Elvis::moveMotors_trunk_joint(wv[i-1].m51);
		jointPub.publish(js);

		cout<<"Elvis::moveMotors_neck_joint(m61)................:";
		cout<<setw(8)<<wv[i-1].m61<<endl;
		cout<<"Elvis::moveMotors_camera_joint(m62)..............:";
		cout<<setw(8)<<wv[i-1].m62<<endl;
		cout<<"Elvis::moveMotors_left_shoulder_joint(m31, m32)..:";
		cout<<setw(8)<<wv[i-1].m31<<setw(8)<<wv[i-1].m32<<endl;
		cout<<"Elvis::moveMotors_right_shoulder_joint(m41, m42).:";
		cout<<setw(8)<<wv[i-1].m41<<setw(8)<<wv[i-1].m42<<endl;
		cout<<"Elvis::moveMotors_right_hip_joint(m22, m23, m21).:";
		cout<<setw(8)<<wv[i-1].m22<<setw(8)<<wv[i-1].m23<<setw(8)<<wv[i-1].m21<<endl;
		cout<<"Elvis::moveMotors_right_knee_joint(m24)..........:";
		cout<<setw(8)<<wv[i-1].m24<<endl;
		cout<<"Elvis::moveMotors_right_ankle_joint(m25, m26)....:";
		cout<<setw(8)<<wv[i-1].m25<<setw(8)<<wv[i-1].m26<<endl;
		cout<<"Elvis::moveMotors_left_hip_joint(m12, m13, m11)..:";
		cout<<setw(8)<<wv[i-1].m12<<setw(8)<<wv[i-1].m13<<setw(8)<<wv[i-1].m11<<endl;
		cout<<"Elvis::moveMotors_left_knee_joint(m14)...........:";
		cout<<setw(8)<<wv[i-1].m14<<endl;
		cout<<"Elvis::moveMotors_left_ankle_joint(m15, m16).....:";
		cout<<setw(8)<<wv[i-1].m15<<setw(8)<<wv[i-1].m16<<endl;
		cout<<"Elvis::moveMotors_left_elbow_joint(m33)..........:";
		cout<<setw(8)<<wv[i-1].m33<<endl;
		cout<<"Elvis::moveMotors_right_elbow_joint(m43).........:";
		cout<<setw(8)<<wv[i-1].m43<<endl;
		cout<<"Elvis::moveMotors_trunk_joint(m51)...............:";
		cout<<setw(8)<<wv[i-1].m51<<endl;
		cout<<endl;
		//Counter2_ ++;
		//printf("SchrittnummerIN #: %d \n",Counter2_);
		//cout<<endl;
}	

string getBinaryPath(int i) 
{
    string fullFileName = "";
    std::string path = "";
    pid_t pid = getpid();
    char buf[20] = {0};
    sprintf(buf,"%d",pid);
    std::string _link = "/proc/";
    _link.append( buf );
    _link.append( "/exe");
    char proc[512];
    int ch = readlink(_link.c_str(),proc,512);
    if (ch != -1) {
        proc[ch] = 0;
        path = proc;
        std::string::size_type t = path.find_last_of("/");
        path = path.substr(0,t);
    }
    switch (i)
    {
	case 1: fullFileName = path + string("/csv/winkeltabelle_verbessert.csv");
	break;
	case 2: fullFileName = path + string("/csv/winkel.csv");
	break;
	case 3: fullFileName = path + string("/csv/winkel_r.csv");
	break;
    }
    
    return fullFileName;
}

/* ------------------------------------------------------------------*/ 
/* Joystick Function */
/* ------------------------------------------------------------------*/ 
void Elvis::callRumblePad2Back(const sensor_msgs::Joy::ConstPtr& joy){
  if(joy->buttons[LB] && joy->buttons[RB]){
     cout << "SHUTTING DOWN!" << endl; 
     ON = 0; 
  }else{	

       // RT - Umschaltung Einzelschritt - Automatik
       // X  - Aufstehen
       // Y  - vorwärts laufen
       // B  - rückwärts laufen
       // A  - Stop



	if(joy->buttons[RT]){  // Umschaltung Einzelschritt - Automatik
		if(laufen == 0){laufen = 1; cout<<"laufen: "<<laufen<<endl;}
		else{laufen = 0; cout<<"laufen: "<<laufen<<endl;}

	}
	if(joy->buttons[RB]&&!(joy->buttons[LB])){ 
		fmode = 1; cout<<"[FMODE]: NORMAL ";
		if(iw<=Vector_Length_){
			if(iw == Vector_Length_){ iw = 1; }		
			iw++;
		}
		cout<<iw<<endl;
		
	}
	if(joy->buttons[LB]&&!(joy->buttons[RB])){ 
		rmode = 1; cout<<"[RMODE]: NORMAL ";
		if(iw<=Vector_Length_){
			if(iw == 1){ iw = Vector_Length_;}
			iw--;		
		}
		cout<<iw<<endl;
			
	}
	if(joy->buttons[X]){operation=1; cout<<"[OPERATION]: STAND UP"<<endl;
		Vector_Length_ = 0;
		Counter_ = 0;		
		Counter2_ = 0;
		Elvis::initElvis_stand_up();
		//string p1 = "/home/ihme/ws/src/elvis/csv/neu/winkeltabelle_verbessert_1.csv";
		//string p1 = "/home/ihme/ws/src/elvis/csv/winkeltabelle_verbessert.csv";
		//string p1 = "/home/ihme/ws/src/elvis/csv/neu/winkeltablle_ruckeln.csv";
		//string p1 = "/home/ihme/ws/src/elvis/csv/neu/winkelst2.csv";
		//string p1 = "/home/ihme/ws/src/elvis/csv/neu/winkeltabelle_verbessert_6.csv";
		string p1 = getBinaryPath(1);
		Elvis::csv(p1);
	}
	if(joy->buttons[Y]){operation=2; cout<<"[OPERATION]: FORWARD"<<endl; 
		Vector_Length_ = 0;
		Counter_ = 0;		
		Counter2_ = 0;
		Elvis::initElvis_move();
		//string p2 = "/home/ihme/ws/src/elvis/csv/winkel.csv";
		string p2 = getBinaryPath(2);		
		Elvis::csv(p2);
		
	}
	if(joy->buttons[B]){operation=3; cout<<"[OPERATION]: BACKWARD"<<endl;
		Vector_Length_ = 0;
		Counter_ = 0;		
		Counter2_ = 0;
		Elvis::initElvis_move();	
		//string p3 = "/home/ihme/ws/src/elvis/csv/winkel_r.csv";
		string p3 = getBinaryPath(3);	
		Elvis::csv(p3);
		
	}
	if(joy->buttons[A]){operation=0; cout<<"[OPERATION]: STOP"<<endl;
		Counter_ = 0;		
		Counter2_ = 0;
		Elvis::initElvis_move();
		wv.clear();
		Vector_Length_ = 0;	
		x_length = 0;
		iw = 1;
	}
	
	     if( mode == 1 ){//[mode 1][OPERATION] -- Translation
		pad.bdT.setX(joy->axes[LR_stick_left]*scaleFacTrans); //body translation X
		pad.bdT.setY(joy->axes[UD_stick_left]*scaleFacTrans); //body translation Y
		pad.bdT.setZ(joy->axes[UD_stick_right]*scaleFacTrans);//body translation Z
		pad.speed.setX(0);
		pad.speed.setY(0);
		pad.speed.setZ(0);
		pad.bdR.setX(0);
		pad.bdR.setY(0);
		pad.bdR.setZ(0);
	     }//IF (mode 1)
	     else if( mode == 2 ){//[mode 2][OPERATION] -- Rotation
		pad.bdR.setX(joy->axes[UD_stick_left]*scaleFacRot);  //body rotation X
		pad.bdR.setY(joy->axes[LR_stick_left]*scaleFacRot);  //body rotation Y
		pad.bdR.setZ(joy->axes[LR_stick_right]*scaleFacRot); //body rotation Z
		pad.speed.setX(0);
		pad.speed.setY(0);
		pad.speed.setZ(0);
		pad.bdT.setX(0);
		pad.bdT.setY(0);
		pad.bdT.setZ(0);
	     }//ELSEIF (mode 2)
	     else{//[mode 0][OPERATION] -- Normal	
		pad.bdT.setX(0);
		pad.bdT.setY(0);
		pad.bdT.setZ(0);
		pad.bdR.setX(0);
		pad.bdR.setY(0);
		pad.bdR.setZ(0);
		if((joy->axes[LR_stick_left]>0.3)||(joy->axes[LR_stick_left]<-0.3)){   // sideward movement
		   pad.speed.setX(-(joy->axes[LR_stick_left])/abs(joy->axes[LR_stick_left]));
		}else{ pad.speed.setX(0);}
		if((joy->axes[UD_stick_left]>0.3)||(joy->axes[UD_stick_left]<-0.3)){   // forward/backward movement
		  pad.speed.setY(joy->axes[UD_stick_left]/abs(joy->axes[UD_stick_left]));
		}else{ pad.speed.setY(0);}
		if((joy->axes[LR_stick_right]>0.3)||(joy->axes[LR_stick_right]<-0.3)){ // rotational movement
		       pad.speed.setZ((joy->axes[LR_stick_right]/abs(joy->axes[LR_stick_right])));
		}else{ pad.speed.setZ(0);}
     	   }//ELSE (mode 0)	
  }//ELSE (shutting down)
//test
}

