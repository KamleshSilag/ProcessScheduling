#include<iostream>
#include<climits>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
 
int process_id=1445;

void swap(int *x, int *y);
 
class ProcessSchedule
{
    int *harr;
    int *p_id;
    int capacity;
    int heap_size;
public:

    ProcessSchedule(int capacity);
 
    void ProcessScheduleify(int );
 
    int parent(int i) { return (i-1)/2; }
 
    int left(int i) { return (2*i + 1); }
 
    int right(int i) { return (2*i + 2); }
 
    int extractMin();
 
    void decreaseKey(int i, int new_val);
 
    int getMin() { return harr[0]; }
 
    void deleteKey(int i);
 
    void insertKey(int k,int p);

    void display();

    void setIdByRandom();

    int getIndexByPriority(int);

    void freeHeap();
};
 
ProcessSchedule::ProcessSchedule(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
    p_id = new int[cap];
}
 
void ProcessSchedule::insertKey(int k,int p)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
 
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
    p_id[i] = p;
 
    while (i != 0 && harr[parent(i)] > harr[i])
    {
       swap(&harr[i], &harr[parent(i)]);
       swap(&p_id[i],&p_id[parent(i)]);
       i = parent(i);
    }
}
 
void ProcessSchedule::decreaseKey(int i, int new_val)
{
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i])
    {
       swap(&harr[i], &harr[parent(i)]);
        swap(&p_id[i],&p_id[parent(i)]);
       i = parent(i);
    }
}
 
 int ProcessSchedule::extractMin()
{
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
 
    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    p_id[0] = p_id[heap_size-1];
    heap_size--;
    ProcessScheduleify(0);
 
    return root;
}
 
 
void ProcessSchedule::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();
}
 
void ProcessSchedule::ProcessScheduleify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
         swap(&p_id[i],&p_id[parent(i)]);
        ProcessScheduleify(smallest);
    }
}
 
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void ProcessSchedule::display()
{
    for(int i=0;i<heap_size;i++)
    {
        cout<<"\n\nPriority:"<<harr[i];
        cout<<"\nProcess ID: "<<p_id[i];
    }
}

void ProcessSchedule::setIdByRandom()
{
        process_id = process_id+rand() %1000+1;
}

int ProcessSchedule::getIndexByPriority(int priority)
{
    for(int i=0;i<heap_size;++i)
    {
        if(priority == p_id[i])
            return i;
    }

    return 0;
}

void ProcessSchedule::freeHeap()
{
    for(int i=0;i<heap_size;i++)
    {
        harr[i]=(int)NULL;
        p_id[i]=(int)NULL;
    }

    heap_size=0;
}
 
int main()
{
     int ch,priority;
    ProcessSchedule h(50);

    do
    {
        system("cls");
        cout<<"______________________________________________________________________";
        cout<<"\n\t\t\tProcess Scheduling\n";
        cout<<"______________________________________________________________________";
     cout<<"\n1)Add Process\n2)Execute Process\n3)Kill Process\n4)Get Highest priority process\n5)Task Manager\n6)Kill All process\n7)Exit\n";
     cin>>ch;

     switch(ch)
     {
        case 1:h.setIdByRandom();
        cout<<"Enter Priority for process "<<process_id<<" "<<endl;
        cin>>priority;
        h.insertKey(priority,process_id);
        break;

        case 2:cout<<"Executing Highest Priority process "<<h.getMin();
                sleep(5);
                cout<<"Process Execute "<<h.extractMin();
                break;

        case 3: cout<<"\nEnter Priority of process to be deleted";
                cin>>priority;
                h.deleteKey(h.getIndexByPriority(priority));
                cout<<"\nProcess Killed";
                break;  

        case 4:
                cout<<"Highest Priority process: "<<h.getMin();
                break;

        case 5: h.display();
                break; 

        case 6:cout<<"Killing All Processes\n";
                sleep(2);
                h.freeHeap();
                cout<<"Processes Killed\n";
                break;
        case 7:
                exit(0);       

     }

     cin.ignore();
     cin.get();

 }while(ch<8);

    return 0;
}