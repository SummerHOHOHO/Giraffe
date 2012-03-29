Project name:Giraffe
Version:  0.1
build-direction:
  windows-building:
    1.enter the win-project directory, open GIRAFFE.sln by Visual Studio
    2.in Giraffe Project there are four sub-projects; rebuild them 
      and executive file will be built into Giraffe/bin/windows derectory
  linux-building:
    1.build network library: enter network directory; make &  make install;
      libnetwork.so will be built into Giraffe/bin/linux
    2.return to Giraffe directory; make giraffe; make client; executive file 
      will be built into Giraffe/bin/linux