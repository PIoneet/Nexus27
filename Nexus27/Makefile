# Makefile for DungeonMap project

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude
#LIBWORK = -L${workspaceFolder} 위 최상의 폴더 경로는 Makefile에서 인식이 안된다.
SRCDIR = src
INCDIR = include
FINDLIB = -Llib
LINK = -lglfw3dll
TARGET = main
OBJECTS = main.o $(SRCDIR)/game_ui.o $(SRCDIR)/character.o $(SRCDIR)/input_utils.o $(SRCDIR)/game_map.o $(SRCDIR)/glad.o $(SRCDIR)/triangle_buffer.o

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(FINDLIB) $(LINK) -o $(TARGET).exe

# Individual object files
#아래에 있는 코드들은 이를 테면 main.cpp 소스코드가 변경되거나 연결된 헤더들이 변경되면 다시 컴파일하겠다는 의미다.
main.o: main.cpp $(INCDIR)/game_ui.h $(INCDIR)/game_map.h $(INCDIR)/character.h $(INCDIR)/glad/glad.h $(INCDIR)/GLFW/glfw3.h $(INCDIR)/triangle_buffer.h
	$(CXX) $(CXXFLAGS) -c main.cpp

$(SRCDIR)/game_ui.o: $(SRCDIR)/game_ui.cpp $(INCDIR)/game_ui.h $(INCDIR)/input_utils.h $(INCDIR)/character.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/game_ui.cpp -o $(SRCDIR)/game_ui.o

$(SRCDIR)/character.o: $(SRCDIR)/character.cpp $(INCDIR)/character.h $(INCDIR)/input_utils.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/character.cpp -o $(SRCDIR)/character.o			

$(SRCDIR)/input_utils.o: $(SRCDIR)/input_utils.cpp $(INCDIR)/input_utils.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/input_utils.cpp -o $(SRCDIR)/input_utils.o

$(SRCDIR)/game_map.o: $(SRCDIR)/game_map.cpp $(INCDIR)/game_map.h $(INCDIR)/game_types.h $(INCDIR)/termcolor.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/game_map.cpp -o $(SRCDIR)/game_map.o

$(SRCDIR)/glad.o: $(SRCDIR)/glad.c $(INCDIR)/glad/glad.h $(INCDIR)/KHR/khrplatform.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/glad.c -o $(SRCDIR)/glad.o

$(SRCDIR)/triangle_buffer.o: $(SRCDIR)/triangle_buffer.cpp $(INCDIR)/triangle_buffer.h $(INCDIR)/glad/glad.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/triangle_buffer.cpp -o $(SRCDIR)/triangle_buffer.o

# Clean up generated files
clean:
	del /Q *.o $(SRCDIR)\*.o *.exe 2>nul || true

# Force rebuild
rebuild: clean all

.PHONY: all clean rebuild
