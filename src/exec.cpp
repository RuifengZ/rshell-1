#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <sys/wait.h>
#include <vector>
#include<boost/tokenizer.hpp>
using namespace std;
using namespace boost;
int main(int argc, char **argv)
{
    char hostname[999];
    if(gethostname(hostname, 999)==-1)
		perror("hostname");
	char login[999];
	if(getlogin_r(login,999)==-1)
		perror("login");
    
	string stringinput;
    char* input[999];
	vector<string> commands;
    char_separator<char> ands("&&");
    char_separator<char> ors("||");
    char_separator<char> semico(";");
	while(true)
    {
        //if the user name and hostname both exists, then the program displays it before the dollar sign.
        cout << login << "@" << hostname << "$ ";
        getline(cin,stringinput);
        //this checks for comments. Basically, everything after the hash symbol is useless
        if(stringinput.find("#") != string::npos)
        {
            stringinput=stringinput.substr(0,stringinput.find("#"));
        }
		//this checks for ||
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
                }
                else if(pid>=1)
                {
                    if(wait(&status)==-1)
						perror("wait");
					if(status<=0)
                        break;
                }
            }
            if(stringinput.find("exit")!=string::npos)
                continue;
        }
        //this checks for &&
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
                }
                else if(pid>=1)
                {
                    if(wait(&status)==-1)
						perror("wait");
					if(status>0)
                        break;
                }
            }
        }
        //this checks for ; and other things
        else
        {
			if(stringinput.find("exit")!=string::npos && stringinput.at(0)== 'e')
			{
				exit(1);
			}
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
                //checks on the child
                else if(pid==0)
                {
                    //starts to parse and token
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
                    //finds a invalid command
                    if(good==-1)
                    {
						if(stringinput.find("exit")!=string::npos)
						exit(1);
					   perror("Command is bad and not good!");
					   exit(1);
                    }
                }
                else if(pid>=1)
                {
                    if(wait(&status)==-1)
						perror("wait");
					//waits for the child to finish
                }
            }
        }
		if(stringinput.find("exit")>=4)
		{
			continue;
		}
		if(stringinput.find("exit")!=string::npos)
        {
            exit(1);
        }
    }
    return 0; 
}



