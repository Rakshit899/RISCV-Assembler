#include<bits/stdc++.h>
using namespace std;
string opcode(string a){
    // if(a=="add" || a=="sub" || a=="xor" || a=="mul" || a=="div" || a=="rem" || a=="srl" || a=="sll" || a=="slt" || a=="or" || a=="and" || a=="sra"){
    if(a=="R"){
        return "0110011";
    }
    else if(a=="S"){
        return "0100011";
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
    else if(a=="or"){
        return "110";
    }
    else if(a=="and"){
        return "111";
    }
    else if(a=="sd"){
        return "011";
    }

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
    // Chances of mistake
    a=a.substr(1);
    int decimalNumber=atoi(a.c_str());
    stringstream ss;
    ss << hex << decimalNumber;
    string ans=ss.str();
    while(ans.size()<5){
        ans="0"+ans;
    }
    return ans;
}
string immediate(string a){
    int decimalNumber=atoi(a.c_str());
    stringstream ss;
    ss << hex << decimalNumber;
    string ans=ss.str();
    while(ans.size()<12){
        ans="0"+ans;
    }
    return ans;
}
string R_format(string operation,string rd,string rs1,string rs2){
    // Can't find mul, div
    // mul,div,add,rem-> same opcode,func7 mul,div-> different func3
    // add-> 0x003100B3
    // mul-> 0x023100B3 -> func3=000
    // div-> 0x023140B3 -> func3=100
    // rem-> 0x023160B3
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
int main(){
    
    return 0;
}
