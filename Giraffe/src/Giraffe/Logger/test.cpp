// test.cpp : 定义控制台应用程序的入口点。
//
#include "Loggerclass.h"
#include "LogItem.h"
using namespace std;




void test_main()
{
	string key;
	U64 i = 0;
	cout<<"input the number 1 is to write logitem "<<endl;
	cout<<"but the number 2 is to read the logitem"<<endl;
	cout<<"but the number 3 is to read directly the logitem"<<endl;
	char get = std::getchar();
	
	int MAX =50000;
	{
		Loggerhandle log;
		log.init();
		string content = "MY";
	   if(get=='1')
	   {
		for(i = 0;i<MAX;i++)
		{
			stringstream str;
			str << i;
			str >> key;
			content += key;
			key += "MYFILE";
			content += "CONTENT";
			PGRFLoggerEventPkt mypkt_i = PGRFLoggerEventPkt(i,WRITE,key,content,false);
			key.clear();
			content.clear();
			content += "MY";
			log.saveItem(mypkt_i);
			if(i%2 == 0)
				log.setEventCommit(i);
		}
		log.terminate();
	//	 log.readfilewithcheck(log.checkpoint);
	//	  log.outCircle->CIQTraverse();
	   }
	   if(get=='2')
	  { 
		 // log.readfilewithcheck(log.checkpoint);
		log.readfromfile();
		log.outCircle->CIQTraverse();
		//  cout<<log.findItem(49950)<<endl;
	//cout<<"要查找的0表示找到，-1表示没找到   "<<endl<< log.findItem(49966)<<endl;
		  
		//  cout<<log.findItem(49951)<<endl;
	   }
	}
	if(i==MAX)
		cout<<"测试数据全部执行"<<endl;
	if(get=='3')
	{
	
	fstream logout;
	logout.open("20000.log");
     logout.seekg(0,ios_base::beg);
	while(!logout)
	{
		cout<<"打开元文件失败"<<endl;
		system("PAUSE");
        logout.open("46000.log");
	}
	for(int i=0;i<200;i++)
	{
	  std::streamoff pospoint = logout.tellg();
	  cout<<"pospoint"<<pospoint<<endl;

	}
	}

	std::getchar();
	std::getchar();
}