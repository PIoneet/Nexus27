# Makefile for DungeonMap project

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude
SRCDIR = src
INCDIR = include
TARGET = main
OBJECTS = main.o $(SRCDIR)/game_ui.o $(SRCDIR)/character.o $(SRCDIR)/input_utils.o $(SRCDIR)/game_map.o

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET).exe $(OBJECTS)

# Individual object files
#아래에 있는 코드들은 이를 테면 main.cpp 소스코드가 변경되거나 연결된 헤더들이 변경되면 다시 컴파일하겠다는 의미다.
main.o: main.cpp $(INCDIR)/game_ui.h $(INCDIR)/game_map.h $(INCDIR)/character.h
	$(CXX) $(CXXFLAGS) -c main.cpp

$(SRCDIR)/game_ui.ㅇo: $(SRCDIR)/game_ui.cpp $(INCDIR)/game_ui.h $(INCDIR)/input_utils.h $(INCDIR)/character.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/game_ui.cpp -o $(SRCDIR)/game_ui.o

$(SRCDIR)/character.o: $(SRCDIR)/character.cpp $(INCDIR)/character.h $(INCDIR)/input_utils.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/character.cpp -o $(SRCDIR)/character.o

$(SRCDIR)/input_utils.o: $(SRCDIR)/input_utils.cpp $(INCDIR)/input_utils.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/input_utils.cpp -o $(SRCDIR)/input_utils.o

$(SRCDIR)/game_map.o: $(SRCDIR)/game_map.cpp $(INCDIR)/game_map.h $(INCDIR)/game_types.h $(INCDIR)/termcolor.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/game_map.cpp -o $(SRCDIR)/game_map.o

# Clean up generated files
clean:
	del /Q *.o $(SRCDIR)\*.o *.exe 2>nul || true

# Force rebuild
rebuild: clean all

.PHONY: all clean rebuild
