#include<bits/stdc++.h>
using namespace std;
bool error=false;
unordered_map<string,string>  mp={{"sp","x2"},{"gp","x3"},{"tp","x4"},{"ra","x1"}};
string convert_to_hex(string a){
    bitset<32> b(a);
    unsigned long int x=b.to_ulong();
    stringstream ss;
    ss << hex << x;
    string hexString = ss.str();
    return hexString;
}
string opcode(string a){
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
    error=true;
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
    error=true;
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
    error=true;
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
    error=true;
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
    error=true;
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
    error=true;
    return "";
}

string U_format(string operation,string rd,string imm){
    string ans="";
    ans+=immediate(imm);
    ans+=register_num(rd);
    ans+=opcode(operation);
    if(error){
        return "";
    }
    ans=convert_to_hex(ans);
    ans="0x"+ans;
    return ans;
}

string R_format(string operation,string rd,string rs1,string rs2){
    // Can't find mul, div
    // mul,div,add,rem-> same opcode,func7 mul,div-> different func3
    // add-> 0x003100B3
    // mul-> 0x023100B3 -> func3=000
    // div-> 0x023140B3 -> func3=100
    // rem-> 0x023160B3 -> func3=110
    string ans="";
    ans+=func7(operation);
    ans+=register_num(rs2);
    ans+=register_num(rs1);
    ans+=func3(operation);
    ans+=register_num(rd);
    ans+=opcode("R");
    if(error){
        return "";
    }
    ans=convert_to_hex(ans);
    ans="0x"+ans;
    return ans;
}
string S_format(string operation,string rs2,string rs1,string imm){
    // I have considered sd as S format -> DOUBTFULL
    string ans="";
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
    if(error){
        return "";
    }
    ans=convert_to_hex(ans);
    ans="0x"+ans;
    return ans;
}

string I_format(string operation,string rd,string rs1, string imm){
    string ans="";    
    ans=immediate(imm);
    ans+=register_num(rs1);
    ans+=func3(operation);
    ans+=register_num(rd);
    ans+=opcode(operation);
    if(error){
        return "";
    }
    ans=convert_to_hex(ans);
    ans="0x"+ans;
    return ans;
}

string SB_format(string operation,string rs1, string rs2, string imm){
    string ans="";
    imm=immediate(imm);
    ans+=imm[0];            //12
    ans+=imm.substr(2,6);   //10:5
    ans+=register_num(rs2);
    ans+=register_num(rs1);
    ans+=func3(operation);
    ans+=imm.substr(8,4);   //4:1
    ans+=imm[1];            //11
    ans+=opcode(operation);
    if(error){
        return "";
    }
    ans=convert_to_hex(ans);
    ans="0x"+ans;
    return ans;
}

string UJ_format(string operation,string rd,string imm){
    string ans="";
    imm=immediate(imm);
    ans+=imm[0];            //20
    ans+=imm.substr(10,10); //10:5
    ans+=imm[9];            //11
    ans+=imm.substr(1,8);   //19:12
    ans+=register_num(rd);
    ans+=opcode(operation);
    if(error){
        return "";
    }
    ans=convert_to_hex(ans);
    ans="0x"+ans;
    return ans;
}

int main(){
    string ifilename;
    string ofilename;

    ifstream ifile(ifilename);
    ofstream ofile(ofilename);
    map<string, int> label;
    int memory_counter=0;
    vector<string>memory;
    string line;
    while (getline(ifile, line)) {
        if(line==".data"){
        while (getline(ifile, line)) {
            if(line==".text")break;
            vector<string> lineVec;
            string seg = "";
            for(int i=0;i<line.size();i++){
                if(line[i]==' ' || line[i]==',' || line[i]=='\t' || line[i] == '\n' || line[i]==':' || line[i]==EOF){
                    if(seg!=""){
                        lineVec.push_back(seg);
                    }
                    seg="";
                    continue;
                }
                seg+=line[i];
            }
            label[lineVec[0]]=memory_counter;
            if(lineVec[1]==".word"){
                int j=2;
                while(j<lineVec.size()){
                    int decimal;
                    string temp= lineVec[j];
                    if(lineVec[j][0]=='0' && lineVec[j][1]=='x'){
                         decimal = stoi(lineVec[j].substr(2),0,16);
                    }
                    else{
                        decimal= stoi(lineVec[j]);
                    }
                    stringstream ss;
                    for(int i=0;i<4;i++){
                        string hexString="";
                        if((decimal%256)==0){
                            hexString+= "00";
                        }
                        else if((decimal %256) <16){
                            hexString+= "0";
                        }
                        ss << hex << decimal%256;
                        hexString += ss.str();
                        memory.push_back(hexString);
                        memory_counter++;
                        decimal/=256;
                    }
                    j++;
                }
            }
            else if(lineVec[1]==".byte"){
                int j=2;
                while(j<lineVec.size()){
                    int decimal;
                    string temp = lineVec[j];
                    if(lineVec[j][0]=='0' && lineVec[j][1]=='x'){
                         decimal = stoi(lineVec[j].substr(2),0,16);
                    }
                    else if(lineVec[j][0]=='\''){
                        decimal = (int)lineVec[j][1];
                    }
                    else{
                        decimal= stoi(lineVec[j]);
                    }
                    stringstream ss;
                    string hexString="";
                    if((decimal) <16){
                        hexString+= "0";
                    }
                    ss << hex << decimal;
                    hexString += ss.str();
                    memory.push_back(hexString);
                    memory_counter++;
                    j++;
                }
            }
            else if(lineVec[1]==".asciiz"){
                int j=2;
                while(j<lineVec.size()){
                    int decimal;
                    if(lineVec[j][0]=='\"'){
                        for(int k=1;lineVec[j][k]!='\"';k++){
                            decimal = (int)lineVec[j][k];
                            stringstream ss;
                            string hexString="";
                            if((decimal) <16){
                                hexString+= "0";
                            }
                            ss << hex << decimal;
                            hexString += ss.str();
                            memory.push_back(hexString);
                            memory_counter++;
                        }
                    }
                    j++;
                }
            }
        }
    }
        vector<string> lineVec;

        string seg = "";
        for(int i=0;i<line.size();i++){
            if(line[i]==' ' || line[i]==',' || line[i]=='\t' || line[i] == '\n' || line[i] == '(' || line[i] == ')' || line[i]==EOF){
                if(seg == "") continue;
                lineVec.push_back(seg);
                seg="";
                continue;
            }
            seg+=line[i];
        }

        string operation = lineVec[0]; 
        string rd;
        string rs1;
        string rs2;
        string imm;

        string ans;

        if(operation=="add" || operation=="sub" || operation=="xor" || operation=="mul" || operation=="div" || operation=="rem" || operation=="srl" || operation=="sll" || operation=="slt" || operation=="or" || operation=="and" || operation=="sra"){
            rd = lineVec[1];
            rs1 = lineVec[2];
            rs2 = lineVec[3];
            ans = R_format(operation, rd, rs1, rs2);
        } else if(operation=="addi" || operation=="andi" || operation=="ori" || operation=="lb" ||  operation=="ld" ||  operation=="lh" ||  operation=="lw" ||  operation=="jalr"){
            rd = lineVec[1];
            rs1 = lineVec[2];
            rs2 = lineVec[3];
            ans = I_format(operation, rd, rs1, imm);
        } else if(operation=="sb" || operation=="sw" || operation=="sd" || operation=="sh"){
            rs2 = lineVec[1];
            imm = lineVec[2];
            rs1 = lineVec[3];
            ans = S_format(operation, rs2, rs1, imm);
        } else if(operation=="beq" || operation=="bne" || operation=="bge" || operation=="blt"){
            rs1 = lineVec[1];
            rs2 = lineVec[2];
            imm = lineVec[3];
            ans = SB_format(operation, rs2, rs1, imm);
        } else if(operation=="jal"){
            rd = lineVec[1];
            imm = lineVec[2];
            ans = UJ_format(operation, rd, imm);
        } else if(operation=="auipc" || operation=="lui"){
            rd = lineVec[1];
            imm = lineVec[2];
            ans = U_format(operation, rd, imm);
        }

        if(error){
            cout<<"Error Occured!"<<endl;
            break;
        }
        ofile << ans << "\n";
    }

    ifile.close();
    ofile.close();

    return 0;
}
