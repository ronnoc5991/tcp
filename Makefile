build: build_client build_server

build_client: ./client/main.c ./utils/mysockets.c
	gcc ./client/main.c ./utils/mysockets.c -o ./bin/client -Wall

build_server: ./server/main.c ./utils/mysockets.c
	gcc ./server/main.c ./utils/mysockets.c -o ./bin/server -Wall

run_client: ./client
	./bin/client

run_server: ./server
	./bin/server

clean:
	rm ./bin/client
	rm ./bin/server
