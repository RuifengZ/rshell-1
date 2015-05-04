all:
		mkdir -p ./bin
		g++ -Wall -Werror -pedantic -ansi ./src/ls.cpp -o ./bin/ls
rshell:
		mkdir -p ./bin
		g++ -Wall -Werror -pedantic -ansi  ./src/exec.cpp -o ./bin/rshell
ls:
		mkdir -p ./bin
		g++ -Wall -Werror -pedantic -ansi ./src/ls.cpp -o ./bin/ls
	
rm:
		mkdir -p ./bin
		g++ -Wall -Werror -pedantic ./src/rm.cpp -o ./bin/rm -std=c++11

clean:
		rm -rf ./bin
