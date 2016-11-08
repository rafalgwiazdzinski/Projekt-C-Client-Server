/************* UDP CLIENT CODE *******************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

struct zmienne {
	char operacja;
	int x;
	int y;
};

struct zmienne sParametry;

void wypiszLiczby(){
printf("Liczba 1: %d \nLiczba 2: %d \nZnak: %c \n",sParametry.x,sParametry.y,sParametry.operacja);
}
void (*wskWypisanie)();

int main(int argc, char *argv[]){

  //Pointer to function
  wskWypisanie = wypiszLiczby;

  if(isdigit(argv[2][0])) {
		sParametry.x = atoi(argv[2]);
	} else {
		printf("Wprowadz liczbe jako parametr\n");
		return 0;
	}

	if(isdigit(argv[3][0])) {
		sParametry.y = atoi(argv[3]);
	} else {
		printf("Wprowadz liczbe jako parametr\n");
		return 0;
	       }


  sParametry.operacja = *argv[1];

  //Writing parameters
  wskWypisanie();

  int clientSocket, portNum, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*Create UDP socket*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("192.168.119.73");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverAddr;

  //Copy structure parameters to buffer to send it to server
  memcpy (buffer, &sParametry, sizeof(sParametry));

  printf("You typed: %s",buffer);  


  nBytes = sizeof(sParametry);
    
  /*Send message to server*/
  sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
  

  while(1){
  /*Receive message from server*/ 

  nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);
  float wynik;
  if(nBytes!=0){
  memcpy(&wynik, buffer, sizeof(wynik));
  }

  printf("\nReceived from server: %f\n",wynik);
  }

  return 0;
}


