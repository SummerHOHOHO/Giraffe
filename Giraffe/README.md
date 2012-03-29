Giraffe-a coordinate service on cloud platform
---------------------
version:  0.1

Description:
---------------------
    Giraffe is a middleware for cloud platform, which provides dependable coordinate service,
    such as lock service ,leader election, failure detetion and so on. It is designed as server-client 
    model, using multi-nodes aimed at hight performance service. Paxos protocol is used to guarantee 
    consistency among cluster. Additionally, a client interface is implemented for external user!
    
Highlight Features:
----------------------
    1. High availability and high dependancy
    2. Light weight coordinate service issue

Build Direction:
----------------------
    windows-building:
      1.enter the win-project directory, open GIRAFFE.sln by Visual Studio
      2.in Giraffe Project there are four sub-projects; rebuild them 
        and executive file will be built into Giraffe/bin/windows derectory
    linux-building:
      1.build network library: enter network directory; make &  make install;
        libnetwork.so will be built into Giraffe/bin/linux
      2.return to Giraffe directory; make giraffe; make client; executive file 
        will be built into Giraffe/bin/linux