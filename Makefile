all:
		mkdir -p ./bin
		g++ -Wall -Werror -pedantic -ansi -pedantic ./src/exec.cpp -o ./bin/rshell
rshell:
		mkdir -p ./bin
		g++ -Wall -Werror -pedantic -ansi -pedantic ./src/exec.cpp -o ./bin/rshell
clean:
		rm -rf ./bin
