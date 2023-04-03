# module_control
Simple code to start controlling OPTIMOM module and play with some Gstreamer plugins


# Release Notes
2.3: fixed-focus compatibility + temperature sensor
2.2: add multifocus
2.1: correct some gst commands

# Installation
IMPORTANT: make sure the time clock and date are correct in the Jetson before any compilation

	sudo apt update
	sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev

Recompile the sources:

	make

Install the following Gstreamer plugins following the associated instructions:
- gst-autofocus
- gst-bacode-reader

in order to have acces to the plugins when terminal is opened, add the following lines at the end of the file: ```~/.bashrc```

	export GST_PLUGIN_PATH=/usr/local/lib/gstreamer-1.0/
	export LD_LIBRARY_PATH=/usr/local/lib/

After resrting the terminal, test the plugin installation with:

	gst-inspect-1.0 autofocus
	gst-inspect-1.0 barcodereader

# Application manual
Open the two applications in separated terminals:

## terminal 1: control module I2C bus

	./ModuleControl

## terminal 2: control GSTREAMER vieo stream I2C bus

	./gstCommands

**IMPORTANT RULES:**
- it is required to have the two applications started at the same time
- the video stream must be started BEFORE controlling module I2C bus


## Additionnal tips:
Shortcut can also be added in the desktop:
- start_gstCommands.desktop
- start_ModuleControl.desktop

VNC remote control can be put in place with: https://developer.nvidia.com/embedded/learn/tutorials/vnc-setup

	cd /usr/lib/systemd/user/graphical-session.target.wants
	sudo ln -s ../vino-server.service ./.
	gsettings set org.gnome.Vino prompt-enabled false
	gsettings set org.gnome.Vino require-encryption false
	gsettings set org.gnome.Vino authentication-methods "['vnc']"
	gsettings set org.gnome.Vino vnc-password $(echo -n 'teledyne2022'|base64)
	sudo reboot

Connect using jetson IP address (not port definition needed), accessible with

	ip a


