Introduction
---------------
This demo is to show how Giraffe work which departed into two version for different platforms!
It is simple only with a structure of three servers and three clients, however more servers or
clients can be generated manually if necessary. Before running server or client, configurations need to be set firstly.
Configure files are in <tt>Giraffe_conf<tt> folder, they are  <tt>client_conf.ini<tt> for client and <tt>Giraffe_conf.ini<tt> <tt>MemberShip_conf.ini<tt>
for server. The followings show detail settings of each configure file!

Server Configurations:
---------------
##Giraffe_conf.ini##:
	local-tcp-server-port/local-udp-server-port: server application service tcp/udp
	giraffe-lease-interval: timeout interval for client (microsecond)
	giraffe-mode: CLUSTER/SINGLE, 'SINGLE' means that only one server provides service while 'CLUSTER' means several servers provide service
	giraffe-paxos-sync-interval: the period time for servers contact with each other(microsecond), smaller than giraffe-lease-interval
	giraffe-workers: the number of servers in the cluster
	giraffe-id: server identification which is used to distinguish from the others
	paxos-tcp-port/paxos-udp-port: port for paxos protocol of cluster

	e.g :
		local-tcp-server = 40032
		local-udp-server = 40033
		giraffe-lease-interval = 3000
		giraffe-mode = CLUSTER
		giraffe-paxos-sync-interval = 2000
		giraffe-workers = 3
		giraffe-id = 1
		paxos-tcp-port = 30032
		paxos-udp-port = 30033

##MemberShip_conf.ini##:
this file is to show the cluster status, it is a list of ip/port, the following 'id' ranges from '1' to giraffe-workers

	replica.id-ip: the ip whose giraffe-id is 'id'
	replica.id-port: the tcp port whose giraffe-id is 'id'

	e.g :
		replica.1-id = 211.69.198.201
		replica.1-port = 30032
		replica.1-id = 211.69.198.201
		replica.1-port = 30034
		replica.1-id = 211.69.198.201
		replica.1-port = 30036

##Client configurations##:
	local-tcp-server-port/local-udp-server-port:client tcp/udp
	giraffe-server-ip: the server ip that client wants to connect at first time
	giraffe-server-tcp-port/giraffe-server-udp-port: the server tcp/udp port
	giraffe-lease-interval: period that client heartbeats with server

	client-test-file-path: for test, the test file path

	e.g :
		local-tcp-server-port = 50032
		local-udp-server-port = 50034
		giraffe-server-ip = 211.69.198.201
		giraffe-server-tcp-port = 40032
		giraffe-server-udp-port = 40033
		giraffe-lease-interval = 2500
		client-test-file-path = ./test/test.txt
