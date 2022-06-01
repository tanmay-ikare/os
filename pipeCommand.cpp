#include <stdio.h>
#include <string.h>
#include <unistd.h>

//Function for writing string
void processA(int writefd)
{
    char str[80]; //String variable
    int strLen;
    printf("\n--> Enter a string: ");
    scanf("%s",str); //Taking Input
    strLen = strlen(str);
    if(str[strLen-1]=='\n') //Removing \n
    {
        strLen--;
    }
    write(writefd,str,strLen); //Writing to pipe
}
//Function for reading string
void processB(int readfd)
{
    int strLen,i,j;
    char str[80],temp;
    strLen=read(readfd,str,80); //Reading from pipe
    str[strLen]='\0'; //Appending special character indicating end of string
    i=0;
    j=strlen(str)-1;
    while(i<j) //Reversing the string
    {
        temp=str[i];
        str[i]=str[j];
        str[j]=temp;
        i++;
        j--;
    }
    printf("\n--> Reversed string: %s\n",str);
}
//Main code
int main() {
    int pipe1[2],childpid;
    pipe(pipe1); //Pipe created
    printf("\n\n--- String Reverse Utility ---\n\n");
    childpid = fork(); //Child process created
    if (childpid==0)
    {
        close (pipe1[1]); //Closing write end
        processB (pipe1[0]);
    }
    else
    {
        close (pipe1[0]); //Closing read end
        processA (pipe1[1]);
    }
    return 9;
}


