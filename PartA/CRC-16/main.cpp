#include <iostream>
#include <vector>

using namespace std;

int crc[17] = {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1};

void doXOR(vector<int> &codeword, int x){
    for(int i=0,j=x; i<17; i++,j++)
        codeword[j] = codeword[j] ^ crc[i];
}
vector<int> getCodeWord(vector<int> dataWord){
    vector<int> codeWord(dataWord.size()+16);
    cout<<"\nGenerating CodeWord\n";
    for(int i=0; i<dataWord.size(); i++)
        codeWord[i] = dataWord[i];
    for(int i=0; i<dataWord.size(); i++){
        if(codeWord[i] == 1)    {
            doXOR(codeWord,i);
        }
    }
    for(int i=0; i<dataWord.size(); i++)
        codeWord[i] = dataWord[i];
    return codeWord;
}
bool checkCodeWord(vector<int> codeWord)    {
    for(int i=0; i<codeWord.size() - 16; i++)   {
        if(codeWord[i] == 1)
            doXOR(codeWord,i);
    }
    for(int i = codeWord.size() - 16; i<codeWord.size(); i++){
        if(codeWord[i] == 1)
            return false;
    }
    return true;
}
int main() {
    cout<<"Enter the size of dataWord: ";
    int size;
    cin>>size;
    vector<int> dataWord(size);
    vector<int> codeWord;
    cout<<"Enter the data word (space separated): ";
    for(int i=0; i < size; i++)
        cin>>dataWord[i];
    codeWord = getCodeWord(dataWord);
    cout<<"\nCodeword: ";
    for(int i=0; i<codeWord.size(); i++)
        cout<<codeWord[i]<<" ";
    cout<<"\nEnter the codeword recieved: ";
    vector<int> codeWordRecieved(codeWord.size());
    for(int i=0; i<codeWord.size(); i++)
        cin>>codeWordRecieved[i];
    if(checkCodeWord(codeWordRecieved))
        cout<<"Transmission Successful";
    else
        cout<<"Transmission Unsuccessful";
    return 1;
}
