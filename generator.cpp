#include<fstream>
#include<iostream>
#include<time.h>
#include<sstream>
#include<cstdlib>
#include<list>

#ifdef _WIN32
	#define CLEAN "cls"
#else
	#define CLEAN "clear"
#endif

using namespace std;

struct Var
{
	double min,max;
	double down,up;
	char type;
	int poz;
	string msg;
};

Var setVar(char v, int p)
{
	Var r;
	r.type=v;
	r.poz=p;
	
	switch(v)
	{
		case 'i':
			r.msg="int  ";
			r.min=-9223372036854775808LL;
			r.max=9223372036854775807LL;
			r.down=-1000000;
			r.up=1000000;
			break;
		case 'f':
			r.msg="float";
			r.min=-1E18;
			r.max=1E18;
			r.down=-1000.0000;
			r.up=1000.0000;
			break;
		case 'c':
			r.msg="char ";
			r.min=0;
			r.max=255;
			r.down=33;
			r.up=126;
			break;
	}
	return r;
}

string createText(string t,list <Var> vs,bool generate=false)
{
	string s;
	int i=0;
	int el=1;
	Var v;
	while(!vs.empty())
	{
		v=vs.front();
		vs.pop_front();
		for(i;i<v.poz;i++)
		{
			s+=t[i];	
		}
		if(generate)
		{
			if(v.type=='f')
			{
				double d = (rand()*rand())%(int(v.up-v.down))+v.down + (rand()%10000)/10000;
				s+=to_string(d);
			}
			else if(v.type=='c')
			{
				s+=char((rand()*rand())%(int(v.up-v.down))+v.down);
			}
			else
			s+=to_string((long long)((rand()*rand())%(int(v.up-v.down))+v.down));
			
		}
		else
			s+="(%"+to_string(el)+")";
		
		el++;
	}
	for(i;i<t.size();i++)
	s+=t[i];
	return s;
}

void addSequence(stringstream& s, string msg)
{
	int dolar=0;
	cout<<msg;
	while(dolar<3)
	{
		char c;
		scanf("%c",&c);
		if(c=='`')dolar++;
		else
		{
			for(int i=0;i<dolar;i++)s<<'`';
			dolar=0;	
			s<<c;
		}
	}	
}

void readTemplate(string s0,string& s1,list <Var> & vs)
{
	Var v;
	int j=0;
	int il=1;
	s1="";
	int dolar=0;
	bool pr=false;
	for(int i=1;i<s0.size();i++)
	{
		char c;
		c=s0[i];
		
		if(pr)
		{
			switch(c)
			{
				case '%':
					s1+='%';
					j++;
					break;
				case 'f':
				case 'c':
				case 'i':
					v=setVar(c,j);
					vs.push_back(v);
					break;
				default:
					v=setVar('i',j);
					vs.push_back(v);
			}
			pr=0;
		}
		else if(c=='`')dolar++;
		else if(c=='%')pr=1;
		else
		{
			for(int i=0;i<dolar;i++){s1+='`';j++;}
			dolar=0;
			s1+=c;
			j++;
		}
	}
	
	

}
void random(stringstream& s)
{
	p:
	stringstream t;
	string temp;
	system(CLEAN);
	cout<<"Write template : \n";
	cout<<"||   ``` to end, % and i,f,c to declare variable, %% to add %   ||\n";
	addSequence(t,"");
	list <Var> vars;
	readTemplate(t.str(),temp,vars);
	string msg;
	msg = createText(temp,vars);
	
	int w;
	do
	{
		system(CLEAN);
		list<Var>::iterator ptr;
		cout<<"Group: \n"<<msg<<"\n-----------------------------------------\n";
		int j=0;
		for(ptr=vars.begin();ptr!=vars.end();++ptr)
		{
			j++; cout<<j<<": "<<(*ptr).msg<<"  Range "<<(*ptr).down<<" : "<<(*ptr).up<<endl;
		}
		cout<<"-----------------------------------------\n"
		"[0] Set amount of groups and generate \n[1] Change range \n[2] Change template\n[3] Exit \n";
		cin>>w;
		
		switch (w)
		{
			case 0:	
				cout<<"Set amount: ";
				int amount;
				cin>>amount;
				for(int i=0;i<amount;i++)
					s<<createText(temp,vars,true);
				break;
			case 1:
				long long a;
				do{
					cout<<"\nNumber of variable to change:  ";
					cin>>a;
				}while(a>j);
				
				ptr=vars.begin();
				for(int i=1;i<a;i++)
				{
					ptr++;
				}
				
				do
				{
					cout<<"Min range:  ";
					cin>>a;
				}while(a>(*ptr).max || a<(*ptr).min);
				
				(*ptr).down = a;
				
				do
				{
					cout<<"Max range:  ";
					cin>>a;
				}while(a>(*ptr).max || a<(*ptr).min);
				
				(*ptr).up = a;
				
				break;
			case 2:
				goto p;
				break;
			default:
				break;
		}
		
	}while(w);
}

void menu()
{

	stringstream s;
	system(CLEAN);
	while(true)
	{
		
		int c;
		cout<<
			"//[1] Add numerical sequence \n"
			"[2] Add pseudo-random numbers \n"
			"[3] Add custom sequence \n"
			"[8] View output \n"
			"[9] Clear output \n"
			"[0] Save output to file \n"
			"[404] Exit \n";
		cin>>c;
		if(!cin.good())
		{
			cin.clear();
			cin.ignore();
			system(CLEAN);
			cout<<"NOT TYPED A NUMBER!!!\n\n";
			continue;
		}
		switch(c)
		{
			case 1:
				cout<<"Not ready yet :[ \n"; 
				break;
			case 2:
				random(s);
				system(CLEAN);
				cout<<"DONE!!! \n\n";
				break;
			case 3:
				cin.ignore();
				system(CLEAN);
				addSequence(s,"Add custom sequence (end with ```) : \n");
				system(CLEAN);
				cout<<"DONE!!! \n\n";
				break;
			case 8:
				system(CLEAN);
				cout<<"----------Start file-----------\n"<<s.str()<<"\n-----------End file------------\n\n";
				break;
			case 9:
				cout<<"Are you sure? y/n ";
				char y;
				cin>>y;
				if(y=='y')s.str("");
				system(CLEAN);
				break;
			case 404:
				return;
			case 0:
			{
				cout<<"name: ";
				string name;
				cin>>name;
				fstream plik;
				plik.open(name,ios::out);
				plik<<s.str();
				plik.close();
				system(CLEAN);
				cout<<"DONE!!! \n\n";
				break;
			}
			default:
				system(CLEAN);
				cout<<"TYPED A WRONG NUMBER!!!\n\n";
				break;
		}
	}
}

int main()
{
	srand(time(NULL));
	menu();
	return 0;
}
