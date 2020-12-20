// Abhishek Rathod.
// Enroll. No. - 17114004

#include <iostream>
#include <bits/stdc++.h>

using namespace std ;

unordered_map<char,vector<string> > productions ;
unordered_set<char> non_terminals ;
unordered_set<char> terminals ;
unordered_set<char> gram_symbols ;

// Start Symbol for the grammar
string START_SYM ;

vector<pair<string,vector<string> > > lr0_names_items ; // map for names and items. ex. I0->(some item)

vector<vector<string> > lr0_items ;

unordered_map<pair<string,char> string> slr_table;

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

vector<string> closure(vector<string> item){
	bool changes_in_item=true ;
	while(changes_in_item){

		int size_ini=item.size() ;
		
		for(int i=0;i<item.size();i++){
			string prod=item[i] ;
			char non_term=prod[0] ;

			for(int j=3;j<prod.size();j++){
				if(prod[j]=='.'){
					if(j==prod.size()-1){
						break ;
					} else {
						char next=prod[j+1] ;
						if(non_terminals.find(next)!=non_terminals.end()){
							vector<string> str=productions[next] ;

							for(int k=0;k<str.size();k++){
								if(str[k]=="@"){
									string s(1,next) ;
									s=s+"->." ;
									if(find(item.begin(),item.end(),s)==item.end()){
										item.push_back(s) ;
									}
								} else {
									string s(1,next) ;
									s=s+"->."+str[k] ;
									if(find(item.begin(),item.end(),s)==item.end()){
										item.push_back(s) ;
									} 
								}
							}
						}
					}
					break ;
				} 
			}
		}
		int size_fin=item.size() ;
		if(size_ini==size_fin){
			changes_in_item=false ;
		}
	}
	return item ;
}

vector<string> GOTO(vector<string> item, char next){

	vector<string> v;
	for(int i=0;i<item.size();i++){
		string prod=item[i] ;
		string temp="" ;
		for(int j=0;j<prod.length();j++){
			temp+=prod[j] ;
			if(prod[j]=='.' && j!=prod.length()-1){
				j++ ;
				if(prod[j]==next){
					temp.erase(temp.length()-1,1) ;
					temp+=prod[j] ;
					temp+="." ;
				} else {
					temp=prod ;
					break ;
				}
			}
		}
		if(temp!=prod){
			v.push_back(temp) ;
		}
	}
	return closure(v) ;
}

void print_lr0_items(){

	cout<<endl ;
	cout<<"There are "<<lr0_items.size()<<" LR(0) items."<<endl ;
	cout<<"Set of LR(0) items are : "<<endl ;
	for(int i=0;i<lr0_names_items.size();i++){
		cout<<"--------------------------"<<endl ;
		pair<string,vector<string> > p=lr0_names_items[i] ;
		cout<<p.first<<" :"<<endl ;
		for(int j=0;j<p.second.size();j++){
			cout<<p.second[j]<<endl ;
		}
	}
	cout<<"--------------------------"<<endl ;
}

void make_lr0_items(){

	vector<string> item ;
	item.push_back("Z->."+START_SYM) ;
	lr0_items.push_back(closure(item)) ;
	bool items_added=true ;

	while(items_added){
		items_added=false ;
		for(int i=0;i<lr0_items.size();i++){
			item=lr0_items[i] ;
			for(auto j=gram_symbols.begin();j!=gram_symbols.end();j++){
				if(!(GOTO(item,*j).empty()) && (find(lr0_items.begin(),lr0_items.end(),GOTO(item,*j))==lr0_items.end()) ){
					lr0_items.push_back(GOTO(item,*j)) ;
					items_added=true ;
				}
			}
		}	
	}
	
}

void get_SLR_table(){

	for(int i=0;i<lr0_names_items.size();i++){
		pair<string,vector<string> > p ;
		for(int j=0;j<p.second.size();j++){
			string item=p.second[j] ;
			string next="" ;
			for(int k=0;k<item.length();k++){
				if(k!='.'){
					next+=item[k] ;
				} else {
					if(k==item.length()-1){
						search_prod(next) ;
					} else {
						next+=item[k+1] ;
						next=next+"." ;
						k++ ;
					}
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

// making a set of grammar symbols
for(auto i=non_terminals.begin();i!=non_terminals.end();i++){
	gram_symbols.insert(*i) ;
}

for(auto i=terminals.begin();i!=terminals.end();i++){
	gram_symbols.insert(*i) ;
}

// Taking the start symbol for the purpose of grammar augmentation.
	cout<<"Enter Start Symbol(To augment the CFG) : ";
	cin>>START_SYM ;

	// print_prod() ;

	make_lr0_items() ;

	// assigning items their names
	for(int i=0;i<lr0_items.size();i++){
		lr0_names_items.push_back(make_pair("I"+to_string(i), lr0_items[i])) ;
	}

	print_lr0_items() ;

	get_SLR_table() ;

	return 0; 
}