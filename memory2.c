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


double subtract_time(struct timespec start, struct timespec end)
{
    return (((end.tv_sec-start.tv_sec)*1000000000)+(end.tv_nsec-start.tv_nsec))/1000000000.0;
}

int main(){
    
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    char *shared_block;
    char *s;
  
    
    int shmid = shmget((key_t) 2351, 1024, 0644 | IPC_CREAT);

    if(shmid == -1){
        printf("Error in creating shared memory\n");
        exit(1);
    }

    shared_block = shmat(shmid,NULL,0);

    if(shared_block == (void *)-1){
        printf("Error in attaching shared memory\n");
        exit(1);
    }

    
    char receive[5][8];

            while(1){

                s = shared_block;
                for(int i = 0; i < 5; i++){
                    strcpy(receive[i], s);
                    s += 8; 
                }
             
                
                char final[5][7];
                for(int i = 0; i < 5; i++){
                    for(int j = 0; j < 6; j++){
                        final[i][j] = receive[i][j];
                    }
                    final[i][6] = '\0';
                }
                for(int j = 0; j < 5; j++){
                    int id = receive[j][6];
                    printf("Received string having id %d:  %s\n", id, final[j]);
                    
                }

            
                int max = receive[4][6];

                char w = (char) (max + 48);

                *shared_block = w;
                if(max == 49){

                    break;
                }
                while(*shared_block == w){}

              }

    int r = shmdt(shared_block);
    if(r == -1){
        printf("Error in detaching shared memory\n");
        exit(1);
    }
    
    int f = shmctl(shmid, IPC_RMID, NULL);
    if(f == -1){
        printf("Error in removing shared memory\n");
        exit(1);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time taken by this IPC : %lf\n", subtract_time(start, end));
    
    return 0;
}
