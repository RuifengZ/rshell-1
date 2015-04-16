#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <sys/wait.h>
#include<boost/tokenizer.hpp>
using namespace std;
using namespace boost;
int main()
{
    bool semicolon=0;
    bool doubleand=0;
    bool doubleor=0;
    string username=getlogin();
    char hostname[999];
    gethostname(hostname, 999);
    string stringinput;
    int inputcnt=0;
    char* input[999];
    const char ands[]="&&";
    while(1)
    {
        //if the user name and hostname both exists, then the program displays it before the dollar sign.
        if(getlogin() != '\0' && gethostname(hostname,999) != -1)    
            cout << username << "@" << hostname << "$ ";
        else{
                perror("your hostname or username couldn't be found!");
                cout << "$ ";
        }
        //takes in a string input
        getline(cin, stringinput);
        //this checks for exit and Exit command 
        if(stringinput.find("exit")==0||stringinput.find("Exit")==0)
                exit(1);
       //this checks for comments. Basically, everything after the hash symbol is useless
       if(stringinput.find("#") != string::npos)
       {
           stringinput=stringinput.substr(0,stringinput.find("#"));
       }
       if(stringinput.find("&&")!=string::npos)
                char_separator<char> sep("&&");
                tokenizer<char_separator<char> > toker(stringinput,sep);
                for(tokenizer<char_separator<char> >::iterator it=toker.                          begin(); it != toker.end(); it++)
                {        
                    int status=0;
                    pid_t pid = fork();
                    if(pid==-1)
                    {        
                        perror("this is an error with fork()");
                        exit(1);
                    }
                    else if(pid==0)
                    {
                        char_separator<char> sep(" ");
                        tokenizer<char_separator<char> > tok(*it, sep);
                        int counter=0;
                        for(tokenizer<char_separator<char> >::iterator it1=tok.                          begin(); it1 != tok.end(); it1++)
                        {
                            counter++;
                            input[counter]=new char[(*it1).size()];
                            strcpy(input[counter],(*it1).c_str());
                        }
                        input[counter]=0;
                        int good=execvp(input[0],input);
                        if(good==-1)
                        {
                                perror("Command is bad and not good!");
                                exit(1);
                        }
                        else{
                                cout << "Good!" << execvp(input[0],input) << endl;
                        }
                    }
                    else if(pid>=1)
                    {
                        if(waitpid(-1,&status,0)==-1)
                        {
                                perror("Please take care of your child!");
                                exit(1);
                        }
                    }
                }
    }       
    return 0;
}




