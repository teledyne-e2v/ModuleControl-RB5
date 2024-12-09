all:
	aarch64-linux-gnu-g++ -o ModuleControl main.cpp -lm
	aarch64-linux-gnu-gcc -o gstCommands gst-main.cpp -lm	
