/*************************************************************
 *                                                           *
 * # KENNYC.H #                                              *
 *                                                           *
 *                                                           *
 * 제작자 : 박현민                                           *
 *                                                           *
 *                                                           *
 * 제작일 : 16.04.19                                         *
 *                                                           *
 *                                                           *
 * 설  명 : 여러가지 함수와 인클루드 파일들을 모아 놓은 헤더 *
 *          파일 입니다.                                     *
 *                                                           *
 *************************************************************/

#ifndef __KENNYC_H__
#define __KENNYC_H__

#include<iostream>
#include<fstream>
#include<cmath>
#include<ctime>
#include<string>
#include<algorithm>
#include<functional>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<tlhelp32.h>
#include<shlwapi.h>
#include<shlobj.h>
#include<wininet.h>
#pragma comment(lib,"wininet.lib")
#pragma comment(lib,"urlmon.lib")
#pragma comment(lib,"shlwapi.lib")
#pragma comment(linker,"/IGNORE:4089")
#pragma warning(disable:4800)
using namespace std;

#define PRE_ARROW -32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define SPACE 32
#define ESC 27
#define CTRLC 3

#define SHLM HKEY_LOCAL_MACHINE
#define SHCU HKEY_CURRENT_USER
#define SHCR HKEY_CLASSES_ROOT

#define clrscr() system("cls")			// 화면을 모두 지운다.
#define delay(n) Sleep(n)				// n/1000초만큼 시간을 지연시킨다.
#define randomize() srand(time(NULL))	// 난수 발생 함수를 초기화한다.
#define random(n) (rand()%n)			// 0~n-1까지의 난수를 발생한다.
#define Random(n) (rand()%n+1)			// 1~n까지의 난수를 발생한다.
#define SetConsoleColor(a,b) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a+(16*b))	// 콘솔의 배경과, 글자의 색을 지정한다.

typedef enum{NOCURSOR,SOLIDCURSOR,NORMALCURSOR}CURSOR_TYPE;
typedef enum{INCREASE,DECREASE}SORT_TYPE;

__int64 P(int n,int r) // nPr(순열)의 값을 구한다.
{
	int a=1;
	for(int i=n;i>=n-r+1;i--)a=a*i;
	return a;
}

__int64 fact(int n) // n!(팩토리얼)의 값을 구한다.
{
	if(n==1||n==0)return 1;
	return n*fact(n-1);
}

__int64 C(int n,int r) // nCr(조합)의 값을 구한다.
{
	return P(n,r)/fact(r);
}

__int64 H(int n,int r) // nHr(중복조합)의 값을 구한다.
{
	return C(n+r-1,r);
}

void bubblesort(int a[],int sta,int end,SORT_TYPE s) // 배열을 오름차순 또는 내림차순으로 정렬한다.
{
	int i,j;
	switch(s)
	{
	case INCREASE:
		for(i=sta;i<end;i++)for(j=i+1;j<=end;j++)if(a[i]>a[j])swap(a[i],a[j]);
		break;

	case DECREASE:
		for(i=sta;i<end;i++)for(j=i+1;j<=end;j++)if(a[i]<a[j])swap(a[i],a[j]);
		break;
	}
} // 사용 예 : bubblesort(b,1,15,INCREASE); - b : 배열, 1,15 : 위치, INCREASE : 오름차순

void quicksort_real_de(int a[],int sta,int end,int pivot,int n)
{
	int i=sta,j=n;
	if(n<=1)return;
	while(1)
	{
		while(a[++i]<a[pivot])if(i>=n)break;
		while(a[--j]>a[pivot]);
		if(i>=j)break;
		swap(a[i],a[j]);
	}
	swap(a[pivot],a[j]);
	quicksort_real_de(a,sta,end,pivot,j);
	quicksort_real_de(a,sta,end,pivot+j+1,n-j-1);
}

void quicksort_real_in(int a[],int sta,int end,int pivot,int n)
{
	int i=sta,j=n;
	if(n<=1)return;
	while(1)
	{
		while(a[++i]>a[pivot])if(i>=n)break;
		while(a[--j]<a[pivot]);
		if(i>=j)break;
		swap(a[i],a[j]);
	}
	swap(a[pivot],a[j]);
	quicksort_real_in(a,sta,end,pivot,j);
	quicksort_real_in(a,sta,end,pivot+j+1,n-j-1);
}

void quicksort(int a[],int sta,int end,SORT_TYPE s) // 배열을 오름차순 또는 내림차순으로 정렬한다.
{
	switch(s)
	{
	case INCREASE:
		quicksort_real_in(a,sta,end,1,end-sta+1);
		break;

	case DECREASE:
		quicksort_real_de(a,sta,end,1,end-sta+1);
		break;
	}
} // 사용 예 : quicksort(b,1,15,INCREASE); - b : 배열, 1,15 : 위치, INCREASE : 오름차순

void gotoxy(int x,int y) // 커서를 x,y좌표로 이동시킨다.
{
	COORD Cur={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

int wherex() // 커서의 x 좌표를 조사한다.
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	return BufInfo.dwCursorPosition.X;
}

int wherey() // 커서의 y좌표를 조사한다.
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	return BufInfo.dwCursorPosition.Y;
}

void SetCursorType(CURSOR_TYPE c) // 커서를 숨기거나 다시 표시한다.
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch(c)
	{
	case NOCURSOR: // 커서 없음
		CurInfo.dwSize=1;
		CurInfo.bVisible=FALSE;
		break;

	case SOLIDCURSOR: // 한 글자 커서
		CurInfo.dwSize=100;
		CurInfo.bVisible=TRUE;
		break;

	case NORMALCURSOR: // 밑줄 커서
		CurInfo.dwSize=20;
		CurInfo.bVisible=TRUE;
		break;

	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}

bool KillProcess(string procname) // 현재 실행중인 Process를 종료시킨다.
{
	HANDLE hProcessSnap=NULL;
	bool Ret=0;
	PROCESSENTRY32 pe32={0};
	string ProcessName=procname;
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap==INVALID_HANDLE_VALUE)return INVALID_HANDLE_VALUE;
	pe32.dwSize=sizeof(PROCESSENTRY32);
	if(Process32First(hProcessSnap,&pe32))
	{
		DWORD Code=0,dwPriorityClass;
		do
		{
			HANDLE hProcess;
			hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
			dwPriorityClass=GetPriorityClass(hProcess);
			string Temp=pe32.szExeFile;
			if(Temp==ProcessName)
			{
				if(TerminateProcess(hProcess,0))GetExitCodeProcess(hProcess,&Code);
				else return GetLastError();
			}
			CloseHandle(hProcess);
		}while(Process32Next(hProcessSnap,&pe32));
		Ret=1;
	}
	CloseHandle(hProcessSnap);
	return Ret;
}

__int64 filecmp(FILE*a,FILE*b) // 파일 2개를 비교한다. 단, 같으면 0이 반환되고, 다르면 최초로 다른 주소값이 반환된다. 여기서 주소값은 맨 처음 Byte를 1번지로 한다.
{
	__int64 cnt=1;
	int t1[1]={0},t2[1]={0};
	while(!feof(a)&&!feof(b))
	{
		fread(t1,1,1,a);
		fread(t2,1,1,b);
		if(t1[0]!=t2[0])return cnt;
		cnt++;
	}
	if(feof(a)&&feof(b))return 0;
	else return cnt;
}

int gcd_real(int max,int min)
{
	if(min==0)return max;
	else return gcd_real(min,max%min);
}

int gcd(int a,int b) // 두 수의 최대공약수를 구한다.
{
	if(a>b)return gcd_real(a,b);
	else return gcd_real(b,a);
}

int lcm(int a,int b) // 두 수의 최소공배수를 구한다.
{
	return a*b/gcd(a,b);
}

FILE*LoadFt(char*Title,char*Filter,char*Extension="",char*Initial="") // 텍스트 모드로 파일을 불러오기 위한 대화상자를 연다.
{
	char file_path[1024],file_name[1024];
	strcpy(file_path,Initial);
	OPENFILENAME open_file={sizeof(OPENFILENAME),GetForegroundWindow(),0,Filter,NULL,0,1,file_path,sizeof(file_path),file_name,sizeof(file_name),NULL,Title,OFN_ENABLESIZING|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,0,12,NULL,0,NULL,NULL};
	if(!GetOpenFileName(&open_file))return NULL;
	FILE*fp=fopen(file_path,"rt");
	return fp;
} // 사용 예 : FILE*fl=LoadFt("KENNYC Load","KENNYC TEST(*.kct)\0*.kct\0KENNYC TEST2(*.kc2)\0*.kc2\0\0"); - 제목 : KENNYC Load, 파일 형식 : KENNYC TEST(*.kct)와 KENNYC TEST2(*.kc2)

FILE*SaveFt(char*Title,char*Filter,char*Extension="",char*Initial="") // 텍스트 모드로 파일을 저장하기 위한 대화상자를 연다.
{
	char file_path[1024],file_name[1024];
	strcpy(file_path,Initial);
	OPENFILENAME open_file={sizeof(OPENFILENAME),GetForegroundWindow(),0,Filter,NULL,0,1,file_path,sizeof(file_path),file_name,sizeof(file_name),NULL,Title,OFN_ENABLESIZING|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,0,12,Extension,0,NULL,NULL};
	if(!GetSaveFileName(&open_file))return NULL;
	FILE*fp=fopen(file_path,"wt");
	return fp;
} // 사용 예 : FILE*fs=SaveFt("KENNYC Save","KENNYC TEST(*.kct)\0*.kct\0KENNYC TEST2(*.kc2)\0*.kc2\0\0","kct","KENNYC_박현민.kct"); - 제목 : KENNYC Save, 파일 형식 : KENNYC TEST(*.kct)와 KENNYC TEST2(*.kc2), 기본 확장자 : kct, 기본 이름 : KENNYC_박현민.kct

FILE*LoadFb(char*Title,char*Filter,char*Extension="",char*Initial="") // 바이너리 모드로 파일을 불러오기 위한 대화상자를 연다.
{
	char file_path[1024],file_name[1024];
	strcpy(file_path,Initial);
	OPENFILENAME open_file={sizeof(OPENFILENAME),GetForegroundWindow(),0,Filter,NULL,0,1,file_path,sizeof(file_path),file_name,sizeof(file_name),NULL,Title,OFN_ENABLESIZING|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,0,12,NULL,0,NULL,NULL};
	if(!GetOpenFileName(&open_file))return NULL;
	FILE*fp=fopen(file_path,"rb");
	return fp;
} // 사용 예 : FILE*fl=LoadFb("KENNYC Load","KENNYC TEST(*.kct)\0*.kct\0KENNYC TEST2(*.kc2)\0*.kc2\0\0"); - 제목 : KENNYC Load, 파일 형식 : KENNYC TEST(*.kct)와 KENNYC TEST2(*.kc2)

FILE*SaveFb(char*Title,char*Filter,char*Extension="",char*Initial="") // 바이너리 모드로 파일을 저장하기 위한 대화상자를 연다.
{
	char file_path[1024],file_name[1024];
	strcpy(file_path,Initial);
	OPENFILENAME open_file={sizeof(OPENFILENAME),GetForegroundWindow(),0,Filter,NULL,0,1,file_path,sizeof(file_path),file_name,sizeof(file_name),NULL,Title,OFN_ENABLESIZING|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,0,12,Extension,0,NULL,NULL};
	if(!GetSaveFileName(&open_file))return NULL;
	FILE*fp=fopen(file_path,"wb");
	return fp;
} // 사용 예 : FILE*fs=SaveFb("KENNYC Save","KENNYC TEST(*.kct)\0*.kct\0KENNYC TEST2(*.kc2)\0*.kc2\0\0","kct","KENNYC_박현민.kct"); - 제목 : KENNYC Save, 파일 형식 : KENNYC TEST(*.kct)와 KENNYC TEST2(*.kc2), 기본 확장자 : kct, 기본 이름 : KENNYC_박현민.kct

int MaxData(int N, ...) // N개의 데이터 중 가장 큰 값을 구한다.
{
	int max=INT_MIN,i,tmp;
	va_list ap;
	va_start(ap,N);
	for(i=1;i<=N;++i)
	{
		tmp=va_arg(ap,int);
		if(max<tmp)max=tmp;
	}
	va_end(ap);
	return max;
}

int MinData(int N, ...) // N개의 데이터 중 가장 작은 값을 구한다.
{
	int min=INT_MAX,i,tmp;
	va_list ap;
	va_start(ap,N);
	for(i=1;i<=N;++i)
	{
		tmp=va_arg(ap,int);
		if(min>tmp)min=tmp;
	}
	va_end(ap);
	return min;
}

int SumData(int N, ...) // N개의 데이터의 합을 구한다.
{
	int sum=0,i,tmp;
	va_list ap;
	va_start(ap,N);
	for(i=1;i<=N;++i)
	{
		tmp=va_arg(ap,int);
		sum=sum+tmp;
	}
	va_end(ap);
	return sum;
}

void SetConsoleSize(int Lines=25,int Cols=80) // 콘솔의 크기를 지정한다.
{
	char command[64];
	sprintf(command,"mode con: lines=%d cols=%d",Lines,Cols);
	system(command);
}

unsigned int SHRegReadInt(HKEY hKey,char*lpKey,char*lpValue,int nDefault) // 레지스트리에서 수를 읽는다.
{
	HKEY key;
	DWORD dwDisp,Size;
	unsigned int Result;
	if(RegCreateKeyEx(hKey,lpKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_READ,NULL,&key,&dwDisp)!=ERROR_SUCCESS)return 0;
	Size=sizeof(long);
	if(RegQueryValueEx(key,lpValue,0,NULL,(LPBYTE)&Result,&Size)!=ERROR_SUCCESS)Result=nDefault;
	RegCloseKey(key);
	return Result;
}

bool SHRegReadString(HKEY hKey,char*lpKey,char*lpValue,char*lpDefault,char*lpRet,DWORD nSize) // 레지스트리에서 문자열을 읽는다.
{
	HKEY key;
	DWORD dwDisp,Size;
	if(RegCreateKeyEx(hKey,lpKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_READ,NULL,&key,&dwDisp)!=ERROR_SUCCESS)return FALSE;
	Size=nSize;
	if(RegQueryValueEx(key,lpValue,0,NULL,(LPBYTE)lpRet,&Size)!=ERROR_SUCCESS)
	{
		strcpy(lpRet,lpDefault);
		return FALSE;
	}
	RegCloseKey(key);
	return TRUE;
}

bool SHRegWriteInt(HKEY hKey,char*lpKey,char*lpValue,unsigned int nData) // 레지스트리에 수를 쓴다.
{
	HKEY key;
	DWORD dwDisp;
	if(RegCreateKeyEx(hKey,lpKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&key,&dwDisp)!=ERROR_SUCCESS)return FALSE;
	if(RegSetValueEx(key,lpValue,0,REG_DWORD,(LPBYTE)&nData,sizeof(UINT))!=ERROR_SUCCESS)return FALSE;
	RegCloseKey(key);
	return TRUE;
}

bool SHRegWriteString(HKEY hKey,char*lpKey,char*lpValue,char*lpData) // 레지스트리에 문자열을 쓴다.
{
	HKEY key;
	DWORD dwDisp;
	if(RegCreateKeyEx(hKey,lpKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&key,&dwDisp)!=ERROR_SUCCESS)return FALSE;
	if(RegSetValueEx(key,lpValue,0,REG_SZ,(LPBYTE)lpData,lstrlen(lpData)+1)!=ERROR_SUCCESS)return FALSE;
	RegCloseKey(key);
	return TRUE;
}

void MakeAssociate(char*Path,char*SWName,char*Extension,char*Description) // 레지스트리에 확장자를 등록시킨다.
{
	char OldProgID[64],OldDesc[64],NewProgID[64],NewDesc[64],szKey[MAX_PATH],path[1024];
	SHRegReadString(SHCR,Extension,NULL,"",OldProgID,64);
	SHRegReadString(SHCR,OldProgID,NULL,"",OldDesc,64);
	sprintf(NewProgID,"%s%s",SWName,Extension);
	if(Description==NULL)strcpy(NewDesc,OldDesc);
	else strcpy(NewDesc,Description);
	SHRegWriteString(SHCR,NewProgID,NULL,NewDesc);
	wsprintf(szKey,"%s\\shell\\open\\command",NewProgID);
	strcpy(path,Path);
	strcat(path," \"%1\"");
	SHRegWriteString(SHCR,szKey,NULL,path);
	SHRegWriteString(SHCR,Extension,NULL,NewProgID);
	if(strcmp(OldProgID,NewProgID)!=0)SHRegWriteString(SHCR,NewProgID,"OldProgID",OldProgID);
	SHChangeNotify(SHCNE_ASSOCCHANGED,SHCNF_IDLIST,NULL,NULL);
} // 사용 예 : MakeAssociate(argv[0],"KENNYTEST",".kt","KENNYTEST Test File"); - 현재 실행 파일의 경로 : argv[0], 프로그램 이름 : KENNYTEST, 확장자 : .kt, 설명 : KENNYTEST Test File

void UnAssociate(char*SWName,char*Extension) // 레지스트리에 확장자가 등록된 것을 해제시킨다.
{
	char OldProgID[64],NewProgID[64];
	sprintf(NewProgID,"%s%s",SWName,Extension);
	SHRegReadString(SHCR,Extension,NULL,"",OldProgID,64);
	if(!strcmp(OldProgID,NewProgID))
	{
		SHRegReadString(SHCR,NewProgID,"OldProgID","",OldProgID,64);
		SHRegWriteString(SHCR,Extension,NULL,OldProgID);
		SHDeleteKey(SHCR,NewProgID);
	}
	SHChangeNotify(SHCNE_ASSOCCHANGED,SHCNF_IDLIST,NULL,NULL);
} // 사용 예 : UnAssociate("KENNYTEST",".kt"); - 프로그램 이름 : KENNYTEST, 확장자 : .kt

void RearrangePath(char*Path,char*CPName,char*SWName,char*Version) // 레지스트리에 등록된 정보를 수정한다.
{
	char InstPath[1024],ExePath[1024],lpSubKey[MAX_PATH],Temp[128],KEY[128];
	int i,Result,len;
	DWORD Size;
	HKEY key;
	strcpy(Temp,SWName);
	strcat(Temp,".");
	sprintf(KEY,"Software\\%s\\%s\\%s",CPName,SWName,Version);
	len=strlen(Temp);
	SHRegReadString(SHCU,KEY,"InstPath","",InstPath,MAX_PATH);
	strcpy(ExePath,Path);
	if(!strcmp(ExePath,InstPath))return;
	SHRegWriteString(SHCU,KEY,"InstPath",ExePath);
	RegOpenKeyEx(SHCR,NULL,0,KEY_READ,&key);
	Result=ERROR_SUCCESS;
	for(i=0;Result==ERROR_SUCCESS;++i)
	{
		Size=MAX_PATH;
		Result=RegEnumKeyEx(key,i,lpSubKey,&Size,NULL,NULL,NULL,NULL);
		if(Result==ERROR_SUCCESS&&!strncmp(lpSubKey,SWName,len))MakeAssociate(Path,SWName,lpSubKey+len-1,NULL);
	}
	RegCloseKey(key);
} // 사용 예 : RearrangePath(argv[0],"KENNYSOFT","KENNYTEST","1.0"); - 현재 실행 파일의 경로 : argv[0], 회사 이름 : KENNTSOFT, 프로그램 이름 : KENNYTEST, 프로그램 버전 : 1.0

void Uninstall(char*SWName) // 레지스트리에 등록된 모든 확장자를 등록 해제시킨다.
{
	char lpSubKey[MAX_PATH],Temp[128];
	int i,Result,len;
	DWORD Size;
	HKEY key;
	strcpy(Temp,SWName);
	strcat(Temp,".");
	len=strlen(Temp);
	RegOpenKeyEx(SHCR,NULL,0,KEY_READ,&key);
	Result=ERROR_SUCCESS;
	for(i=0;Result==ERROR_SUCCESS;++i)
	{
		Size=MAX_PATH;
		Result=RegEnumKeyEx(key,i,lpSubKey,&Size,NULL,NULL,NULL,NULL);
		if(Result==ERROR_SUCCESS&&!strncmp(lpSubKey,SWName,len))
		{
			UnAssociate(SWName,lpSubKey+len-1);
			i--;
		}
	}
	RegCloseKey(key);
} // 사용 예 : Uninstall("KENNYTEST"); - 프로그램 이름 : KENNYTEST

int FindStringAtEnv(char*Env[],char*String) // Env 문자열에서 String에 해당하는 헤더를 가지고 있는 줄을 찾는다.
{
	int i,j,len=strlen(String);
	char copyofenv[128]={0};
	for(i=0;;++i)
	{
		for(j=0;j<len;++j)
		{
			copyofenv[j]=Env[i][j];
			if(!copyofenv[j])break;
		}
		if(!strcmp(copyofenv,String))return i;
	}
} // 사용 예 : int point=FindStringAtEnv(env,"HOMEDRIVE"); - 찾을 문자열 : HOMEDRIVE

unsigned int GetFilesize(char*FileName) // 파일의 크기를 구한다.
{
	unsigned int Ret;
	HANDLE hFile=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	Ret=GetFileSize(hFile,NULL);
	CloseHandle(hFile);
	return Ret;
}

bool StringToClipboard(char*String) // 문자열을 클립보드로 복사한다.
{
	int OK=OpenClipboard(NULL);
	if(!OK)return 0;
	HGLOBAL hGlobal=GlobalAlloc(GMEM_DDESHARE,strlen(String)+1);
	char*Buffer=(char*)GlobalLock(hGlobal);
	strcpy(Buffer,String);
	GlobalUnlock(hGlobal);
	EmptyClipboard();
	SetClipboardData(CF_TEXT,hGlobal);
	CloseClipboard();
	return 1;
}

bool isPrime(int N) // 주어진 수인 N이 소수인지 검사한다.
{
	int i,root=sqrt(N);
	if(N<3)return 1;
	if(N%2==0)return 0;
	for(i=3;i<=root;i=i+2)if(N%i==0)break;
	return i>root;
}

istream& operator>>(istream &is,__int64 &a) // cin에서 __int64를 사용할 수 있도록 한다.
{
	char tmp[30];
	is>>tmp;
	sscanf(tmp,"%I64d",&a);
	return is;
}

ostream& operator<<(ostream &os,const __int64 &a) // cout에서 __int64를 사용할 수 있도록 한다.
{
	char tmp[30];
	sprintf(tmp,"%I64d",a);
	os<<tmp;
	return os;
}

extern "C++"
{
	template<typename T> void** IID_PPV_ARGS_Helper(T** pp) 
	{
		static_cast<IUnknown*>(*pp);
		return reinterpret_cast<void**>(pp);
	}
}

#define IID_PPV_ARGS(ppType) __uuidof(**(ppType)), IID_PPV_ARGS_Helper(ppType)

typedef enum THUMBBUTTONFLAGS{THBF_ENABLED=0,THBF_DISABLED=0x1,THBF_DISMISSONCLICK=0x2,THBF_NOBACKGROUND=0x4,THBF_HIDDEN=0x8,THBF_NONINTERACTIVE=0x10}THUMBBUTTONFLAGS;
typedef enum THUMBBUTTONMASK{THB_BITMAP=0x1,THB_ICON=0x2,THB_TOOLTIP=0x4,THB_FLAGS=0x8}THUMBBUTTONMASK;
typedef struct THUMBBUTTON
{
	THUMBBUTTONMASK dwMask;
	UINT iId;
	UINT iBitmap;
	HICON hIcon;
	WCHAR szTip[260];
	THUMBBUTTONFLAGS dwFlags;
}THUMBBUTTON,*LPTHUMBBUTTON;

EXTERN_C const IID IID_ITaskbarList;
MIDL_INTERFACE("56FDF342-FD6D-11d0-958A-006097C9A090")
ITaskbarList : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE HrInit()=0;
	virtual HRESULT STDMETHODCALLTYPE AddTab(HWND hwnd)=0;
	virtual HRESULT STDMETHODCALLTYPE DeleteTab(HWND hwnd)=0;
	virtual HRESULT STDMETHODCALLTYPE ActivateTab(HWND hwnd)=0;
	virtual HRESULT STDMETHODCALLTYPE SetActiveAlt(HWND hwnd)=0;
};

EXTERN_C const IID IID_ITaskbarList2;
MIDL_INTERFACE("602D4995-B13A-429b-A66E-1935E44F4317")
ITaskbarList2 : public ITaskbarList
{
public:
	virtual HRESULT STDMETHODCALLTYPE MarkFullscreenWindow(HWND hwnd,BOOL fFullscreen)=0;
};

typedef enum TBPFLAG{TBPF_NOPROGRESS=0,TBPF_INDETERMINATE=0x1,TBPF_NORMAL=0x2,TBPF_ERROR=0x4,TBPF_PAUSED=0x8}TBPFLAG;

EXTERN_C const IID IID_ITaskbarList3;
MIDL_INTERFACE("ea1afb91-9e28-4b86-90e9-9e9f8a5eefaf")
ITaskbarList3 : public ITaskbarList2
{
public:
	virtual HRESULT STDMETHODCALLTYPE SetProgressValue(HWND hwnd,ULONGLONG ullCompleted,ULONGLONG ullTotal)=0;
	virtual HRESULT STDMETHODCALLTYPE SetProgressState(HWND hwnd,TBPFLAG tbpFlags)=0;
	virtual HRESULT STDMETHODCALLTYPE RegisterTab(HWND hwndTab,HWND hwndMDI)=0;
	virtual HRESULT STDMETHODCALLTYPE UnregisterTab(HWND hwndTab)=0;
	virtual HRESULT STDMETHODCALLTYPE SetTabOrder(HWND hwndTab,HWND hwndInsertBefore)=0;
	virtual HRESULT STDMETHODCALLTYPE SetTabActive(HWND hwndTab,HWND hwndMDI,DWORD dwReserved)=0;
	virtual HRESULT STDMETHODCALLTYPE ThumbBarAddButtons(HWND hwnd,UINT cButtons,LPTHUMBBUTTON pButton)=0;
	virtual HRESULT STDMETHODCALLTYPE ThumbBarUpdateButtons(HWND hwnd,UINT cButtons,LPTHUMBBUTTON pButton)=0;
	virtual HRESULT STDMETHODCALLTYPE ThumbBarSetImageList(HWND hwnd,HIMAGELIST himl)=0;
	virtual HRESULT STDMETHODCALLTYPE SetOverlayIcon(HWND hwnd,HICON hIcon,LPCWSTR pszDescription)=0;
	virtual HRESULT STDMETHODCALLTYPE SetThumbnailTooltip(HWND hwnd,LPCWSTR pszTip)=0;
	virtual HRESULT STDMETHODCALLTYPE SetThumbnailClip(HWND hwnd,RECT *prcClip)=0;
};

class CCallback : public IBindStatusCallback
{
private:
	int(*Callback)(int,int);
public:
	CCallback(int(*callback)(int,int)){Callback=callback;}
	STDMETHOD(OnStartBinding)(DWORD dwReserved,IBinding __RPC_FAR *pib){return E_NOTIMPL;}
	STDMETHOD(GetPriority)(LONG __RPC_FAR *pnPriority){return E_NOTIMPL;}
	STDMETHOD(OnLowResource)(DWORD reserved){return E_NOTIMPL;}
	STDMETHOD(OnProgress)(ULONG ulProgress,ULONG ulProgressMax,ULONG ulStatusCode,LPCWSTR wszStatusText){return Callback(ulProgress,ulProgressMax);}
	STDMETHOD(OnStopBinding)(HRESULT hresult,LPCWSTR szError){return E_NOTIMPL;}
	STDMETHOD(GetBindInfo)(DWORD __RPC_FAR *grfBINDF,BINDINFO __RPC_FAR *pbindinfo){return E_NOTIMPL;}
	STDMETHOD(OnDataAvailable)(DWORD grfBSCF,DWORD dwSize,FORMATETC __RPC_FAR *pformatetc,STGMEDIUM __RPC_FAR *pstgmed){return E_NOTIMPL;}
	STDMETHOD(OnObjectAvailable)(REFIID riid,IUnknown __RPC_FAR *punk){return E_NOTIMPL;}
	STDMETHOD_(ULONG,AddRef)(){return 0;}
	STDMETHOD_(ULONG,Release)(){return 0;}
	STDMETHOD(QueryInterface)(REFIID riid,void __RPC_FAR *__RPC_FAR *ppvObject){return E_NOTIMPL;}
};

#endif // __KENNYC_H__