#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>


int main(){

char array[50][8];

	srand((unsigned int)(time(NULL)));

    
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


    printf("\n");
    printf("\n");
    printf("\n");


    int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if(socket_fd == -1){
        printf("Error in creating socket\n");
        exit(1);
    }

    struct sockaddr_un socket_address;

    memset(&socket_address, 0, sizeof(socket_address));
	
    socket_address.sun_family = AF_UNIX;

    strcpy(socket_address.sun_path, "food");

    int ret = connect(socket_fd, (struct sockaddr *) &socket_address, sizeof(socket_address));

    if(ret == -1){
        printf("Error in connecting to the socket\n");
        exit(1);
    }

     int index = 0;

     while(1){

        printf("Sending 5 consecutive strings to the server from index %d to %d\n", index, index + 4);

        char send[5][8];

        for(int i = index; i <= index + 4; i++){
    
            strcpy(send[i - index], array[i]);

        }
        
        int r1 = write(socket_fd, send, sizeof(send));

        if(r1 == -1){
            printf("Error in writing to the socket\n");
            exit(1);
        }
        

       	int id;
        char str[10];

        
        int r2 = read(socket_fd, str, sizeof(str));

        if(r2 == -1){
            printf("Error in reading from the socket\n");
            exit(1);
        }
        

        id = atoi(str);
        printf("The server has sent the maximum id %d\n", id);
        
        index = id + 1;
        
        if(index == 50){
            break;
        }
 			
    }

	return 0;
}

