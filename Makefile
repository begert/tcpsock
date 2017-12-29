both: server client udp_server udp_client

server: server.c
	gcc server.c -o server

client: client.c
	gcc client.c -o client

udp_server: udp_server.c
	gcc udp_server.c -o udp_server

udp_client: udp_client.c
	gcc udp_client.c -o udp_client
