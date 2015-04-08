#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
//this function splits string into separate words and places into a vector
vector<string> splitter(string input)
{
    vector <string> words;
    int currcount=0;//counter of current word
    string store;//storage for words that come from inputted string

    //there are a few cases we need to consider
    //Cases include " ", ";", "#" 
    for(int i=0; i<input.size(); i++)
    {
        if(input.at(i)=='#')
        {
            if(store != "" && store!=" ")
            words.push_back(store);
            store = "";
            break;

        }
        else if(input.at(i) == ';')
        else if(input.at(i) == ' ')
    }
    return words;
}
int main(int argc, char** argv)
{
    string input;
    while(1)
    {
        cout << "$ :" << endl; 
        getline(cin, input);
        vector<string> words=splitter(input);
        for(int i=0; i<input.size(); i++)
        {        
            cout << words.at(i);
        }
    }       
    return 0;
}

