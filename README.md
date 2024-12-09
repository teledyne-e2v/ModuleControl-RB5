# ModuleControl
Simple code to start controlling OPTIMOM module on Qualcomm RB5 platform


# Release Notes


# Compilation
On host PC:
```
	sudo apt update
	sudo apt install -y g++-aarch64-linux-gnu
	sudo apt install make
	sudo apt install adb	
```
to launch the compilation:
```
	make
```

then push the result to the RB5 using `adb' commands
```
	adb root
	adb remount
	adb push gstCommands /home/.
	adb push ModuleControl /home/.
```


# Application manual
Open the two applications in separated terminals:


## terminal 1: start GSTREAMER video stream (required to control the device)

	./gstCommands

## terminal 2: control module I2C bus

	./ModuleControl

**IMPORTANT RULES:**
- it is required to have the two applications started at the same time
- the video stream must be started BEFORE controlling image sensor through I2C bus


