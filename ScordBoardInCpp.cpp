#include <iostream>
#include <conio.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <graphics.h>
using namespace std;
int st[2]={1,2};	//To store the strike and non strike player number
char* SHOW_STATUS(int i)
{
	switch (i)
	{
		case 0:  return "";
		case 1:  return "not out";
		case 2:  return "bold out";
		case 3:  return "caught out";
		case 4:  return "run out";
		default: return "unknown";
	}
	return "unknown";
}
class Team
{
	char team_name[20];
	char p_name[12][20];
	int p_run[12];
	int p_status[12];
	int p_ball[12];
	int p_num;
	int Extra_run;
public:
	Team();
	int Init(void);
	char* get_name(int i){return p_name[i];}
	int get_run(int i){return p_run[i];}
	int get_status(int i){return p_status[i];}
	int get_extra(void){return Extra_run;}
	int get_ball(int i){return p_ball[i];}
	char* get_t_name(){return team_name;}
	int get_Total(void);
	void Add_Run(int player_num,int run);
	void Set_Status(int player,int status){p_status[player]=status;};
	void Set_Out(int out_player,int type,int new_player);
	void Set_Ball(int player){p_ball[player]++;}
	void Set_Extra(int run){Extra_run+=run;};
	Team(int a);
};
/************ Default Contructor**************************/
Team::Team()
{
	for(int i=1; i<=12;i++)
	{
		strcpy(p_name[i],"Player");
		p_run[i]=0;
		p_status[i]=0;
		p_ball[i]=0;
	}
	strcpy(team_name,"India");
	Extra_run=0;
	p_num=0;
}
/************** Initialize Team***************************/
int Team::Init(void)
{
       	clrscr();
	cout<<"Enter Team Name: ";
	cin>>team_name;
	p_num=11;
	cout<<"Enter Name of the Players:\n";
	for(int i=1;i<=p_num;i++)
	{
		cout<<"                  Player"<<i<<": ";
		cout<<"\n\n";
		p_run[i]=0;
		p_status[i]=0;
	}
	for(i=1;i<=p_num;i++)
	{
		gotoxy(30,1+2*i);
		cin>>p_name[i];
	}
	return p_num;
}
void Team::Add_Run(int player_num,int run)
{
	p_run[player_num] += run;
	get_Total();
}
/*************** Calculate & Get Total Run ************/
int Team::get_Total()
{
	int local_total=0;
	for(int i=1;i<=p_num;i++)
	local_total += p_run[i];           //Players Score
	local_total += Extra_run;            //Add Extra
	return local_total;
}
void Team::Set_Out(int out_player,int type,int new_player)
{
	p_status[out_player]=type;             //Current Player out
	p_status[new_player]=1;                //New Player Not out
}
/***************************my score**********************************/
class myscore
{
	int player1;
	int player2;
	int Ball_count;
	int Over;
	int Max_Over;
	int Out;
	int Max_out;
	Team team1;
	int extra;
	int flag;
	int chk[2];
public:
	myscore();
	void show(void);
	void dot_ball(void);
	void add_run(int a);
	void wicket(void);
	void extra1(void);
	void over_complete(void);
};
myscore::myscore()
{
	flag=1;
	player1=0;
	player2=0;
	extra=0;
	Over=0;
	Out=0;
	Max_out=10;
	Ball_count=0;
	Max_out=team1.Init();                            // Initialize Team
	clrscr();
	cout<<"\nEnter no of Overs in one Innings: ";
	cin>>Max_Over;
	player1=1;                              //Opening
	team1.Set_Status(player1,1);                       //Batsman
      	player2=2;
	team1.Set_Status(player2,1);
	gotoxy(47,10);
	cout<<"CREATED BY MADHAN | @Mr.Panda_Boi"; 
       }
/******************** Showing Entire Score **********************/
void myscore::show(void)
{
	clrscr();
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\bgi");
	cleardevice();
	setcolor(14);
	setfillstyle(1,9);
	bar(0, 0, 400,70+Max_out*16+70);
	char option;
	cout<<"//////////////////////////////////////////////////"<<endl;
	cout<<"                   "<<team1.get_t_name()<<" Score                     "<<endl;
	cout<<"//////////////////////////////////////////////////"<<endl<<endl;
	gotoxy(47,10);
	cout<<"CREATED BY MADHAN | @Mr.Panda_Boi";
	for(int i=1;i<=Max_out;i++)
	{
		gotoxy(5,4+i);
		cout<<team1.get_name(i)<<"                          ";
		gotoxy(20,4+i);
		cout<<SHOW_STATUS(team1.get_status(i))<<"                    ";
		gotoxy(42,4+i);
		cout<<team1.get_run(i);
		if(team1.get_status(i))
			cout<<"("<<team1.get_ball(i)<<")";
		if(st[0]==i)
			cout<<"*";
		cout<<endl;
	}
	cout<<"\nExtra";gotoxy(42,4+i+1);
	cout<<team1.get_extra()<<endl<<endl;
	gotoxy(42,4+i);
	cout<<"\n\n--------------------------------------------------"<<endl;
	cout<<"Over "<<Over<<"."<<Ball_count<<"  Wicket "<<Out;
	cout<<" || total score: ";
	gotoxy(42,6+i+1);
	cout<<team1.get_Total()<<endl;
	gotoxy(45,8+i);
	cout<<"\nChoose option:\n";                  //Options for
	cout<<"\n\tDot Ball[0]||";                    //Updating
	cout<<"\n\tAdd Run[1-6]||";                    //Score Card
	cout<<"\n\tExtra[E]||";
	cout<<"\n\tWicket[O]||";
	cout<<"\n\tExit[X]\n";
	cout<<"\t\t\t.................";
	cin>>option;
	switch (option)
	{
		case '0': dot_ball(); break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6': add_run(option);  break;
		case 'E':
		case 'e': extra1(); break;
		case 'O':
		case 'o': wicket(); break;
		case 'X':
		case 'x': return;
		default: cout<<"Wrong input. Considered as dot ball."; getch(); dot_ball();
	}
}
/***************** One Dot Ball ********************/
void myscore::dot_ball(void)
{
	Ball_count++;
	team1.Set_Ball(player1);
	if(Ball_count==6)
	{
		over_complete();
		return;
	}
	getch();
	show();
}
/***************** Add Extra Run *********************/
void myscore::extra1(void)
{
	team1.Set_Extra(1);
	show();
}
/****************** Add Current Player Run******************/
void myscore::add_run(int a)
{
	int runs=a-48;
	Ball_count++;
	team1.Set_Ball(player1);
	team1.Add_Run(player1,runs);
	if(runs==1||runs==3||runs==5)
	{
		int temp = player1;
		player1=player2;
		player2=temp;
		int tempp=st[0];
		st[0]=st[1];
		st[1]=tempp;
	}
	if(Ball_count==6)
	{
		over_complete();
		return;
	}
	show();
}
/***************** Over Complete ***************************/
void myscore::over_complete(void)
{
	cout<<"\n\n*********************************\n";
	cout<<"           Over Complete\n";
	cout<<"*********************************\n";
	Over++;
	Ball_count=0;
	int temp = player1;
	player1=player2;
	player2=temp;
	int tempp=st[0];
	st[0]=st[1];
	st[1]=tempp;
	if(Over==Max_Over)
	{
		cout<<"\n\n*********************************\n";
		cout<<"           Innings Complete\n";
		cout<<"*********************************\n";
		getch();
		return;
	}
	else
	{
		getch();
		show();
	}
}
/********************** Wicket Fallen ************************/
void myscore::wicket(void)
{
	int o_type,new_player;
	cout<<"\n\n*********************************\n";
	cout<<"           Wicket\n";
	cout<<"*********************************\n";
	cout<<"\n1.Bold 2.Caught 3.Run out:";
	cin>>o_type;
	Out++;
	Ball_count++;
	team1.Set_Ball(player1);
	if(Out>=Max_out)
	{
		cout<<"\n\n*********************************\n";
		cout<<"           Innings Complete\n";
		cout<<"*********************************\n";
		team1.Set_Status(player1,o_type+1);
		getch();
		return;
	}
	new_player=(st[0]>st[1]?st[0]:st[1])+1;
	st[0]=new_player;
	team1.Set_Out(player1,o_type+1,new_player);
	player1=new_player;
	if(Ball_count==6)
	{
		over_complete();
		return;
	}
	getch();
	show();
}

void main(void)
{
	clrscr();
	myscore MS;
	MS.show();
	gotoxy(45,25);
}
