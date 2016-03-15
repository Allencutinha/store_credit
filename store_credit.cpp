#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include <algorithm>

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
typedef struct{
    int index0;
    int index1;
}Index;

void algorithm(Store_credit &storeInfo){
    vector<int> unsortedStoreInfo(storeInfo.priceListOfItemsAvailable);
    sort(storeInfo.priceListOfItemsAvailable.begin(), storeInfo.priceListOfItemsAvailable.end());
    vector<int>list(storeInfo.priceListOfItemsAvailable);
    int index0 = 0;
    int index1 = 0;

    int newIndex0 = 0;
    int newIndex1 = 0;
    bool solutionFound = false;
    for(int j = 0; j < list.size()-1; j++){
        for(int k = 1; k < list.size(); k++){
            if(storeInfo.creditAvailable - list[j] == list[k] && j != k){
                index0 = j;
                index1 = k;
                //cout<<j<<":"<<list[j] <<" "<<k<<":"<<list[k] << " "<<storeInfo.creditAvailable<<endl;
                solutionFound = true;
                break;
            }
        }
        if(solutionFound){
            vector<int>Unsortedlist(unsortedStoreInfo);
            int match1 = 0;
            for(int x = 0; x < list.size();x++){
                //cout<<unsortedStoreInfo[x]<< " ";
                if(list[index0] == Unsortedlist[x] && !match1){
                    newIndex0 = x;
                    match1 = x;
                }
                if(list[index1] == Unsortedlist[x] && match1 !=x){
                    newIndex1 = x;
                }
            }
            cout<<endl;
            break;
        }
    }
    index0 = newIndex0;
    index1 = newIndex1;
#if 1
    if(index0 < index1){
        cout<< index0+1<<" ";
        cout<< index1+1<<endl;
        cout<<unsortedStoreInfo[index0] << "+" <<unsortedStoreInfo[index1]<< " = "<< storeInfo.creditAvailable<<endl;
    }
    else{
        cout<<index1+1<<" ";
        cout<<index0+1<<endl;
        cout<<unsortedStoreInfo[index0] << "+" <<unsortedStoreInfo[index1]<< " = "<< storeInfo.creditAvailable<<endl;
    }

#endif
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

   for (int i = 0; i < storeCreditSamples.size();i++){
       cout<<"Case #"<<i<<": ";
       algorithm(storeCreditSamples[i]);
   }
#if 0
    vector<Index> ListOfIndices(storeCreditSamples.size());
    vector<Index> ListOfMatchinIndicesInUnsortedItrmList(storeCreditSamples.size());
    vector<Store_credit> UnsortedstoreCreditSamples(storeCreditSamples);
    for (int i = 0; i < storeCreditSamples.size();i++){
        sort(storeCreditSamples[i].priceListOfItemsAvailable.begin(),
             storeCreditSamples[i].priceListOfItemsAvailable.end());
        int creditAvailable = storeCreditSamples[i].creditAvailable;
        int numberOfItems   = storeCreditSamples[i].numberOfItemsAvailable;
        bool solutionFound = false;
        vector<int>list(storeCreditSamples[i].priceListOfItemsAvailable);
        for(int j = 0; j < list.size()-1; j++){
            for(int k = 1; k < list.size(); k++){
                //if(list[j])
                if(creditAvailable - list[j] == list[k] && j != k){
                    ListOfIndices[i].index0 = j;
                    ListOfIndices[i].index1 = k;
                    cout<<j<<" "<<k<<endl;
                    solutionFound = true;
                    break;
                }
            }
            if(solutionFound){
                vector<int>Unsortedlist(UnsortedstoreCreditSamples[i].priceListOfItemsAvailable);
                int match1 = 0;
                for(int x = 0; x < list.size();x++){
                    if(list[ListOfIndices[i].index0] == Unsortedlist[x] && !match1){
                        ListOfMatchinIndicesInUnsortedItrmList[i].index0 = x;
                        match1 = x;
                    }
                    if(list[ListOfIndices[i].index1] == Unsortedlist[x] && match1 != x){
                        ListOfMatchinIndicesInUnsortedItrmList[i].index1 = x;
                    }
                }
                break;
            }
        }
    }
    for (int i = 0; i < storeCreditSamples.size();i++){
        cout<<storeCreditSamples[i].creditAvailable<<endl;
        cout<<ListOfMatchinIndicesInUnsortedItrmList[i].index0+1<<" : ";
        cout<<storeCreditSamples[i].priceListOfItemsAvailable[ListOfIndices[i].index0]<<" ";
         cout<<ListOfMatchinIndicesInUnsortedItrmList[i].index1+1<<" : ";
        cout<<storeCreditSamples[i].priceListOfItemsAvailable[ListOfIndices[i].index1]<<endl;
    }

    for (int i = 0; i < storeCreditSamples.size();i++){
        cout<<UnsortedstoreCreditSamples[i].creditAvailable<<endl;

        cout<<ListOfMatchinIndicesInUnsortedItrmList[i].index0+1<<" : ";
        cout<<UnsortedstoreCreditSamples[i].priceListOfItemsAvailable[ListOfMatchinIndicesInUnsortedItrmList[i].index0]<<" ";


        cout<<ListOfMatchinIndicesInUnsortedItrmList[i].index1+1<<" : ";
        cout<<UnsortedstoreCreditSamples[i].priceListOfItemsAvailable[ListOfMatchinIndicesInUnsortedItrmList[i].index1]<<endl;
    }

    for (int i = 0; i < storeCreditSamples.size();i++){
        cout<<"Case #"<<i<<": ";
        if(ListOfMatchinIndicesInUnsortedItrmList[i].index0 < ListOfMatchinIndicesInUnsortedItrmList[i].index1){
            cout<<ListOfMatchinIndicesInUnsortedItrmList[i].index0+1<<" ";
            cout<<ListOfMatchinIndicesInUnsortedItrmList[i].index1+1<<endl;
        }
        else{
            cout<<ListOfMatchinIndicesInUnsortedItrmList[i].index1+1<<" ";
            cout<<ListOfMatchinIndicesInUnsortedItrmList[i].index0+1<<endl;
        }
    }

    displayInputs(UnsortedstoreCreditSamples);
#endif
    return 1;
}
