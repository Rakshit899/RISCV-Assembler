#include<bits/stdc++.h>
using namespace std;
string opcode(string a){
    if(a=="auipc"){
        return "0010111";
    }
    else if(a=="lui"){
        return "0110111";
    }
    return "error";
}

string register_num(string a){
    string reg_string;
    for(int i=1;i<a.size();i++){
        reg_string+= a[i];
    }
    int reg_no= stoi(reg_string);
    if(reg_no>=0 && reg_no<32){
        string ans;
        for(int i=0;i<5;i++){
            ans+= ('0'+reg_no%2);
            reg_no/=2;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
    return "error";
}

string immediate(string a){
    int imm= stoi(a);
    if(imm>=0 && imm<1048576){
        string ans;
        for(int i=0;i<20;i++){
            ans+=('0' + imm%2);
            imm/=2;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
    return "error";
}

string U_format(string a,string operation,string rd,string imme){
    string ans="0x";
    ans+=immediate(imme);
    ans+=register_num(rd);
    ans+=opcode(operation);
    return ans;
}

int main(){
    
    return 0;
}