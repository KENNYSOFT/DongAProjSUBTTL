#include"KENNYC_160419.H"
#include"KENNYFILE.H"
#include"KENNYSTRHELPER.H"
#define HOME 71
#define END 79
#define ESCAPE 0
#define ALTF4 107
FILE *fini,*fin,*fout;
int width=180,height=40,finished=-1,article=5,focus=3,idx;
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
inline void wprintc(wchar_t ch)
{
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),&ch,1,NULL,NULL);
}
void print(int pos,int line,int y)
{
	int i,j,fg=0;
	bool focused=(y>=(focus-1)*7&&y<focus*7);
	if(!focused)fg=7;
	gotoxy(0,y);
	SetConsoleColor(fg,15);
	if(data[pos].article_a[line]!=data[pos].article_s.texth)for(i=0;data[pos].article_a[line][i]&&wherex()<width-2;++i)wprintc(data[pos].article_a[line][i]);
	else
	{
		for(i=0;data[pos].article_a[line][i-1]!='\t';++i)wprintc(data[pos].article_a[line][i]);
		SetConsoleColor(15,fg);
		for(;i<=data[pos].article_s.cut&&wherex()<width-2;++i)wprintc(data[pos].article_a[line][i]);
		if(focused)
		{
			for(j=i;data[pos].article_a[line][j];++j)if(isDelimeter[data[pos].article_a[line][j]])break;
			if(data[pos].article_a[line][j])
			{
				SetConsoleColor(15,7);
				for(;i<=j&&wherex()<width-2;++i)wprintc(data[pos].article_a[line][i]);
			}
		}
		SetConsoleColor(fg,15);
		for(;data[pos].article_a[line][i]&&wherex()<width-2;++i)wprintc(data[pos].article_a[line][i]);
	}
	for(i=wherex();i<width;++i)printf(" ");
	SetConsoleColor(0,15);
}
void printFocus(int pos,int line)
{
	print(pos,line,(focus-1)*7+line);
}
void print(int idx,int y7)
{
	int i,j;
	if(idx<0||idx>=avails.size())
	{
		for(i=0;i<7;++i)
		{
			gotoxy(0,7*y7+i);
			for(j=0;j<width;++j)printf(" ");
		}
		return;
	}
	for(i=0;i<7;++i)print(avails[idx],i,7*y7+i);
}
void print()
{
	int i;
	for(i=0;i<article;++i)print(idx-focus+1+i,i);
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
void loadSetting()
{
	int i,sta,end;
	char line[1024],var[1024],val[1024];
	fini=fopen("DongAProjSUBTTL.ini","r");
	while(fgets(line,1024,fini))
	{
		for(i=0;line[i];++i)if(line[i]=='=')break;
		if(line[i]==0)continue;
		for(sta=0;line[sta]==' '||line[sta]=='\t';++sta);
		for(end=i-1;line[end]==' '||line[end]=='\t';--end);
		strncpy(var,line+sta,end-sta+1);
		var[end-sta+1]=0;
		for(sta=i+1;line[sta]==' '||line[sta]=='\t';++sta);
		for(end=strlen(line)-1;line[end]==' '||line[end]=='\t'||line[end]=='\n';--end);
		strncpy(val,line+sta,end-sta+1);
		val[end-sta+1]=0;
		if(!strcmpi(var,"width"))sscanf(val,"%d",&width);
		else if(!strcmpi(var,"height"))sscanf(val,"%d",&height);
		else if(!strcmpi(var,"filename"))strcpy(filename,val);
		else if(!strcmpi(var,"finished"))sscanf(val,"%d",&finished);
		else if(!strcmpi(var,"delimeter"))utf8_to_unicode(val,delimeter);
		else if(!strcmpi(var,"article"))sscanf(val,"%d",&article);
		else if(!strcmpi(var,"focus"))sscanf(val,"%d",&focus);
	}
	fclose(fini);
	if(height<7*article+2)height=article*7+2;
	if(focus<1)focus=1;
	if(focus>article)focus=article;
}
void saveSetting()
{
	char *tmp;
	fini=fopen("DongAProjSUBTTL.ini","w");
	fprintf(fini,"width=%d\n",width);
	fprintf(fini,"height=%d\n",height);
	fprintf(fini,"filename=%s\n",filename);
	fprintf(fini,"finished=%d\n",finished);
	fprintf(fini,"delimeter=%s\n",unicode_to_utf8(delimeter,&tmp));
	fprintf(fini,"article=%d\n",article);
	fprintf(fini,"focus=%d\n",focus);
	fclose(fini);
	free(tmp);
}
void loadFile()
{
	int i,j;
	bool available;
	if(filename[0]==0||(fin=fopen(filename,"r"))==NULL)
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
void saveFile()
{
	int i,j;
	char filename2[1024],command[1024];
	sprintf(filename2,"%s.tmp",filename);
	fout=fopen(filename2,"w");
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
	sprintf(command,"del \"%s\"",filename);
	system(command);
	sprintf(command,"ren \"%s\" \"%s\"",filename2,filename);
	system(command);
	finished=avails[idx];
	saveSetting();
}
int main()
{
	int i;
	char ch,ch2;
	loadSetting();
	saveSetting();
	SetConsoleTitle("DongAProjSUBTTL v4.0");
	SetConsoleSize(height,width);
	SetCursorType(NOCURSOR);
	system("color f0");
	gotoxy(0,height-1);
	printf("¢Õ move / ¡ê[Hm][En] adjust / [ ]¢Ò commit / r reset / x mark / s save / q quit");
	for(i=0;delimeter[i];++i)isDelimeter[delimeter[i]]=true;
	loadFile();
	for(idx=0;idx<avails.size();++idx)if(avails[idx]>finished)break;
	print();
	while(1)
	{
		int pos=avails[idx];
		ch=getch();
		gotoxy(0,height-2);
		printf("                              ",ch);
		switch(ch)
		{
		case PRE_ARROW:
			ch2=getch();
			switch(ch2)
			{
			case LEFT:
				if(data[pos].article_s.cut>5)for(data[pos].article_s.cut--;!isDelimeter[data[pos].article_s.texth[data[pos].article_s.cut]]&&data[pos].article_s.cut>5;--data[pos].article_s.cut);
				printFocus(pos,4);
				break;
			case RIGHT:
				if(data[pos].article_s.cut<wcslen(data[pos].article_s.texth)-1)for(data[pos].article_s.cut++;!isDelimeter[data[pos].article_s.texth[data[pos].article_s.cut]]&&data[pos].article_s.texth[data[pos].article_s.cut+1];++data[pos].article_s.cut);
				printFocus(pos,4);
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
				printFocus(pos,4);
				break;
			case END:
				data[pos].article_s.cut=wcslen(data[pos].article_s.texth)-1;
				printFocus(pos,4);
				break;
			default:
				gotoxy(0,height-2);
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
				gotoxy(0,height-2);
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
				printFocus(pos,3);
				printFocus(pos,4);
			}
			break;
		case 'r':
		case 'R':
			memmove(data[pos].article_s.texth+6+(wcslen(data[pos].article_s.subttl)-data[pos].article_s.subttllen),data[pos].article_s.texth+6,sizeof(wchar_t)*(wcslen(data[pos].article_s.texth)+1-6));
			wcsncpy(data[pos].article_s.texth+6,data[pos].article_s.subttl+data[pos].article_s.subttllen,wcslen(data[pos].article_s.subttl)-data[pos].article_s.subttllen);
			data[pos].article_s.subttl[data[pos].article_s.subttllen]=0;
			data[pos].article_s.cut=5;
			cut(pos);
			printFocus(pos,3);
			printFocus(pos,4);
			break;
		case 'x':
		case 'X':
			if(wcslen(data[pos].article_s.comnt)==7)wcscat(data[pos].article_s.comnt,L"xx");
			else if(!wcscmp(data[pos].article_s.comnt+7,L"xx"))data[pos].article_s.comnt[7]=0;
			printFocus(pos,6);
			break;
		case 's':
		case 'S':
			gotoxy(0,height-2);
			printf("Saving...");
			saveFile();
			gotoxy(0,height-2);
			printf("         ");
			break;
		case CTRLC:
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			gotoxy(0,height-2);
			printf("Unknown keycode: %d",ch);
			break;
		}
	}
	fcloseall();
	return 0;
}