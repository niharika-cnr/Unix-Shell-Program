#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 80

void displayHistory(FILE* F_out);

int main()	{
/*
 *opens a 'history.txt' for the purpose of APPENDING. If file does not 
 *exist, creates file with specified name and lets user add data to it.
 */
	FILE *F_in=fopen("history.txt","a"), *F_out=NULL;
	
	//declares and initializes a few looping and condtion-checking variables
	int i,inCount=0,outCount=0,should_run=1;
	
	//declares an array of pointers to store all the user-given commands
	char *args[MAX/2 + 1];
	
	//allocating space to all the pointers in the array
	for(i=0 ; i<=MAX/2 ; i++)
	   args[i] = malloc(256*sizeof(char));
	   
	//starts the shell   
	do {
	   printf("NihaSanju> ");
	   
	   //stores the command typed by the user in the args[]
	   gets(args[inCount]);
	   
	   //puts the command typed by the user into the created file and goes to a new line
	   fputs(args[inCount],F_in);
	   fputc('\n',F_in);
	   fflush(F_in);
	   
	   //display the whole history if the user requests
	   if(!strcmp(args[inCount],"history"))  {
	      F_out=fopen("history.txt","r");
	      displayHistory(F_out);
	   }
	   
	   //exits from shell if user types 'quit'or 'q()'
	   should_run = strcmp(args[inCount],"quit") * strcmp(args[inCount++],"q()");
	}while(should_run);

   fclose(F_in);
   fclose(F_out);   
	return 0;
}


//function to display hitory of commands written in the shell
void displayHistory(FILE* F_out) {
   
   //declares a char to print commands when user requests to
	char s='0';
		
	//an int to keep track of command cmdCount
	int cmdCount=1;
	
   //checks if the file exists
   if(F_out!=NULL) {
	   while(1)     {
	   	//scan each character at a time from the file and print it if it is not EOF
         s=fgetc(F_out);
         if(s!=EOF)  {
         	//prints the command number if entering into a new line
            if(s=='\n')
               printf("\n%d  ",cmdCount++);
            else
               printf("%c",s);           
         }//endif
         //if there are no commands already saved in file, print the latest command typed, 'history'
         else  {
            if(cmdCount==1)
               printf("history\n");           
            break; 
         }//end else   
	   }//end while	            
	}//end if
	
	else printf("\nFile not found");
}