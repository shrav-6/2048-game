#include <iostream.h>
#include <graphics.h>
#include <fstream.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <dos.h>

void save();
void mainpage();
void scoreboard();
void intro();
void instruct();
void login();
void loginpage();

class log //logging user info
{
	public:
	char un[20],pass[20];
	int b[4][4], flag[4][4];
	int score;int mov;
	log();
	void getun()
	{
		clrscr();
		cleardevice();
		cout<<"Enter username:"<<endl;
		cin>>un;
	}
	void getpass();
	int putscore()
	{
		return score;
	}
	void display();
	int isfull();
	void play();
	void moves(char,int);
	void ran();
	void resume();

}l,lf; //two objects created for file and user info storing

void log :: getpass() //enter user password
{
	cout<<"Enter password:"<<endl;
	char ch='\0';
	int i;
	for(i=0;i>=0;)
	{
		ch=getch();
		if(ch!=13)
		{
			cout<<"*";
			pass[i]=ch;
			i++;
		}

		else if(ch==13)
		{
			pass[i]='\0';
			i++;
			break;
		}
		else
			break;
	}
	cout<<endl<<endl;
}

log::log() //log a new board
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			b[i][j]=0;
			flag[i][j]=0;
		}
	}
	score=0;
}

int log :: isfull() //end game if board is full
{
	int count=0;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(b[i][j]!=0)
				count++;
		}
	}
	if(count==16)
		return 1;//board is full- return 1
	else
		return 0;
}

void log :: ran() //generate a number randomly
{
	int i,j,f;
	f=isfull(); //returns 1 when full
	for(;;)
	{
		srand(time(0));
		i= rand()%4;
		j= rand()%4;
		if(f==1)
		{
			cout<<"Oops! Box is full"<<endl;
			moves('x',0);
			return;
		}
		else if(b[i][j]==0)
		{
			b[i][j]=2;
			display();
			return;
		}
	}
}

void log :: moves(char ch,int scor) //actions to be taken for every move
{
	int sum;
	switch(ch)
	{
		case 'x': //exiting move
		{
			clrscr();
			cleardevice();
			cout<<"Exiting.";
			delay(1000);
			clrscr();
			cleardevice();
			cout<<"Exiting..";
			delay(1000);
			clrscr();
			cleardevice();
			cout<<"Exiting...";
			delay(1000);
			cleardevice();
			save();
			exit(0);

		}
		case 'w': //w key operation
		{
			int flag[4][4]={0};
				for(int i=0;i<4;i++)
			{
				for(int j=0;j<4;j++)
				{
					if(b[i][j]==0)
						continue;
					else if(i>=1)
					{
						if(b[i-1][j]==0)
						{
							b[i-1][j]=b[i][j];
							b[i][j]=0,i=0,j=-1;
						}

						else if(flag[i-1][j]==0 && flag[i][j]==0 && b[i-1][j]==b[i][j])
						{
							b[i-1][j]+=b[i][j];
							flag[i-1][j]=1;
							b[i][j]=0,i=0,j=-1;
						}
					}
				}
			}
			mov++;
			ran();
			break;
		}
		case 's': //s key operation
		{
			int flag[4][4]={0};
			for(int i =0;i<4;i++)
			{
				for(int j=0;j<4;j++)
				{
					if(b[i][j]==0)
						continue;
					else if( i<=2 )
					{

						if(b[i+1][j]==0)
						{
							b[i+1][j]=b[i][j];
							b[i][j]=0,i=0,j=-1;
						}
						else if(flag[i+1][j]==0 && flag[i][j]==0 && b[i+1][j]==b[i][j] )
						{
							b[i+1][j]+=b[i][j];
							flag[i+1][j]=1;
							b[i][j]=0,i=0,j=-1;
						}
					}
				}
			}
			mov++;
			ran();
			break;
		}
		case 'a': //a key operation
		{
			int flag[4][4]={0};
			for(int i =0;i<4;i++)
				{
				for(int j=0;j<4;j++)
				{

					if(b[i][j]==0)
						continue;
					else if( j>=1)
					{
						if(b[i][j-1]==0)
						{
							b[i][j-1]=b[i][j];
							b[i][j]=0,i=0,j=-1;
						}
						else if(flag[i][j-1]==0 && flag[i][j]==0 && b[i][j-1]==b[i][j])
						{
							b[i][j-1]+=b[i][j];
							flag[i][j-1]=1;
							b[i][j]=0,i=0,j=-1;
						}
					}
				}
			}
			mov++;
			ran();
			break;
		}
		case 'd': //d key operation
		{
			int flag[4][4]={0};
			for(int i =0;i<4;i++)
			{
				for(int j=0;j<4;j++)
				{

					if(b[i][j]==0)
						continue;
					else if( j<=2)
					{
						if(b[i][j+1]==0)
						{
							b[i][j+1]=b[i][j];
							b[i][j]=0,i=0,j=-1;
						}
						else if(flag[i][j+1]==0 && flag[i][j]==0 && b[i][j+1]==b[i][j])
						{
							b[i][j+1]+=b[i][j];
							flag[i][j+1]=1;
							b[i][j]=0,i=0,j=-1;
						}
					}
				}

			}
			mov++;
			ran();
			break;
		}
	}//switch

	sum=0;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			sum=sum+b[i][j]; //add the sum of the numbers of every move
		}
	}

	if(mov==0 && scor==0)
		score=0;
	else
		score=(int)(sum/mov); //score of the user 
}

void log :: play() //play the game
{
	clrscr();
	cleardevice();
	char ch;
	int f;
	f= isfull();
	display();
	ran();
	ran();
	cout<<"Enter move - A,W,S,D"<<endl;
	while(f!=1)
	{
		cin>>ch;
		ch=tolower(ch);
		if(ch=='p')
		{
			clrscr();
			cleardevice();
			settextstyle(0,0,2);
			setcolor(CYAN);
			rectangle(50,50,600,425);
			setcolor(RED);
			outtextxy(90,100,"GAME PAUSED!!"); //display intructions
			outtextxy(90,150,"R - Resume game");
			outtextxy(90,180,"M - Logout(Taking you back to");
			outtextxy(155,210,"main page)");
			outtextxy(90,240,"L - Login Page");
			outtextxy(90,270,"X - Exit");
			outtextxy(90,300,"I - To view instructions");
			cin>>ch;
			ch=tolower(ch);
			if(ch=='r')
			{
				clrscr();
				cleardevice();
				cout<<"Resuming..."<<endl;
				l.play();
			}
			else
			{
				cout<<"Invalid choice, taking you to board"<<endl;
				l.play();
			}

		}
		else if(ch=='a'||ch=='w'||ch=='s'||ch=='d'||ch=='x')
		{
			moves(ch,lf.score);
		}
		else if(ch=='m')
		{
			save();
			mainpage();
		}
		else if(ch=='l')
		{
			save();
			loginpage();
		}
		else if(ch=='i')
		{
			instruct();
			l.play();
		}

		f=isfull();
	}
	if(f==1) //display score at the end of the game
	{
		cout<<"Game over!";
		cout<<"Your score:"<<score;
		delay(2000);
	}
	else
		return;
	getch();
}

void createnew() //new user creation
{
	clrscr();
	cleardevice();
	ifstream fin("l.txt", ios::in|ios::binary);
	ofstream fout("l.txt", ios::app|ios::binary);
	int flag = 0;
	l.getun();
	l.getpass();
	while(fin)
	{
		fin.read((char*)&lf, sizeof(lf));

		if(strcmp(l.un,lf.un)==0)
		{
			flag=1;
			cout<<"Username already exists... Try again!!"<<endl;
			break;
		}

	}
	if(flag==0) //username doesnt exist, then write on file
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				l.b[i][j]=0;
				l.flag[i][j]=0;
			}
		}
		l.score=0;
		fout.write((char*)&l,sizeof(l));
		cout<<"Account created successfully!!!"<<endl;
		delay(1000);
	}

	fin.close();
	fout.close();
	cout<<"Taking you back to the main page...\nLogin to continue!!"<<endl;
	mainpage();

}

void log:: display() //displaying the game board
{
	clrscr();
	cleardevice();
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	for(int i=0;i<4;i++)
	{
		cout<<"\t\t";
		for(int j=0;j<4;j++)
		{
			cout<<"\t    "<<b[i][j];
		}
		cout<<endl<<endl<<endl;
	}
	setcolor(CYAN);
	line(200,195,450,195);
	line(200,242,450,242);
	line(200,285,450,285);
	line(262,150,262,330);
	line(330,150,330,330);
	line(392,150,392,330);
	settextstyle(0,0,3);
	setcolor(CYAN);
	rectangle(200,150,450,330);
	delay(500);
}

void save() //saving userid and passowrd
{
	ifstream fin;
	ofstream fout;
	fin.open("l.txt",ios::in|ios::binary);
	fout.open("temp.txt",ios::trunc|ios::binary);
	while(!fin.eof())
	{
			fin.read((char*)&lf, sizeof(lf));
			if(((strcmp(l.un,lf.un)==0)&&(strcmp(l.pass,lf.pass)==0)))
				fout.write((char*)&l, sizeof(l));
			else
				fout.write((char*)&lf, sizeof(lf));
	}
	fin.close();
	fout.close();
	remove("l.txt");
	rename("temp.txt","l.txt");
}

void mainpage() //game mainpage
{
	int choice;
	clrscr();
	cleardevice();
	settextstyle(0,0,3);
	setcolor(CYAN);
	rectangle(50,50,600,425);
	setcolor(RED);
	outtextxy(100,100,"2048 MAIN PAGE");
	outtextxy(100,200,"1.LOGIN");
	outtextxy(100,230,"2.CREATE NEW");
	outtextxy(100,260,"3.EXIT");
	settextstyle(0,0,2);
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t      Enter your choice: ";
	settextstyle(0,0,0);
	cin>>choice;
	cleardevice();
	switch(choice)
	{
		case 1:
		{
			login();
			break;
		}
		case 2:
		{
			createnew();
			break;
		}
		case 3:
		{
			cleardevice();
			l.moves('x',0);
			cleardevice();
			break;
		}
		default:
		{
			cout<<"Invalid choice"<<endl;
			cout<<"Enter choice again"<<endl;
			delay(1200);
			mainpage();
		}
	}
}

void instruct() //game general instructions
{
	clrscr();
	cleardevice();
	settextstyle(0,0,3);
	setcolor(CYAN);
	rectangle(50,50,600,425);
	setcolor(RED);
	outtextxy(100,110,"A -> LEFT");
	outtextxy(100,140,"W -> UP");
	outtextxy(100,170,"S -> DOWN");
	outtextxy(100,200,"D -> RIGHT");
	outtextxy(100,230,"X -> EXIT");
	outtextxy(100,260,"P -> PAUSE");
	outtextxy(100,290,"I -> INSTRUCTIONS");
	outtextxy(100,320,"R -> RESUME");
	outtextxy(100,350,"M -> MAINPAGE");
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t     Press any key to continue"<<endl;
	getch();
	settextstyle(0,0,0);
}

void intro() //welcome page of the game
{
	cleardevice();
	settextstyle(0,0,3);
	setcolor(CYAN);
	rectangle(50,50,600,425);
	setcolor(RED);
	outtextxy(135,215,"Welcome to 2048!");
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl;
	cout<<"\t\t\t     Press any key to continue";
	getch();
	settextstyle(0,0,0);
}

void login() //user login operation
{
	ifstream fin("l.txt",ios::in);
	int flag=0;
	l.getun();
	l.getpass();
	while(fin)
	{
		if(!fin.eof())
		{
			fin.read((char*)&lf, sizeof(lf));
			if((strcmp(l.un,lf.un)==0)&&(strcmp(l.pass,lf.pass)==0) )
			{
				flag=1;
				break;
			}
		}
	}
	fin.close();
	if(flag==0)
	{
		cout<<"Incorrect username and password :("<<endl;
		cout<<"Taking you back to mainpage..."<<endl;
		delay(1000);
		mainpage();
	}
	else if(flag==1)
	{
		cout<<"Logged in successfully"<<endl;
		delay(1000);
		loginpage();
	}
}

void loginpage() //user after logging in can perform following operations
{
	int c;
	clrscr();
	cleardevice();
	settextstyle(0,0,3);
	setcolor(CYAN);
	rectangle(50,50,600,425);
	setcolor(RED);
	outtextxy(100,170,"1. RESUME");
	outtextxy(100,200,"2. NEW GAME");
	outtextxy(100,230,"3. LOGOUT");
	outtextxy(100,260,"4. SCORE");
	outtextxy(100,320,"Enter your choice");
	settextstyle(0,0,2);
	cin>>c;
	switch(c)
	{
		case 1:
		{
			clrscr();
			cleardevice();
			cout<<"Resuming..."<<endl;
			delay(1200);
			l.resume();
			break;
		}
		case 2:
		{
			char con;
			clrscr();
			cleardevice();
			cout<<"Are you sure you want to delete the previous board?"<<endl;
			cout<<"Enter y to continue"<<endl;
			cin>>con;
			con=tolower(con);
			if(con=='y')
			{
				cout<<"New game created:"<<endl;
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						l.b[i][j]=0;
						l.flag[i][j]=0;
					}
				}
				l.score=0;
				l.play();
			}
			else
			{
				cout<<"Failed to create new game!"<<endl;
				cout<<"Taking you back to login page..."<<endl;
				loginpage();
			}
			break;
		}
		case 3:
		{
			clrscr();
			cleardevice();
			cout<<"Logging out..."<<endl;
			delay(1200);
			clrscr();
			cleardevice();
			cout<<"Logged out successfully! "<<endl;
			mainpage();
			break;
		}
		case 4:
		{
			cleardevice();
			cout<<"Your score is:"<<l.score<<endl;
			delay(1000);
			loginpage();
			break;
		}
		default:
		{
			cout<<"Invalid choice!\nEnter again:"<<endl;
			loginpage();
			break;
		}
	}
}

void log :: resume() //resume user's game from whereever they paused
{
	int flag=0;
	int i,j;
	ifstream fin;
	fin.open("l.txt", ios::binary|ios::in);
	while(!fin.eof())
	{

		fin.read((char*)&lf,sizeof(lf));
		if((strcmp(l.un,lf.un)==0)&&(strcmp(l.pass,lf.pass)==0))
		{
			flag=1;
			break;
		 }
		else
			continue;
	}
	if(flag==1)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				l.b[i][j]=lf.b[i][j];
				l.flag[i][j]=lf.flag[i][j];
				l.score=lf.score;
			}
		}
		fin.close();
		l.play();
	}
	else if(flag==-1)
	{
		cout<<"Previous game not found!!\nTaking you back to loginpage...\nYou can create a new game and continue!!"<<endl;
		delay(1000);
		fin.close();
		loginpage();
	}
	else
		fin.close();
}

void main() //maim function to handle the flow of data
{
	clrscr();
	int gd= DETECT,gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	intro();
	instruct();
	delay(1000);
	mainpage();
	getch();
}