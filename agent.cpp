#include"Header.h"
/*.....................Input................*/
Input::Input(string input_file)
{
	this->input_file = input_file;
}
void Input::readFile()
{
	string line,cnt;
	std::ifstream read(input_file.c_str());
	getline(read, query);
	getline(read, cnt);
	istringstream(cnt) >> count;
	for (line; getline(read, line);)
	{
		if (count == -1)
			break;
		count--;
		kb_v.push_back(line);
	}
	read.close();
}
void Input::display()
{
	for (vector<string>::iterator it = kb_v.begin(); it != kb_v.end(); it++)
		cout << *it<<'\n';
}
void Input::parse_object(KB *myKB)
{
	for (vector<string>::iterator it = kb_v.begin(); it != kb_v.end(); it++)
	{
		 myKB->addSentence(*it);
	}
}
string Input::getQuery()
{
	return this->query;
}
/*.....................Input................*/

string myConstSub::getConstStr()
{
	return this->str;
}
myConstSub::myConstSub(myConstSub str, bool subBool)
{
	this->str.assign(str.getConstStr());
	this->sub = true;
}
myConstSub::myConstSub(char* str, bool subBool)
{
	string tString(str);
	this->str.assign(tString);
	this->sub = subBool;
}
void myConstSub::addConst(string str)
{
	this->str.assign(str);
	this->sub = false;
}
bool myConstSub::getSub()
{
	return this->sub;
}
bool myConstSub::compareSub(myConstSub myConstSub)
{
	if (this->str.compare(myConstSub.str) == 0)
		return true;
	else
		return false;
}
/*.....................Object................*/

Object::Object()
{
	this->name = "\0";
	this->val = -1;
}
bool Object::isNullObj()
{
	if (this->name.compare("\0") == 0 && this->val == -1)
		return true;
	else
		return false;
}
Object::Object(string str)
{
	if (str.empty())
	{
		this->val = -1;
		this->name = "\0";
	}
	char * c_Line = new char[str.length()];
	strcpy(c_Line, str.c_str());
	char* tok = strtok(c_Line, "(, , , )");
	while (tok != NULL)
	{
		if (this->name.empty())
			name = tok;
		else if (islower(tok[0]))
			this->var.push_back(tok);
		else
		{
			myConstSub tempConst = myConstSub(tok, false);
			this->myConst.push_back(tempConst);
		}
		//cout << tok <<"..**..\n";
		tok = strtok(NULL, "(, , ,)");
	}
}
void Object::Display()
{
	cout << "\n" << this->name << "\n";
	for (vector<string>::iterator it = this->var.begin(); it != this->var.end(); ++it)
	{
		cout << "variable : " << *it << "\n";
	}
	for (vector<myConstSub>::iterator it = this->myConst.begin(); it != this->myConst.end(); ++it)
	{
		cout << "Constants : " << it->getConstStr() << "\n";
	}
}
bool Object::isConst()
{
	return this->var.empty();
}
string Object::Findname()
{
	return (this->name);
}
int Object::constCount()
{
	return this->myConst.size();
}
int Object::varCount()
{
	return this->var.size();
}
bool Object::compareObject(Object fObject)
{
	int c1 = fObject.constCount();
	int c2 = this->constCount();
	int v1 = fObject.varCount();
	int v2 = this->varCount();
	if (this->name.compare(fObject.name) == 0)
	{
		if (fObject.hasConst() && this->hasConst())
		{
			if (!((c1 + v1) == (c2 + v2)))
				return false;
			for (vector<myConstSub>::iterator it = fObject.myConst.begin(); it != fObject.myConst.end(); it++)
			{
				for (vector<myConstSub>::iterator itt = this->myConst.begin(); itt != this->myConst.end(); itt++)
				{
					if (it->getConstStr().compare(itt->getConstStr()) == 0)
						return true;
				}
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}
bool Object::compareObjectQuery(Object fObject)
{
	bool check_const = false;
	if (this->name.compare(fObject.name) == 0)
	{
		if (fObject.hasConst())
		{
			for (vector<myConstSub>::iterator it = fObject.myConst.begin(); it != fObject.myConst.end(); it++)
			{
				for (vector<myConstSub>::iterator itt = this->myConst.begin(); itt != this->myConst.end(); itt++)
				{
					if (it->getConstStr().compare(itt->getConstStr()) == 0)
						check_const = true;
				}
				if (check_const == false)
					return false;
			}
		}
	}
	else
		return false;
	return true;
}
bool Object::compareObjectConst(Object fObject)
{
	bool count=false;
	int c1 = fObject.constCount();
	int v1 = fObject.varCount();
	int c2 = this->constCount();
	if (this->name.compare(fObject.name) == 0)
	{
		if (fObject.hasConst() && this->hasConst())
		{
			if (!((c1+v1) == (c2)))
				return false;
			for (vector<myConstSub>::iterator it = fObject.myConst.begin(); it != fObject.myConst.end(); it++)
			{
				count = false;
				for (vector<myConstSub>::iterator itt = this->myConst.begin(); itt != this->myConst.end(); itt++)
				{
					if (it->getConstStr().compare(itt->getConstStr()) == 0)
					{
						count = true;
						break;
					}
				}
				if (count == false)
					return false;
			}
		}
		else
		{
			return true;
		}
	}
	else
	return false;
	return true;
}
vector<myConstSub> Object::get_const()
{
	return this->myConst;
}
vector<myConstSub> Object::get_sub()
{
	vector<myConstSub> mySub;
	for (vector<myConstSub>::iterator it = this->myConst.begin(); it != this->myConst.end(); it++)
	{
		if (it->getSub())
			mySub.push_back(*it);
	}
	return mySub;
}
vector<string> Object::get_var()
{
	return this->var;
}
void Object::setConst(vector<myConstSub> myConst)
{
	vector<myConstSub> obj_const = this->get_const();
	for (vector<myConstSub>::iterator itt = myConst.begin(); itt != myConst.end(); itt++)
	{
		if (!obj_const.empty())
		{
			for (vector<myConstSub>::iterator it = obj_const.begin(); it != obj_const.end(); it++)
			{
				if (itt->getConstStr().compare(it->getConstStr()))
				{
					myConstSub mySubNew = myConstSub(*itt, true);
					this->myConst.push_back(mySubNew);
					this->var.pop_back();
				}
			}
		}
		else
		{
			myConstSub mySubNew = myConstSub(*itt, true);
			this->myConst.push_back(mySubNew);
			this->var.pop_back();
		}
	}
}
void Object::setSub(vector<myConstSub> myConst)
{
	int count = 0;
	for (vector<myConstSub>::iterator itt = myConst.begin(); itt != myConst.end(); itt++)
	{
		for (vector<string>::iterator it = this->var.begin(); it != this->var.end(); it++)
		{
			count++;
			myConstSub mySubNew = myConstSub(*itt, true);
			this->myConst.push_back(mySubNew);
			it->erase();
		}
	}
	for (int i = 0; i < count; i++)
	{
		this->var.pop_back();
	}
}
void Object::objSub(Object ret)
{
	vector<myConstSub> myConst;
	if (ret.checkObjectSub())
	{
		myConst = ret.get_sub();
		this->setSub(myConst);
		//this->Display();
	}
	else if (!this->get_var().empty())
	{
		myConst = ret.get_const();
		this->setConst(myConst);
	}
}
bool Object::checkObjectSub()
{
	for (vector<myConstSub>::iterator it = this->myConst.begin(); it != this->myConst.end(); it++)
	{
		if (it->getSub())
			return true;
	}
	return false;
}
Object Object::nullObject()
{
	Object nullobj = Object();
	return nullobj;
}
bool Object::hasConst()
{
	return (!this->get_const().empty());
}
void Object::subQuery(vector<Object> retLine)
{
	vector<myConstSub> tmpSub;
	cout << "\n....Replace....\n";
	for (vector<Object>::iterator it = retLine.begin(); it != retLine.end(); it++)
	{
		it->Display();
		if (!it->get_sub().empty())
		for (vector<myConstSub>::iterator itt = it->get_sub().begin(); itt != it->get_sub().end(); itt++)
		{
			bool i = false;
			for (vector<myConstSub>::iterator ittt = tmpSub.begin(); ittt != tmpSub.end(); ittt++)
			{
				if (ittt->compareSub(*itt))
				{
					i = true;
					break;
				}
			}
			if (!i)
			{
				tmpSub.push_back(*itt);
			}
		}
		tmpSub = it->get_const();
	}
	this->setConst(tmpSub);
}
/*.....................Object................*/


/*.....................KB_LINE................*/
KB_Line::KB_Line(string query)
{
	this->used = false;
	Object query_object(query);
	this->query = query_object;
}
KB_Line::KB_Line(string pred, string impli)
{
	this->used = false;
	vector<string> str_v;
	Object impli_object(impli);
	this->implication = impli_object;
	char * c_Line = new char[pred.length()];
	strcpy(c_Line, pred.c_str());
	char* tok = strtok(c_Line, "&");
	while (tok != NULL)
	{
		//cout << tok << "..*&&*..\n";
		str_v.push_back(tok);
		tok = strtok(NULL, "&");
	}

	for (vector<string>::iterator it = str_v.begin(); it != str_v.end(); ++it)
	{
		Object pred_object(*it);
		this->predicate.push_back(pred_object);
	}
}
void KB_Line::DisplayQuery()
{

	this->query.Display();
}
void KB_Line::Display()
{
	cout << "\nLine ........\n";
	for (vector<Object>::iterator it = this->predicate.begin(); it != this->predicate.end(); it++)
	{
		it->Display();
	}
	cout << "\n....Impli.....\n";
	this->implication.Display();
}
KB_Line::KB_Line()
{
	this->implication = this->implication.nullObject();
	this->used = false;
}

bool KB_Line::findImpli(Object query)
{
	return this->implication.compareObject(query);
}
bool KB_Line::findConstpred(Object query)
{
	for (vector<Object>::iterator it = this->predicate.begin(); it != this->predicate.end()&& it->isConst(); it++)
	{
		if (it->compareObjectConst(query))
			return true;
	}
	return false;
}
void KB_Line::extractObject(vector<Object> *pred_objects, Object *impli_objects)
{
	*impli_objects = this->implication;
	for (vector<Object>::iterator it = this->predicate.begin(); it != this->predicate.end(); it++)
	{
		pred_objects->push_back(*it);
	}
}
Object KB_Line::getQuery()
{
	return this->query;
}
Object KB_Line::getImpli()
{
	return this->implication;
}
void KB_Line::setUsed()
{
	this->used = true;
}
bool KB_Line::getUsed()
{
	return this->used;
}
void KB::sortpred(vector<Object>* pred)
{
	int sent_count[2],i=0;
	Object temp;
	for (vector<Object>::iterator it = pred->begin(); it != pred->end(); it++)
	{
		vector<KB_Line> nextLine = this->findSentence(*it);
		sent_count[i] = nextLine.size();
		i++;
	}
	if (sent_count[0] > 1)
	{
		temp = (*pred)[0];
		(*pred)[0] = (*pred)[1];
		(*pred)[1] = temp;
	}
}

/*.....................KB_LINE................*/


Object KB::backwardChain(Object query)
{
	cout << "\n...Query...\n";
	query.Display();
	vector<Object> retLine,pre_ret;
	vector<Object> pred_objects;
	Object impli_objects, ret;
	bool check_pred = false;
	vector<myConstSub> pred_vec;
	vector<KB_Line> nextLine = findSentence(query);
	//nextLine[0].setUsed();
//	for (vector<KB_Line>::iterator itn = nextLine.begin(); itn != nextLine.end(); itn++)
	nextLine[0].Display();
	nextLine[0].extractObject(&pred_objects, &impli_objects);
	if (pred_objects.size() == 2)
	{
		this->sortpred(&pred_objects);
	}
	if (!impli_objects.isNullObj())
	{
		impli_objects.objSub(query);
	//	cout << "\n..hahahah.."; impli_objects.Display(); cout << ".....\n";
		if (!impli_objects.get_sub().empty())
		{
			for (vector<Object>::iterator it = pred_objects.begin(); it != pred_objects.end(); it++)
			{
				it->objSub(impli_objects);
			//	cout << "################################";
			//	it->Display();
			}
		}
	}
	for (vector<Object>::iterator it = pred_objects.begin(); it != pred_objects.end(); it++)
	{
		if (!it->isConst()||!it->get_sub().empty())
		{
			if (check_pred == true)
			it->setSub(pred_vec);
			ret = backwardChain(*it);
			if (ret.isNullObj())
			{
				if (nextLine.size()==1)
				return ret;
			}
				
			if (check_pred == true)
			{
				if (!pred_vec[0].compareSub(ret.get_sub()[0]))
				{
					ret = ret.nullObject();
					return ret;
				}
				check_pred = false;
			}
			check_pred = true;
			pred_vec = ret.get_sub();
		//	cout << "\n........ret........\n";
		//	ret.Display();
			it->objSub(ret);
		//	cout << "\n........sub........\n";
		//	it->Display();
			retLine.push_back(*it);
		}
		else
			retLine.push_back(*it);
	}
	//nextLine.Display();
	Object tmp;
	if (!retLine.empty())
	{
		//query.subQuery(retLine);
		for (vector<Object>::iterator it = retLine.begin(); it != retLine.end(); it++)
		{
		//	cout << "\n Before sub";
		//	it->Display();
			if (!query.isConst())
				query.objSub(*it);
			else
			{
				if (impli_objects.isConst() && !impli_objects.isNullObj())
				query = impli_objects;
			}
		//	cout << "\n After sub.....";
		//	query.Display();
		}
		tmp = query;
		retLine.pop_back();
	}
	else
	{
		tmp = tmp.nullObject();
	}
	return tmp;
}
KB::KB(string line)
{
	char * c_Line = new char[line.length()];
	int i = 0;
	string sent[2] = { "/0" };
	strcpy(c_Line, line.c_str());
	char* tok = strtok(c_Line, "=>");
	while (tok != NULL)
	{
		//cout << tok << "..*=>*..\n";
		sent[i++] = tok;
		tok = strtok(NULL, "=>");
	}
	KB_Line myKb_Line = KB_Line(sent[0], sent[1]);
	this->syntax.push_back(myKb_Line);
}
void KB::addSentence(string line)
{
	char * c_Line = new char[line.length()];
	int i = 0;
	string sent[2] = { "/0" };
	strcpy(c_Line, line.c_str());
	char* tok = strtok(c_Line, "=>");
	while (tok != NULL)
	{
		//cout << tok << "..*=>*..\n";
		sent[i++] = tok;
		tok = strtok(NULL, "=>");
	}
	KB_Line myKb_Line = KB_Line(sent[0], sent[1]);
	this->syntax.push_back(myKb_Line);
}
void KB::addQuery(string line)
{
	KB_Line myKb_Line_Query = KB_Line(line);
	this->query = KB_Line(myKb_Line_Query);
}
void KB::Display()
{
	for (vector<KB_Line>::iterator it = this->syntax.begin(); it != this->syntax.end(); it++)
	{
		it->Display();
	}
	cout << "\nquery";
	this->query.DisplayQuery();

}
vector<KB_Line> KB::findSentence(Object query)
{
	vector<KB_Line> lineSelect;
	for (vector<KB_Line>::iterator it = this->syntax.begin(); it != this->syntax.end(); it++)
	{
	//	if (!it->getUsed())
		if (it->getImpli().isNullObj())
		{
			if (it->findConstpred(query) == true)
			{
				lineSelect.push_back(*it);
				//return *it;
			}
		}
	}
	for (vector<KB_Line>::iterator it = this->syntax.begin(); it != this->syntax.end(); it++)
	{
	//	if (!it->getUsed())
		if (it->findImpli(query) == true)
		lineSelect.push_back(*it);
		//return *it;
	}
	if (!lineSelect.empty())
		return lineSelect;
	KB_Line kbNull = KB_Line();
	lineSelect.push_back(kbNull);
	return (lineSelect);
}
bool KB::parseKB()
{
	vector<Object> pred_objects;
	Object impli_objects;
	Object temp;
	Object query = this->query.getQuery();
	temp = this->backwardChain(query);
	cout << "\n....return.....\n";
	temp.Display();
	return temp.compareObjectQuery(this->query.getQuery());
}
KB::KB()
{}
int main()
{
	KB* myKB = new KB();
	Input in("input.txt");
	in.readFile();
	myKB->addQuery(in.getQuery());
	in.parse_object(myKB);
	//myKB->Display();
	//in.display();
	string print = (myKB->parseKB())?"\ntrue":"\nfalse";
	cout << print;
}
