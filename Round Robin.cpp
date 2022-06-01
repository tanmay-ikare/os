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
     int main()
    {
        process p[MAX_PROCESS],temp;
        int num,i,j,ch;
            {
            	 cout<<" ROUND ROBIN\n";
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
                                                    return 0;
            }
        }
