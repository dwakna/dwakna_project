.SUFFIXES = .c -o
CXX = g++
CPPFLAGS = -g -Wall --std=c++14
TARGET = ft

OBJS = $(SRCS:.c=.o)
SRCS = \
filetest3.cpp\
#jsonParsing.cpp\
#storageIO.cpp\
main.cpp\
#main.cpp\
#FileIO.cpp\

INC=\
-I./ \
-I./include \
-I$(VOMSLOG_HOME) \
-I$(HOME)/MP/ExternalLib/spdlog/include\
-I$(EXT_LIB_HOME)/OpenCV-3.0.0/linux/inc \
-I$(EXT_LIB_HOME)/OpenCV-3.0.0/linux/inc/opencv \
-I$(EXT_LIB_HOME)/OpenCV-3.0.0/linux/inc/opencv2 \


LIBS_DIR=\
-L$(HOME)/lib\
-L/usr/lib64/\

LIBS=\
-lvomslog\
-lpthread\
-lcpprest\
-lboost_system\
-lcrypto\
-ljsoncpp\
-lopencv_core \
-lopencv_flann \
-lopencv_imgcodecs \
-lopencv_imgproc \
-lopencv_video \

$(TARGET) : $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(INC) $(LIBS_DIR) $(LIBS)

clean : 
	rm -rf $(TARGET)

