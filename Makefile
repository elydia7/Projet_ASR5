REP=$(shell pwd | sed "s%/.*/%%")

CODEC=demo.c
CODECPP=
POINTH=$(wildcard *.h)
POINTHPP=$(wildcard *.hpp)
LIBCPP=
LIBC=socklib.c ListeNoeud.c

FICHIERSBAK=$(wildcard *~)


EXE=$(CODEC:.c=.ex) $(CODECPP:.cpp=.exx)
LIBCPPO=$(LIBCPP:.cpp=.O)
LIBCO=$(LIBC:.c=.o)


CC=gcc
CPP=g++
CFLAGS=-g -Wall -I.
CPPFLAGS=-g -Wall -std=c++11 -I.
LDFLAGS=
LDDFLAGS=


FICHIERS=$(CODEC) $(POINTH) $(CODECPP) $(POINTHPP) $(LIBCPP)

all: $(EXE)

exec: $(EXE)

%.ex: %.o $(LIBCO)
	$(CC) $(CFLAGS) $< $(LIBCO) $(LDFLAGS) -o $@

%.exx: %.cpp $(LIBCPPO)
	$(CPP) $(CPPFLAGS) $< $(LIBCPPO) $(LDDFLAGS) -o $@

%.O: %.cpp $(POINTHPP)
	$(CPP) -c $(CPPFLAGS) $<  -o $@

%.o: %.c $(POINTH)
	$(CC) -c $(CFLAGS) $< -o $@

%.class: %.java
	javac $<

clean:
	@for i in $(EXE) $(LIBCO) $(LIBCPPO); \
        do \
                if [ -f $$i ]; then \
                        echo "efface "$$i;\
                        rm $$i; \
                fi; \
        done


grosclean: clean
	@for i in $(FICHIERSBAK); \
        do \
                if [ -f $$i ]; then \
                        echo "efface "$$i;\
                        rm $$i; \
                fi; \
        done \

tgz:: clean
	tar czvf ../$(REP)-IPC-`date +%y%m%d`.tar.gz -C ..  --exclude '*.swp' --exclude '*~' --exclude '.svn' $(REP)

Doxyfile :
	doxygen -g
	perl -p -i -e "s/^OUTPUT_DIRECTORY\s*=\s*$$/OUTPUT_DIRECTORY = Docs/" Doxyfile
	perl -p -i -e "s/^BUILTIN_STL_SUPPORT\s*=\s*NO$$/BUILTIN_STL_SUPPORT = YES/" Doxyfile
	perl -p -i -e "s/^EXTRACT_ALL\s*=\s*NO$$/EXTRACT_ALL = YES/" Doxyfile
	perl -p -i -e "s/^EXTRACT_PRIVATE\s*=\s*NO$$/EXTRACT_PRIVATE = YES/" Doxyfile
	perl -p -i -e "s/^EXTRACT_STATIC\s*=\s*NO$$/EXTRACT_STATIC = YES/" Doxyfile
	perl -p -i.bak -e "s/^OUTPUT_LANGUAGE\s*=\s*English$$/OUTPUT_LANGUAGE = French/i" Doxyfile

doc : Doxyfile $(FICHIERS)
	mkdir -p Docs
	doxygen
	rm Doxyfile
