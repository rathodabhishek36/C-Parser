
// Abhishek Rathod
// 17114004

// C++ program to remove comments and blank spaces from a C/C++ program
// The program takes input from a file named inp_lab1.cpp and writes the output in the file out_lab1.txt

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <streambuf>
#include <string>      

using namespace std;
  
  
int main()
{
    string prgm ; 
    
    ofstream output_file;
    ifstream input_file("inp_lab1.cpp");
    
    if(input_file){
	ostringstream ss ;
	ss<<input_file.rdbuf() ;
	prgm = ss.str() ;
    }
	
    int len = prgm.length();
    string res;
  
    bool s_cmt = false;
    bool m_cmt = false;
    bool quote = false ;
  
    for (int i=0; i<len; i++)
    {   
	
        if (s_cmt == true && prgm[i] == '\n')
            s_cmt = false;
  
        else if  (m_cmt == true && prgm[i] == '*' && prgm[i+1] == '/')
            m_cmt = false,  i++;
  
        else if (s_cmt || m_cmt)
            continue;
  
        else if (prgm[i] == '/' && prgm[i+1] == '/' && !quote)
            s_cmt = true, i++;

        else if (prgm[i] == '/' && prgm[i+1] == '*' && !quote)
            m_cmt = true,  i++;
  	
	else if (prgm[i]=='\"'){
	    quote=(!quote) ;
	    res += prgm[i] ;
	}
        else  res += prgm[i];
    }

    string modified="" ;

    len = res.length() ;
    for(int i=0;i<len;i++){
	if(res[i]==' ' || res[i]=='\n' || res[i]=='\t'){
	    continue ;
	} else {
	    modified=modified+res[i] ;	
	}
    }
  

    output_file.open("out_lab1.txt") ;
    output_file<<modified;
    output_file.close() ;
    return 0;
}

