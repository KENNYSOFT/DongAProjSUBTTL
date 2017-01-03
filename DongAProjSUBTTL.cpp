#include"KENNYC_160419.H"
#include"KENNYFILE.H"
#include"KENNYSTRHELPER.H"
#define HOME 71
#define END 79
#define ESCAPE 0
#define ALTF4 107
#define HEIGHT 40
#define WIDTH 180
FILE *ffn,*ffs,*fin,*fout;
int idx;
char filename[1010],line[8][510];
wchar_t delimeter[]=L"¢Ò\x2016¡½\xFE3C";
bool isDelimeter[65536];
vector<int> avails;
union article_u
{
	article_u()
	{
		article_s.no=(wchar_t*)malloc(sizeof(wchar_t)*15);
		article_s.author=(wchar_t*)malloc(sizeof(wchar_t)*210);
		article_s.title=(wchar_t*)malloc(sizeof(wchar_t)*210);
		article_s.subttl=(wchar_t*)malloc(sizeof(wchar_t)*210);
		article_s.texth=(wchar_t*)malloc(sizeof(wchar_t)*210);
		article_s.hangul=(wchar_t*)malloc(sizeof(wchar_t)*210);
		article_s.comnt=(wchar_t*)malloc(sizeof(wchar_t)*15);
		article_s.cut=5;
		article_s.subttllen=0;
	}
	struct
	{
		wchar_t *no,*author,*title,*subttl,*texth,*hangul,*comnt;
		int cut,subttllen;
	}article_s;
	wchar_t *article_a[7];
};
vector<article_u> data;
inline void wprint(wchar_t ch)
{
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),&ch,1,NULL,NULL);
}
void print(int pos,int idx,int y,bool focus=false)
{
	int i,j,fg=0;
	if(!focus)fg=7;
	gotoxy(0,y);
	SetConsoleColor(fg,15);
	if(data[pos].article_a[idx]!=data[pos].article_s.texth)for(i=0;data[pos].article_a[idx][i]&&wherex()<WIDTH-2;++i)wprint(data[pos].article_a[idx][i]);
	else
	{
		for(i=0;data[pos].article_a[idx][i-1]!='\t';++i)wprint(data[pos].article_a[idx][i]);
		SetConsoleColor(15,fg);
		for(;i<=data[pos].article_s.cut&&wherex()<WIDTH-2;++i)wprint(data[pos].article_a[idx][i]);
		if(focus)
		{
			for(j=i;data[pos].article_a[idx][j];++j)if(isDelimeter[data[pos].article_a[idx][j]])break;
			if(data[pos].article_a[idx][j])
			{
				SetConsoleColor(15,7);
				for(;i<=j;++i)wprint(data[pos].article_a[idx][i]);
			}
		}
		SetConsoleColor(fg,15);
		for(;data[pos].article_a[idx][i]&&wherex()<WIDTH-2;++i)wprint(data[pos].article_a[idx][i]);
	}
	for(i=wherex();i<WIDTH;++i)printf(" ");
	SetConsoleColor(0,15);
}
void print(int idx,int y7)
{
	int i,j;
	if(idx<0||idx>=avails.size())
	{
		for(i=0;i<7;++i)
		{
			gotoxy(0,7*y7+i);
			for(j=0;j<WIDTH;++j)printf(" ");
		}
		return;
	}
	for(i=0;i<7;++i)print(avails[idx],i,7*y7+i,y7==2);
}
void print()
{
	int i;
	for(i=0;i<=4;++i)print(idx-2+i,i);
}
void cut(int pos)
{
	int i;
	for(i=6;data[pos].article_s.texth[i];++i)
	{
		if(isDelimeter[data[pos].article_s.texth[i]])data[pos].article_s.cut=i;
		if(i>data[pos].article_s.cut+20)break;
	}
}
void load()
{
	int i,j;
	bool available;
	if(strlen(filename)==0||(fin=fopen(filename,"r"))==NULL)
	{
		gotoxy(0,0);
		printf("file not exist");
		exit(1);
	}
	for(i=0;;++i)
	{
		data.push_back(article_u());
		for(j=0;j<7;++j)
		{
			fgets(line[j],500,fin);
			if(feof(fin))goto end;
			utf8_to_unicode(line[j],data[i].article_a[j]);
			if(data[i].article_a[j][wcslen(data[i].article_a[j])-1]=='\n')data[i].article_a[j][wcslen(data[i].article_a[j])-1]=0;
		}
		data[i].article_s.subttllen=wcslen(data[i].article_s.subttl);
		if(wcsstr(data[i].article_s.title+6,L"#N/A")&&wcslen(data[i].article_s.comnt)==7)available=true;
		else
		{
			available=false;
			for(j=6;data[i].article_s.texth[j];++j)
			{
				if((data[i].article_s.texth[j]>='A'&&data[i].article_s.texth[j]<='Z')||(data[i].article_s.texth[j]>='a'&&data[i].article_s.texth[j]<='z')||isDelimeter[data[i].article_s.texth[j]])
				{
					available=true;
					break;
				}
			}
		}
		if(available)
		{
			cut(i);
			avails.push_back(i);
		}
	}
end:
	data.pop_back();
	fclose(fin);
}
void save()
{
	int i,j;
	fout=fopen(filename,"w");
	for(i=0;i<data.size();++i)
	{
		for(j=0;j<7;++j)
		{
			unicode_to_utf8(data[i].article_a[j],line[j]);
			strcat(line[j],"\n");
			fputs(line[j],fout);
		}
	}
	fclose(fout);
	ffs=fopen("finished.txt","w");
	fprintf(ffs,"%d",avails[idx]);
	fclose(ffs);
}
int main()
{
	int i,finished;
	char ch,ch2;
	SetConsoleTitle("DongAProjSUBTTL v3.0");
	SetConsoleSize(HEIGHT,WIDTH);
	SetCursorType(NOCURSOR);
	system("color f0");
	gotoxy(0,HEIGHT-1);
	printf("¢Õ move / ¡ê[Hm][En] adjust / [ ]¢Ò commit / r reset / x mark / s save / q quit");
	if(ffn=fopen("filename.txt","r"))fgets(filename,1000,ffn);
	else ffn=fopen("filename.txt","w");
	fclose(ffn);
	if(ffs=fopen("finished.txt","r"))fscanf(ffs,"%d",&finished);
	else ffs=fopen("finished.txt","w");
	fclose(ffs);
	for(i=0;delimeter[i];++i)isDelimeter[delimeter[i]]=true;
	load();
	for(idx=0;idx<avails.size();++idx)if(avails[idx]>finished)break;
	print();
	while(1)
	{
		int pos=avails[idx];
		ch=getch();
		switch(ch)
		{
		case PRE_ARROW:
			ch2=getch();
			switch(ch2)
			{
			case LEFT:
				if(data[pos].article_s.cut>5)for(data[pos].article_s.cut--;!isDelimeter[data[pos].article_s.texth[data[pos].article_s.cut]]&&data[pos].article_s.cut>5;--data[pos].article_s.cut);
				print(pos,4,18,true);
				break;
			case RIGHT:
				if(data[pos].article_s.cut<wcslen(data[pos].article_s.texth)-1)for(data[pos].article_s.cut++;!isDelimeter[data[pos].article_s.texth[data[pos].article_s.cut]]&&data[pos].article_s.texth[data[pos].article_s.cut+1];++data[pos].article_s.cut);
				print(pos,4,18,true);
				break;
			case UP:
				if(idx>0)idx--;
				print();
				break;
			case DOWN:
				if(idx<avails.size()-1)idx++;
				print();
				break;
			case HOME:
				data[pos].article_s.cut=5;
				print(pos,4,18,true);
				break;
			case END:
				data[pos].article_s.cut=wcslen(data[pos].article_s.texth)-1;
				print(pos,4,18,true);
				break;
			default:
				gotoxy(0,HEIGHT-2);
				printf("                              ",ch);
				gotoxy(0,HEIGHT-2);
				printf("Unknown arrow keycode: %d",ch2);
				break;
			}
			break;
		case ESCAPE:
			ch2=getch();
			switch(ch2)
			{
			case ALTF4:
				exit(0);
				break;
			default:
				gotoxy(0,HEIGHT-2);
				printf("                              ",ch);
				gotoxy(0,HEIGHT-2);
				printf("Unknown escape keycode: %d",ch2);
				break;
			}
			break;
		case ' ':
		case ENTER:
			if(data[pos].article_s.cut>5)
			{
				wcsncat(data[pos].article_s.subttl,data[pos].article_s.texth+6,data[pos].article_s.cut-5);
				memmove(data[pos].article_s.texth+6,data[pos].article_s.texth+data[pos].article_s.cut+1,sizeof(wchar_t)*(wcslen(data[pos].article_s.texth)+1-data[pos].article_s.cut));
				data[pos].article_s.cut=5;
				cut(pos);
				print(pos,3,17,true);
				print(pos,4,18,true);
			}
			break;
		case 'r':
		case 'R':
			memmove(data[pos].article_s.texth+6+(wcslen(data[pos].article_s.subttl)-data[pos].article_s.subttllen),data[pos].article_s.texth+6,sizeof(wchar_t)*(wcslen(data[pos].article_s.texth)+1-6));
			wcsncpy(data[pos].article_s.texth+6,data[pos].article_s.subttl+data[pos].article_s.subttllen,wcslen(data[pos].article_s.subttl)-data[pos].article_s.subttllen);
			data[pos].article_s.subttl[data[pos].article_s.subttllen]=0;
			data[pos].article_s.cut=5;
			cut(pos);
			print(pos,3,17,true);
			print(pos,4,18,true);
			break;
		case 'x':
		case 'X':
			if(wcslen(data[pos].article_s.comnt)==7)wcscat(data[pos].article_s.comnt,L"xx");
			else if(!wcscmp(data[pos].article_s.comnt+7,L"xx"))data[pos].article_s.comnt[7]=0;
			print(pos,6,20,true);
			break;
		case 's':
		case 'S':
			gotoxy(0,HEIGHT-2);
			printf("Saving...");
			save();
			gotoxy(0,HEIGHT-2);
			printf("         ");
			break;
		case CTRLC:
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			gotoxy(0,HEIGHT-2);
			printf("                              ",ch);
			gotoxy(0,HEIGHT-2);
			printf("Unknown keycode: %d",ch);
			break;
		}
	}
	fcloseall();
	return 0;
}