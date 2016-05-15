#include <iostream>
#include <queue>
using namespace std;
queue<int> q1, q2;


void displayData() {
    cout<<"\nHigh Queue: ";
    if(!q1.empty()){
        queue<int> temp = q1;
        for(int i=0;i<q1.size();i++) {  //remember size should be of q1 and not temp as when we pop from temp size changes
            cout << temp.front()<<",";
            temp.pop();
        }
    } else
        cout<<"Empty";
    cout<<"\nLow Queue: ";
    if(!q2.empty()){
        queue<int> temp = q2;
        for(int i=0;i<q2.size();i++) {//remember size should be of q2 and not temp as when we pop from temp size changes
            cout << temp.front()<<",";
            temp.pop();
        }
    } else
        cout<<"Empty";
}

void sendData() {

    cout<<"\nSending Data: ";
    if(!q1.empty()) {
        cout<<q1.front()<<"\n";
        q1.pop();
    }else{
        if(!q2.empty()) {
            cout<<q2.front()<<"\n";
            q2.pop();
        }else{
            cout<<"No data to send";
        }
    }
}

void insertData(int data, int prior) {
    if(prior == 1)
        q1.push(data);
    else if(prior == 2)
        q2.push(data);
    else
        cout<<"\nInvalid Priority\n";

}

int main() {
    int ch;
    while(true) {
        displayData();
        cout<<"\n1. insert data\n2. Send Data\n3.Exit";
        cin>>ch;
        switch(ch) {
            case 1:
                cout<<"\nEnter data";
                int data;
                cin>>data;
                cout<<"Enter priority: (1 or 2): ";
                int prior;
                cin>>prior;
                insertData(data,prior);
                break;
            case 2:
                sendData();
                break;
            case 3:
                return 0;


            default:break;
        }

    }
}