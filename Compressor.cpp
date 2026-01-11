#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>

//std::string testText = "According to all known laws of aviation, there is no way that a bee should be able to fly. Its wings are too small to get its fat little body off the ground. The bee, of course, flies anyways. Because bees don't care what humans think is impossible.";
//std::string testText = "AABCBAD";
std::string testText = "This is a sentence which is for medium tests";

std::vector<std::array<int, 2>> freq;
std::vector<std::array<int, 2>> tree;

std::vector<std::pair<char, std::string>> codes;

//All the sorting part
void getCharacterFrequency(std::string& text){
    freq.clear();
    for(char& x : text){
        int target = -x;

        auto it = std::find_if(freq.begin(), freq.end(), [target](const std::array<int, 2>& p) {
            return p[0] == target;
        });

        if(it != freq.end()){
            (*it)[1] ++;
        }
        else{
            freq.push_back({target, 1});
        }
    }
}

void sortList(){
    std::sort(freq.begin(), freq.end(), [](const std::array<int, 2>& a , const std::array<int, 2>& b) {
        return a[1] < b[1];  
    });
}

void printCharacterFrequency(){
    std::cout << std::endl;
    for(int i = 0; i < freq.size(); i++){
        //std::cout << freq[i][0] << " : " << freq[i][1] << std::endl;
    }
}

void printTree(int index, std::string chars){

    if(tree[index][0] >= 0){
        printTree(tree[index][0], chars + "─");//├
    }
    else{
        std::cout << chars << "─" << char(-tree[index][0]) << std::endl;
    }    

    if(tree[index][1] >= 0){
        printTree(tree[index][1], chars + " ");
    }
    else{
        std::cout << chars << "└" << char(-tree[index][1]) << std::endl;
    }    

    return;
}

//Create binary tree
void getTree(){

    int itt = freq.size() - 1;

    std::vector<std::array<int, 2>> t;
    
    while(freq.size() > 1){
        std::array<int, 2> v1 = freq[0];  //Grabs current index charcter and frequencys
        std::array<int, 2> v2 = freq[1]; //grabs next index character and frequencys
        //std::cout << v1[0] << " " << v1[1] << std::endl;
        //std::cout << v2[0] << " " << v2[1] << std::endl;
        int size = t.size(); // gets size of tree
        std::array<int, 2> temp = {size, v1[1] + v2[1]}; // gets the {index of next spot on tree, freq[i] + freq[i+1]}
        
        int i1 = freq[0][0]; //Gets the actual character of [i] index
        int i2 = freq[1][0]; //gets actual value of [i+1] index

        //std::cout << i1 << " " << i2 << std::endl;

        t.push_back({i1, i2});
        
        freq.erase(freq.begin());
        freq.erase(freq.begin());

        freq.insert(freq.begin(), temp);
        
        sortList();
        
    }

    tree = t;
}

std::string convertCode(std::vector<int> code){
    std::string strCode;
    for(int i = 0; i < code.size(); i++){
        char num = '0' + code[i];
        strCode += num;
    }

    return strCode;

}

void checkVals(int pointer, std::vector<int> code){
    std::array<int,2> vals = tree[pointer];

    //Look at index 0
    if(vals[0] >= 0){
        code.push_back(0);
        pointer = vals[0];
        checkVals(pointer,code);
    }
    else{
        code.push_back(0);
        std::pair<char, std::string> pr = {char(-vals[0]), convertCode(code)};
        codes.push_back(pr);

        
    }

    code.pop_back();
    //Look at index 1

    if(vals[1] >= 0){
        code.push_back(1);
        pointer = vals[1];
        checkVals(pointer,code);
    }
    else{
        code.push_back(1);
        std::pair<char, std::string> pr = {char(-vals[1]), convertCode(code)};
        codes.push_back(pr);
        
    }
    code.pop_back();
}

void getCodes(){
    
    int pointer = tree.size() - 1; 
    
    std::vector<int> code;

    checkVals(pointer, code);

}

void printCodes(){
    for(auto& x : codes){
        std::cout << x.first << " : " << x.second << std::endl;
    }
}

void createBinString(){
    std::string greatString;
    for(auto& chr : testText){
        auto it = std::find_if(codes.begin(), codes.end(), [chr](const std::pair<int, std::string>& p) {
            return p.first == chr;  // Match key
        });

        if(it != codes.end()){
            greatString += it->second;
        }

    }
    
    std::cout << greatString << std::endl;

    std::ofstream file("output.txt");

    if (file.is_open()) {
        file.write(greatString.c_str(), greatString.size());
        file.close();
        std::cout << "Binary data written to 'output.bin'" << std::endl;
    } 
    else {
        std::cerr << "Error opening file!" << std::endl;
    }

}

int main(){
    getCharacterFrequency(testText);

    sortList();

    getTree();

    for(auto& x : tree){std::cout << x[0] << "|" << x[1] << std::endl;}
    printTree(tree.size()-1 ,"");

    getCodes();

    printCodes();
    
    createBinString();

    return 0;
}

