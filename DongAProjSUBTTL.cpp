#include"KENNYC_160419.H"
FILE*ffn=fopen("filename.txt","r");
FILE*ffs=fopen("finished.txt","r");
#include"KENNYFILE.H"
#include"KENNYSTRHELPER.H"
#define HEIGHT 40
#define WIDTH 180
FILE*fin,*fout;
//char line[45010][10][510];
char filename[1010],line[10][510];
wchar_t linew[10][210],delimeter[]=L"ขา";
int avail,cut;
inline void wprintf(const wchar_t ch)
{
	if(wprintf(L"%c",ch)!=1)wprintf(ch<128?L"?":L"ฃฟ");
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
	if(line!=5)for(i=0;linew[line][i]&&wherex()<WIDTH-2;++i)wprintf(linew[line][i]);
	else
	{
		for(i=0;linew[line][i]!='\t';++i)wprintf(linew[line][i]);
		SetConsoleColor(15,0);
		for(;i<=cut;++i)wprintf(linew[line][i]);
		SetConsoleColor(0,15);
		for(;linew[line][i]&&wherex()<WIDTH-2;++i)wprintf(linew[line][i]);
	}
	for(i=wherex();i<WIDTH-2;++i)printf(" ");
	gotoxy(0,7);
}
void load()
{
	int i;
	for(i=1;i<=7;++i)
	{
		fgets(line[i],500,fin);
		utf8_to_unicode(line[i],linew[i]);
		if(linew[i][wcslen(linew[i])-1]=='\n')linew[i][wcslen(linew[i])-1]=0;
	}
	cut=5;
	if(wcsstr(linew[5],delimeter))
	{
		avail=1;
		for(i=6;linew[5][i];++i)
		{
			if(linew[5][i]==delimeter[0])cut=i;
			if(i>cut+20)break;
		}
		print();
	}
	else avail=0;
	// alphabet include -> xx?
}
void save()
{
	int i;
	for(i=1;i<=7;++i)
	{
		wcscat(linew[i],L"\n");
		unicode_to_utf8(linew[i],line[i]);
		fputs(line[i],fout);
	}
	fflush(fout);
}
int main()
{
	int i,j,k,finished,pos;
	char ch,ch2;
	SetConsoleTitle("DongAProjSUBTTL");
	SetConsoleSize(HEIGHT,WIDTH);
	system("color f0");
	setlocale(LC_ALL,"korean");
	gotoxy(0,39);
	//printf("ขี prev, next");
	printf("ก้ next / ก๊ adjust / [ ]ขา commit / x mark / q quit");
	fgets(filename,1000,ffn);
	fscanf(ffs,"%d",&finished);
	fin=fopen(filename,"r");
	if(fin==NULL)
	{
		cout<<"file not exist";
		return 1;
	}
	for(i=strlen(filename)-1;i>=0;--i)if(filename[i]=='.')break;
	memmove(filename+i+7,filename+i,strlen(filename)-i+1);
	memcpy(filename+i,"_result",7);
	fout=fopen(filename,"w");
	for(i=0;i<=finished;++i)
	{
		for(j=1;j<=7;++j)
		{
			fgets(line[j],400,fin);
			fputs(line[j],fout);
		}
	}
	load();
	while(1)
	{
		if(!avail)
		{
			save();
			load();
			continue;
		}
		ch=getch();
		switch(ch)
		{
		case PRE_ARROW:
			ch2=getch();
			switch(ch2)
			{
			case LEFT:
				if(cut>5)for(cut--;linew[5][cut]!=delimeter[0]&&cut>5;--cut);
				print(5);
				break;
			case RIGHT:
				if(cut<wcslen(linew[5])-1)for(cut++;linew[5][cut]!=delimeter[0]&&linew[5][cut+1];++cut);
				print(5);
				break;
			case DOWN:
				save();
				load();
				break;
			}
			break;
		case ' ':
		case ENTER:
			wcsncat(linew[4],linew[5]+6,cut-5);
			memmove(linew[5]+6,linew[5]+cut+1,sizeof(wchar_t)*(wcslen(linew[5])-cut));
			cut=5;
			print(4);
			print(5);
			break;
		case 'x':
		case 'X':
			if(wcslen(linew[7])==7)wcscat(linew[7],L"xx");
			else linew[7][7]=0;
			print(7);
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