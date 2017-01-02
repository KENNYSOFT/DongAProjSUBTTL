#include"KENNYC_160419.H"
FILE*ffn=fopen("filename.txt","r");
FILE*ffs=fopen("finished.txt","r");
#include"KENNYFILE.H"
#include"KENNYSTRHELPER.H"
#define HEIGHT 40
#define WIDTH 180
FILE*fin,*fout;
char filename[1010],line[45010][8][510];
wchar_t linew[45010][8][210],delimeter[]=L"¢Ò";
int n,pos,avail,cut,dir=1;
inline void wprintf(const wchar_t ch)
{
	if(wprintf(L"%c",ch)!=1)wprintf(ch<128?L"?":L"£¿");
}
void print(int line=0)
{
	int i;
	if(line==0)
	{
		for(i=1;i<=7;++i)print(i);
		return;
	}
	gotoxy(0,line-1);
	if(line!=5)for(i=0;linew[pos][line][i]&&wherex()<WIDTH-2;++i)wprintf(linew[pos][line][i]);
	else
	{
		for(i=0;linew[pos][line][i-1]!='\t';++i)wprintf(linew[pos][line][i]);
		SetConsoleColor(15,0);
		for(;i<=cut&&wherex()<WIDTH-2;++i)wprintf(linew[pos][line][i]);
		SetConsoleColor(0,15);
		for(;linew[pos][line][i]&&wherex()<WIDTH-2;++i)wprintf(linew[pos][line][i]);
	}
	for(i=wherex();i<WIDTH-2;++i)printf(" ");
}
void move()
{
	int i;
	pos=pos+dir;
	cut=5;
	if(wcsstr(linew[pos][5],delimeter))// todo: multi delemeter
	{
		avail=1;
		for(i=6;linew[pos][5][i];++i)
		{
			if(linew[pos][5][i]==delimeter[0])cut=i;
			if(i>cut+20)break;
		}
	}
	else if(wcsstr(linew[pos][3]+6,L"#N/A")&&wcslen(linew[pos][7])==7)avail=1;
	else
	{
		avail=0;
		/*for(i=6;linew[pos][5][i];++i)
		{
			if((linew[pos][5][i]>='A'&&linew[pos][5][i]<='Z')||(linew[pos][5][i]>='a'&&linew[pos][5][i]<='z'))
			{
				avail=1;
				cut=5;
				break;
			}
		}*/
	}
	if(avail)print();
}
void load()
{
	int i,j;
	for(i=0;;++i)
	{
		for(j=1;j<=7;++j)
		{
			fgets(line[i][j],500,fin);
			if(feof(fin))goto end;
			utf8_to_unicode(line[i][j],linew[i][j]);
			if(linew[i][j][wcslen(linew[i][j])-1]=='\n')linew[i][j][wcslen(linew[i][j])-1]=0;
		}
		wcscpy(linew[i][0],linew[i][4]);
	}
end:
	n=i-1;
}
void save()
{
	int i,j;
	char command[1024];
	sprintf(command,"copy %s %s.bak >nul",filename,filename);
	system(command);
	fout=fopen(filename,"w");
	for(i=0;i<=n;++i)
	{
		for(j=1;j<=7;++j)
		{
			unicode_to_utf8(linew[i][j],line[i][j]);
			strcat(line[i][j],"\n");
			fputs(line[i][j],fout);
		}
	}
	fclose(fout);
}
int main()
{
	char ch,ch2;
	SetConsoleTitle("DongAProjSUBTTL");
	SetConsoleSize(HEIGHT,WIDTH);
	SetCursorType(NOCURSOR);
	system("color f0");
	setlocale(LC_ALL,"korean");
	gotoxy(0,HEIGHT-1);
	wprintf(L"¢Õ move / ¡ê adjust / [ ]¢Ò commit / r reset / x mark / s save / q quit");
	fgets(filename,1000,ffn);
	fscanf(ffs,"%d",&pos);
	fin=fopen(filename,"r");
	if(fin==NULL)
	{
		wprintf(L"file not exist");
		return 1;
	}
	load();
	fclose(fin);
	move();
	while(1)
	{
		while(!avail)move();
		ch=getch();
		switch(ch)
		{
		case PRE_ARROW:
			ch2=getch();
			switch(ch2)
			{
			case LEFT:
				if(cut>5)for(cut--;linew[pos][5][cut]!=delimeter[0]&&cut>5;--cut);
				print(5);
				break;
			case RIGHT:
				if(cut<wcslen(linew[pos][5])-1)for(cut++;linew[pos][5][cut]!=delimeter[0]&&linew[pos][5][cut+1];++cut);
				print(5);
				break;
			case UP:
				dir=-1;
				move();
				break;
			case DOWN:
				dir=1;
				move();
				break;
			}
			break;
		case ' ':
		case ENTER:
			if(cut>5)
			{
				wcsncat(linew[pos][4],linew[pos][5]+6,cut-5);
				memmove(linew[pos][5]+6,linew[pos][5]+cut+1,sizeof(wchar_t)*(wcslen(linew[pos][5])+1-cut));
				cut=5;
				print(4);
				print(5);
			}
			break;
		case 'r':
		case 'R':
			memmove(linew[pos][5]+6+(wcslen(linew[pos][4])-wcslen(linew[pos][0])),linew[pos][5]+6,sizeof(wchar_t)*(wcslen(linew[pos][5])+1-6));
			memcpy(linew[pos][5]+6,linew[pos][4]+7,sizeof(wchar_t)*(wcslen(linew[pos][4])-wcslen(linew[pos][0])));
			wcscpy(linew[pos][4],linew[pos][0]);
			print(4);
			print(5);
			break;
		case 'x':
		case 'X':
			if(wcslen(linew[pos][7])==7)wcscat(linew[pos][7],L"xx");
			else linew[pos][7][7]=0;
			print(7);
			break;
		case 's':
		case 'S':
			gotoxy(0,HEIGHT-2);
			wprintf(L"Saving...");
			save();
			gotoxy(0,HEIGHT-2);
			wprintf(L"         ");
			break;
		case CTRLC:
		case 'q':
		case 'Q':
			exit(0);
			break;
		}
	}
	return 0;
}