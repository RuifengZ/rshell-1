
## RSHELL 
Shell Terminal for UCR CS100
This program is a bash terminal that runs bash commands located in /bin. Examples of these commands include "ls", "pwd", "echo" and etc. 
### Installation
To install and run rshell on your computer, open terminal and type the following commands:

```
1. git clone http://www.github.com/kchan049/rshell.git

2. cd rshell

3. git checkout hw0

4. make

5. bin/rshell
```

###Program Features

-Rshell supports all the bash commands located in /bin.

-Rshell also supports connectors such as ";", "&&", and "||".

-The ";" connector: the next command is always executed.

-The "&&" connector: the next command is executed if the first one succeeds.

-The "||" connector: the next command will execute if the first one fails.

-The "#" symbol: Anything after this symbol will be a comment.

-In order to exit the program, simply type "exit".

###Bugs and Limitations
-If you type 3 or more consecutive "&" like "&&&", this program will treat it as "&&". The same applies to "|" and ";". 

-Having one symbol will not execute commands.

-uses boost library so you need to install boost when using this program.

-does not support " " (quotes) in this version

-if you use (ls &&), it will execute ls.

-if you use (&& ls ), it will execute ls too.

-Hostname and Username have a 999 character maximum.
 
### Installation
To install and run rshell on your computer, open terminal and type the following commands:

```
1. git clone http://www.github.com/kchan049/rshell.git

2. cd rshell

3. git checkout hw1

4. make ls

5. bin/ls
```
###Program Features and Bugs for LS

-files are outputted are outputted left to right instead of columns like the real ls

-files are sorted by number of links and the priority is for the hidden files

-ls supports the flags -l, -a, -R and combinations of these flags. 

-flags and parameters must be used as following:

``` 
Example: bin/ls -alR, bin/ls parameter -lRa
```

-flags must be exactly l,a, R. Lower case version of R will not work and uppercase version of l a will not work.

-everytime there is a perror, the program will automatically exit
 
### Installation for io redirection and piping
To install and run rshell on your computer, open terminal and type the following commands:

```
1. git clone http://www.github.com/kchan049/rshell.git

2. cd rshell

3. git checkout hw2

4. make 

5. bin/rshell
```
###Program Features and Bugs for IO Redirection and Piping

-The two extra credit are implemented and work perfectly but the <<< operator only works on double quotes as specified

-However, extra credit part 1 might have some newline bugs as shown in the script!.

-The extra credit part 2 works like this:

```
Example: g++ main.cpp 2> errors
Example: g++ main.cpp 2>> errors
```

-If you combine hw0 operators and hw2 operators, the program will not work!

-The program supports one instance of each method of redirection and it can also support multiple pipes

-The '<' symbol will run input redirection if the syntax is (command '<' <file>)

-The '>' symbol will run output redirection if the syntax is (command '>' <file>)

-The '>>' symbol will run output redirection (append) if the syntax is (command '>>' <file>)

-The '|' symbol will run piping and can be grouped multiple times with the syntax (file '|' command '|' command)

-The program doesnt support multiple instances of each method of redirection.

### Installation for io redirection and piping
To install and run rshell on your computer, open terminal and type the following commands:

```
1. git clone http://www.github.com/kchan049/rshell.git

2. cd rshell

3. git checkout hw3

4. make 

5. bin/rshell
```
###Program Features and Bugs for IO Redirection and Piping

-The three extra credit commands('^z','fg','bg') are implemented and work perfectly as demoed in the script.

-The five point extra credit is also implemented. If the directory contains home/user, it will replace home/user with ~.

-'^z' will do nothing unless a process is trying to be stopped. In that case, it will pause the process and if fg is typed, then it will continue the process. 

-fg resumes a paused process and brings it to the foreground.

-bg resumes a paused process and brings it to the background.

-'^c' will no longer exit the rshell. It will interrupt the current foreground process.

-The cd command will take you back to the home user directory.

-The cd <path> command will lead you into the path.







