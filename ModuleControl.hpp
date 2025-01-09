#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>


class ModuleCtrl
{
private:
    /**
     * @brief 
     * Device node
     * 
     */
    int fd;

public:
    /**
     * @brief 
     * Initialise IC2 connection
     */
    void ModuleControlInit();

    ~ModuleCtrl();

    /**
     * @brief 
     * Close IC2 connection
     * 
     */
    void ModuleControlClose();

    /**
     * @brief write specified value in the specified register
     * 
     * @param register address 
     * @param value to write
     * @return int 
     */
    int writeReg(int regAddr, int value);

    /**
     * @brief 
     * Read specified register
     * 
     * @param register address 
     * @param pointer to store the read value
     * @return int 
     */
    int readReg(int regAddr, int *value);


    /**
     * @brief Read the state of the sensor
     * 
     * @return int The sensor state value
     */
    int read_sensor_state(int *state);

    /**
     * @brief Set the exposition time
     * 
     * @param tint in milisecond 
     * @return int 
     */
    int setTint(float tint);

    /**
     * @brief Set the Analog Gain
     * 
     * @param again 
     * @return int 
     */
    int setAnalogGain(float again);

    /**
     * @brief Set the Digital Gain
     * 
     * @param dgain 
     * @return int 
     */
    int setDigitalGain(float dgain);
    
     /**
     * @brief Set the Gain
     * 
     * @param gain 
     * @return int 
     */   
    int setGain(float gain);
    
    /**
     * @brief Set the period time for frame rate control
     * 
     * @param tperiod in milisecond 
     * @return int 
     */
    int setFramePeriod(float tperiod);
    
};

struct solution
{
    int tintLL;
    int tintCK;
};
