#include<iostream>
using namespace std;

#define MAX_SIZE 3

struct message  {
    int id =-1;
    int priority = 0 ;
}q[MAX_SIZE];
int numMessages=0;
int findHighestPriorityMessage()   {
    int high = 0;
    for(int i=1; i<MAX_SIZE; i++)   {
        if(q[high].priority<q[i].priority)
            high = i;
    }
    return high;
}
int findLowestPriorityMessage()   {
    int low = 0;
    for(int i=0; i<MAX_SIZE; i++)   {
        if(q[low].priority>q[i].priority)
            low = i;
    }
    return low;
}
void displayQueue() {
    cout<<"\nQueue: \n";
    cout<<"Size: "<<numMessages<<endl;
    for(int i=0;i<MAX_SIZE;i++) {
        if(q[i].id != -1)   {
            cout<<"Message: "<<q[i].id<<"\tPriority: "<<q[i].priority<<endl;
        }
    }
}
int findEmptySlot() {
    //displayQueue();
    //cout<<"\nFinding Empty:- ";
    for(int i=0;i<MAX_SIZE;i++)    {
        if(q[i].id == -1){
           // cout<<"\nEmpty: "<<i;
            return i;
            }
    }
}

void addNewMessage(int id,int priority) {
    if(numMessages < MAX_SIZE)  {
        int emptySlot = findEmptySlot();
        q[emptySlot].id=id;
        q[emptySlot].priority = priority;
        cout<<"\nMessage added";
        //cout<<"\nMessage: "<<q[emptySlot].id<<endl;
        //displayQueue();
        numMessages++;
    }
    else{
        int lowest = findLowestPriorityMessage();
        if(q[lowest].priority >= priority)  {
            cout<<"Queue full, New message dropped";
            return;
        }else{
            cout<<"Queue full, Message"<<q[lowest].id<<" dropped";
            q[lowest].id = id;
            q[lowest].priority = priority;
        }
    }

}
bool sendMessage()  {
    if(numMessages > 0){
        int highest = findHighestPriorityMessage();
        cout<<"Sending Message: "<<q[highest].id;
        q[highest].id = -1;
        q[highest].priority = 0;
        numMessages--;
        return true;
    }
    else
    return false;
}

int main()  {
    int k;
    do{
        displayQueue();
        cout<<"\n1.Send Message\n2.Add message\n3.Exit\n";
        cin>>k;
        switch(k)   {
        case 1:
            if(!sendMessage())
                cout<<"\nQueue Empty";
            break;
        case 2: cout<<"\nEnter message ID: ";
            int id;
            cin>>id;
            cout<<"Enter Priority of message: ";
            int priority;
            cin>>priority;
            addNewMessage(id,priority);
            break;
        case 3: break;
        default: cout<<"\nWrong Option";
        }
    }while(k!=3);
    return 0;
}
