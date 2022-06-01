#include<iostream>
#include<stdio.h>
using namespace std;
void fifo(){
	int n,a[50],frame[10],no,k,avail,count=0;
     
     //To input the value of number of pages 
	cout<<"\n Enter the number of pages :\n";
     cin>>n;
            
	//To take the value of input string
	cout<<"\n Enter the value for page number \n";
     for(int i=1;i<=n;i++){
     	cout<<"Page no a["<<i<<"] ";
     	cin>>a[i];
	}
	
	//Take input of number of frames
	cout<<"\nEnter number of frames\n";
     cin>>no;
            
     //To make all frames -1
	for(int i=0;i<no;i++){
		frame[i]= -1;
	}
          
          int j=0;
          cout<<"\tRef Pg Number\t  Page frames\n";
		for(int i=1;i<=n;i++)
          {
          	//To print reference string
               cout<<"\t\t"<<a[i];
               
			avail=0;
               
			for(k=0;k<no;k++){
               	if(frame[k]==a[i])		//To check if the page is present
                              avail=1;		//To make flag 1 if page is present
			}
				
				//Page not present
                    if (avail==0)
                    {
                              frame[j]=a[i];		//Add new page
                              j=(j+1)%no;		//cyclically repeat
                              count++;			//increase page falult
                              
                         	for(k=0;k<no;k++){
                         		cout<<"\t"<<frame[k];	
						}
                              
				
				}
     		cout<<endl;
		}
                        cout<<"\nNumber of page fault : "<<count;
}
int main(){
	
	
		cout<<"\nPage Replacement Algorithm\n";
		
		    cout << "\nFirst In First Out (FIFO)\n";
		    fifo();
		    
		
	   
	}
