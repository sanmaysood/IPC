#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/un.h>
#include <fcntl.h>

int main () {

    char array[50][8];

	srand((unsigned int)(time(NULL)));

    // Last element of the string is the index
    for(int i = 0; i < 50; i++){
        array[i][6] = i ;
    }

    // using rand() function to generate a random integer (and eventually generating a random character)
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 6; j++){
            array[i][j] = (rand() % 26) + 65;
        }
        array[i][7] = '\0';
    }
	
    printf("The array of size 50 containing random strings of size 6 each is:\n");

	for(int i = 0; i < 50; i++) {

		for(int j = 0; j < 8; j++) {

			if(j != 6) {
                printf("%c", array[i][j]);
				
			}

			else{
                printf("ID : %d", array[i][j]);
            }
		}
		printf("\n");
	}


    mkfifo("pipeA", 0666);

    
    mkfifo("pipeB", 0666);


    int index = 0;

     while(1){

        printf("Sending 5 consecutive strings to the server from index %d to %d\n", index, index + 4);

        char send[5][8];

        for(int i = index; i <= index + 4; i++){
    
            strcpy(send[i - index], array[i]);

        }

        int fd1 = open("pipeA", O_WRONLY);
        write(fd1, send, sizeof(send));

       
        close(fd1);

       	int id;
        char str[10];

        int fd2 = open("pipeB", O_RDONLY);
         read(fd2, str, sizeof(str));

    
        close(fd2);

        id = atoi(str);
        printf("The server has sent the maximum id %d\n", id);
        
        index = id + 1;
        
        if(index == 50){
            break;
        }
 			
    }


    return 0;
}

