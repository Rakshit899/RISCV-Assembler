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
    string ifilename1 = "actual_pc.txt";
    string ifilename2 = "machine_code.txt";

    ifstream ifile1(ifilename1);
    ifstream ifile2(ifilename2);

    if (!ifile1.is_open() || !ifile2.is_open()) {
        cout << "Error opening files." << endl;
        return 1;
    }

    vector<int> pc;

    string line1;
    while (getline(ifile1, line1)) {
        if(line1.size() == 0) continue;
        int value = stoi(line1, nullptr, 2);
        pc.push_back(value);
    }

    string line2;

    vector<int> target;

    while (getline(ifile2, line2)) {
        if(line2.size() == 0) continue;
        string opcode = line2.substr(32-7, 7);
        if(opcode == "1100011"){
            string imm(13, '0');
            imm[12-12] = line2[31-31];
            imm[12-11] = line2[31-7];
            for(int i = 31-25, j = 12-5; i >= 31-30, j >= 12-10; i--, j--){
                imm[j] = line2[i];
            }
            for(int i = 31-8, j = 12-1; i >= 31-11, j >= 12-4; i--, j--){
                imm[j] = line2[i];
            }
            int value = stoi(imm, nullptr, 2);
            if(imm[0]=='1'){
                value= value - pow(2,13);
            }
            target.push_back(value);

        } else {
            target.push_back(0);
        }
    }

    vector<bool> choice;

    for(int i = 0; i < pc.size()-1; i++){
        if(pc[i+1]-pc[i] == target[i]){
            choice.push_back(1);
        } else {
            choice.push_back(0);
        }
    }

    for(auto x : choice){
        cout << x << " ";
    }

    ifile1.close();
    ifile2.close();

}
