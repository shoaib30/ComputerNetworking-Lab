#include <iostream>
#include <cstring>

using namespace std;
class Message   {
    char* str;
    int size;
    int checksum;
    int wordSize;
public: Message(char str[])   {
        size = (int) strlen(str);
        this->str = str;
        checksum = 0;
        wordSize = ((size % 2) != 0 ? size + 1 : size) / 2;
    }
    void calculateChecksum(int initialChecksum = 0)    {
        checksum = initialChecksum;
        for(int i = 0; i < wordSize; i++)    {
            checksum += (str[i*2]*256) + str[(i*2)+1];      //(256)base10 = (100)base16
        }
        if(checksum%65536 != 0)
            checksum = (checksum/65536) + (checksum%65536);
        checksum = 65535-checksum;

    }
    void printChecksum()    {
        printf("%x",checksum);
    }
    bool validateMessage(int initialChecksum)  {
        calculateChecksum(initialChecksum);
        printChecksum();
        return checksum == 0;
    }

};
int main() {
    int ch;
    bool k=true;
    char message[100];
    cout<<"Enter Message: ";
    cin>>message;
    Message m(message);
    while(k)    {
        cout<<"\n1.Generate Checksum\n2.Detect Error in message\n3.Exit";
        cin>>ch;

        switch(ch)  {
            case 1:

                m.calculateChecksum();
                cout<<"Checksum: ";
                m.printChecksum();
                break;
            case 2:

                cout<<"Enter checksum: ";
                int init;
                scanf("%x",&init);
                if(m.validateMessage(init))
                    cout<<"Message valid";
                else
                    cout<<"Message invalid";
                break;
            case 3:
                k=false;
                break;
            default:
                cout<<"Wrong input";
        }
    }
    return 0;
}