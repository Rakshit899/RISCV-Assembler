#include<bits/stdc++.h>
using namespace std;
string opcode(string a){
    if(a=="addi" || a=="andi" || a=="ori"){
            return "0010011";
    }
    else if(a=="lb" || a=="ld" || a=="lw" || a=="lh"){
            return "0000011";
    }
    else if(a=="jalr"){
            return "1100111";
    }
    return "error";
}

string funct3(string a){
    if(a=="lb" || a=="jalr" || a=="addi"){
        return "000";
    }
    else if(a=="lh"){
        return "001";
    }
    else if(a=="lw"){
        return "010";
    }
    else if(a=="ld"){
        return "011";
    }
    else if(a=="ori"){
        return "110";
    }
    else if(a=="andi"){
        return "111";
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
    if(imm<0){
        imm = 4096 +imm;
    }
    if(imm>=0 && imm<4096){
        string ans;
        for(int i=0;i<12;i++){
            ans+=('0' + imm%2);
            imm/=2;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
    return "error";
}

string I_format(string a,string operation,string rd,string rs1, string imme){
    string ans="0x";
    ans+=immediate(imme);
    ans+=register_num(rs1);
    ans+=funct3(operation);
    ans+=register_num(rd);
    ans+=opcode(operation);
    return ans;
}

int main(){
    
    return 0;
}