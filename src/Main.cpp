//demo
#include "Console.h"

int main(int argc, char** argv)
{
	Console c;

	//color text
	c.error("this is a error");
	c.warning("this is a warning");
	c.mark("this is a mark: stage#1");
	c.ask("this is a question");

	cout<<endl;

	//turn on timer
	c.turnOnTimer();
	Sleep(1000);
	c.turnOffTimer();
	cout<<c.getTimeDiff()<<endl;

	//Use command line param parser
	vector<string> options;
	options.push_back("-ic");
	options.push_back("-d");
	c.initCommandLineParser(argc, argv, options);
	c.setDefaultValue("-ic", 6);
	c.setDefaultValue("-d",323);
	//获取选项为-ic，-d的选项值
	cout<<c.getParam<int>("-ic")<<endl;
	cout<<c.getParam<int>("-d")<<endl;
	//通过遍历来获取的各个选项的值
	map<string,string> paramPairs = c.getParams();
	for(map<string,string>::iterator iter=paramPairs.begin(); iter!=paramPairs.end(); iter++)
	{
		cout<<"options: "<<iter->first<<" value: "<<iter->second<<endl;
	}

	//使用调试输出函数
	DEBUG();
	
	//获取当前时间
	c.printCurrentTime();

	//获取系统版本
	cout<<c.getSystemVersion()<<endl;

	//创建密码
	c.mark("the new password is: " + c.createPassword());
	return 0;
}