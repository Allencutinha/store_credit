#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;
class Store_credit{
public:
    int creditAvailable;
    int numberOfItemsAvailable;
    std::vector<int>  priceListOfItemsAvailable;

    Store_credit(){
    }
    ~Store_credit(){}

    void addItem(int item){
        priceListOfItemsAvailable.push_back(item);
    }
    void displayItems(){
        for(int i = 0; i < priceListOfItemsAvailable.size(); i++){
            cout<<priceListOfItemsAvailable[i]<<"\t";
        }
        cout<<endl;
    }
    void readCredit(std::ifstream &inputFile)
    {
        std::string line;
        if(getline(inputFile,line)){
            cout<<"credit loaded"<<endl;
            std::stringstream lineStream(line);
            if(lineStream >> creditAvailable){
            }
        }else{cout<<"failed to load credit"<<endl;}
    }
    void readNumberOfItems(std::ifstream &inputFile)
    {
        std::string line;
        if(getline(inputFile,line)){
            std::stringstream lineStream(line);
            if(lineStream >> numberOfItemsAvailable){
                cout<<"number of items loaded"<<endl;
            }
            else{cout<<"failure in parsing number of items"<<endl;}
        }
    }

    void readListOfItems(std::ifstream &inputFile)
    {
        std::string line;
        line.clear();
        if(getline(inputFile,line)){
            std::stringstream lineStream(line);
            int value;
            while(lineStream >> value){
                priceListOfItemsAvailable.push_back(value);
            }
        }
    }
};
void displayExpectedFormat()
{
    cout<<"\tExpect an inputfile name!!!"<<endl;
    cout<<"\tformat: ./app filename.in"<<endl;
}
bool  handleInputs(int argc, char* argv[],vector<Store_credit>& storeCreditSamples)
{
    bool retVal = false;
    if(argc != 2 || argv[1] == NULL){
        displayExpectedFormat();
        retVal = false;
    }
    else{
        cout<<"Entered file name :"<<argv[1]<<endl;

        std::ifstream inputFile(argv[1]);
        if(inputFile.is_open()){
            cout<<"file opened successfully"<<endl;

            int number;
            int i = 0;

            {
                std::string line;
                if(getline(inputFile,line)){  std::stringstream lineStream(line);  lineStream >>number; cout<<"nuber of examples : "<<number<<endl;}
            }
            while(i < number){
                 Store_credit storeCredit;
                 // the parsing should  be performed in this order since the file format is as below
                 storeCredit.readCredit(inputFile);
                 storeCredit.readNumberOfItems(inputFile);
                 storeCredit.readListOfItems(inputFile);
                 storeCreditSamples.push_back(storeCredit);

                i++;
            }
            retVal = true;
        }
        else{
            cout<<"file open failed"<<endl;
            retVal = false;
        }
    }
    return retVal;
}

void displayInputs(vector<Store_credit> storeCreditSamples)
{
    for(int r = 0; r <storeCreditSamples.size();r++){
        cout<<storeCreditSamples[r].creditAvailable<<endl;
        cout<<storeCreditSamples[r].numberOfItemsAvailable<<endl;
        storeCreditSamples[r].displayItems();
    }
}
int main(int argc, char* argv[])
{
    cout<<"_____________Code Jam:: Store Credit____________"<<endl;

    std::vector<Store_credit>  storeCreditSamples;
    if(!handleInputs(argc, &argv[0], storeCreditSamples)){
        cout<<"\tinputs could not be loaded sucessfully!!!"<<endl;
        return 0;
    }

    displayInputs(storeCreditSamples);

    return 1;
}
