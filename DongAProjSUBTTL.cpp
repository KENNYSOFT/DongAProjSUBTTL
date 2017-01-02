#include"KENNYC_160419.H"
#include"KENNYFILE.H"
#include"KENNYSTRHELPER.H"
#define HEIGHT 40
#define WIDTH 180
FILE *ffn,*ffs,*fin,*fout;
int n,pos,cut,dir=1;
char filename[1010],line[8][510];
wchar_t linew[60010][8][210],delimeter[]={182,8214,12305,65084};
bool available[60010],isDelimeter[65536];
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
	cut=5;
	if(available[pos=pos+dir])
	{
		for(i=6;linew[pos][5][i];++i)
		{
			if(linew[pos][5][i]==delimeter[0])cut=i;
			if(i>cut+20)break;
		}
		print();
	}
}
void load()
{
	int i,j;
	fin=fopen(filename,"r");
	if(fin==NULL)
	{
		gotoxy(0,0);
		wprintf(L"file not exist");
		exit(1);
	}
	for(i=0;;++i)
	{
		for(j=1;j<=7;++j)
		{
			fgets(line[j],500,fin);
			if(feof(fin))goto end;
			utf8_to_unicode(line[j],linew[i][j]);
			if(linew[i][j][wcslen(linew[i][j])-1]=='\n')linew[i][j][wcslen(linew[i][j])-1]=0;
		}
		wcscpy(linew[i][0],linew[i][4]);
		if(wcsstr(linew[i][3]+6,L"#N/A")&&wcslen(linew[i][7])==7)available[i]=1;
		else
		{
			available[i]=0;
			for(j=6;linew[i][5][j];++j)
			{
				if((linew[i][5][j]>='A'&&linew[i][5][j]<='Z')||(linew[i][5][j]>='a'&&linew[i][5][j]<='z')||isDelimeter[linew[i][5][j]])
				{
					available[i]=1;
					break;
				}
			}
		}
	}
end:
	n=i-1;
	fclose(fin);
}
void save()
{
	int i,j;
	fout=fopen(filename,"w");
	for(i=0;i<=n;++i)
	{
		for(j=1;j<=7;++j)
		{
			unicode_to_utf8(linew[i][j],line[j]);
			strcat(line[j],"\n");
			fputs(line[j],fout);
		}
	}
	fclose(fout);
	ffs=fopen("finished.txt","w");
	fprintf(ffs,"%d",pos);
	fclose(ffs);
}
int main()
{
	int i;
	char ch,ch2;
	SetConsoleTitle("DongAProjSUBTTL");
	SetConsoleSize(HEIGHT,WIDTH);
	SetCursorType(NOCURSOR);
	system("color f0");
	setlocale(LC_ALL,"korean");
	gotoxy(0,HEIGHT-1);
	wprintf(L"¢Õ move / ¡ê adjust / [ ]¢Ò commit / r reset / x mark / s save / q quit");
	ffn=fopen("filename.txt","r");
	if(ffn)fgets(filename,1000,ffn);
	fclose(ffn);
	ffs=fopen("finished.txt","r");
	if(ffs)fscanf(ffs,"%d",&pos);
	fclose(ffs);
	for(i=0;delimeter[i];++i)isDelimeter[delimeter[i]]=1;
	load();
	move();
	while(1)
	{
		while(!available[pos])move();
		ch=getch();
		switch(ch)
		{
		case PRE_ARROW:
			ch2=getch();
			switch(ch2)
			{
			case LEFT:
				if(cut>5)for(cut--;!isDelimeter[linew[pos][5][cut]]&&cut>5;--cut);
				print(5);
				break;
			case RIGHT:
				if(cut<wcslen(linew[pos][5])-1)for(cut++;!isDelimeter[linew[pos][5][cut]]&&linew[pos][5][cut+1];++cut);
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
			else if(!wcscmp(linew[pos][7]+7,L"xx"))linew[pos][7][7]=0;
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
	fcloseall();
	return 0;
}