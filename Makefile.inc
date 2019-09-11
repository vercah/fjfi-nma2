INSTALL_DIR = ${HOME}/.local

CXX = g++
#CXXFLAGS = -DNDEBUG -O3 -funroll-loops -g -std=c++11 -Dlinux
CXXFLAGS = -DNDEBUG -O0 -g -Dlinux -std=c++11 -fPIC
CPPFLAGS = -MD -MP

LDFLAGS += -lm #-lgomp
