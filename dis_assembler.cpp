#include <bits/stdc++.h>
using namespace std;

ofstream outp("output.txt");

vector<string> code;
map<int,vector<int>> mp;
int line = 1;

string hex_to_binary(string s)
{
    string ans = "";
    int n = s.length();
    for(int i=0;i<n;i++)
    {
        char c = s[i];
        if(c == '0')
            ans = ans + "0000";
        else if(c == '1')
            ans = ans + "0001";
        else if(c == '2')
            ans = ans + "0010";
        else if(c == '3')
            ans = ans + "0011";
        else if(c == '4')
            ans = ans + "0100";
        else if(c == '5')
            ans = ans + "0101";
        else if(c == '6')
            ans = ans + "0110";
        else if(c == '7')
            ans = ans + "0111";
        else if(c == '8')
            ans = ans + "1000";
        else if(c == '9')
            ans = ans + "1001";
        else if(c == 'a' || c == 'A')
            ans = ans + "1010";
        else if(c == 'b' || c == 'B')
            ans = ans + "1011";
        else if(c == 'c' || c == 'C')
            ans = ans + "1100";
        else if(c == 'd' || c == 'D')
            ans = ans + "1101";
        else if(c == 'e' || c == 'E')
            ans = ans + "1110";
        else if(c == 'f' || c == 'F')
            ans = ans + "1111";
    }
    return ans;
}

int binary_to_int(string s)
{
    int n = s.length();
    int ans = 0;
    int k = 1;
    for(int i=n-1;i>=0;i--)
    {
        ans = ans + k*(s[i]-'0');
        k = k*2;
    }
    return ans;
}

int sign_binary_to_int(string s)
{
    if(s[0] == '0')
        return binary_to_int(s);
    else
        return (binary_to_int(s)-(1<<s.length()));
}

void R_type(string s)
{
    string funct7   = s.substr(0,7);
    string rs2      = s.substr(7,5);
    string rs1      = s.substr(12,5);
    string funct3   = s.substr(17,3);
    string rd       = s.substr(20,5);

    int a = binary_to_int(rd);  // rd
    int b = binary_to_int(rs1); // rs1
    int c = binary_to_int(rs2); // rs2

    if(funct3 == "000" && funct7 == "0000000")
    {
        // add instruction
        string q = "add  x" + to_string(a) + "  " + "x" + to_string(b) + "  " + "x" + to_string(c);
        code.push_back(q);
    }
    else if(funct3 == "000" && funct7 == "0100000")
    {
        // sub instruction
        string q = "sub  x" + to_string(a) + "  " + "x" + to_string(b) + "  " + "x" + to_string(c);
        code.push_back(q);
    }
    else if(funct3 == "111" && funct7 == "0000000")
    {
        // and instruction
        string q = "and  x" + to_string(a) + "  " + "x" + to_string(b) + "  " + "x" + to_string(c);
        code.push_back(q);
    }
    else if(funct3 == "110" && funct7 == "0000000")
    {
        // or instruction
        string q = "or  x" + to_string(a) + "  " + "x" + to_string(b) + "  " + "x" + to_string(c);
        code.push_back(q);
    }
    else if(funct3 == "100" && funct7 == "0000000")
    {
        // xor instruction
        string q = "xor  x" + to_string(a) + "  " + "x" + to_string(b) + "  " + "x" + to_string(c);
        code.push_back(q);
    }
    else if(funct3 == "001" && funct7 == "0000000")
    {
        // sll instruction
        string q = "sll  x" + to_string(a) + "  " + "x" + to_string(b) + "  " + "x" + to_string(c);
        code.push_back(q);
    }
    else if(funct3 == "101" && funct7 == "0000000")
    {
        // srl instruction
        string q = "srl  x" + to_string(a) + "  " + "x" + to_string(b) + "  " + "x" + to_string(c);
        code.push_back(q);
    }
    else if(funct3 == "101" && funct7 == "0100000")
    {
        // sra instruction
        string q = "sra  x" + to_string(a) + "  " + "x" + to_string(b) + "  " + "x" + to_string(c);
        code.push_back(q);
    }
}

void I_type(string s)
{
    string imm      = s.substr(0,12);
    string rs1      = s.substr(12,5);
    string funct3   = s.substr(17,3);
    string rd       = s.substr(20,5);
    string opcode   = s.substr(25,7);
    string tempimm  = s.substr(1,6);

    int a = binary_to_int(rd);  // rd
    int b = binary_to_int(rs1); // rs1
    int c = sign_binary_to_int(imm); // imm

    if(opcode == "0010011")
    {
        if(funct3 == "000")
        {
            // addi instruction
            string q = "addi  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);            
        }
        else if(funct3 == "111")
        {
            // andi instruction
            string q = "andi  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);          
        }
        else if(funct3 == "110")
        {
            // ori instruction
            string q = "ori  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);           
        }
        else if(funct3 == "100")
        {
            // xori instruction
            string q = "xori  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);            
        }
        else if(funct3 == "001")
        {
            // slli instruction
            string q = "slli  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);           
        }
        else if(funct3 == "101" && tempimm == "000000")
        {
            // srli instruction
            string q = "srli  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);            
        }
        else if(funct3 == "101" && tempimm == "010000")
        {
            // srai instruction
            string q = "srai  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);          
        }
    }
    else if(opcode == "0000011")
    {
        if(funct3 == "011")
        {
            // ld instruction
            string q = "ld  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);         
        }
        else if(funct3 == "010")
        {
            // lw instruction
            string q = "lw  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);          
        }
        else if(funct3 == "001")
        {
            // lh instruction
            string q = "lh  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);          
        }
        else if(funct3 == "000")
        {
            // lb instruction
            string q = "lb  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);            
        }
        else if(funct3 == "110")
        {
            // lwu instruction
            string q = "lwu  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);          
        }
        else if(funct3 == "101")
        {
            // lhu instruction
            string q = "lhu  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);           
        }
        else if(funct3 == "100")
        {
            // lbu instruction
            string q = "lbu  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);          
        }
    }
    else if(opcode == "1100111")
    {
        if(funct3 == "000")
        {
            // jalr instruction
            string q = "jalr  x" + to_string(a) + "  "+"x"+to_string(b)+"  "+to_string(c);
            code.push_back(q);      
        }
    }
}

void S_type(string s)
{
    string imm      = s.substr(0,7) + s.substr(20,5);
    string rs2      = s.substr(7,5);
    string rs1      = s.substr(12,5);
    string funct3   = s.substr(17,3);

    int a = binary_to_int(rs2); // rs2
    int b = binary_to_int(rs1); // rs1
    int c = sign_binary_to_int(imm); // imm

    if(funct3 == "011")
    {
        // sd instruction
        string q = "sd  x" + to_string(a) + "  " + to_string(c) + "(x" +to_string(b)+ ")";
        code.push_back(q);
    }
    else if(funct3 == "010")
    {
        // sw instruction
        string q = "sw  x" + to_string(a) + "  " + to_string(c) + "(x" +to_string(b)+ ")";
        code.push_back(q);
    }
    else if(funct3 == "001")
    {
        // sb instruction
        string q = "sb  x" + to_string(a) + "  " + to_string(c) + "(x" +to_string(b)+ ")";
        code.push_back(q);
    }
    else if(funct3 == "000")
    {
        // sh instruction
        string q = "sh  x" + to_string(a) + "  " + to_string(c) + "(x" +to_string(b)+ ")";
        code.push_back(q);
    }
}

void B_type(string s)
{
    string imm = s.substr(0,1) + s.substr(24,1) + s.substr(1,6) + s.substr(20,4) + "0"; 
    string rs2 = s.substr(7,5);
    string rs1 = s.substr(12,5);
    string funct3 = s.substr(17,3);

    int a = binary_to_int(rs2); // rs2
    int b = binary_to_int(rs1); // rs1
    int c = sign_binary_to_int(imm); // imm

    mp[line + (c/4)].push_back(line); 

    if(funct3 == "000")
    {
        // beq instruction
        string q = "beq  x" + to_string(b) + "  " + "x" + to_string(a) + "  ";
        code.push_back(q);
    }
    else if(funct3 == "001")
    {
        // bne instruction
        string q = "bne  x" + to_string(b) + "  " + "x" + to_string(a) + "  ";
        code.push_back(q);
    }
    else if(funct3 == "100")
    {
        // blt instruction
        string q = "blt  x" + to_string(b) + "  " + "x" + to_string(a) + "  ";
        code.push_back(q);
    }
    else if(funct3 == "101")
    {
        // bge instruction
        string q = "bge  x" + to_string(b) + "  " + "x" + to_string(a) + "  ";
        code.push_back(q);
    }
    else if(funct3 == "110")
    {
        // bltu instruction
        string q = "bltu  x" + to_string(b) + "  " + "x" + to_string(a) + "  ";
        code.push_back(q);
    }
    else if(funct3 == "111")
    {
        // bgeu instruction
        string q = "bgeu  x" + to_string(b) + "  " + "x" + to_string(a) + "  ";
        code.push_back(q);
    }
}

void J_type(string s)
{
    string imm = s.substr(0,1) + s.substr(12,8) + s.substr(11,1) + s.substr(1,10) + "0";
    string rd = s.substr(20,5);

    int a = binary_to_int(rd);  // rd
    int b = sign_binary_to_int(imm); // imm

    mp[line + (b/4)].push_back(line);

    // jal instruction
    string q = "jal  x" + to_string(a) + "  ";
    code.push_back(q);
}

void U_type(string s, string gg)
{
    string opcode = s.substr(25,7);
    string imm = s.substr(0,20);
    string rd = s.substr(20,5);

    int a = binary_to_int(rd);  // rd
    int b = sign_binary_to_int(imm); // imm

    if(opcode == "0110111")
    {
        // lui instruction
        string q = "lui  x" + to_string(a) + "  " + "0x" + gg.substr(0,5);
        code.push_back(q);
    }
}

int main()
{
    fstream fp;
    string gg;
    fp.open("input.txt",ios::in);
    while(getline(fp,gg))
    {
        string str = hex_to_binary(gg);
    
        string opcode = str.substr(25,7);

        if(opcode == "0110011")
            R_type(str);
        else if(opcode == "0010011" || opcode == "0000011" || opcode == "1100111" || opcode == "1110011")
            I_type(str);
        else if(opcode == "0100011")
            S_type(str);
        else if(opcode == "1100011")
            B_type(str);
        else if(opcode == "1101111")
            J_type(str);
        else if(opcode == "0110111" || opcode == "0010111")
            U_type(str,gg);
        line++;
    }

    int p = 1;
    for(auto it : mp)
    {
        if(it.first < 0 || it.first > line)
        {
            cout<<"error : label out of range"<<"   "<<it.first<<endl;
            return 0;
        }
        code[it.first - 1] = "L" + to_string(p) + ":  " + code[it.first -1];
        for(auto j : it.second)
        {
            code[j-1] = code[j-1] + "L" + to_string(p);
        }
        p++;
    }

    for(int i=0;i<code.size();i++)
    {
        outp<<code[i]<<endl;
    }
    return 0;
}