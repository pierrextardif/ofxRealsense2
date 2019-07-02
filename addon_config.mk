meta:
	ADDON_NAME = ofxRealsense2
	ADDON_DESCRIPTION = Addon for Intel librealsense2 (supports D400 series depth camera)
	ADDON_AUTHOR = Hiroshi Matoba
	ADDON_TAGS = "device"
	ADDON_URL = http://github.com/hiroMTB/ofxRealsense2

common:

	#ADDON_INCLUDES =  libs/realsense2/include/

linux64:
	# linux only, any library that should be included in the project using
	# pkg-config

linuxarmv7l:	
	ADDON_PKG_CONFIG_LIBRARIES = cuda-10.0 cudart-10.0 libusb-1.0 realsense2 #OpenCL
	ADDON_LDFLAGS = -L/usr/local/lib/ -L/usr/local/cuda/lib64 -lcuda -lcudart

#The library is installed in /usr/local/lib
#The header files are in /usr/local/include
#The demos and tools are located in /usr/local/bin
