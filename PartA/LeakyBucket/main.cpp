#include <iostream>

using namespace std;

int main() {
    int bufferSize, rate, ch, bufferFilled=0, data;
    cout<<"Enter buffer size: ";
    cin>>bufferSize;
    cout<<"Enter output rate: ";
    cin>>rate;
    while(true) {
        cout<<"\nBuffer: "<<bufferFilled<<"bytes\n";
        cout<<"1.send data\n2.No data\n3.Exit\n";
        cin>>ch;
        switch(ch)  {
            case 1:
                cout<<"\nEnter size of data: ";
                cin>>data;
                if(data+bufferFilled > bufferSize){
                    cout<<"\nInsufficient Space: packet dropped";
                }else {
                    bufferFilled += data;
                    cout << "\nPacket Added";
                }
            case 2:
                if(!bufferFilled){
                    cout<<"\nNo data to send";
                    break;
                }
                if(bufferFilled >= rate)    {
                    bufferFilled -= rate;
                    cout<<endl<<rate<<" bytes sent" <<endl;
                } else{
                    cout<<endl<<bufferFilled<<" bytes sent"<<endl;
                    bufferFilled = 0;
                }
                break;
            case 3:
                return 0;
            default:break;
        }
    }
}