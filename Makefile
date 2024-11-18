# Makefile for ThreadPoolTest project

# 编译器
CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall

# 文件名
TARGET = main

# 源文件
SRC = main.cc \
      ThreadPool.cc \
      Task.cc \
      Logger.cc \
      ConcurrentThread.cc

# 目标文件
OBJ = $(SRC:.cc=.o)

# 编译规则
all: $(TARGET)

# 链接目标文件并生成可执行文件
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) -pthread  # 确保在链接阶段使用 -pthread

# 编译每个源文件
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理目标
clean:
	rm -f $(OBJ) $(TARGET)

# 重新生成
rebuild: clean all
