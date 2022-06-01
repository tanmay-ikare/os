#include <bits/stdc++.h>
#define MAX_PROCESS 10
using namespace std;
class process
{
    public:
        int process_num;
        int burst_time;
        int arrival_time;
        int response_time;
        int waiting_time;
        int turnaround_time;
        int pr;
        void input_process(int);
        int get_at()
        {
            return arrival_time;
            }
};
void calc_wait_tat(process*,int);
void average(process*,int);
void display(process*,int);
void process::input_process(int count)
{
    process_num=count+1;
    cout<<"\nEnter Burst Time "<<count+1<<" : ";
    cin>>burst_time;
    cout<<"\nEnter Arrival Time "<<count+1<<" : ";
    cin>>arrival_time;
}
void calc_wait_tat(process *p,int n)
{
    int i;
    p[0].response_time=0;
    for(i=1;i<n;++i)
{
    p[i].response_time=p[i-1].burst_time+p[i-1].response_time;
    if(p[i].response_time<p[i].arrival_time)
        p[i].response_time=p[i].arrival_time;
}
 p[0].waiting_time=0;
 for(i=1;i<n;++i)
    p[i].waiting_time=p[i].response_time-p[i].arrival_time;
 for(i=0;i<n;++i)
    p[i].turnaround_time=p[i].waiting_time+p[i].burst_time;
}
void average(process *p,int n)
{
    float avg_wt=0,avg_tat=0;
    for(int i=0;i<n;++i)
{
    avg_wt+=(float)p[i].waiting_time;
    avg_tat+=(float)p[i].turnaround_time;
}
    avg_wt/=n;
    avg_tat/=n;
    cout<<"\n\nAverage Waiting Time : "<<avg_wt;
    cout<<"\nAverage Turn Around Time : "<<avg_tat;
}
void display(process *p,int n)
{
    cout<<"Processes "<<" Arrival time "<<" Burst time "<<" Waiting time "<<" Turn around time\n";
    for (int i=0;i<n;i++)
{
    cout<<"\n "<<p[i].process_num<<"\t\t"<<p[i].arrival_time<<"\t "<<p[i].burst_time<<"\t "<<p[i].waiting_time<<"\t\t "<<p[i].turnaround_time;
}
    average(p,n);
}
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void bubble_sort(process *p, int num)
{
    process t;
    int i, j;
    for (i = 1; i < num; i++)
        for (j = 0; j < num - i; j++)
        {
            if (p[j].arrival_time > p[j + 1].arrival_time)
            {
                t = p[j];
    p[j] = p[j + 1];
    p[j + 1] = t;
            }
        }
}
void RoundRobin(int *burstTime, int n, int timequant)
{
    int t = 0;
    int completionTime[n];
    int waitingTime[n];
    int remBt[n];
    for (int i = 0; i < n; i++)
{
    remBt[i] = burstTime[i];
}
    queue<int> q;
    for (int i = 0; i < n; i++)
        q.push(i);
    while (!q.empty())
        {
            int temp = q.front();
    q.pop();
    if (remBt[temp] < timequant)t += remBt[temp];
    else
        t += timequant;
    remBt[temp] -= timequant;
    if (remBt[temp] > 0)
        q.push(temp);
    else
        completionTime[temp] = t;
    }
    for (int i = 0; i < n; i++)
        waitingTime[i] = completionTime[i] - burstTime[i];
    cout << "\nProcess\t Burst Time\tCompletion Time\t Waiting Time";
    for (int i = 0; i < n; i++)
        {
            cout << "\nP" << i << "\t\t" << burstTime[i] << "\t\t" << completionTime[i] << "\t\t" << waitingTime[i] << endl;
    }
    float avgCompletionTime = 0;
    float avgWaitingTime = 0;
    for (int i = 0; i < n; i++)
        {
            avgCompletionTime += completionTime[i];
    avgWaitingTime += waitingTime[i];
    }
    avgCompletionTime /= n;
    avgWaitingTime /= n;
    cout << "\nAverage Completion Time: " << avgCompletionTime;
    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    }
void SJF_prem()
{
    int arrival_time[10], burst_time[10], temp[10];
    int i, smallest, count = 0, time, limit;
    double wait_time = 0, turnaround_time = 0, end;
    float average_waiting_time, average_turnaround_time;
    cout<<"\nEnter the Total Number of Processes:\t";
    cin>>limit;
    for(i = 0; i < limit; i++)
        {
            cout<<"\nEnter Arrival Time:\t";
    cin>>arrival_time[i];
    cout<<"Enter Burst Time:\t";
    cin>>burst_time[i];
    temp[i] = burst_time[i];
    }
    burst_time[9] = 9999;
    for(time = 0; count != limit; time++)
        {
            smallest = 9;
    for(i = 0; i < limit; i++)
        {
            if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
            {
                smallest = i;
    }
    }
    burst_time[smallest]--;
    if(burst_time[smallest] == 0)
        {
            count++;
    end = time + 1;
    wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
    turnaround_time = turnaround_time + end - arrival_time[smallest];
    }
    }
    average_waiting_time = wait_time / limit;
    average_turnaround_time = turnaround_time / limit;
    cout<<"\n\nAverage Waiting Time="<<average_waiting_time<<endl;
    cout<<"Average Turnaround Time="<<average_turnaround_time;
    }
    int main()
    {
        process p[MAX_PROCESS],temp;
        int num,i,j,ch;
        do
            {
                cout<<"\n--STIMULATION OF CPU SCHEDULING ALGORITHMS--\n";
        cout<<"1) FCFS \n";
        cout<<"2) SJF (Pre-emptive)\n";
        cout<<"3) SJF (Non Pre-emptive) \n";
        cout<<"4) PRIORITY Scheduling (Non Pre-emptive)\n";
        cout<<"5) ROUND ROBIN\n";
        cout<<" Exit\n";
        cout<<" Enter your choice you want : ";
        cin>>ch;
        switch(ch)
        {
            case 1:
                {
                    cout<<"\nFCFS SCHEDULING\n";
                    cout<<"Enter the number of processes : ";
                    cin>>num;
                    for(i=0;i<num;++i)
                        p[i].input_process(i);
                    bubble_sort(p, num);
                    calc_wait_tat(p,num);
                    display(p,num);
                    break;
                    }
                    case 2:
                        {
                            cout<<"SJF PREEMPTIVE";
                            SJF_prem();
                            break;
                            }
                            case 3:
                                {
                                    cout<<"SJF NON PREEMPTIVE";
                                    bubble_sort(p, num);
                                    cout<<"ENTER NUMBER OF PROCESSES : ";
                                    cin>>num;
                                    for(i=0;i<num;++i)
                                        p[i].input_process(i);
                                    for ( int i = 2; i < num; i++)
                                        for ( int j = 1; j < num - i + 1; j++) {
                                            if (p [j].burst_time > p [j + 1].burst_time) {
                                                swap( p[j],p[j+1]);
                                    }
                                    }
                                    calc_wait_tat(p,num);display(p,num);
                                    break;
                                    }
                                    case 4:
                                        {
                                            cout<<"ENTER NUMBER OF PROCESSES : ";
                                            cin>>num;
                                            for(i=0;i<num;++i)
                                                p[i].input_process(i);
                                            cout<<"Priority";
                                            cout<<"\nEnter the priority of process";
                                            cin>>p[i].pr;
                                            for(i=0;i<num;i++)
                                                {
                                                    for(j=0;j<num-i-1;j++)
                                                    {
                                                        if(p[j].pr<p[j+1].pr)
                                                        {
                                                            swap( p[j].burst_time, p[j+1].burst_time);
                                            swap( p[j], p[j+1]);
                                            swap( p[j].pr, p[j+1].pr);
                                            }
                                            }
                                            }
                                            calc_wait_tat(p,num);
                                            display(p,num);
                                            break;
                                            }
                                            case 5:
                                                {
                                                    cout<<"RoundRobin";
                                                    cout<<"Number of process";
                                                    int n;
                                                    cin >> n;
                                                    int burstTime[n];
                                                    cout<<"Burst time";
                                                    for (int i = 0; i < n; i++)
                                                        cin >> burstTime[i];
                                                    int timequant;
                                                    cout << "\nEnter Time Slice : ";
                                                    cin >> timequant;RoundRobin(burstTime, n, timequant);
                                                    break ;
                                                    }
                                                    case 6:
                                                    {
                                                        exit(0);
                                                        }
                                                        default:
                                                            {
                                                                cout<<"\nWrong Choice";
                                                                break;
                                                                }
                                                                }
                                                                }
                                                                while(ch!=8);
                                                                return 0;
                                                                }

