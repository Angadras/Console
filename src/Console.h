//Console = CmdParser + Console + 其它功能
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>

//*****************************用于输出调试信息的工具*********************
#define __DEBUG__//不想令代码中的DEBUG显示信息时可以注释该指令或将其改为#undef __DEBUG__ 
#ifdef __DEBUG__
#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d "format"\n", __LINE__, ##__VA_ARGS__)
//' ## '的意思是，如果可变参数被忽略或为空，将使预处理器（ preprocessor ）去除掉它前面的那个逗号。
#else
#define DEBUG(format,...)//该指令的作用是在未定义__DEBUG__宏且代码中使用了DEBUG语句的情况下，保证编译器不报错，并且令DEBUG不发挥显示信息的作用
#endif

//*************命令行前景和背景的颜色******************
//B = bright
#define BLACK       0
#define BLUE        1
#define GREEN       2
#define PALEBLUE    3
#define RED         4
#define PURPLE      5
#define YELLOW      6
#define WHITE       7
#define GRAY        8
#define B_BLUE      9
#define B_GREEN    10
#define B_PALEBLUE 11
#define B_RED      12
#define B_PURPLE   13
#define B_YELLOW   14
#define B_WHITE    15
//***************时间单位*****************************
#define S   0
#define MS  1

using std::string;
using std::map;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

class Console
{
public:
	//***********************Color cout*********************************
	//输出语句均自带换行
	void error(string s);//输出错误信息
	void warning(string s);//输出警告信息
	//void prompt(string s);//输出提示信息
	void mark(string s);//输出标记信息
	void ask(string s);//输出问题（末尾自带>>）
	//***********************Cmd Parser********************************
	//使用文件来载入选项的各个值，还未实现
	void initConfigureFileParser(string filePath);
	//使用命令行来载入选项的各个值
	void initCommandLineParser(int argc, char** argv, vector<string> options);
	//设置指定选项的默认值，当命令行没有设置该参数时就使用该默认值，建议为每一个参数都设置默认值
	template <class T> void setDefaultValue(string option, T value);
	void setDefaultValues(string configureFile);
	//获取指定选项的参数，并指定其返回类型，调用该函数必须执行返回值类型。例如int value = CD.getParam<int>("-i");
	template <class T> T getParam(string option);
	map<string,string> getParams();
	//**********************计时****************************************
	void turnOnTimer();
	void turnOffTimer();
	double getTimeDiff(int timeUnit);
	//**********************其它****************************************
	//获取系统当前时间，格式为Sat May 02 17:32:15 2015，自带换行
	void printCurrentTime();
	void pause();
	//获取操作系统版本
	string getSystemVersion();
private:
	//***********************Color cout*********************************
	void setConsoleTextColor(unsigned short ForeColor = WHITE, unsigned short BackGroundColor = BLACK);
	void templateCout(string s, int color);
	//***********************Cmd Parser********************************
	string programName;
	vector<string> options;
	map<string,string> paramPairs;
	void exitWithHelp();
	template <class Input, class Output>
	Output convertDataType(const Input& a);
	//***********************计时**************************************
	clock_t startTime;
	clock_t endTime;
};

template <class T> void Console::setDefaultValue(string option, T value)
{
	bool optionExist = false;
	for(vector<string>::size_type index=0; index<options.size(); index++)
	{
		if(0 == options.at(index).compare(option))
		{
			//检查值是否被连字符修饰，修饰则认为非法
			if(0 == convertDataType<T, string>(value).substr(0,1).compare("-"))
			{
				error("The value of " + option + " is illegal");
				exitWithHelp();
			}
			paramPairs.insert(make_pair(options.at(index),convertDataType<T, string>(value)));
			//paramPairs[options.at(index)] = value;
			optionExist = true;
		}
	}
	if(false == optionExist)
	{
		error("Unknown option: " + option);
		exitWithHelp();
	}
}

template <class T> T Console::getParam(string option)
{
	map<string,string>::iterator iter = paramPairs.find(option);
	if(paramPairs.end() != iter)
	{
		return convertDataType<string, T>(iter->second);
	}
	else
	{
		error("The value of the option " + option + " does not exist!");
		exitWithHelp();
	}
}

template <class Input, class Output>
Output Console::convertDataType(const Input& a)
{
	stringstream ss;
	Output b;
	ss<<a;
	ss>>b;
	return b;
}

#endif