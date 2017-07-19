#include "../include/client.h"

int main( int argc, char **argv ) {
  int sk;
  struct ip_mreq req;
  struct sockaddr_in server;
  char buf[MAXBUF];
  int n_read;


  if ((sk = socket( AF_INET, SOCK_DGRAM, 0 )) < 0){
    printf("Problem creating socket\n");
    exit(-1);
  }


  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("224.5.5.5");
  server.sin_port = htons(7777);


  req.imr_multiaddr.s_addr = inet_addr("224.5.5.5");
  req.imr_interface.s_addr = htonl(INADDR_ANY);

  setsockopt(sk, IPPROTO_IP, IP_ADD_MEMBERSHIP, &req, sizeof(struct ip_mreq));

  if(bind(sk,(struct sockaddr*) &server,sizeof(server)) < 0){
		perror("bind error");
		exit(-1);
	}
	while(1){
		n_read = recvfrom(sk, buf, MAXBUF, 0, NULL, NULL);
		if (n_read<0) {
			perror("#UDP# Problem in recvfrom");
			exit(-1);
		}
		printf("#UDP# Client receive message from server: %s (%d bytes)\n\n", buf,
                                                                       n_read);
	}
	return(0);
}
