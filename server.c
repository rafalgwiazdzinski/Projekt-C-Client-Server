#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "projektbiblioteka.h"

struct Liczby {
	char dzialanie;
	int liczba1;
	int liczba2;
};

int main(){
	struct Liczby liczby;
  	int udpSocket, nBytes;
  	char buffer[1024];
  	struct sockaddr_in serverAddr, clientAddr;
  	struct sockaddr_storage serverStorage;
  	socklen_t addr_size, client_addr_size;
  	int i;

  	/*Create UDP socket*/
  	udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  	/*Configure settings in address struct*/
  	serverAddr.sin_family = AF_INET;
  	serverAddr.sin_port = htons(7891);
  	serverAddr.sin_addr.s_addr = inet_addr("192.168.119.73");
  	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  	/*Bind socket with address struct*/
  	bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  	/*Initialize size variable to be used later on*/
  	addr_size = sizeof serverStorage;

  	while(1){
    	/* Try to receive any incoming UDP datagram. Address and port of 
    	  requesting client will be stored on serverStorage variable */
    	nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
	
    	if(nBytes !=0) {
		memcpy(&liczby, buffer, sizeof(liczby));
		float wynik;
		if(liczby.dzialanie == '+') {
			wynik = dodawanie(liczby.liczba1, liczby.liczba2);
		} else if(liczby.dzialanie == '-') {
			wynik = odejmowanie(liczby.liczba1, liczby.liczba2);
		} else if(liczby.dzialanie == '*') {
			wynik = mnozenie(liczby.liczba1, liczby.liczba2);
		} else if(liczby.dzialanie == '/') {
			wynik = dzielenie(liczby.liczba1, liczby.liczba2);
		}
		memcpy(buffer, &wynik, sizeof(wynik));

		//printf("buffer = %d\n", buffer);
    		/*Send uppercase message back to client, using serverStorage as the address*/
    		sendto(udpSocket,buffer,sizeof(wynik),0,(struct sockaddr *)&serverStorage,addr_size);
		}
 	}

  	return 0;
}
