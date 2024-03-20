#include<bits/stdc++.h>
using namespace std;
bool last_taken=false;
string two="";
bool two_bit_current=false, two_bit_prev=false;
int num_single=0,num_double=0,num_all_taken=0,num_all_not=0;
map<int , string> single_bit_history, two_bit_history, taken_history, not_history;

void single_bit(int pc,bool taken){
    if(taken==last_taken){
        num_single++;
    }
    if(last_taken){
        single_bit_history[pc]+="T";
    }
    else{
        single_bit_history[pc]+="N";
    }
    last_taken=taken;
    
}
void always_taken(int pc,bool taken){
    if(taken==true){
        num_all_taken++;
    }
    taken_history[pc]+="T";
}
void always_not_taken(int pc,bool taken){
    if(taken==false){
        num_all_not++;
    }
    not_history[pc]+="N";
}

void two_bit(int pc, bool taken){
    
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
    if(predict){
        two_bit_history[pc]+="T";
        two+="T";
    }
    else{
        two+="N";
        two_bit_history[pc]+="N";
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
    map<int,string> history;
    int j=0;
    int branch=0;
    string abc="";
    for(int i=0;i<target.size();i++){
        if(target[i]){
            single_bit(pc[i],(bool)choice[i]);
            two_bit(pc[i],(bool)choice[i]);
            always_taken(pc[i],(bool)choice[i]);
            always_not_taken(pc[i],(bool)choice[i]);
            if(choice[i]){
                history[pc[i]].push_back('T');
                abc+='T';
            }
            else{
                history[pc[i]].push_back('N');
                abc+='N';
            }
            branch++;
        }
    }
    cout<<"overall history "<<abc<<endl;
    cout<<"Two "<<two<<endl;
    for(auto it=history.begin();it!=history.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }cout<<endl;
    for(auto it=two_bit_history.begin();it!=two_bit_history.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }cout<<endl;
    for(auto it=single_bit_history.begin();it!=single_bit_history.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }cout<<endl;
    for(auto it=taken_history.begin();it!=taken_history.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }cout<<endl;
    for(auto it=not_history.begin();it!=not_history.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }
    cout<<"Accuracy of single bit branch predictor: "<<((float)num_single/branch)*100<<endl;
    cout<<"Accuracy of two bit branch predictor: "<<((float)num_double/branch)*100<<endl;
    cout<<"Accuracy of always not taken bit branch predictor: "<<((float)num_all_not/branch)*100<<endl;
    cout<<"Accuracy of always taken bit branch predictor: "<<((float)num_all_taken/branch)*100<<endl;
    ifile1.close();
    ifile2.close();
    cout<<"x";
}
