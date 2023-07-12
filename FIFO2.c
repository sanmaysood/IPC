#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/un.h>
#include <fcntl.h>
#include <time.h>


double subtract_time(struct timespec start, struct timespec end)
{
    return (((end.tv_sec-start.tv_sec)*1000000000)+(end.tv_nsec-start.tv_nsec))/1000000000.0;
}

int main(){

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    mkfifo("pipeA", 0666);
    mkfifo("pipeB", 0666);

    char receive[5][8];

            for(int x = 0; x < 10; x++){
            
                int fd1 = open("pipeA", O_RDONLY);
                read(fd1, receive , sizeof(receive));
                close(fd1);
                
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


	            char temp[8];
                sprintf(temp, "%d", receive[4][6]);

                int fd2 = open("pipeB", O_WRONLY);
                write(fd2, temp, sizeof(temp));
                close(fd2);
            
              }  


    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time taken in IPC mechanism : %lf\n", subtract_time(start, end));
    return 0;
}
