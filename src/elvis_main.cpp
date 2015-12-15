#include<ros/ros.h>
#include<std_msgs/Float64.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<fstream>
#include<elvis/elvis_init.h>

/* ------------------------------------------------------------------*/ 
/* Main Program */
/* ------------------------------------------------------------------*/ 
//---------------------------------MAIN-----------------------------------//
int main(int argc, char** argv){

	ros::init(argc, argv, "elvis_main");
	Elvis elvis1;
	ros::Rate loop_rate(4.5);

	//WHILE-LOOP
	while(ros::ok() && ON){	
		//std::cout<<"Bin in der While"<<endl;
		if(operation == 1 || operation == 2 || operation == 3){
			if(laufen) {iw=1;}
			while((iw<=Vector_Length_) && (ON) && operation != 0 && ros::ok()){
				elvis1.moveElvis(iw); 
				ros::spinOnce();
				loop_rate.sleep();
				if((operation == 1) && (Vector_Length_ == iw)){operation=0;}
				if(laufen) {iw++;}
			}
			//Counter2_ = 0;	
			//Counter_ ++;
			//printf("SchrittnummerOUT #: %d \n",Counter_);
		}
		ros::spinOnce();
		loop_rate.sleep();
	}//END WHILE
}	
//-----------------------------END Main---------------------------------//

