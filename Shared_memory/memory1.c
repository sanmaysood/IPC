#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/un.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){

    char array[50][8];

	srand((time(NULL)));

    
    for(int i = 0; i < 50; i++){
        array[i][6] = i ;
    }

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


  
    char *shared_block;
    char *shm;
  
   
    int shmid = shmget((key_t) 2351, 1024, 0644 | IPC_CREAT);
    if(shmid == -1){
        printf("Error in creating shared memory\n");
        return 0;
    }

    shared_block = shmat(shmid,NULL,0);

    int index = 0;

     while(1){

        printf("Sending 5 consecutive strings to the server from index %d to %d\n", index, index + 4);
        

        char send[5][8];

        for(int i = index; i <= index + 4; i++){
    
            strcpy(send[i - index], array[i]);

        }
        
       shm = shared_block;

        for(int i = 0; i < 5; i++){
            strcpy(shm,send[i]);
            shm = shm + 8;
        }


        while(1){
            if(*shared_block == index + 52){
                break;
            }
            else{
                sleep(1);
            }
        }
       
        printf("The server has sent the maximum id %d\n", index+4);
        

        index +=5;
        
        if(index == 50){
            break;
        }
 			
    }

    int t = shmdt(shared_block);
    if(t == -1){
        printf("Error in detaching shared memory\n");
        return 0;
    }

    int v = shmctl(shmid, IPC_RMID, NULL);
    // if(v == -1){
    //     printf("Error in removing shared memory\n");
    //     return 0;
    // }

    return 0;
}

