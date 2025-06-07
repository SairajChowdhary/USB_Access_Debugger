CXX = clang++
CXXFLAGS = -std=c++17 -Iinclude -I/opt/homebrew/include -Wall
LDFLAGS = -L/opt/homebrew/lib -lsqlite3 -lusb-1.0

SRC = src/main.cpp src/usb_monitor.cpp src/logger.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = usb_logger

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) src/*.o




