#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <time.h>

double subtract_time(struct timespec start, struct timespec end)
{
    return (((end.tv_sec-start.tv_sec)*1000000000)+(end.tv_nsec-start.tv_nsec))/1000000000.0;
}

int main(){

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    int new_socket_fd;

    int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if(socket_fd == -1){
        printf("Error in creating socket\n");
        exit(1);
    }

    struct sockaddr_un socket_address;

    memset(&socket_address, 0, sizeof(socket_address));
	
    socket_address.sun_family = AF_UNIX;

    strcpy(socket_address.sun_path, "food");

    int ret = bind(socket_fd, (struct sockaddr *) &socket_address, sizeof(socket_address));

    if(ret == -1){
        printf("Error in binding\n");
        exit(1);
    }

    int c = listen(socket_fd, 0);

    if(c == -1){
        printf("Error in listening\n");
        exit(1);
    }

    new_socket_fd = accept(socket_fd, NULL, NULL);


    if(new_socket_fd == -1){
        printf("Error in accepting the connection\n");
        return 0;
    }

    char receive[5][8];

            for(int x = 0; x < 10; x++){
            
                
                int a = read(new_socket_fd, receive , sizeof(receive));
                if(a == -1){
                    printf("Error in reading\n");
                    exit(1);
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

	            char temp[8];
                sprintf(temp, "%d", max);

                
                int h = write(new_socket_fd, temp, sizeof(temp));
                if(h == -1){
                    printf("Error in writing\n");
                    exit(1);
                }
                
            
              }  


        
        printf("Server is closing the connection\n");
		unlink(socket_address.sun_path);

        clock_gettime(CLOCK_REALTIME, &end);
        printf("Time taken by this IPC : %lf\n", subtract_time(start, end));
        return 0;   
    }


    
