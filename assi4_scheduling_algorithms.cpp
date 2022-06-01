#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;


class priority
{
    int process[50][5]; 
    int processCount; 
public:
    
    priority()
    {
    reenter:
        cout<<"\n--> How many processes want to schedule: ";
        cin>>processCount;
        if(processCount > 50)
        {
            cout<<"\n--- Please enter value less than or equal to 50 ---\n";
            goto reenter; 
        }
        memset(process, 0, sizeof(process)); 
        for(int i=0; i<processCount; i++)
        {
            cout<<"\n--> Process P"<<i;
            cout<<"\n\t Burst Time: ";
            cin>>process[i][0];
            cout<<"\t Arrival Time: ";
            cin>>process[i][1];
            cout<<"\t Priority: ";
            cin>>process[i][4];
        }
    }
    
    void nonPreemptiveScheduling()
    {
        cout<<"\n\n--- Gantt Chart ---\n\n";
        cout<<"0";
        for(int time=0, processesCompleted=0;;)
        {
            int currentProcess = PriorityJob(time); 
            if(currentProcess == -1) 
            {
                time++;
                cout<<"-"<<time;
            }
            else
            {
                process[currentProcess][2] = time; 
                time += process[currentProcess][0];
                process[currentProcess][3] = time;
                cout<<"| P"<<currentProcess<<" |"<<time;
                processesCompleted++;
                if(processesCompleted == processCount) 
                    break;
            }
        }
        
        cout<<"\n\n"<<setw(10)<<"Process"<<setw(10)<<"Priority"<<setw(8)<<"WT"<<setw(10)<<"TAT\n";
        for(int i=0; i<processCount; i++)
        {
            cout<<setw(6)<<"P"<<i<<setw(10)<<process[i][4]<<setw(10)<<process[i][2]<<setw(10)<<process[i][3]<<"\n";
        }
    }
    

    void PreemptiveScheduling()
    {
        cout<<"\n\n--- Gantt Chart ---\n\n";
        for(int time=0, previousProcess=-1, processesCompleted=0;;)
        {
            int currentProcess = PriorityJob(time); 
            if(currentProcess == -1) 
            {
                cout<<time<<"-";
                time++;
                continue;
            }
            if(previousProcess != currentProcess) 
            {
                previousProcess = currentProcess;
                cout<<time<<"| P"<<currentProcess<<" |";
            }
            process[currentProcess][3]++; 
            time++;
            if(process[currentProcess][0] - (process[currentProcess][3] - process[currentProcess][2]) <= 0) 
            {
                process[currentProcess][3] = time; 
                process[currentProcess][2] = time - process[currentProcess][0]; 
                processesCompleted++;
                if(processesCompleted == processCount)
                {
                    cout<<time;
                    break;
                }
            }
        }
        
        cout<<"\n\n"<<setw(10)<<"Process"<<setw(10)<<"Priority"<<setw(8)<<"WT"<<setw(10)<<"TAT\n";
        for(int i=0; i<processCount; i++)
        {
            cout<<setw(6)<<"P"<<i<<setw(10)<<process[i][4]<<setw(10)<<process[i][2]<<setw(10)<<process[i][3]<<"\n";
        }
    }
    
    int PriorityJob(int time)
    {
        int PriorityJobIndex = -1;
        int HighestPriority;
        int i = 0;
        for(i; i<processCount; i++)
        {
            int diff = process[i][0] - (process[i][3] - process[i][2]);
            if(process[i][1] <= time && diff>0)
            {
                PriorityJobIndex = i;
                HighestPriority = process[i][4];
                break;
            }
        }
        for(i; i<processCount; i++)
        {
            int diff = process[i][0] - (process[i][3] - process[i][2]);
            if(process[i][1] <= time && diff>0 && process[i][4] < HighestPriority) 
            {
                PriorityJobIndex = i;
                HighestPriority = process[i][4];
            }
        }
        return PriorityJobIndex;
    }
};

class rr
{
    int process[50][4]; 
    int processCount; 
    int quantum;
public:
    
    rr()
    {
    reenter:
        cout<<"\n--> How many processes want to schedule: ";
        cin>>processCount;
        if(processCount > 50)
            goto reenter; 
        cout<<"\n--> Quantum/Slice Time: ";
        cin>>quantum;
        memset(process, 0, sizeof(process)); 
        for(int i=0; i<processCount; i++)
        {
            cout<<"\n--> Process P"<<i;
            cout<<"\n\t Burst Time: ";
            cin>>process[i][0];
            cout<<"\t Arrival Time: ";
            cin>>process[i][1];
        }
    }
    
    void scheduling()
    {
        int processesCompleted = 0;
        cout<<"\n\n--- Gantt Chart ---\n\n";
        cout<<"0";
        for(int i=0, time=0, countIter=0; i<processCount; i++)
        {
            countIter++; 
            if(countIter > processCount)
            {
                time++;
                cout<<"-"<<time;
                countIter = 0;
            }
            if(process[i][1] <= time) 
            {
                int diff = process[i][0] - (process[i][3] - process[i][2]);
                if(diff > 0) 
                {
                    countIter = 0;
                    cout<<"| P"<<i<<" |";
                    if(diff > quantum) 
                    {
                        process[i][3] += quantum;
                        time += quantum;
                    }
                    else
                    {
                        time += diff;
                        process[i][3] = time - process[i][1]; 
                        process[i][2] = process[i][3] - process[i][0]; 
                        processesCompleted++;
                        if(processesCompleted == processCount) 
                        {
                            cout<<time;
                            break;
                        }
                    }
                    cout<<time;
                }
            }
            if(i == processCount-1) 
                i = -1;
        }
        
        cout<<"\n\n"<<setw(5)<<"Process"<<setw(5)<<"WT"<<setw(5)<<"TAT\n";
        for(int i=0; i<processCount; i++)
        {
            cout<<setw(5)<<"P"<<i<<setw(5)<<process[i][2]<<setw(5)<<process[i][3]<<"\n";
        }
    }
};

class fcfs
{
    int process[50][4]; 
    int processCount; 
public:
    
    fcfs()
    {
        cout<<"\n 1] FCFS with Arrival Time";
        cout<<"\n 2] FCFS without Arrival Time";
        cout<<"\n Select One Option: ";
        int option1;
        cin>>option1;
    reenter:
        cout<<"\n--> How many processes want to schedule: ";
        cin>>processCount;
        if(processCount > 50)
        {
            cout<<"\n--- Please enter value less than or equal to 50 ---\n";
            goto reenter; 
        }
        memset(process, 0, sizeof(process)); 
        for(int i=0; i<processCount; i++)
        {
            cout<<"\n--> Process P"<<i;
            cout<<"\n\t Burst Time: ";
            cin>>process[i][0];
            if(option1 == 2)
            {
                process[i][1] = 0;
            }
            else
            {
                cout<<"\t Arrival Time: ";
                cin>>process[i][1];
            }
        }
    }
    
    void scheduling()
    {
        cout<<"\n\n--- Gantt Chart ---\n\n";
        cout<<"0";
        for(int i=0, time=0, countIter=0, processesCompleted=0; i<processCount; i++)
        {
            countIter++; 
            if(countIter > processCount)
            {
                time++;
                cout<<"-"<<time;
                countIter = 0;
            }
            if(process[i][1] <= time) 
            {
                int diff = process[i][0] - (process[i][3] - process[i][2]);
                if(diff > 0) 
                {
                    countIter = 0;
                    process[i][2] = time; 
                    time += process[i][0];
                    process[i][3] = time; 
                    cout<<"| P"<<i<<" |"<<time;
                    processesCompleted++;
                    if(processesCompleted == processCount) 
                        break;
                }
            }
            if(i == processCount-1) 
                i = -1;
        }
        
        cout<<"\n\n"<<setw(5)<<"Process"<<setw(5)<<"WT"<<setw(5)<<"TAT\n";
        for(int i=0; i<processCount; i++)
        {
            cout<<setw(5)<<"P"<<i<<setw(5)<<process[i][2]<<setw(5)<<process[i][3]<<"\n";
        }
    }
};

class sjf
{
    int process[50][4]; 
    int processCount;
public:
   
    sjf()
    {
    reenter:
        cout<<"\n--> How many processes want to schedule: ";
        cin>>processCount;
        if(processCount > 50)
        {
            cout<<"\n--- Please enter value less than or equal to 50 ---\n";
            goto reenter; 
        }
        memset(process, 0, sizeof(process)); 
        for(int i=0; i<processCount; i++)
        {
            cout<<"\n--> Process P"<<i;
            cout<<"\n\t Burst Time: ";
            cin>>process[i][0];
            cout<<"\t Arrival Time: ";
            cin>>process[i][1];
        }
    }
   
    void nonPreemptiveScheduling()
    {
        cout<<"\n\n--- Gantt Chart ---\n\n";
        cout<<"0";
        for(int time=0, processesCompleted=0;;)
        {
            int currentProcess = ShortestJob(time); 
            if(currentProcess == -1) 
            {
                time++;
                cout<<"-"<<time;
            }
            else
            {
                process[currentProcess][2] = time; 
                time += process[currentProcess][0];
                process[currentProcess][3] = time; 
                cout<<"| P"<<currentProcess<<" |"<<time;
                processesCompleted++;
                if(processesCompleted == processCount) 
                    break;
            }
        }
        
        cout<<"\n\n"<<setw(5)<<"Process"<<setw(5)<<"WT"<<setw(5)<<"TAT\n";
        for(int i=0; i<processCount; i++)
        {
            cout<<setw(5)<<"P"<<i<<setw(5)<<process[i][2]<<setw(5)<<process[i][3]<<"\n";
        }
    }
    
    void PreemptiveScheduling()
    {
        cout<<"\n\n--- Gantt Chart ---\n\n";
        for(int time=0, previousProcess=-1, processesCompleted=0;;)
        {
            int currentProcess = ShortestJob(time); 
            if(currentProcess == -1) 
            {
                cout<<time<<"-";
                time++;
                continue;
            }
            if(previousProcess != currentProcess) 
            {
                previousProcess = currentProcess;
                cout<<time<<"| P"<<currentProcess<<" |";
            }
            process[currentProcess][3]++; 
            time++;
            if(process[currentProcess][0] - (process[currentProcess][3] - process[currentProcess][2]) <= 0) 
            {
                process[currentProcess][3] = time; 
                process[currentProcess][2] = time - process[currentProcess][0]; 
                processesCompleted++;
                if(processesCompleted == processCount) 
                {
                    cout<<time;
                    break;
                }
            }
        }

        cout<<"\n\n"<<setw(5)<<"Process"<<setw(5)<<"WT"<<setw(5)<<"TAT\n";
        for(int i=0; i<processCount; i++)
        {
            cout<<setw(5)<<"P"<<i<<setw(5)<<process[i][2]<<setw(5)<<process[i][3]<<"\n";
        }
    }
    
    int ShortestJob(int time)
    {
        int ShortestJobIndex = -1;
        int ShortestBurstTime;
        int i = 0;
        for(i; i<processCount; i++)
        {
            int diff = process[i][0] - (process[i][3] - process[i][2]);
            if(process[i][1] <= time && diff>0) 
            {
                ShortestJobIndex = i;
                ShortestBurstTime = process[i][0];
                break;
            }
        }
        for(i; i<processCount; i++)
        {
            int diff = process[i][0] - (process[i][3] - process[i][2]);
            if(process[i][1] <= time && diff>0 && process[i][0] < ShortestBurstTime)
            {
                ShortestJobIndex = i;
                ShortestBurstTime = process[i][0];
            }
        }
        return ShortestJobIndex;
    }
};

int main()
{
restart:
    system("cls");
    cout<<"\nScheduling(CPU) Algorithms\n";
    cout<<"\n 1. Priority Scheduling";
    cout<<"\n 2. Round Robin Scheduling";
    cout<<"\n 3. FCFS Scheduling";
    cout<<"\n 4. SJF Scheduling";
    cout<<"\n 5. Exit";
    cout<<"\n Select One Option: ";
    int option1;
    cin>>option1;
    switch(option1)
    {
        case 1:{
            cout<<"\n---- Priority Scheduling ----\n";
            cout<<"\n 1] Preemptive";
            cout<<"\n 2] Non-Preemptive";
            cout<<"\n Select One Option: ";
            int option2;
            cin>>option2;
            priority p1;
            if(option2 == 1)
                p1.PreemptiveScheduling();
            else
                p1.nonPreemptiveScheduling();
            break;
        }
        case 2:{
            cout<<"\n---- Round Robin Scheduling ----\n";
            rr r1;
            r1.scheduling();
            break;
        }    
        case 3:{
            cout<<"\n---- FCFS Scheduling ----\n";
            fcfs f1;
            f1.scheduling();
            break;
        }
        case 4:{
            cout<<"\n---- SJF Scheduling ----\n";
            cout<<"\n 1] Preemptive";
            cout<<"\n 2] Non-Preemptive";
            cout<<"\n Select One Option: ";
            int option2;
            cin>>option2;
            sjf s1;
            if(option2 == 1)
                s1.PreemptiveScheduling();
            else
                s1.nonPreemptiveScheduling();
            break;
        }
        case 5:
            cout<<"\nExit...\n";
            break;
        default:
            cout<<"\ninvalid option\n";
    }
    cout<<endl;
    system("pause");
    if(option1 != 5)
        goto restart;
    return 0;
}
