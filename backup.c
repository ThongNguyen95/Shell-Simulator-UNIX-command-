#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/types.h>
static void parse( char* input, char* args[] );
void child_process(char* strArray[]);
void parent_process();

int main(int ac, char* av[]) {
	char input[255];	//buffer to read input from user
	char* strArray[255];	//array of 255 c_strings 
	signal(SIGINT,SIG_IGN);
	do {
		printf("$ ");
		fgets(input,255,stdin);
		parse(input, strArray);
		if (strcmp(strArray[0],"exit") != 0) {
			if (strcmp(strArray[0], "cd") == 0) {
				if (chdir(strArray[1]) < 0)
					printf("ERROR: failed to change directory!\n");
			} else {
				int fork_return;
				fork_return = fork();
				if (fork_return == 0) {
					//child process
					child_process(strArray);
					return 0;
				} else {
					//parent process
					parent_process();
				}
			}
		}
	} while(strcmp(strArray[0],"exit") != 0);
	return 0;
}

static void parse( char* input, char* args[] )
{
  int i = 0;
  
  // fgets reads the \n, so overwrite it
  if (input[strlen(input)-1] = '\n')
	input[strlen(input)-1] = '\0';  
  
  // get the first token
  args[i] = strtok( input, " " );
  
  // get the rest of them
  while( ( args[++i] = strtok(NULL, " ") ) );
}

void child_process(char* strArray[]) {
	//Check for i/o redirection
	int i;
	for(i=0; strArray[i] != 0;i++) {
		if (!strcmp(strArray[i],"|") {
			//Piping
			
			
		} else if (!strcmp(strArray[i],">")) {
				if (strArray[i+1] != 0) {
				int fd;
				//Output redirection
				close(1);
				fd = creat(strArray[i+1], 0644);
				strArray[i] = 0;
			} else {
				printf("SYNTAX ERROR!\n");
				return;
			}
			break;
		} else if (!strcmp(strArray[i],"<")) {
			if (strArray[i+1] != 0) {
				int fd;
				//Output redirection
				close(0);
				fd = open(strArray[i+1], 0644);
				strArray[i] = 0;
			} else {
				printf("SYNTAX ERROR!\n");
				return;
			}
			break;
		}
	}
	//Calling exevp
	if (execvp(strArray[0],strArray) < 0)
		printf("ERROR: program execution failed!\n");
}
void parent_process() {
	wait();
}