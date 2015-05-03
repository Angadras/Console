# Console

Console is a simple, small, efficient win32 console application tool that can be easily integrated into other programs.

The master is hosted on github:
<https://github.com/Wu-Hong/Console>

Examples
--------
	Console c;

#### Print color text.
	c.error("this is a error");
	c.warning("this is a warning");
	c.mark("this is a mark: stage#1");
	c.ask("this is a question");
![](https://github.com/Wu-Hong/Console/blob/master/pix/color_text.png "")

#### Use the timer.
	c.turnOnTimer();
	Sleep(1000);
	c.turnOffTimer();
	cout<<c.getTimeDiff()<<endl;

### Use command line param parser
	vector<string> options;
	options.push_back("-ic");
	options.push_back("-d");
	
	//Initialize parser
	c.initCommandLineParser(argc, argv, options);
	c.setDefaultValue("-ic", 6);
	c.setDefaultValue("-d",323);
	
	//get the values of -ic and -d
	cout<<c.getParam<int>("-ic")<<endl;
	cout<<c.getParam<int>("-d")<<endl;
	
	//traverse values of each option
	map<string,string> paramPairs = c.getParams();
	for(map<string,string>::iterator iter=paramPairs.begin(); iter!=paramPairs.end(); iter++)
	{
		cout<<"options: "<<iter->first<<" value: "<<iter->second<<endl;
	}
![](https://github.com/Wu-Hong/Console/blob/master/pix/cmd_parser.png "")

### Use debug printer
	DEBUG();
![](https://github.com/Wu-Hong/Console/blob/master/pix/debug_printer.png "")

### Get system version
	cout<<c.getSystemVersion()<<endl;

### Get current time
	c.printCurrentTime();
![](https://github.com/Wu-Hong/Console/blob/master/pix/current_time.png "")

### Create password
	c.mark("the new password is: " + c.createPassword());
![](https://github.com/Wu-Hong/Console/blob/master/pix/create_passwd.png "")


