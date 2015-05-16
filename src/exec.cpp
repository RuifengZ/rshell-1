#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include<boost/tokenizer.hpp> 
using namespace std; 
using namespace boost; //this function checks for which file descriptor 

bool triplecheck=false;
bool singlecheck=false;
struct pipeid
{
	string left;
	int fd[2];

};
vector <pipeid> a;
int savestd[2];
int openF(const string &in, int perms)
{
	char_separator<char> space(" ");
 	tokenizer<char_separator<char> > tok(in, space);
	tokenizer<char_separator<char> >::iterator it1=tok.begin();
	int good=open((*it1).c_str(),perms,S_IRWXU|S_IRWXG|S_IRWXO);
	if(good==-1)
		perror("open");
	return good;
}
void execP(const string &in)
{
	char *input[999];
	int counter=0;
	char_separator<char> space(" ");
 	tokenizer<char_separator<char> > tok(in, space);
	tokenizer<char_separator<char> >::iterator it1=tok.begin();
	for(;it1!=tok.end();it1++,counter++)
	{
    	input[counter]=new char[(*it1).size()];
    	strcpy(input[counter],(*it1).c_str());
  	}
   	input[counter]=0;

	int good=(execvp(input[0],input));
	if(good==-1)
	{
		perror("execvp");
		for(counter=0,it1=tok.begin(); it1!=tok.end(); it1++, counter++)
			delete[] input[counter];
		exit(1);
	}


}
void setpipe(bool first, bool last, pipeid i, pipeid p)
{	
	if (first)
	{
		if((savestd[0] = dup(0))==-1)
		{
			perror("dup");
			exit(1);
		}
		if((savestd[1] = dup(1))==-1)
		{
			perror("dup");
			exit(1);
		}
	}
	if (!first)
	{
		if(close(0)==-1)
		{
			perror("close");
			exit(1);
		}
		if(dup(p.fd[0])==-1)
		{
			perror("dup");
			exit(1);
		}
		if(close(p.fd[0])==-1)
		{
			perror("close");
			exit(1);
		}
	}
	if (!last)
	{
		if(close(1)==-1)
		{
			perror("close");
			exit(1);
		}
		if(dup(i.fd[1])==-1)
		{
			perror("dup");
			exit(1);
		}
		if(close(i.fd[1])==-1)
		{
			perror("close");
			exit(1);
		}

	}
	if (last)
	{
		if(close(1)==-1)
		{
			perror("close");
			exit(1);
		}
		if(dup2(savestd[1], 1)==-1)
		{
			perror("dup2");
			exit(1);
		}
		if(close(savestd[1])==-1)
		{
			perror("close");
			exit(1);
		}
		
	}
}
void reset(bool b)
{
	if (b)
	{
		if(close(0)==-1)
		{
			perror("close");
			exit(1);
		}
		if(dup2(savestd[0], 0)==-1)
		{
			perror("dup2");
			exit(1);
		}
		if(close(savestd[0])==-1)
		{
			perror("close");
			exit(1);
		}
	}
}
void errorfd(int sin, int sout, int serr)
{
	if(sin >= 0)
	{
		if(close(0)==-1)
		{
			perror("close");
			exit(1);
		}
		if(dup(sin)==-1)
		{
			perror("dup");
			exit(1);
		}
	}
	if(sout >= 0)
	{
		if(close(1)==-1)
		{
			perror("close");
			exit(1);
		}
		if(dup(sout)==-1)
		{
			perror("dup");
			exit(1);
		}
	}
	if(serr >= 0)
	{
		if(close(2)==-1)
		{
			perror("close");
			exit(1);
		}
		if(dup(serr)==-1)
		{
			perror("dup");
			exit(1);
		}
	}
}
void execR(const string &in, int sin, int sout, int serr)
{
	char *input[999];
	int counter=0;
	char_separator<char> space(" ");
 	tokenizer<char_separator<char> > tok(in, space);
	tokenizer<char_separator<char> >::iterator it1=tok.begin();
	for(;it1!=tok.end();it1++,counter++)
	{
    	input[counter]=new char[(*it1).size()];
    	strcpy(input[counter],(*it1).c_str());
  	}
   	input[counter]=0;
	errorfd(sin,sout,serr);
	int good=(execvp(input[0],input));
	if(good==-1)
	{
		perror("execvp");
		for(counter=0,it1=tok.begin(); it1!=tok.end(); it1++, counter++)
			delete[] input[counter];
		exit(1);
	}

}
int main()
{
    char hostname[999];
    if(gethostname(hostname, 999)==-1)
		perror("hostname");
	char login[999];
	if(getlogin_r(login,999)==-1)
		perror("login");
    
	string stringinput;
    char* input[999];
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
					tokenizer<char_separator<char> >::iterator it1=tok.begin();
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
						for(counter=0,it1=tok.begin(); it1!=tok.end(); it1++,counter++)
							delete[] input[counter];
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
                    tokenizer<char_separator<char> >::iterator it1=tok.begin(); 
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
                        for(counter=0,it1=tok.begin(); it1!=tok.end(); it1++,counter++)
							delete[] input[counter];
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
		else if(stringinput.find("<<<")!=string::npos)
		{
			string triple="<<<";
			string single="<";
			string result;
			int out=-1,in=-1;
			int fd[2];
			if(stringinput.find("\"")!=string::npos)
			{
				//if we find only one double quote then we report an error
				result=stringinput.substr(stringinput.find("\"")+1);
				if(result.find("\"")==string::npos)
				{
					cout << "only found one double quote" << endl;
					exit(1);
				}
				result=result.substr(0,result.find("\""));
				if(pipe(fd)==-1)
				{
					perror("pipe is broken");
					exit(1);
				}
				char *buffer=new char[result.size()];
				strcpy(buffer,result.c_str());
				if(write(fd[1],buffer,result.size())==-1)
				{
					perror("write");
					exit(1);
				}
				if(close(fd[1])==-1)
				{
					perror("close");
					exit(1);
				}
				in=fd[0];
				delete [] buffer;
			}
			else
			{
				cout << "please!" << endl;
				exit(1);
			}
			string left=stringinput.substr(0,stringinput.find(single));
			string right=stringinput.substr(stringinput.find(single)+single.size());
			string prev=right;
			//checks for additional symbols right after <<<
			if(right.find(">")!=string::npos)
			{
				prev=prev.substr(0,right.find(">"));
				int perm=O_RDWR|O_CREAT;
				int index;
				//if it sees output append then it appends
				if(right.find(">>")!=string::npos)
				{
					perm |= O_APPEND;
					index=right.find(">>")+2;
				}
				//if it sees output then it destructs
				else
				{
					perm |= O_TRUNC;
					index=right.find(">")+1;
				}
				right=right.substr(index);
				out=openF(right,perm);
			}
			pid_t pid=fork();
			if(pid==-1)
				perror("fork");
			else if(pid==0)
				execR(left,in,out,-1);
			else
			{
				if(wait(0)==-1)
				{
					perror("wait");
					exit(1);
				}
				if(in!=-1)
				{
					if(close(in)==-1)
					{
						perror("close");
						exit(1);
					}
				}
				if(out!=-1)
				{
					if(close(out)==-1)
					{
						perror("close");
						exit(1);
					}
				}
			}
			cout << endl;
		}
		else if(stringinput.find("<")!=string::npos)
		{
			string single="<";
			string result;
			int out=-1,in=-1;
			string left=stringinput.substr(0,stringinput.find(single));
			string right=stringinput.substr(stringinput.find(single)+single.size());
			string prev=right;
			in=openF(prev,O_RDWR);
			if(in==-1)
				perror("in");
			if(right.find(">")!=string::npos)
			{
				prev=prev.substr(0,right.find(">"));
				int perm=O_RDWR|O_CREAT;
				int index;
				if(right.find(">>")!=string::npos)
				{
					perm |= O_APPEND;
					index=right.find(">>")+2;
				}
				else
				{
					perm |= O_TRUNC;
					index=right.find(">")+1;
				}
				right=right.substr(index);
				out=openF(right,perm);
			}
			pid_t pid=fork();
			if(pid==-1)
				perror("fork");
			else if(pid==0)
				execR(left,in,out,-1);
			else
			{
				if(wait(0)==-1)
				{
					perror("wait");
					exit(1);
				}
				if(in!=-1)
				{
					if(close(in)==-1)
					{
						perror("close");
						exit(1);
					}
				}
				if(out!=-1)
				{
					if(close(out)==-1)
					{
						perror("close");
						exit(1);
					}
				}
			}

		}
		else if (stringinput.find("|") != string::npos)
		{	
			//removes signes from stringinput
			int tt = 0;
			bool out = false;
			bool appen = false;
			tt = stringinput.find("<");
			if (tt >= 0)
				stringinput.erase(tt, 1);
			tt = stringinput.find(">");
			if (tt >= 0)
			{
				out = true;
			//	stringinput.erase(tt,1);
			}
			tt = stringinput.find(">>");
			if (tt >= 0)
			{
			//	stringinput.erase(tt,2);
				appen = true;
			}
			tt= stringinput.find("<<<");
			if (tt >= 0)
				stringinput.erase(tt, 3);



			if (out)
			{
				int i = 0;
				i = stringinput.find("|");
				stringinput = stringinput.substr(i + 1);
				goto out;



			}
			if (appen)
			{
				int i = 0;
				i = stringinput.find("|");
				stringinput = stringinput.substr(i + 1);
				goto appen;


			}

			a.clear();
			bool b = true;
			string singlein="|";
			size_t index;
			//while loop makes a vector of all the arguments passed in with a pipe
			//while loop also creates a pipe for all the arguments
			pipeid tmp;
			while ( string::npos !=  (index=stringinput.find(singlein)))
			{
				tmp.left=stringinput.substr(0,index);
				if(pipe(tmp.fd)==-1)
				{
					perror("pipe");
					exit(1);
				}
				a.push_back(tmp);
				stringinput=stringinput.substr(stringinput.find(singlein)+singlein.size());
			}
			tmp.left = stringinput;
			if(pipe(tmp.fd)==-1)
			{
				perror("pipe");
				exit(1);
			}
			a.push_back(tmp);
			//loop through and execute all arguemnts 
			size_t i = 0;
			while(i != a.size())
			{
				//sets the pipe 
				bool first = false;
				bool last = false;
				pipeid asdf = a.at(i);
				//first argument
				if (i == 0)
				{
					first = true;
					setpipe(first, last, asdf, asdf);
				}
				//last arguemnt
				else if (i == a.size() - 1)
				{
					pipeid asdfp;
					asdfp = a.at(i-1);
					last = true;
					setpipe(first, last, asdf, asdfp);
				}
				//middle arguments
				else
				{
					pipeid asdfp = a.at(i-1);
					setpipe(first, last, asdf, asdfp);
				}
				//forks and executes the commands 

				pid_t pid=fork();
				if(pid==-1)
					perror("fork");
				else if(pid==0)
				{
					execP(a.at(i).left);
				}
				i++;
				
			}
			int status = 0;
			while ( wait(&status) > 0);
			reset(b);
		}

        else if(stringinput.find(">>")!=string::npos)
		{
		appen:
			string doublein=">>";
			int perm=O_RDWR|O_CREAT;
			perm |= O_APPEND;
			int index=stringinput.find(doublein);
			//extra credit part 2
			if(stringinput.find("2>>")!=string::npos)
				index--;
			if(stringinput.find("1>>")!=string::npos)
				index--;
			string left=stringinput.substr(0,index);
			string right=stringinput.substr(stringinput.find(doublein)+doublein.size());
			//open files
			int good=openF(right,perm);
			pid_t pid=fork();
			if(pid==-1)
				perror("fork");
			else if(pid==0)
			{
				if (stringinput.find("2>>")!=string::npos)
					execR(left, -1, -1, good);
				execR(left,-1,good,-1);
			}
			else
			{
				if(wait(0)==-1)
				{
					perror("wait");
					exit(1);
				}
				if(close(good)==-1)
				{
					perror("close");
					exit(1);
				}
			}	
		}
		else if(stringinput.find(">")!=string::npos)
		{
		out:
			string singlein=">";
			int perm=O_RDWR|O_CREAT;
			perm |= O_TRUNC;
			int index=stringinput.find(singlein);
			if(stringinput.find("2>")!=string::npos)
				index--;
			if(stringinput.find("1>")!=string::npos)
				index--;
			string left=stringinput.substr(0,index);
			string right=stringinput.substr(stringinput.find(singlein)+singlein.size());
			int good=openF(right,perm);
			pid_t pid=fork();
			if(pid==-1)
				perror("fork");
			else if(pid==0)
			{
				if	(stringinput.find("2>")!=string::npos)
					execR(left,-1,-1,good);
				else
					execR(left,-1,good,-1);
			}
			else
			{
				if(wait(0)==-1)
				{
					perror("wait");
					exit(1);
				}
				if(close(good)==-1)
				{
					perror("close");
					exit(1);
				}
			}	
		}
		//this checks for ; and other things
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
                        for(counter=0,it1=tok.begin(); it1!=tok.end(); it1++,counter++)
							delete[] input[counter];
						exit(1);
 						perror("Command is bad and not good!");
                    }
                }
                else if(pid>=1)
                {
                    //waits for the child to finish
                    if(wait(&status)==-1)
						perror("wait");
					//waits for the child to finish
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



