compiler := gcc
flags := -Wall

bindir := ./bin
objdir := ./obj
utilsdir := ./utils
clientdir := ./client
serverdir := ./server
includedir := ./include

build: $(bindir)/client $(bindir)/server

$(bindir)/client: $(objdir)/client.o $(objdir)/mysockets.o
	$(compiler) $^ -o $@ $(flags)

$(objdir)/client.o: $(clientdir)/main.c $(includedir)/mysockets.h
	$(compiler) -c $< -o $@ $(flags)

$(objdir)/mysockets.o: $(utilsdir)/mysockets.c $(includedir)/mysockets.h
	$(compiler) -c $< -o $@ $(flags)

$(bindir)/server: $(objdir)/server.o $(objdir)/mysockets.o
	$(compiler) $^ -o $@ $(flags)

$(objdir)/server.o: $(serverdir)/main.c $(includedir)/mysockets.h
	$(compiler) -c $< -o $@ $(flags)

clean:
	rm $(bindir)/client
	rm $(bindir)/server
	rm $(objdir)/client.o
	rm $(objdir)/server.o
	rm $(objdir)/mysockets.o
