#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

#include "ModuleControl.hpp"

#define SENSORS_I2C_ADDR 0x10
#define PDA50_I2C_ADDR 0x0C
#define TEMP_NCT_I2C_ADDR 0x4C
#define TEMP_TMP_I2C_ADDR 0x4E
#define EEPROM_I2C_ADDR 0x50
#define REG_FB_STATE 0x53
#define REG_LINE_LENGTH 0x06
#define REG_TINT_LL 0x0B
#define REG_TINT_CK 0x0C
#define REG_ANA_GAIN 0x0D
#define REG_DIG_GAIN 0x0E


#define E2V_NODE_PATH       "/sys/devices/platform/soc/ac50000.qcom,cci/ac50000.qcom,cci:qcom,cam-sensor3/e2v_node"
#define E2VTOPAZ_READ_MODE 0
#define E2VTOPAZ_WRITE_MODE 1

/************************************************
 *Main fuction
 ************************************************/

ModuleCtrl::~ModuleCtrl()
{
#ifndef DEBUG_MODE
	ModuleControlClose(); // close IC2
#endif
}

/************************************************
 *Init I2C bus
 ************************************************/
void ModuleCtrl::ModuleControlInit()
{

	/* Open device node */
	fd = open(E2V_NODE_PATH, O_RDWR);
	
	if(fd < 0)
	{
		fprintf(stderr, "E2V_NODE_PATH open error\n");
	}
	printf("open E2V_NODE_PATH\n");

}

/************************************************
 *Close I2C bus
 ************************************************/
void ModuleCtrl::ModuleControlClose()
{

	/* Close device node */
	close(fd);

	printf("close E2V_NODE_PATH\n");

}


int ModuleCtrl::hexStrToInt(char* hex_str)
{
	return strtoul(hex_str, NULL, 16);
}

int ModuleCtrl::getReadValue(char* read_str)
{
	char value_str[5];
	int value;
//	printf(read_str);
	
//	printf(value_str);
	value=this->hexStrToInt(value_str);
	return value;
}

/************************************************
 *Read register
 ************************************************/
int ModuleCtrl::readReg(int regAddr, int *value)
{

	char buf[50] = {0};
	char read_buf[50] = {0};
	int ret;
	int error=0;
	
	sprintf(buf, "%d 0x%02hx", E2VTOPAZ_READ_MODE, regAddr);
    
	ret = write(fd, buf, strlen(buf)+1);
	printf("return write: %d\n", ret);

	ret = lseek(fd, 0, SEEK_SET);
	printf("return lseek: %d\n", ret);
	//write() change the fd pos, need use lseek to make pos point to the start of the file

	ret = read(fd, read_buf, sizeof(read_buf));
	printf("return read: %d, buf: %s\n", ret, read_buf);

	*value=1; //to be developped

	return error;
}

/************************************************
 *Write register
 ************************************************/
int ModuleCtrl::writeReg(int regAddr, int value)
{

	int ret;
	char buf[30] = {0};
	int error=0;
	
	printf("reg_addr: 0x%x, reg_data: 0x%x\n", regAddr, value);

	sprintf(buf, "%d 0x%02hx 0x%04hx", E2VTOPAZ_WRITE_MODE, regAddr, value);
	printf("buf val: %s\n", buf);

	ret = write(fd, buf, strlen(buf)+1);
	printf("return write: %d\n", ret);
	
	return error;
}

/************************************************
 *Get the sensor state
 ************************************************/
int ModuleCtrl::read_sensor_state(int *state)
{
	int regAddr;
	int value=0;
	int error=0;

	regAddr = REG_FB_STATE;

	error=this->readReg(regAddr, &value);
	*state=value;

	return error;
}

/************************************************
 *Set the integration time
 ************************************************/
int ModuleCtrl::setTint(float tint)
{
	int regAddr, tline;
	struct solution init;
	int error=0;

	tint = tint * 1000000; // convert to nanoseconds
	tint = tint / 20; // convert to clock cycle 50MHz

	// read the line length
	regAddr = REG_LINE_LENGTH;
	error=this->readReg(regAddr, &tline);
	
	if (error != 0)
	{
		fprintf(stderr, "READ ERROR: 0x%x\n", regAddr);
		error=-1;
		return error;
	}
	
	init.tintLL = (int)tint / tline;
	init.tintCK = (int)(tint - init.tintLL * tline);

	// write in reg_tint_ll
	regAddr = REG_TINT_LL;
	error=this->writeReg(regAddr, init.tintLL);
	if (error != 0)
	{
		fprintf(stderr, "WRITE ERROR: 0x%x\n", regAddr);
		error=-2;
		return error;
	}

	// write in reg_tint_ck
	regAddr = REG_TINT_CK;
	error=this->writeReg(regAddr, init.tintCK);
	if (error != 0)
	{
		fprintf(stderr, "WRITE ERROR: 0x%x\n", regAddr);
		error=-3;
		return error;
	}

	return error;
}

/************************************************
 *Set the analog gain
 ************************************************/
int ModuleCtrl::setAnalogGain(float again)
{
	int regAddr, value;
	int error=0;

	value = (int)(again * 100);

	switch (value)
	{
	case 100:
		value = 0;
		break;
	case 120:
		value = 1;
		break;
	case 145:
		value = 2;
		break;
	case 150:
		value = 2;
		break;
	case 171:
		value = 3;
		break;
	case 200:
		value = 4;
		break;
	case 240:
		value = 5;
		break;
	case 300:
		value = 6;
		break;
	case 343:
		value = 7;
		break;
	case 400:
		value = 8;
		break;
	case 480:
		value = 9;
		break;
	case 500:
		value = 9;
		break;
	case 600:
		value = 10;
		break;
	case 686:
		value = 11;
		break;
	case 700:
		value = 11;
		break;
	case 800:
		value = 12;
		break;
	case 900:
		value = 13;
		break;
	case 960:
		value = 13;
		break;
	case 1000:
		value = 13;
		break;
	case 1200:
		value = 14;
		break;
	case 1600:
		value = 15;
		break;
	default:
		printf("Forbidden value, couldn't set analog gain\n");
		return 0;
	}

	// write in register
	regAddr = REG_ANA_GAIN;
	error=this->writeReg(regAddr, value);
	if (error != 0)
	{
		fprintf(stderr, "WRITE ERROR: 0x%x\n", regAddr);
		error=-1;
		return error;
	}

	return 0;
}

/************************************************
 *Set the digital gain
 ************************************************/
int ModuleCtrl::setDigitalGain(float dgain)
{
	int regAddr, value;
	int error=0;
	regAddr = REG_DIG_GAIN;

	//from x0.004 to x16 (decimal ex: x1=256, x1.5=384...)
	value = (int)(dgain * 256);

	if (value > 4095)
	{
		value = 4095;
	}
	
	if (value < 1)
	{
		value = 1;
	}

	// write in register
	regAddr = REG_DIG_GAIN;
	error=this->writeReg(regAddr, value);
	if (error != 0)
	{
		fprintf(stderr, "WRITE ERROR: 0x%x\n", regAddr);
		error=-1;
		return error;
	}
		
	return error;
}

/************************************************
 *Set the global gain
 ************************************************/
int ModuleCtrl::setGain(float gain)
{
	float again, dgain;
	int againVal, dgainVal, regAddr, value;
	int error=0;

	regAddr = REG_DIG_GAIN;

	
	//RANGE: x0.004 to x256 (decimal ex: x1=256, x1.5=384...)

	//again = (int)(gain * 100);

	if(gain < 1.2) 
	{
		again=1;	
		againVal = 0; //x1
	}
	else if(gain < 1.45) 
	{
		again=1.2;
		againVal = 1; //x1.2
	}
	else if(gain < 1.71) 
	{
		again=1.45;
		againVal = 2; //x1.45
	}
	else if(gain < 2.00) 
	{
		again=1.71;
		againVal = 3; //x1.71
	}
	else if(gain < 2.40) 
	{
		again=2;
		againVal = 4; //x2.0	
	}
	else if(gain < 3.00) 
	{
		again=2.4;
		againVal = 5; //x2.4
	}
	else if(gain < 3.43) 
	{
		again=3.0;
		againVal = 6; //x3.0	
	}
	else if(gain < 4.00) 
	{
		again=3.43;
		againVal = 7; //x3.43
	}
	else if(gain < 4.80)  
	{
		again=4.0;
		againVal = 8; //x4.0	
	}
	else if(gain < 6.00)  
	{
		again=4.80;
		againVal = 9; //x4.8	
	}
	else if(gain < 6.86)  
	{
		again=6.0;
		againVal = 10; //x6.0	
	}
	else if(gain < 8.00)  
	{
		again=6.86;
		againVal = 11; //x6.86
	}
	else if(gain < 9.60)  
	{
		again=8.0;
		againVal = 12; //x8	
	}
	else if(gain < 12.00)  
	{
		again=9.60;
		againVal = 13; //x9.6	
	}
	else if(gain < 16.00)  
	{
		again=12.0;
		againVal = 14; //x12	
	}
	else
	{
		again=16.0;
		againVal = 15; //x16	
	}
		
	//from x0.004 to x16 (decimal ex: x1=256, x1.5=384...)
	dgain=gain/again;
	dgainVal = (int)(dgain * 256);

	if (dgainVal > 4095)
	{
		dgainVal = 4095;
	}
	
	if (dgainVal < 1)
	{
		dgainVal = 1;
	}

	printf("GAIN: %4.2lf => AGAIN:  %4.2lf (%d) / DGAIN: %4.2lf (%d)\n",gain, again, againVal, dgain, dgainVal);

	// write in register
	regAddr = REG_ANA_GAIN;
	error=this->writeReg(regAddr, againVal);
	if (error != 0)
	{
		fprintf(stderr, "WRITE ERROR: 0x%x\n", regAddr);
		error=-1;
		return error;
	}
	
	// write in register
	regAddr = REG_DIG_GAIN;
	error=this->writeReg(regAddr, dgainVal);
	if (error != 0)
	{
		fprintf(stderr, "WRITE ERROR: 0x%x\n", regAddr);
		error=-2;
		return error;
	}
		
	return error;
}
