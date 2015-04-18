
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
