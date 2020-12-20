#include <iostream>
#include <bits/stdc++.h>

using namespace std ;

bool check_astar(string s){

	if(s.length()==0){
		return true ;
	}

	int dfa=0 ;
	int len=s.length() ;
	for(int i=0;i<len;i++){
		if(s[i]=='a'){
			dfa=1 ;
		} else {
			dfa=-1 ;
			break ;
		}
	}
	if(dfa==1){
		return true ;
	} else {
		return false ;
	}
}

bool check_astar_bplus(string s){

	if(s.length()==0){
		return false ;
	}

	int len=s.length() ;
	int dfa=0 ;
	for(int i=0;i<len;i++){
		if(s[i]=='a' && dfa==0){
			dfa=0 ;
		} else if(s[i]=='b' && dfa==0){
			dfa=1 ;
		} else if(s[i]=='a' && dfa==1){
			dfa=-1 ;
			break ;
		} else if(s[i]=='b' && dfa==1){
			dfa=1 ;
		}
	}

	if(dfa==1){
		return true ;
	} else {
		return false ;
	}
}

int main(){


	string inp ;
	cout<<"Enter an input string : " ;
	getline(cin,inp) ;


	if(check_astar(inp)){
		cout<<inp<<" is accepted under rule 'a*'"<<endl ;
	}
	if(check_astar_bplus(inp)){
		cout<<inp<<" is accepted under rule 'a*b+'"<<endl ;
	}

	return 0 ;
}