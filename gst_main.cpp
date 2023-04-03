#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fstream>

void printHelp();

/************************************************
*Main fuction
************************************************/

int main(){

	int isRunning = 1;
	char input;
	int err =0;
	printHelp();


	while (isRunning){
		printf(">");
		scanf(" %c",&input);
		switch (input)
		{
			//General functions
			case 'h': //print help
				printHelp();
				break;
			case 'q': //quit menu
				isRunning=0;
				break;
			case 'c': //clear terminal
				system("clear");
				break;
			//Application specific
			case '1': //Simple video stream
				system("echo PRESS 'CTRL+C' TO STOP THE STREAM");
				system("v4l2-ctl -d /dev/video0 --set-fmt-video=width=1920,height=1080,pixelformat='GREY' --set-ctrl sensor_mode=2");
				system("gst-launch-1.0 v4l2src ! queue ! videoconvert ! queue ! xvimagesink sync=false");
				printHelp();
				break;
			case '2': //Autofocus: manual control
				system("echo PRESS 'A' TO START AUTOFOCUS");
				system("echo PRESS 'CTRL+C' TO STOP THE STREAM");
				system("echo Focus calculated within an ROI: 200x100");
				system("v4l2-ctl -d /dev/video0 --set-fmt-video=width=1920,height=1080,pixelformat='GREY' --set-ctrl sensor_mode=2");
				system("gst-launch-1.0 v4l2src ! autofocus step_small=5 offset=2 continuous=false continuous_update_interval=5 x=860 y=440 width=200 height=100 ! queue ! videoconvert ! queue ! xvimagesink sync=false");
				printHelp();
 				break;
			case '3': //Autofocus: manual control + Bacode decoding
				system("echo PRESS 'A' TO START AUTOFOCUS");
				system("echo PRESS 'CTRL+C' TO STOP THE STREAM");
				system("echo Focus calculated within an ROI: 200x100");
				system("echo Number of decoded barcode per image: 1");
				system("v4l2-ctl -d /dev/video0 --set-fmt-video=width=1920,height=1080,pixelformat='GREY' --set-ctrl sensor_mode=2");
				system("gst-launch-1.0 v4l2src ! autofocus step_small=5 offset=2 continuous=false continuous_update_interval=5 x=860 y=440 width=200 height=100 ! barcodereader framing=false  type=all ! queue ! videoconvert ! queue ! xvimagesink sync=false");
				printHelp();
 				break;
			case '4': //Autofocus: continuous
				system("echo PRESS 'A' TO START AUTOFOCUS");
				system("echo PRESS 'CTRL+C' TO STOP THE STREAM");
				system("echo Focus calculated within an ROI: 200x100");
				system("v4l2-ctl -d /dev/video0 --set-fmt-video=width=1920,height=1080,pixelformat='GREY' --set-ctrl sensor_mode=2");
				system("gst-launch-1.0 v4l2src ! autofocus step_small=5 offset=2 continuous=true continuous_update_interval=5 x=860 y=440 width=200 height=100 ! queue ! videoconvert ! queue ! xvimagesink sync=false");
				printHelp();
 				break;
			case '5': //Autofocus: continuous + Bacode decoding
				system("echo PRESS 'A' TO START AUTOFOCUS");
				system("echo PRESS 'CTRL+C' TO STOP THE STREAM");
				system("echo Focus calculated within an ROI: 200x100");
				system("echo Number of decoded barcode per image: 1");
				system("v4l2-ctl -d /dev/video0 --set-fmt-video=width=1920,height=1080,pixelformat='GREY' --set-ctrl sensor_mode=2");
				system("gst-launch-1.0 v4l2src ! autofocus step_small=5 offset=2 continuous=true continuous_update_interval=5 x=860 y=440 width=200 height=100 ! barcodereader framing=false  type=all ! queue ! videoconvert ! queue ! xvimagesink sync=false");
				printHelp();
 				break;
			case '6': //Fixed-focus module: Bacode decoding
				system("echo PRESS 'CTRL+C' TO STOP THE STREAM");
				system("echo Number of decoded barcode per image: 5");
				system("v4l2-ctl -d /dev/video0 --set-fmt-video=width=1920,height=1080,pixelformat='GREY' --set-ctrl sensor_mode=2");
				system("gst-launch-1.0 v4l2src ! barcodereader framing=false  type=all number-barcode=5 ! queue ! videoconvert ! queue ! xvimagesink sync=false");
				printHelp();
 				break;
			default:
				printf("Wrong input!\n\n");
				printHelp();
		}
		if (err != 0) isRunning = 0;
	}

	return 0;
}

/************************************************
*Print help
************************************************/
void printHelp(){
	system("clear");
	printf("\nTELEDYNE-E2V OPTIMOM 2M Module running with Nvidia Jetson Nano\n");
	printf("\nGSTREAMER CONTROL\n");
	printf("Tools menu:\n");
	printf("\t1:\tSimple video stream\n");
	printf("\t2:\tAutofocus manual control\n");
	printf("\t3:\tAutofocus manual control + Barcode decoding\n");
	printf("\t4:\tAutofocus continuous mode\n");
	printf("\t5:\tAutofocus continuous mode + Barcode decoding\n");
	printf("\t6:\tFixed-focus module: Barcode decoding\n");
	printf("\tc:\tclear window\n");
	printf("\th:\tprint this help\n");
	printf("\tq:\tquit\n");
}

