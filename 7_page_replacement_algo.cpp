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



void optimal(){
	int no_of_frames, no_of_pages, frames[10], pages[30], temp[10], flag1, flag2, flag3, i, j, k, pos, max, faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);
    
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);
    
    printf("Enter page reference string: ");
    
    for(i = 0; i < no_of_pages; ++i){
        scanf("%d", &pages[i]);
    }
    
    for(i = 0; i < no_of_frames; ++i){
        frames[i] = -1;
    }
    
    for(i = 0; i < no_of_pages; ++i){
        flag1 = flag2 = 0;
        
        for(j = 0; j < no_of_frames; ++j){
            if(frames[j] == pages[i]){
                   flag1 = flag2 = 1;
                   break;
               }
        }
        
        if(flag1 == 0){
            for(j = 0; j < no_of_frames; ++j){
                if(frames[j] == -1){
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }    
        }
        
        if(flag2 == 0){
         flag3 =0;
        
            for(j = 0; j < no_of_frames; ++j){
             temp[j] = -1;
            
             for(k = i + 1; k < no_of_pages; ++k){
             if(frames[j] == pages[k]){
             temp[j] = k;
             break;
             }
             }
            }
            
            for(j = 0; j < no_of_frames; ++j){
             if(temp[j] == -1){
             pos = j;
             flag3 = 1;
             break;
             }
            }
            
            if(flag3 ==0){
             max = temp[0];
             pos = 0;
            
             for(j = 1; j < no_of_frames; ++j){
             if(temp[j] > max){
             max = temp[j];
             pos = j;
             }
             }            
            }
frames[pos] = pages[i];
faults++;
        }
        
        printf("\n");
        
        for(j = 0; j < no_of_frames; ++j){
            printf("%d\t", frames[j]);
        }
    }
    
    printf("\n\nTotal Page Faults = %d", faults);
}


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
int main(){
	int choice=1;
	
	while(choice!=0){
		cout<<"\nPage Replacement Algorithms\n";
		cout<<"\n1. First In First Out (FIFO) \n";
		cout<<"2. Optimal Page replacement \n";
		cout<<"3. Least Recently Used\n";
		cout<<"0. Exit\n\n";
		cout<<"Enter your choice\n";
		cin>>choice;
		
		switch (choice) {
		  case 1:
		    cout << "\nFirst In First Out (FIFO)\n";
		    fifo();
		    break;
		  case 2:
		    cout << "\nOptimal Page replacement \n";
		    optimal();
		    break;
		  case 3:
		    cout << "\nLeast Recently Used\n";
		    lru();
		    break;
		 
		}
		
		
	}
}
