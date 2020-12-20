// Abhishek Rathod
// Enroll. No. - 17114004
// This program takes input a grammar and a string and produces a LL parse through it using the LL(1) parsing table. 

#include <iostream>
#include <bits/stdc++.h>

using namespace std ;

unordered_map<char,vector<string> > productions ;
unordered_set<char> non_terminals ;
unordered_set<char> terminals ;

unordered_map<char,set<char> > FIRST ;
unordered_map<char,set<char> > FOLLOW ;

map<pair<char,char>, string> parsing_table ;

// are there any changes taking place in the FIRST/FOLLOW in one iteration
bool changes_in_first=true ;
bool changes_in_follow=true ;

string char_to_str(char c){
	string s(1,c) ;
	return s ;
}

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


void print_follow(){

	cout<<endl ;
	for(auto i=FOLLOW.begin();i!=FOLLOW.end();i++){
		if(i->first=='@'){
			continue ;
		}
		cout<<"FOLLOW("<<i->first<<") = {" ;
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


void insert_FOLLOW(char c, set<char> inp){

	int size_ini=FOLLOW[c].size() ;
	for(auto i=inp.begin();i!=inp.end();i++){
		if(*i=='@'){
			continue ;
		}
		FOLLOW[c].insert(*i) ;
	}
	int size_fin=FOLLOW[c].size() ;

	if(size_ini != size_fin){
		changes_in_follow=true ;
	}
}


void find_follow(){

	for(auto i=productions.begin();i!=productions.end();i++){
		char non_term = i->first ;
		vector<string> v = i->second ;

		for(int j=0;j<v.size();j++){
			string body=v[j] ;
			for(int k=body.length()-1;k>=0;k--){
				if(terminals.find(body[k])==terminals.end() && body[k]!='@'){
					if(k==body.length()-1){
						set<char> inp=FOLLOW[non_term] ;
						insert_FOLLOW(body[k],inp) ;

					} else {
						insert_FOLLOW(body[k],FIRST[body[k+1]]) ;
						int t=k+1 ;
						while(FIRST[body[t]].find('@')!=FIRST[body[t]].end() && t<=body.length()-1){
							if(t==body.length()-1){
								insert_FOLLOW(body[k],FOLLOW[non_term]) ;
								break ;
							}
							insert_FOLLOW(body[k],FIRST[body[t+1]]) ;
							t++ ;
						}
					}
				}
			}
		}
	}
}

void print_table(){

	cout<<"The LL(1) Parsing Table for the given grammar is : "<<endl ;
	for(auto i=parsing_table.begin();i!=parsing_table.end();i++){
		pair<char,char> p=i->first ;
		string body=i->second ;
		cout<<"{"<<p.first<<","<<p.second<<"} -> "<<body<<endl ;
	}
	cout<<endl ;
}

void make_parsing_table(){

	for(auto i=productions.begin();i!=productions.end();i++){
		char non_term=i->first ;
		vector<string> prods=i->second;
		for(int j=0;j<prods.size();j++){
			string body=prods[j] ;
			set<char> first; // will hold the FIRST of the body of present production
			int if_epsilon=0 ;
			
			for(int k=0;k<body.length();k++){
				first.insert(FIRST[body[k]].begin(),FIRST[body[k]].end()) ;
				if(FIRST[body[k]].find('@')!=FIRST[body[k]].end()){
					if_epsilon++ ;
					first.erase('@') ;
				} else {
					break ;
				}
			}
			
			if(if_epsilon==body.length()){
				first.insert('@') ;
			}

			for(auto m=first.begin();m!=first.end();m++){
				if(*m=='@'){
					for(auto n=FOLLOW[non_term].begin();n!=FOLLOW[non_term].end();n++){
						pair<char,char>p = make_pair(non_term,*n) ;
						string s(1,non_term) ;
						s=s+"/"+body ;
						parsing_table.insert({p,s});	
					}
				} else {
					pair<char,char>p = make_pair(non_term,*m) ;
					string s(1,non_term) ;
					s=s+"/"+body ;
					parsing_table.insert({p,s});
				}
			}
		}
	}
}

void print_parse(string inp, string s_cont){

	cout<<inp<<"        " ;
	cout<<s_cont<<endl ;
}


void parse_input(string inp, string inp_ins, char start_sym){
	
	inp=inp+"$" ;
	inp_ins=inp_ins+"$" ;

	stack<char> st ;
	st.push('$') ;
	st.push(start_sym) ;
	string stack_cont=char_to_str(start_sym)+"$" ;
	
	cout<<endl ;
	cout<<"Input        Stack"<<endl ;
	cout<<endl ;

	print_parse(inp_ins,stack_cont) ;

	while(!st.empty()){	
		if(st.top()==inp[0]){
			st.pop() ;
			stack_cont.erase(stack_cont.begin()) ;
			inp.erase(inp.begin()) ;
			inp_ins.erase(inp_ins.begin()) ;
		} else {
			pair<char,char> p=make_pair(st.top(),inp[0]) ;
			string prod=parsing_table[p] ;	
			string body=prod.substr(2,prod.length()-2) ;
			st.pop() ;
			stack_cont.erase(stack_cont.begin()) ;
			for(int i=body.length()-1;i>=0;i--){
				st.push(body[i]) ;
				stack_cont.insert(0,char_to_str(body[i])) ;
			}
		}
		if(!st.empty() && st.top()=='@'){
			st.pop() ;
			stack_cont.erase(stack_cont.begin()) ;
		}
		print_parse(inp_ins,stack_cont) ;
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

// Taking the start symbol as input for the FOLLOW set initialization.
	char start ;
	cout<<"Enter Start Symbol(To assign '$' while calculating FOLLOW) : ";
	cin>>start ;

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

	FOLLOW[start].insert('$') ;

	for(auto i=terminals.begin();i!=terminals.end();i++){
		set<char> s ;
		s.insert(*i) ;
		FIRST.insert({*i,s}) ;
	}

	// inserting @(epsilon) in the first set for convenience.
	set<char> s={'@'};
	FIRST.insert({'@',s}) ;

	print_prod() ;

	// finding the FIRST and then printing it.
	while(changes_in_first){
		changes_in_first=false ;
		find_first() ;	
	}
	// print_first() ;

	// finding the FOLLOW and then printing it.
	while(changes_in_follow){
		changes_in_follow=false ;
		find_follow() ;
	}
	// print_follow() ;

	// to make and print the LL(1) parsing table.
	make_parsing_table() ;
	print_table() ;

	string input_ins ;
	cout<<"Enter the string to be parsed : " ;
	cin>>input_ins ;

	// converting the numerical instances to respective token : i
	string input="" ;
	for(int j=0;j<input_ins.size();j++){
	    if(input_ins[j]>='0' && input_ins[j]<='9'){
	    	input+="i";
		} else {
			input+=input_ins[j] ;
		}
	}

	parse_input(input,input_ins,start) ;

	return 0 ;
}