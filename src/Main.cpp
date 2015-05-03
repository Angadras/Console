//demo
#include "Console.h"

int main(int argc, char** argv)
{
	Console c;
	c.turnOnTimer();

	vector<string> options;
	options.push_back("-iabc");
	options.push_back("-d");
	
	c.initCommandLineParser(argc, argv, options);
	c.setDefaultValue("-iabc", 6);
	c.setDefaultValue("-d",323);

	//获取选项为-i的选项值
	cout<<c.getParam<int>("-iabc")<<endl;
	cout<<c.getParam<int>("-d")<<endl;

	//遍历得到的参数
	map<string,string> paramPairs = c.getParams();
	for(map<string,string>::iterator iter=paramPairs.begin(); iter!=paramPairs.end(); iter++)
	{
		cout<<"options: "<<iter->first<<" value: "<<iter->second<<endl;
	}
	DEBUG();
	c.turnOffTimer();
	c.printCurrentTime();
	cout<<c.getTimeDiff(MS)<<endl;
	cout<<c.getSystemVersion()<<endl;
	c.ask("please input your password: ");
	c.getPassword();
	c.mark("the password is: " + c.getSavedPassword());
	return 0;
}