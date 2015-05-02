#include "Console.h"

void Console::setConsoleTextColor(unsigned short ForeColor,unsigned short BackGroundColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (ForeColor%16)|(BackGroundColor%16*16));
}

void Console::templateCout(string s, int color)
{
	setConsoleTextColor(color);
	std::cout<< s <<std::endl;
	setConsoleTextColor();
}

void Console::error(string s)
{
	templateCout("Error: "+s, B_RED);
}

void Console::warning(string s)
{
	templateCout("Warning: "+s, B_YELLOW);
}

/*void Console::prompt(string s)
{
	templateCout(s, WHITE);
}*/

void Console::mark(string s)
{
	templateCout(s, B_GREEN);
}

void Console::ask(string s)
{
	templateCout(s, B_WHITE);
	cout<<">>";
}

void Console::initCommandLineParser(int argc, char** argv, vector<string> options)
{
	this->options = options;
	this->programName = argv[0];

	//�ж��û��Ƿ�û�������κ�ѡ���ֵ
	if(1==argc)
	{
		warning("No options have been set in the command, they will be set to default values");
		//exitWithHelp();
	}

	for(int i=1; i<argc; i=i+2)
		//i��ȡֵ��1��argc-1����argc������������������option��������������1֮�����option����������������
		//argv[i]�ǵ�ַ����ָ��һ���ַ�������ͬ���ַ��������������argv[i][j]���Ǹ������е�ĳһԪ��
	{
		string optionDash, optionChar, value;
		optionDash = convertDataType<char,string>(argv[i][0]);
		optionChar = convertDataType<char,string>(argv[i][1]);

		//���ÿ��ѡ��ĵ�һ���ַ�����-���Ǿ��˳�ѭ������Ϊ�����ѡ���ʽ���Ϸ�
		if(0 != optionDash.compare("-"))
		{
			error("Illegal input: " + optionDash + ", need to add the -");
			exitWithHelp();
			break;
		}

		//�ж�ѡ������Ƿ����ַ���
		if((i+1) > (argc-1))
		{
			error("No value: " + optionDash + optionChar);
			exitWithHelp();
		}
		value = convertDataType<char*,string>(argv[i+1]);

		bool optionExist = false;
		for(vector<string>::size_type index=0; index<options.size(); index++)
		{
			if(0 == options.at(index).compare(optionDash + optionChar))
			{
				//���ֵ�Ƿ����ַ����Σ���������Ϊ�Ƿ�
				if(0 == value.substr(0,1).compare("-"))
				{
					error("The value of " + optionDash + optionChar + " is illegal");
					exitWithHelp();
				}
				//paramPairs.insert(make_pair(options.at(index),value));
				paramPairs[options.at(index)] = value;
				optionExist = true;
			}
		}
		if(false == optionExist)
		{
			error("Unknown option: -" + optionChar);
			exitWithHelp();
		}
	}
}

void Console::exitWithHelp()
{
	cout<<"Usage: "<<programName<<" [-option] value"<<endl
		<<"[-option]: ";
	for(vector<string>::size_type i=0; i<options.size(); i++)
	{
		cout<<options.at(i)<<" ";
	}
	cout<<endl;
	exit(1);
	//throw std::exception("");
}

map<string,string> Console::getParams()
{
	return paramPairs;
}

void Console::pause()
{
	system("pause");
}

void Console::turnOnTimer()
{
	startTime = clock();
}

void Console::turnOffTimer()
{
	endTime = clock(); 
}

double Console::getTimeDiff(int timeUnit)
{
	long diffTime_ms = endTime-startTime;
	switch(timeUnit)
	{
	case S:
		{
			return (double)(diffTime_ms)/CLOCKS_PER_SEC;
			break;
		}
	case MS:
		{
			return (double)diffTime_ms;
			break;
		}
	}
}

/*
���й���windows�汾��������Ϣ���������ӣ�
http://msdn.microsoft.com/en-us/library/ms724834(v=vs.85).aspx
��Щ����Ϣ���ض���ͨ�����жϵġ�
*/
string Console::getSystemVersion()
{  
	OSVERSIONINFO osvi;  
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));  
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);  
	if (!GetVersionEx(&osvi)) {  
		return NULL;  
	}  

	//�жϰ汾  
	if (osvi.dwMajorVersion == 5) {  

		switch (osvi.dwMinorVersion) {  
		case 0:  
			return "Windows 2000";  
		case 1:  
			return "Windows XP";  
		case 2:  
			return "Windows Server 2003";  
		default:  
			return "Unknown System";  
		}  

	}else if (osvi.dwMajorVersion == 6) {  

		switch (osvi.dwMinorVersion) {  
		case 0:  
			return "Windows Vista";  
		case 1:  
			return "Windows 7";  
		case 2:  
			return "Windows 8";  
		default:  
			return "Unknown System";  
		}  

	}else {  
		return "Unknown System";  
	}  
}  

void Console::printCurrentTime()
{
	time_t t;
    time(&t);
	cout<<ctime(&t);
}