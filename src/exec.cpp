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
    string username=getlogin();
    char hostname[999];
    gethostname(hostname, 999);
    string stringinput;
    char* input[999];
    char_separator<char> ands("&&");
    char_separator<char> ors("||");
    char_separator<char> semico(";");
    while(true)
    {
        //if the user name and hostname both exists, then the program displays it before the dollar sign.
        if(getlogin() != '\0' && gethostname(hostname,999) != -1)    
            cout << username << "@" << hostname << "$ ";
        else
        {
            perror("your hostname or username couldn't be found!");
            cout << "$ ";
        }
        getline(cin,stringinput);
        //this checks for comments. Basically, everything after the hash symbol is useless
        if(stringinput.find("#") != string::npos)
        {
            stringinput=stringinput.substr(0,stringinput.find("#"));
        }
        if(stringinput.find("||")!=string::npos )
        {
            tokenizer<char_separator<char> > toke(stringinput,ors);
            tokenizer<char_separator<char> >::iterator it=toke.begin();
            for(; it != toke.end(); it++)
            {      
                char_separator<char> space(" ");
                tokenizer<char_separator<char> > tok(*it, space);
                int status=0;
                pid_t pid = fork();
                if(pid==-1)
                {        
                    perror("this is an error with fork()");
                    exit(1);
                }
                else if(pid==0)
                {
                    int counter=0;
                    for(tokenizer<char_separator<char> >::iterator 
                        it1=tok.begin(); it1 != tok.end(); 
                        it1++,counter++)
                    {
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
                    else
                    {
                        cout << "Good!" << execvp(input[0],input) << endl;
                    }
                }
                else if(pid>=1)
                {
                    waitpid(-1,&status,0);
                    if(status<=0)
                        break;
                }
            }
            if(stringinput.find("exit")!=string::npos)
                continue;
        }
        else if(stringinput.find("&&")!=string::npos )
        {
            if(stringinput.find("exit")!=string::npos)
                exit(1);
            tokenizer<char_separator<char> > toke(stringinput,ands);
            tokenizer<char_separator<char> >::iterator it=toke.begin();
            for(; it != toke.end(); it++)
            {      
                char_separator<char> space(" ");
                tokenizer<char_separator<char> > tok(*it, space);
                int status=0;
                pid_t pid = fork();
                if(pid==-1)
                {        
                    perror("this is an error with fork()");
                    exit(1);
                }
                else if(pid==0)
                {
                    int counter=0;
                    for(tokenizer<char_separator<char> >::iterator 
                        it1=tok.begin(); it1 != tok.end(); 
                        it1++,counter++)
                    {
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
                    else
                    {
                        cout << "Good!" << execvp(input[0],input) << endl;
                    }
                }
                else if(pid>=1)
                {
                    waitpid(-1,&status,0);
                    if(status>0)
                        break;
                }
            }
        }
        else
        {
            tokenizer<char_separator<char> > toke(stringinput,semico);
            tokenizer<char_separator<char> >::iterator it=toke.begin();
            for(; it != toke.end(); it++)
            {      
                char_separator<char> space(" ");
                tokenizer<char_separator<char> > tok(*it, space);
                int status=0;
                pid_t pid = fork();
                if(pid==-1)
                {        
                    perror("this is an error with fork()");
                    exit(1);
                }
                else if(pid==0)
                {
                    int counter=0;
                    tokenizer<char_separator<char> >::iterator 
                    it1=tok.begin();
                    for(; it1 != tok.end(); 
                        it1++,counter++)
                    {
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
                    else
                    {
                        cout << "Good!" << execvp(input[0],input) << endl;
                    }
                }
                else if(pid>=1)
                {
                    waitpid(-1,&status,0);
                }
            }
        }
        if(stringinput.find("exit")!=string::npos)
        {
            exit(1);
        }
    }
    return 0; 
}



