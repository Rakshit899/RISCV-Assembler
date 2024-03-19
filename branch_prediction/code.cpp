#include<bits/stdc++.h>
using namespace std;
bool last_taken=false;
bool two_bit_current=false, two_bit_prev=false;
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

void two_bit( bool taken){
    bool predict;
    if(two_bit_prev == two_bit_current ){
        predict = two_bit_prev;
        two_bit_prev=taken;
    }
    else{
        predict = two_bit_current;
        if(taken == two_bit_prev){
            two_bit_current= taken;
        }
        else{
            two_bit_prev= taken;
        }
    }
    if(predict == taken) num_double++;
}

int main(){

    return 0;
}
