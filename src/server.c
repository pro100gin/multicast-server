#include "../include/server.h"


int main() {
	/*var for udp*/
	int ld = 0, n = 0;
	struct sockaddr_in skaddr;
	socklen_t length;
	char bufout[MAX_MSG_SIZE] = "hello, i'm udp multicast server";

	/*initialize UDP server*/
	if ((ld = socket( AF_INET, SOCK_DGRAM, 0 )) < 0) {
		printf("#UDP# Problem creating socket\n");
		exit(1);
	}

	skaddr.sin_family = AF_INET;
	skaddr.sin_addr.s_addr = inet_addr("224.5.5.5");/*htonl(INADDR_BROADCAST)*/
	skaddr.sin_port = htons(7777);


  length = sizeof(skaddr);
	printf("#UDP# The server ip is %s port number is %d\n",
		inet_ntoa(skaddr.sin_addr), ntohs(skaddr.sin_port));

	/*main loop*/
	while(1) {
		n = sendto(ld, bufout, strlen(bufout), 0,
		        (struct sockaddr *)&skaddr, length);
		if(n < 0){
			perror("#UDP# Error sending to client");
		}
		printf("#UDP# Sending datagram to client\n");
		sleep(2);
	}
	close(ld);

	exit(EXIT_SUCCESS);
}
