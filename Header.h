#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std;
class KB;
class Input
{
	vector<string> kb_v;
	string query;
	string input_file;
	int count;
public:
	Input(string input_file);
	void readFile();
	void display();
	void parse_object(KB*);
	string getQuery();
};

class myConstSub
{
	string str;
	bool sub;
public:
	myConstSub(myConstSub, bool);
	myConstSub(char *, bool);
	void addConst(string);
	string getConstStr();
	bool getSub();
	bool compareSub(myConstSub);
};
class Object
{
	vector<string> var;
	vector<myConstSub> myConst;
	string name;
	int val;
public:
	Object();
	Object(string);
	void Display();
	string Findname();
	bool compareObject(Object);
	bool compareObjectQuery(Object);
	bool compareObjectConst(Object);
	bool isConst();
	vector<myConstSub> get_const();
	vector<myConstSub> get_sub();
	vector<string> get_var();
	void setConst(vector<myConstSub>);
	void setSub(vector<myConstSub>);
	void objSub(Object);
	Object nullObject();
	bool isNullObj();
	bool checkObjectSub();
	bool hasConst();
	void subQuery(vector<Object>);
	int constCount();
	int varCount();
};

class KB_Line
{
	vector<Object> predicate;
	Object implication;
	Object query;
	bool used;
public:
	KB_Line();
	KB_Line(string);
	KB_Line(string, string);
	void Display();
	void DisplayQuery();
	bool findImpli(Object);
	Object getQuery();
	Object getImpli();
	void extractObject(vector<Object>*, Object*);
	bool findConstpred(Object); 
	void setUsed();
	bool getUsed();

};

class KB
{
	vector<KB_Line> syntax;
	KB_Line query;
public:
	KB();
	KB(string);
	void Display();
	void addSentence(string);
	void addQuery(string);
	Object getQuery();
	Object backwardChain(Object);
	bool parseKB();
	vector<KB_Line> findSentence(Object);
	void sortpred(vector<Object>*);
};

