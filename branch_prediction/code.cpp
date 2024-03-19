#include<bits/stdc++.h>
using namespace std;
// vector<int> single,two,all_taken,all_not;
map<int, pair<bool,bool>>two_bit_map;
unordered_map<int,bool> single_bit_map;
int num_single=0,num_double=0,num_all_taken=0,num_all_not=0;
void single_bit(int pc,bool taken){
    if(taken==single_bit_map[pc]){
        num_single++;
    }
    else{
        single_bit_map[pc]=taken;
    }
}
int main(){

    return 0;
}