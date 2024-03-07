#include<bits/stdc++.h>
using namespace std;
bool error=false;
unordered_map<string,string>  mp={{"sp","x2"},{"gp","x3"},{"tp","x4"},{"ra","x1"}}
string opcode(string a){
    // if(a=="add" || a=="sub" || a=="xor" || a=="mul" || a=="div" || a=="rem" || a=="srl" || a=="sll" || a=="slt" || a=="or" || a=="and" || a=="sra"){
    if(a=="R"){
        return "0110011";
    }
    else if(a=="S"){
        return "0100011";
    }
    else if(a=="addi" || a=="andi" || a=="ori"){
            return "0010011";
    }
    else if(a=="lb" || a=="ld" || a=="lw" || a=="lh"){
            return "0000011";
    }
    else if(a=="jalr"){
            return "1100111";
    }
    else if(a=="auipc"){
        return "0010111";
    }
    else if(a=="lui"){
        return "0110111";
    }
    return "";
}
string func3(string a){
    if(a=="add" || a=="sub" || a=="mul" || a=="sb"){
        return "000";
    }
    else if(a=="xor" || a=="div"){
        return "100";
    }
    else if(a=="srl"){
        return "101";
    }
    else if(a=="sra"){
        return "101";
    }
    else if(a=="sll" || a=="sh"){
        return "001";
    }
    else if(a=="slt" || a=="sw"){
        return "010";
    }
    else if(a=="or" || a=="rem"){
        return "110";
    }
    else if(a=="and"){
        return "111";
    }
    else if(a=="sd"){
        return "011";
    }
    else if(a=="lb" || a=="jalr" || a=="addi"){
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
    return "";
}
string func7(string a){
    if(a=="add" || a=="sll" || a=="slt" || a=="xor" || a=="srl" || a=="or" || a=="and"){
        return "0000000";
    }
    else if(a=="mul" || a=="div" || a=="rem"){
        return "0000001";
    }
    else if(a=="sub" || a=="sra"){
        return "0100000";
    }
    return "";
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
    return "";
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
    return "";
}

string immediate_U(string a){
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
    return "";
}

string U_format(string a,string operation,string rd,string imme){
    string ans="0x";
    ans+=immediate(imme);
    ans+=register_num(rd);
    ans+=opcode(operation);
    return ans;
}

string R_format(string operation,string rd,string rs1,string rs2){
    // Can't find mul, div
    // mul,div,add,rem-> same opcode,func7 mul,div-> different func3
    // add-> 0x003100B3
    // mul-> 0x023100B3 -> func3=000
    // div-> 0x023140B3 -> func3=100
    // rem-> 0x023160B3 -> func3=110
    string ans="0x";
    ans+=func7(operation);
    ans+=register_num(rs2);
    ans+=register_num(rs1);
    ans+=func3(operation);
    ans+=register_num(rd);
    ans+=opcode("R");
    return ans;
}
string S_format(string operation,string rs2,string rs1,string imm){
    // I have considered sd as S format -> DOUBTFULL
    string ans="0x";
    imm=immediate(imm);
    string imm1=imm.substr(5),imm2=imm.substr(0,5);
    reverse(imm1.begin(),imm1.end());
    reverse(imm2.begin(),imm2.end());
    ans+=imm1;
    ans+=register_num(rs2);
    ans+=register_num(rs1);
    ans+=func3(operation);
    ans+=imm2;
    ans+=opcode("S");
    return ans;
}

string I_format(string operation,string rd,string rs1, string imme){
    string ans="0x";    
    ans=immediate(imme);
    ans+=register_num(rs1);
    ans+=funct3(operation);
    ans+=register_num(rd);
    ans+=opcode(operation);
    return ans;
}

string SB_format(string operation,string rd,string rs1, string rs2, string imm){
    string ans="0x";
    imm=immediate(imm);
    ans+=imm[0];            //12
    ans+=imm.substr(2,6);   //10:5
    ans+=register_num(rs2);
    ans+=register_num(rs1);
    ans+=funct3(operation);
    ans+=imm.substr(8,4);   //4:1
    ans+=imm[1];            //11
    ans+=opcode(operation);
    return ans;
}

string UJ_format(string operation,string rd,string rs1, string imm){
    string ans="0x";
    imm=immediate(imm);
    ans+=imm[0];            //20
    ans+=imm.substr(10,10); //10:5
    ans+=imm[9];            //11
    ans+=imm.substr(1,8);   //19:12
    ans+=register_num(rd);
    ans+=opcode(operation);
    return ans;
}

int main(){
    
    return 0;
}
