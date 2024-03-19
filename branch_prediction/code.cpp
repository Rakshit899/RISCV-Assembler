#include<bits/stdc++.h>
using namespace std;
bool last_taken=true;
int num_single=0,num_double=0,num_all_taken=0,num_all_not=0;
void single_bit(bool taken){
    if(taken==last_taken){
        num_single++;
    }
    last_taken=taken;
}
void always_taken(bool taken){
    if(taken==true){
        num_all_taken++;
    }
}
void always_not_taken(bool taken){
    if(taken==false){
        num_all_not++;
    }
}
int main(){

    return 0;
}