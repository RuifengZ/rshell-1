all:
		mkdir -p ./bin
		g++ -Wall -Werror -pedantic -ansi ./src/ls.cpp -o ./bin/ls
rshell:
		mkdir -p ./bin
		g++ -Wall -Werror -pedantic -ansi  ./src/exec.cpp -o ./bin/rshell
ls:
		mkdir -p ./bin
		g++ -Wall -Werror -pedantic -ansi ./src/ls.cpp -o ./bin/ls
clean:
		rm -rf ./bin
