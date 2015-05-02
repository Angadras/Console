//Console = CmdParser + Console + ��������
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

//*****************************�������������Ϣ�Ĺ���*********************
#define __DEBUG__//����������е�DEBUG��ʾ��Ϣʱ����ע�͸�ָ������Ϊ#undef __DEBUG__ 
#ifdef __DEBUG__
#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d "format"\n", __LINE__, ##__VA_ARGS__)
//' ## '����˼�ǣ�����ɱ���������Ի�Ϊ�գ���ʹԤ�������� preprocessor ��ȥ������ǰ����Ǹ����š�
#else
#define DEBUG(format,...)//��ָ�����������δ����__DEBUG__���Ҵ�����ʹ����DEBUG��������£���֤������������������DEBUG��������ʾ��Ϣ������
#endif

//*************������ǰ���ͱ�������ɫ******************
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
//***************ʱ�䵥λ*****************************
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
	//��������Դ�����
	void error(string s);//���������Ϣ
	void warning(string s);//���������Ϣ
	//void prompt(string s);//�����ʾ��Ϣ
	void mark(string s);//��������Ϣ
	void ask(string s);//������⣨ĩβ�Դ�>>��
	//***********************Cmd Parser********************************
	//ʹ���ļ�������ѡ��ĸ���ֵ����δʵ��
	void initConfigureFileParser(string filePath);
	//ʹ��������������ѡ��ĸ���ֵ
	void initCommandLineParser(int argc, char** argv, vector<string> options);
	//����ָ��ѡ���Ĭ��ֵ����������û�����øò���ʱ��ʹ�ø�Ĭ��ֵ������Ϊÿһ������������Ĭ��ֵ
	template <class T> void setDefaultValue(string option, T value);
	void setDefaultValues(string configureFile);
	//��ȡָ��ѡ��Ĳ�������ָ���䷵�����ͣ����øú�������ִ�з���ֵ���͡�����int value = CD.getParam<int>("-i");
	template <class T> T getParam(string option);
	map<string,string> getParams();
	//**********************��ʱ****************************************
	void turnOnTimer();
	void turnOffTimer();
	double getTimeDiff(int timeUnit);
	//**********************����****************************************
	//��ȡϵͳ��ǰʱ�䣬��ʽΪSat May 02 17:32:15 2015���Դ�����
	void printCurrentTime();
	void pause();
	//��ȡ����ϵͳ�汾
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
	//***********************��ʱ**************************************
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
			//���ֵ�Ƿ����ַ����Σ���������Ϊ�Ƿ�
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