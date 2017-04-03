INSTALL_DIR = ${HOME}/.local

CXX = g++
#CXX_FLAGS = -DNDEBUG -O3 -funroll-loops -g -std=c++11 -Dlinux
CXX_FLAGS = -DNDEBUG -O3 -g -Dlinux -std=c++11

LD_FLAGS += -lm #-lgomp
