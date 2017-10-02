include Makefile.inc

FILES = Makefile \
        Makefile.inc \
        CommandLineParser.cpp \
        CommandLineParser.h \
        Timer.cpp \
        Timer.h \
        Vector.cpp \
        Vector.h \
        real.h \
        string-split.cpp \
        string-split.h

SUBDIRS = data \
          eigenvalues \
          gem \
          matrices \
          ode \
          stationary

SUBDIRSCLEAN=$(addsuffix clean,$(SUBDIRS))

all: bin subdirs

.PHONY:	subdirs $(SUBDIRS)
subdirs:    $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@	

bin:
	mkdir -p bin

install: all
	mkdir -p $(INSTALL_DIR)/bin
	cp bin/* $(INSTALL_DIR)/bin

.PHONY:	clean
clean:	$(SUBDIRSCLEAN) clean_curdir

clean_curdir:
	rm -f *.o
	
%clean:	%
	$(MAKE) -C $< clean

dist: clean
	tar zcvf fjfi-num1-src.tgz $(SUBDIRS) $(FILES)
