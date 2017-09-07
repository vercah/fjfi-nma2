INSTALL_DIR = ${HOME}/.local

CXX = g++
#CXXFLAGS = -DNDEBUG -O3 -funroll-loops -g -std=c++11 -Dlinux
CXXFLAGS = -DNDEBUG -O3 -g -Dlinux -std=c++11
CPPFLAGS = -MD -MP

LDFLAGS += -lm #-lgomp
