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
				system("gst-launch-1.0 qtiqmmfsrc camera=0 exposure-mode=0 manual-exposure-time=10000000 ! video\/x-raw\\(memory:GBM\\), format=NV12,width=1920,height=1080, framerate=60\/1 ! waylandsink fullscreen=false async=true sync=false");
				printHelp();
				break;
			case '2': //Simple video stream in Full screen
				system("WARNING: switch off the board to stop the stream");
				system("sleep 5");
				system("gst-launch-1.0 qtiqmmfsrc camera=0 exposure-mode=0 manual-exposure-time=10000000 ! video\/x-raw\\(memory:GBM\\), format=NV12,width=1920,height=1080, framerate=60\/1 ! waylandsink fullscreen=true async=true sync=false");
				printHelp();
 				break;
			case '3': //Save RAW images
				system("echo Save 3x consecutive RAW images here: /data/misc/camera/");
				system("echo PRESS 'CTRL+C' TO STOP THE STREAM");
				system("gst-launch-1.0 -e qtiqmmfsrc camera=0 ! video\/x-bayer,format=\\(string\\)mono,bpp=\\(string\\)10,width=1920,height=1080,framerate=60\/1 ! queue ! multifilesink location=\/data\/misc\/camera\/frame%d.raw sync=true async=false max-files=3");
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
	printf("\nTELEDYNE-E2V OPTIMOM Module running with Qualcomm RB5\n");
	printf("\nGSTREAMER CONTROL\n");
	printf("Tools menu:\n");
	printf("\t1:\tSimple video stream\n");
	printf("\t2:\tSimple video stream in full screen (Need to power OFF the board to stop it)\n");
	printf("\t3:\tSave RAW images\n");
	printf("\tc:\tclear window\n");
	printf("\th:\tprint this help\n");
	printf("\tq:\tquit\n");
}

