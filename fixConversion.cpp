// Abhishek Rathod.
// Enroll No. - 17114004
// This program take in an infix expression as input and gives its prefix and postfix expressions as output.

#include <iostream>
#include <bits/stdc++.h>

using namespace std ;

int precedence(char c){

	if(c=='^'){
		return 3 ;
	} else if(c=='*' || c=='/'){
		return 2 ;
	} else if(c=='+' || c=='-'){
		return 1 ;
	} else {
		return -1 ;
	}
}

int main(){

	cout<<"Enter the infix expression : ";
	string inf;
	cin>>inf ;
	string post="" ;
	stack<char> st ;
	for(int i=0;i<inf.length();i++){
		if(isalpha(inf[i])){
			post+=inf[i] ;
		} else if(inf[i]=='(' || st.empty()) {
			st.push(inf[i]) ;
		} else if(precedence(inf[i])>precedence(st.top())){
			st.push(inf[i]) ;
		}else if(inf[i]==')'){
			while(st.top()!='('){
				post+=st.top() ;
				st.pop() ;
			}
			st.pop() ;
		} else {
			while(precedence(inf[i])<=precedence(st.top())){
				post+=st.top() ;
				st.pop() ;
				if(st.empty()){
					break ;
				}
			}
			st.push(inf[i]) ;
		}
	}

	while(!st.empty()){
		post+=st.top() ;
		st.pop() ;
	}

	cout<<"The postfix expression is : "<<post<<endl ;

	stack<string> st1 ;
	string pre="" ;

	for(int i=0;i<post.length();i++){
		if(isalpha(post[i])){
			st1.push(string(1,post[i])) ;
		} else {
			string op1=st1.top() ;
			st1.pop() ;
			string op2=st1.top() ;
			st1.pop() ;
			string temp=string(1,post[i])+op2+op1 ;
			st1.push(temp) ;
		}
	}

	pre=st1.top() ;
	cout<<"The prefix expression is : "<<pre<<endl ;
	return 0 ;
}