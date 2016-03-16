#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include <algorithm>

using namespace std;

int main(int argc , char * argv[]){
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    if(!inFile){cout<<"input file name needed!!"<<endl;return -1;}
    if(!outFile){cout<<"output file name needed!!"<<endl;return -1;}

    int cases, caseIterator = 0, credit, noOfItems;
    inFile >> cases;
    while(caseIterator < cases){
        inFile>>credit;
        inFile>>noOfItems;
        vector<int>priceList;
        for(int j = 0; j < noOfItems; j++){
            int price;
            inFile>>price;
            priceList.push_back(price);
        }
        for (int i = 0; i < noOfItems - 1; i++){
            for(int j = i+1; j< noOfItems; j++){
                if(credit - priceList[i] == priceList[j]){
                    outFile << "Case #"<<caseIterator+1<<": "<<i+1<<" "<<j+1<<endl;
                    cout<<"Case# "<<caseIterator+1<<": "<<i+1<<" "<<j+1<<endl;
                }
            }
        }
        caseIterator++;
    }
}
