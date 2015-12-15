#include<ros/ros.h>
#include<std_msgs/Float64.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<fstream>

using namespace std;
typedef struct 
{
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

class Dynamixel{
	private:
		ros::NodeHandle n;
		ros::Publisher pub_m11;
		ros::Publisher pub_m12;
		ros::Publisher pub_m13;
		ros::Publisher pub_m14;
		ros::Publisher pub_m15;
		ros::Publisher pub_m16;
		ros::Publisher pub_m21;
		ros::Publisher pub_m22;
		ros::Publisher pub_m23;
		ros::Publisher pub_m24;
		ros::Publisher pub_m25;
		ros::Publisher pub_m26;
		ros::Publisher pub_m31;
		ros::Publisher pub_m32;
		ros::Publisher pub_m33;
		ros::Publisher pub_m41;
		ros::Publisher pub_m42;
		ros::Publisher pub_m43;
		ros::Publisher pub_m51;	
		ros::Publisher pub_m61;
		ros::Publisher pub_m62;
		
	public:
		Dynamixel();
		double string_to_double (const std::string& s);
		int init_Stand_Motors();
		int moveMotors_neck_joint(double z);
		int moveMotors_left_shoulder_joint(double x, double y);
		int moveMotors_left_elbow_joint(double x);
		int moveMotors_right_shoulder_joint(double x, double y);
		int moveMotors_right_elbow_joint(double x);
		int moveMotors_right_hip_joint(double x, double y, double z);
		int moveMotors_right_knee_joint(double x);
		int moveMotors_right_ankle_joint(double x, double y);	
		int moveMotors_left_hip_joint(double x, double y, double z);
		int moveMotors_left_knee_joint(double x);
		int moveMotors_left_ankle_joint(double x, double y);	
		int moveMotors_camera_joint(double z);
		int moveMotors_trunk_joint(double x);

};


Dynamixel::Dynamixel(){
	pub_m11 = n.advertise<std_msgs::Float64>("/controller_m11/command",1);
	pub_m12 = n.advertise<std_msgs::Float64>("/controller_m12/command",1);
	pub_m13 = n.advertise<std_msgs::Float64>("/controller_m13/command",1);
	pub_m14 = n.advertise<std_msgs::Float64>("/controller_m14/command",1);
	pub_m15 = n.advertise<std_msgs::Float64>("/controller_m15/command",1);
	pub_m16 = n.advertise<std_msgs::Float64>("/controller_m16/command",1);
	pub_m21 = n.advertise<std_msgs::Float64>("/controller_m21/command",1);
	pub_m22 = n.advertise<std_msgs::Float64>("/controller_m22/command",1);
	pub_m23 = n.advertise<std_msgs::Float64>("/controller_m23/command",1);
	pub_m24 = n.advertise<std_msgs::Float64>("/controller_m24/command",1);
        pub_m25 = n.advertise<std_msgs::Float64>("/controller_m25/command",1);
	pub_m26 = n.advertise<std_msgs::Float64>("/controller_m26/command",1);
	pub_m31 = n.advertise<std_msgs::Float64>("/controller_m31/command",1);
	pub_m32 = n.advertise<std_msgs::Float64>("/controller_m32/command",1);
	pub_m33 = n.advertise<std_msgs::Float64>("/controller_m33/command",1);
	pub_m41 = n.advertise<std_msgs::Float64>("/controller_m41/command",1);
	pub_m42 = n.advertise<std_msgs::Float64>("/controller_m42/command",1);
	pub_m43 = n.advertise<std_msgs::Float64>("/controller_m43/command",1);
	pub_m51 = n.advertise<std_msgs::Float64>("/controller_m51/command",1);
	pub_m61 = n.advertise<std_msgs::Float64>("/controller_m61/command",1);
	pub_m62 = n.advertise<std_msgs::Float64>("/controller_m62/command",1);
}
/* ------------------------------------------------------------------*/ 
// String to Double Function
/* ------------------------------------------------------------------*/ 

double string_to_double (const std::string& s)
{
	std::istringstream i(s);
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

int Dynamixel::moveMotors_neck_joint(double z)
{
	std_msgs::Float64 aux;
	aux.data = z*3.14/180;
	pub_m61.publish(aux); 
	return 1;
}
/* ------------------------------------------------------------------*/ 
// Camera Head Movement (Up-Down)
/* ------------------------------------------------------------------*/ 
int Dynamixel::moveMotors_camera_joint(double z)
{
	std_msgs::Float64 aux;
	aux.data = z*3.14/180;
	pub_m62.publish(aux); 
	return 1;
}
/* ------------------------------------------------------------------*/ 
// Trunk
/* ------------------------------------------------------------------*/ 
int Dynamixel::moveMotors_trunk_joint(double x)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m51.publish(aux); 
	return 1;
}

/* ------------------------------------------------------------------*/ 
// Joint Functions for the Arms 
/* ------------------------------------------------------------------*/ 
// Left Arm 
/* ------------------------------------------------------------------*/ 
// Left Shoulder Joint
int Dynamixel::moveMotors_left_shoulder_joint(double x, double y)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m31.publish(aux);
	aux.data = y*3.14/180;
	pub_m32.publish(aux);
	return 1;
}

// Left Elbow Joint
int Dynamixel::moveMotors_left_elbow_joint(double x)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m33.publish(aux); 
	return 1;
}
/* ------------------------------------------------------------------*/ 
// Right Arm 
/* ------------------------------------------------------------------*/ 
// Right Shoulder Joint
int Dynamixel::moveMotors_right_shoulder_joint(double x, double y)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m41.publish(aux);
	aux.data = y*3.14/180;
	pub_m42.publish(aux);
	return 1;
}

// Right Elbow Joint
int Dynamixel::moveMotors_right_elbow_joint(double x)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m43.publish(aux); 
	return 1;
}

/* ------------------------------------------------------------------*/ 
// Joint Functions for the Legs 
/* ------------------------------------------------------------------*/ 
// Left Leg 
/* ------------------------------------------------------------------*/ 
// Left Hip Joint
int Dynamixel::moveMotors_left_hip_joint(double x, double y, double z)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m12.publish(aux);
	aux.data = y*3.14/180;
	pub_m13.publish(aux);
	aux.data = z*3.14/180;
	pub_m11.publish(aux);
	return 1;
}
// Left Knee Joint
int Dynamixel::moveMotors_left_knee_joint(double x)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m14.publish(aux); 
	return 1;
}
// Left Ankle Joint
int Dynamixel::moveMotors_left_ankle_joint(double x, double y)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m15.publish(aux);
	aux.data = y*3.14/180;
	pub_m16.publish(aux);
	return 1;
}
/* ------------------------------------------------------------------*/ 
// Right Leg 
/* ------------------------------------------------------------------*/ 
// Right Hip Joint
int Dynamixel::moveMotors_right_hip_joint(double x, double y, double z)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m22.publish(aux);
	aux.data = y*3.14/180;
	pub_m23.publish(aux);
	aux.data = z*3.14/180;
	pub_m21.publish(aux);
	return 1;
}
// Right Knee Joint
int Dynamixel::moveMotors_right_knee_joint(double x)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m24.publish(aux);
	return 1;
}
// Right Ankle Joint
int Dynamixel::moveMotors_right_ankle_joint(double x, double y)
{
	std_msgs::Float64 aux;
	aux.data = x*3.14/180;
	pub_m25.publish(aux);
	aux.data = y*3.14/180;
	pub_m26.publish(aux);
	return 1;
}
/* ------------------------------------------------------------------*/
int Dynamixel::init_Stand_Motors()
{ 
        std_msgs::Float64 aux;
	aux.data = 0;
        pub_m11.publish(aux);
        pub_m12.publish(aux);
        pub_m13.publish(aux);
        pub_m14.publish(aux);
        pub_m15.publish(aux);
        pub_m16.publish(aux);
        pub_m21.publish(aux);
        pub_m22.publish(aux);
        pub_m23.publish(aux);
        pub_m24.publish(aux);
        pub_m25.publish(aux);
        pub_m26.publish(aux);
        pub_m31.publish(aux);
        pub_m32.publish(aux);
        pub_m33.publish(aux);
        pub_m41.publish(aux);
        pub_m42.publish(aux);
        pub_m43.publish(aux);
        pub_m51.publish(aux);
        pub_m61.publish(aux);
return 1;
}

/* ------------------------------------------------------------------*/ 
/* Main Program */
/* ------------------------------------------------------------------*/ 

int main(int argc,char** argv)
{
	ros::init(argc, argv, "move_motor_node");
	Dynamixel motors;
	string StringValue_;
	int Counter_ = 0;
	int Vector_Length_ = 0;
	int Schritte_ = 0;
	
/* ------------------------------------------------------------------*/ 
	/* Here is read the angles parameters from a .csv file,
	then the info is located in a structure and the structrure 
	is located in a Vector. */

	structmotoren winkelstruktur;
	/* Here is defined the structures in a vector, each line is
	   a structure and each structure a position in a vector */	
	vector<structmotoren> wv; /* wv = winkelvektoren */
	/*-------------------------------------------------------*/
	ros::Rate loop_rate(0.5);

			//motors.init_Stand_Motors();
			//loop_rate.sleep();
			
			//motors.init_Stand_Motors();
			//loop_rate.sleep();
	
	std::ifstream file("/home/cjimenez/catkin_ws/src/node_motor/bin/winkel.csv");
	std::string line;

	getline(file,line); 
	/*Here is read the first line of the parameters file. 
	The first line of the file has the ID of the Motors*/
	while(getline(file,line))
	{
				
		Vector_Length_ ++;
		
		std::stringstream iss(line);
		std::getline(iss,StringValue_,',');
		winkelstruktur.m11 = string_to_double(StringValue_);
		
		std::getline(iss,StringValue_,',');
		winkelstruktur.m12 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m13 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m14 = string_to_double(StringValue_);
		
		std::getline(iss,StringValue_,',');
		winkelstruktur.m15 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m16 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m21 = string_to_double(StringValue_);
		
		std::getline(iss,StringValue_,',');
		winkelstruktur.m22 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m23 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m24 = string_to_double(StringValue_);
		
		std::getline(iss,StringValue_,',');
		winkelstruktur.m25 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m26 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m31 = string_to_double(StringValue_);
		
		std::getline(iss,StringValue_,',');
		winkelstruktur.m32 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m33 = string_to_double(StringValue_);
		
		std::getline(iss,StringValue_,',');
		winkelstruktur.m41 = string_to_double(StringValue_);
		
		std::getline(iss,StringValue_,',');
		winkelstruktur.m42 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m43 = string_to_double(StringValue_);

		std::getline(iss,StringValue_,',');
		winkelstruktur.m51 = string_to_double(StringValue_);
		
		std::getline(iss,StringValue_,',');
		winkelstruktur.m61 = string_to_double(StringValue_);

		std::getline(iss,StringValue_);
		winkelstruktur.m62 = string_to_double(StringValue_);
	
	/* ---- Here is included the structure in a vector ----- */
	wv.push_back(winkelstruktur);
	/*-------------------------------------------------------*/
			
	}
	file.close();	
	cout<<"Anzahl von Bewegungen per Schritt: "<<Vector_Length_<<endl;
/* ------------------------------------------------------------------*/ 
	cout<<"Wie viele Schritte? ";
	cin >> Schritte_;

			motors.init_Stand_Motors();
			loop_rate.sleep();
			
			motors.init_Stand_Motors();
			loop_rate.sleep();
	
	while(ros::ok() && Counter_ < Schritte_)
	{	
		int i =0;			
		for (i=1;i<=Vector_Length_;i++) {
		motors.moveMotors_neck_joint(wv[i-1].m61);
		motors.moveMotors_left_shoulder_joint(wv[i-1].m31,wv[i-1].m32);
		motors.moveMotors_right_shoulder_joint(wv[i-1].m41,wv[i-1].m42);
		motors.moveMotors_right_hip_joint(wv[i-1].m22,wv[i-1].m23,wv[i-1].m21);
		motors.moveMotors_right_knee_joint(wv[i-1].m24);
		motors.moveMotors_right_ankle_joint(wv[i-1].m25,wv[i-1].m26);
		motors.moveMotors_left_hip_joint(wv[i-1].m12,wv[i-1].m13,wv[i-1].m11);
		motors.moveMotors_left_knee_joint(wv[i-1].m14);
		motors.moveMotors_left_ankle_joint(wv[i-1].m15,wv[i-1].m16);
		motors.moveMotors_left_elbow_joint(wv[i-1].m33);
		motors.moveMotors_right_elbow_joint(wv[i-1].m43);
		motors.moveMotors_trunk_joint(wv[i-1].m51);
		loop_rate.sleep();	
		}	

	Counter_ ++;
	printf("Schrittnummer #: %d \n",Counter_);
			
		
	}
}	
