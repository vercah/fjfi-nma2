INSTALL_DIR = ${HOME}/local

CXX = g++
#CXX_FLAGS = -DNDEBUG -O3 -funroll-loops -g -std=c++11 -Dlinux
CXX_FLAGS = -DNDEBUG -O3 -g -std=c++11 -Dlinux

LD_FLAGS += #-lgomp
