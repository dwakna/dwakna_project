.SUFFIXES = .c -o
CXX = g++
CPPFLAGS = -g -Wall --std=c++14
TARGET = storage

OBJS = $(SRCS:.c=.o)
SRCS =\
storageIO.cpp\
main.cpp\
#main.cpp\
#FileIO.cpp\

INC=\
-I./ \
-I./include \
-I$(VOMSLOG_HOME) \
-I$(HOME)/MP/ExternalLib/spdlog/include\

LIBS_DIR=\
-L$(HOME)/lib\

LIBS=\
-lvomslog\
-lpthread\


$(TARGET) : $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(INC) $(LIBS_DIR) $(LIBS)

clean : 
	rm -rf $(TARGET)

