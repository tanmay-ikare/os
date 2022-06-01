#include<iostream>
#include<stdio.h>
using namespace std;
void lru(){
	int nopages,noframe , page[20],i ,count=0;
            
            cout<<"\n Enter no of pages for which you want to calculate page faults : "; 
            cin>> nopages;  //it will store the number of Pages
            
		  cout<<"\n Enter the value for page number :";
            for(i=0;i< nopages;i++)
            {
	            cout<<"Page no a["<<i<<"] "; 
	            cin>>page[i];
            }  
		   
            cout<<"\n Enter the Number of frames:"; 
            cin>> noframe;
            
            int frame[noframe],fcount[noframe];
            
            for(i=0;i< noframe;i++)
            {
	            frame[i]=-1;
	            fcount[i]=0; //it will keep the track of when the page was last used
            }
            
            i=0;
             cout<<"\n Ref Pg Number\t\t  Page frames\n";
            while(i< nopages)
            {
                int j=0,flag=0;
                
                while(j< noframe)
                {
	                if(page[i]==frame[j]){ 
		                flag=1;
		                fcount[j]=i+1;
                		}
                	j++;
                }
			    
                j=0;  
                cout<<"\t\n";
                cout<<"\t"<<page[i]<<" ";
			    
                if(flag==0)
                {
                	int min=0,k=0;
                	while(k<noframe-1) 
                	{ 
                    	if(fcount[min]>fcount[k+1]) //It will calculate the page which is least recently used
	                    	min=k+1;
	                    	
	                    k++;
                    }
                
			 	frame[min]=page[i]; 
                	fcount[min]=i+1;  //Increasing the time
                	count++;           //it will count the total Page Fault
                	
				 while(j< noframe)
	                {
		                cout<<"\t\t"<<frame[j]<<"";
		                j++;
	                }
                }
            	i++; 
            }
            cout<<"\n\t\n";
            cout<<"\n\t Page Fault:"<<count;
}
int main()
{
	cout<<"\nPage Replacement Algorithm\n";
	cout << "\nLeast Recently Used\n";
		    lru();
		}
