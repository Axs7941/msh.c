


  /*
   Name:Abhyudai Singh
   ID: 1002027941
  */ 
  


#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>




// Used for case in which maximun 10 inputs can be given 
// Have also added null which adds the count uptill 11
#define MAX_ARGS_SIZE 11


//Maximum size of command that a user can enter 
#define MAX_INPUT_SIZE 1024

#define WHITESPACE " \t\n"

// This is to direct the path of program to  /usr/local/bin,/usr/bin & /bin
#define PATH_DIR 		"PATH=.:/usr/local/bin:/usr/bin:/bin"


 
 // initialize and allocate memory to store 
    void initialize(char** charArray, int size)
    {
         int i;
        for(i = 0; i < size; i++)
        {
            free(charArray[i]);
        }
    }

    int main(int argc, char** argv)
    {
        //Will be used to store the user input and commands for parsing later while execution 
        char* str = (char*)malloc(MAX_INPUT_SIZE);  //MALLOC
    
        //Will be used to store the PID ID of child processes and check of how many have turned out
        int pids[15];
        int PIDS_Counter = 0;

        //Will be used to store history which can be viewed 
        //The history will also be resued later to print the history 
        char* cmdhistory[15];
        int i;
        int cmdhistory_count = 0;
    
        putenv(PATH_DIR);
        for(i = 0; i < 15; i++)
        {
            cmdhistory[i] = (char*)malloc(MAX_INPUT_SIZE); //MALLOC
            memset(cmdhistory[i], 0, MAX_INPUT_SIZE);
        }
        
        //This is sitoring the arguments that will be executable 
        char* args[MAX_ARGS_SIZE];
        int token_count = 0;

        //This will make the program run umtill e quits/exits cmd gets called
        while(1)
        {
            printf("msh> ");

            //Reseting the args input so that it does not takes in previous values 
            //As input for the current value
        
            if(token_count !=0)
            {
                initialize(args, token_count);
                token_count = 0;
            }
        
       
            //This is being used to ask for user command input 
            //This needs to be looped until exit/quit commad is called 
            while(fgets(str, MAX_INPUT_SIZE, stdin) != NULL)
            {
                //Neglet input if enterend to avoid running fork
            
                if(strcmp(str, "\n") == 0)
            
                {
                    break;
                }      
            
                else if(strpbrk(str, "!") != NULL)
                {
                    //Checks if user is reusing command in history by comparing index number
                    //This helps to reprint history when ! is found in the str
                    char* token = strtok(str, "!");
                    int cmdhistory_num = atoi(token)-1;
                
                    //Previous commands can be resued if found to be in range
                    //Range: It cannot be greater than 15
                    //Range: It can also be less than 15 when less than 15 commands have been given 
                    //Range: can not be greater than 15
                
                    if(cmdhistory_num <= cmdhistory_count && cmdhistory_num <= 15)
                    {
                        strcpy(str, cmdhistory[cmdhistory_num]);
                    }
                    
                    else
                    {
                        //If command is not found or does not exist, ignore
                        printf("Command not in history.\n");
                        break;
                    }
                }

                //This is History counter used to store history 
                //This will also be used to print 
                //And increment counter to check size of history
                strcpy(cmdhistory[cmdhistory_count++%15], str);
                
                //This is to get the name of the executable
                char* token = strtok(str, WHITESPACE);
                    
                //This will be used to parse the string into tokens keeping in mind the max count 
                //Tokens are used as parameters for execvp(). 
                //I will run this with MAX_ARGS_SIZE-1 so that NULL can be added at end
                while(token != NULL && token_count < MAX_ARGS_SIZE-1)
            
                {
                    args[token_count] = (char*)malloc(MAX_INPUT_SIZE);  //MALLOC
                    strcpy(args[token_count], token);
                    if(strlen(args[token_count]) == 0)
                    args[token_count] = NULL;
                    token = strtok(NULL, WHITESPACE);
                    token_count++;
                }
            
                //This will set all leftover arguments to NULL 
                //Null is needed to use exec
                for(i = token_count; i < MAX_ARGS_SIZE; i++)
                args[i] = NULL;     
            
                //Codded the commands which will be executed and do not require fork
                //Program also needs to end quit or exit is being called as defined earlier
                if(strcmp(args[0], "quit") == 0 || strcmp(args[0], "exit") == 0)
            
                {
                    //Malloc spaces needs to be freed before exiting
                    free(str);
                    initialize(cmdhistory, 15);
                    initialize(args, token_count);
                    return 0;
                }
            
                else if(strcmp(args[0], "pidhistory") == 0)
                {
                    //To print last 15 PID ID's. 
                    //Only 15 PID Ids will be printed and wrap. 
                    for(i = 0; i < PIDS_Counter && i < 15; i++)
                        printf("PID %d: %d\n", i+1, pids[i]);
                    break;
                }   
            
                else if(strcmp(args[0], "history") == 0)
                {
                    //To Print last 15 commands. 
                    //Only 15 commands will be printed. 
                    for(i = 0; i < cmdhistory_count && i < 15; i++)
                        printf("%d: %s", i+1, cmdhistory[i]);
                    break;
                }
            
                else if(strcmp(args[0], "cd") == 0)
                {
                    //The directory will only be changed when arg is greater than 1.
                    //Check for NULL path to avoid chdir() gettings errors about segmentation fault
                    //Check will also avoid incorrect path.
                if(args[1] == NULL)
                        chdir("");
                else
                    chdir(args[1]);
                break;
                }
            
                //Here the child process will run.
                pid_t pid = fork();
                if(pid == 0)
            
                {       
                    int ret = execvp(args[0], args);

                    //When exec failed, print command that failed.
                    if(ret == -1)
                        printf("%s: Command not found.\n", args[0]);
                    return 0;
                    exit(EXIT_SUCCESS);
                }
            
                else if(pid == -1)
                {
                    //If  fork failed, exit the program to prevent further issues
                    perror("Fork failed: ");
                    exit(EXIT_FAILURE);
                }
            
                else
                {
                    int status;
                    //This will make the process Wait until child process finishes and  before allowing another command
                    waitpid(pid, &status, 0);
                
                    //This will store the pids
                    //Only 15W PIDS will be stored and then wraps after 15 pids 
                    pids[PIDS_Counter++%15] = pid;
                    break;
                }  
           }
        } 
    }  


