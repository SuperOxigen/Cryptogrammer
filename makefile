COMPILER = g++
CFLAG = -std=c++11
SRCTYPE = cpp
SOURCE = src
BINARY = bin
NAME = cryptogrammer

all: $(BINARY)

build: $(BINARY)

$(BINARY): $(SOURCE)/*.$(SRCTYPE)
	g++ -std=c++11 -o $(BINARY)/$(NAME) $(SOURCE)/*.$(SRCTYPE)

clean:
	rm $(BINARY)/*

run: $(BINARY)
	$(BINARY)/$(NAME)

