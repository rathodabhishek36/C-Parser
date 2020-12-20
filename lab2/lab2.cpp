// Abhishek Rathod
// 17114004

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <streambuf>

using namespace std ;


string type(string s, unordered_set<string> keywords){
    
    if(keywords.find(s)!=keywords.end()){
        return "Keyword" ;
    } else {
        return "Identifier" ;    
    }

}


string getString(char x)  { 
    string s(1, x); 
    return s;    
} 


int main(){

	string prgm ; 
    
    ifstream input_file("inp_lab2.txt");
    ofstream output_file ;

    if(input_file){
		ostringstream ss ;
		ss<<input_file.rdbuf() ;
		prgm = ss.str() ;
    }

    unordered_set<string> keywords = {
        "auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char",
        "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "do", "if",
        "static", "void", "default", "goto", "sizeof", "volatile", "asm", "bool", "catch", "class", "const_cast", "delete",
        "dynamic_cast", "explicit", "export", "false", "friend", "inline", "mutable", "namespace", "new", "operator", "private",
        "protected", "public", "reinterpret_cast", "static_cast", "template", "this", "throw", "true", "try", "typeid", "typename",
        "using", "virtual", "wchar_t" } ;

    unordered_set<string> special_sym = {
        "(", ")", "[", "]", "{", "}", ",", ";", "*", "=", "#", "\'", "\""
    } ;

    unordered_set<string> operators = {
        "++", "--", "+", "-", "/", "%", "<", "<=", "==", ">", ">=", "!=", "&&", "||", "!", "|", "&", "<<", ">>", "~", "^", "+=", "-=", "*=",
        "/=", "%=", "?", ":"
    } ;

    int len=prgm.length() ;

    string word="" ;

    string answer="" ;

    for(int i=0;i<len;i++){

        if(prgm[i]==' ' || prgm[i]=='\n' || prgm[i]=='\t'){
            if(prgm[i]=='\n'){
                answer = answer + "\n" ;
            }
            if(word==""){
                continue ;
            } else {
                answer=answer+type(word, keywords)+" " ;
                word="" ;
            }
        } else {

            if(special_sym.find(getString(prgm[i]))!=special_sym.end()) {

                if(prgm[i]=='='){
                    if(prgm[i+1]=='='){
                        if(word==""){
                            answer = answer + "Operator " ;
                        } else {
                            answer = answer + type(word, keywords) + " Operator " ;
                            word="" ;
                            i++ ;
                        }
                    } else {
                        if(word==""){
                            answer = answer + "Special character " ;
                        } else {
                            answer = answer + type(word, keywords) + " Special character " ;
                            word="" ;
                        }    
                    }
                } else if(prgm[i]=='\"'){
                    answer = answer + "String " ;
                    i++ ;
                    
                    while(prgm[i]!='\"'){
                        i++ ;
                    }

                } else if(prgm[i]=='\''){
                    
                    answer = answer + "Character " ;
                    i++ ;
                    
                    while(prgm[i]!='\''){
                        i++ ;
                    }

                } else {
                    if(word==""){
                        answer = answer + "Special character " ;
                    } else {
                        answer = answer + type(word, keywords) + " Special character " ;
                        word="" ;
                    }
                }
                

            } else if(((int)prgm[i]>=65 && (int)prgm[i]<=90) || ((int)prgm[i]>=97 && (int)prgm[i]<=122) || ((int)prgm[i]==95)) {
                
                while(((int)prgm[i]>=65 && (int)prgm[i]<=90) || ((int)prgm[i]>=97 && (int)prgm[i]<=122) || ((int)prgm[i]==95)
                     || ((int)prgm[i]>=48 && (int)prgm[i]<=57)){

                    word=word+prgm[i] ;
                    i++ ;    
                }
                i-- ;
            
            } else if((int)prgm[i]>=48 && (int)prgm[i]<=57){

                while((int)prgm[i]>=48 && (int)prgm[i]<=57){
                    i++ ;
                }

                i-- ;
                answer = answer + "Constant " ;

            } else if(operators.find(getString(prgm[i])) != operators.end()){

                string temp=getString(prgm[i])+getString(prgm[i+1]) ;
                
                if(operators.find(temp) != operators.end()){

                    if(word==""){
                        answer = answer + "Operator " ;    
                    } else {
                        answer = answer + type(word, keywords)+ " Operator " ;
                        word="" ;
                    }
                    
                    i++ ;
                } else {
                    if(word==""){
                        answer = answer + "Operator " ;    
                    } else {
                        answer = answer + type(word, keywords) + " Operator " ;
                        word="" ;
                    }
                    
                }

            }
            
        }
        
    }

    output_file.open("out_lab2.txt") ;
    output_file<<answer ;
    output_file.close() ;

	return 0 ;
}