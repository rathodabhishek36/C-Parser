// Abhishek Rathod
// Enroll. No. - 17114004
// A CPP program to find the FIRST set of symbols in a CFG. 

#include <iostream>
#include <bits/stdc++.h>

using namespace std ;

unordered_map<char,vector<string> > productions ;
unordered_set<char> non_terminals ;
unordered_set<char> terminals ;

unordered_map<char,set<char> > FIRST ;

// are there any changes taking place in the FIRST in one iteration
bool changes_in_first=true ;


void print_prod(){

	cout<<endl ;
	for(auto i=productions.begin();i!=productions.end();i++){
		cout<<i->first<<" -> " ;
		for(int j=0;j<(i->second).size();j++){
			cout<<i->second[j]<<"/" ;
		}
		cout<<"\b"<<endl ;
	}
	cout<<endl ;
}


void print_first(){

	cout<<endl ;
	for(auto i=FIRST.begin();i!=FIRST.end();i++){
		if(i->first=='@'){
			continue ;
		}
		cout<<"FIRST("<<i->first<<") = {" ;
		for(auto j=(i->second).begin();j!=(i->second).end();j++){
			cout<<*j<<"," ;
		}
		cout<<"\b}."<<endl ;
	}
	cout<<endl ;
}

void insert_FIRST(char non_term, set<char> inp){

	int size_ini = FIRST[non_term].size() ;
	for(auto i=inp.begin();i!=inp.end();i++){
		FIRST[non_term].insert(*i) ;
	}
	int size_fin = FIRST[non_term].size() ;
	
	if(size_fin!=size_ini){
		changes_in_first=true ;
	}
}

void find_first(){

	for(auto i=productions.begin();i!=productions.end();i++){
		char non_term = i->first ;
		vector<string> v = i->second ;

		for(int j=0;j<v.size();j++){
			string body=v[j] ;
			if(body=="@" && (FIRST[non_term].find('@')==FIRST[non_term].end())) {
				FIRST[non_term].insert('@') ;
				changes_in_first=true ;
			} else {
				int if_epsilon=0 ;
				for(int k=0;k<body.length();k++){
					set<char> inp=FIRST[body[k]] ;
					if(inp.find('@')!=inp.end()){
						inp.erase('@') ;
						insert_FIRST(non_term,inp) ;
						if_epsilon++ ;
					} else {
						insert_FIRST(non_term,inp) ;	
						break ;
					}
				}	
				if(if_epsilon==body.length() && (FIRST[non_term].find('@')==FIRST[non_term].end())) {
					FIRST[non_term].insert('@') ;
					changes_in_first=true ;
				}
			}
			
		}
	}
}


int main(){

	int n ;
	cout<<"Enter the number of production rules : " ;
	cin>>n ;

	for(int i=0;i<n;i++){
		string s ;
		cin>>s ;
		non_terminals.insert(s[0]) ;
		string temp="" ;
		vector<string> vec ;
		for(int j=2;j<s.length();j++){
			if(s[j]!='/'){
				temp+=s[j] ;
			} else {
				vec.push_back(temp) ;
				temp="" ;
			}
			if(islower(s[j])){
				terminals.insert(s[j]) ;
			}
		}
		vec.push_back(temp) ;
		productions.insert({s[0],vec}) ;
	}

// finding the remaining terminals in the productions.
	for(auto i=productions.begin();i!=productions.end();i++){
		vector<string> v=i->second ;
		for(int j=0;j<v.size();j++){
			string body=v[j] ;
			for(int k=0;k<body.length();k++){
				if(non_terminals.find(body[k])==non_terminals.end()){
					if(body[k]!='@'){
						terminals.insert(body[k]) ;
					}
				}	
			}
		}
	}

	for(auto i=terminals.begin();i!=terminals.end();i++){
		set<char> s ;
		s.insert(*i) ;
		FIRST.insert({*i,s}) ;
	}

	// inserting @(epsilon) in the first set for convenience.
	set<char> s={'@'};
	FIRST.insert({'@',s}) ;

	// print_prod() ;

	while(changes_in_first){
		changes_in_first=false ;
		find_first() ;	
	}
	
	print_first() ;

	return 0 ;
}
