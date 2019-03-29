/*
Author: Maisa
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 2: Phase V Program
This project will take users input for a word and the program will report the pronunciation, identical, replace phoneme, add phoneme and remove phoneme.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>

using namespace std;

void splitOnSpace(string s, string & before, string & after) 
{
  // reset strings
    before = ""; 
    after = "";
  // accumulate before space
    int i = 0;
    while (i < s.size() && not isspace(s[i])) 
    { 
        before += s[i]; i++; 
    }
    // skip the space
    i++;
      // accumulate after space
    while (i < s.size()) 
    {
        after += s[i]; i++;
    }
}

int counting(string p) {
    int c = 0;
    for (int i = 0; i < p.length(); i++) 
    {
        if (p[i] == ' ') 
        {
            c++;
        }
    }
    return c;
}

bool valid (string user_word) 
{

    for (int i = 0; i < user_word.length(); i++) 
    {
        if (user_word[i] >= 0 && user_word[i] < 39) 
        {
            return false;
        }
        else if (user_word[i] > 39 && user_word[i] <= 64) 
        {
            return false;
        }
    }
    return true;
}


int main() 
{
    //pronunciation
    bool found = false;
    string x, a, p, pron, identical;
    string user_word;
    cout << "> ";
    cin >> user_word; //input word

    ifstream fin("cmudict.0.7a");  //read file
    if (fin.fail()) {
        cerr << "File cannot be opened for reading." << endl;
        exit(1);
    }

    for (int i = 0; i < user_word.length(); i++)//loop through word to make case insensitive
    {
        if (user_word[i] >= 97 && user_word[i] <= 122)
        {
            user_word[i] = user_word[i] - 32; //uses decimal and converts lowercase letters to nothing
        }
        else if (user_word[i] >= 0  && user_word[i] < 39)
        {
            return -1; //returns nothing
        }
        else if (user_word[i] > 39 && user_word[i] <= 64)
        {
            return -1;
        }
        else if (user_word[i] >= 91  && user_word[i] <=96 )
        {
            return -1;
        }
        else if (user_word[i] >= 123  && user_word[i] <= 127)
        {
            return -1;
        }
        else; //ignore letters that are already capital
    }

    while(fin)
    {
        getline(fin, x);
        splitOnSpace (x, a, p);
        
        if (user_word == a)
        {
            cout << "Pronunciation: " << p << endl<< endl;
            pron = p;
            found = true;
        }
    }
    
    if (found == false)
    {
        cout << "Not found" << endl;
        exit(1);
    }
    
    fin.close();
    
    fin.open("cmudict.0.7a");

//identical
    while(fin)
    {
        getline(fin, x);
        splitOnSpace (x, a, p);
        if (pron == p && a != user_word)
         {
            identical = identical + a + " ";
            found = true;
         }
    }
    
    if (found == false)
    {
       cout << "Not found" << endl;
    }
    
    cout << "Identical: " << identical << endl;//print identical
    fin.close();//close file
    
    
    fin.open("cmudict.0.7a");//open file to start from beginning again
    
//this is replace phoneme   
    string rep = " ";
    while(fin)
    {
        getline(fin,x);
        splitOnSpace(x,a,p);
        string pron2 = pron; //new variable to store old
        string phon1, phon2;
        int space1 = counting(p);
        int space2 = counting(pron);
        int space3 = space1 + 1;
        int c = 0;
        
        while (space3 > 0)
        {
            splitOnSpace(pron2, phon1, pron2);
            splitOnSpace(p, phon2, p);
            if(phon2 != phon1)
            {
                c++;
            }
            space3--;
        }
        
        if (valid(a) && c == 1 && (space1 == space2)) 
        {
            rep = rep + a + " ";
        }
    }
    cout << "Replace phoneme: " << rep << endl;
    
    fin.close();//close file to start over again

    //we adding phonemes 
    fin.open("cmudict.0.7a");//open again
    
    string add = " ";
    while (fin)
    {
        getline(fin, x);
        splitOnSpace(x,a,p);
        string pron2 = pron;
        string phon1, phon2;
        int space1 = counting(p); //make function to make easier
        int space2 = counting(pron);
        int space3 = space1 + 1;
        int space4 = counting(pron) + 1;
        int c = 0;
        
        while (space3 > 0)
        {
            splitOnSpace(pron2, phon1, pron2);
            splitOnSpace(p, phon2, p);
            if(phon2 != phon1)
            {
                c++;
                splitOnSpace(p, phon2, p);
                if (phon2 != phon1) 
                {
                    c++;
                }
            }
            space3--;
        }
        
        if (valid(a) && c == 1  && (space1 == space4))
        {
            add = add + a + " ";
        }
    }
    
    cout << "Add phoneme: " << add << endl;
    
    fin.close();//close again

    fin.open("cmudict.0.7a");//open again

 //remove phoneme
    string remov = " ";

   while (fin)
    {
        getline(fin, x);
        splitOnSpace(x,a,p);
        string pron2 = pron;
        string phon1, phon2;
        int space1 = counting(p);
        int space2 = counting(pron);
        int space3 = space1 + 1;
        int c = 0;
        
        for(int i = 0; i <= space3 ;i++) {
            splitOnSpace(pron2, phon1, pron2);
            splitOnSpace(p, phon2, p);
            if (phon2 != phon1) 
            {
                c++;
                splitOnSpace(pron2, phon1, pron2);
                if (phon2 != phon1) 
                {
                    c++;    
                }
            }
        }
        
        if ((valid(a) && c == 1) && (space3 == space2)) 
        {
            remov = remov + a + " ";
        } 
    }
    cout << "Remove phoneme   : " << remov << endl; 
    
    return 0;
}