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
	//��ȡѡ��Ϊ-ic��-d��ѡ��ֵ
	cout<<c.getParam<int>("-ic")<<endl;
	cout<<c.getParam<int>("-d")<<endl;
	//ͨ����������ȡ�ĸ���ѡ���ֵ
	map<string,string> paramPairs = c.getParams();
	for(map<string,string>::iterator iter=paramPairs.begin(); iter!=paramPairs.end(); iter++)
	{
		cout<<"options: "<<iter->first<<" value: "<<iter->second<<endl;
	}

	//ʹ�õ����������
	DEBUG();
	
	//��ȡ��ǰʱ��
	c.printCurrentTime();

	//��ȡϵͳ�汾
	cout<<c.getSystemVersion()<<endl;

	//��������
	c.mark("the new password is: " + c.createPassword());
	return 0;
}