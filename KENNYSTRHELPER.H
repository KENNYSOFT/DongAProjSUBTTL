#ifndef __KENNYSTRHELPER_H__
#define __KENNYSTRHELPER_H__
#define VERSION_KENNYSTRHELPER "2.0.0"
#include<iostream>
using namespace std;
#include<string.h>
#include<windows.h>
wchar_t* ansi_to_unicode(const char *pszCode,wchar_t *pszOut)
{
	int nLength;
	nLength=MultiByteToWideChar(CP_ACP,0,pszCode,-1,NULL,NULL);
	MultiByteToWideChar(CP_ACP,0,pszCode,-1,pszOut,nLength);
	return pszOut;
}
wchar_t* ansi_to_unicode(const char *pszCode,wchar_t **pszOut)
{
	int nLength;
	nLength=MultiByteToWideChar(CP_ACP,0,pszCode,-1,NULL,NULL);
	*pszOut=SysAllocStringLen(NULL,nLength);
	ansi_to_unicode(pszCode,*pszOut);
	return *pszOut;
}
char* ansi_to_utf8(const char *pszCode,char *pszOut)
{
	int nLength;
	wchar_t *bstrWide;
	nLength=MultiByteToWideChar(CP_ACP,0,pszCode,-1,NULL,NULL);
	bstrWide=SysAllocStringLen(NULL,nLength);
	MultiByteToWideChar(CP_ACP,0,pszCode,-1,bstrWide,nLength);
	nLength=WideCharToMultiByte(CP_UTF8,0,bstrWide,-1,NULL,0,NULL,NULL);
	WideCharToMultiByte(CP_UTF8,0,bstrWide,-1,pszOut,nLength,NULL,NULL);
	SysFreeString(bstrWide);
	return pszOut;
}
char* ansi_to_utf8(const char *pszCode,char **pszOut)
{
	int nLength;
	wchar_t *bstrWide;
	nLength=MultiByteToWideChar(CP_ACP,0,pszCode,-1,NULL,NULL);
	bstrWide=SysAllocStringLen(NULL,nLength);
	MultiByteToWideChar(CP_ACP,0,pszCode,-1,bstrWide,nLength);
	nLength=WideCharToMultiByte(CP_UTF8,0,bstrWide,-1,NULL,0,NULL,NULL);
	*pszOut=(char*)malloc(nLength);
	ansi_to_utf8(pszCode,*pszOut);
	SysFreeString(bstrWide);
	return *pszOut;
}
char* unicode_to_ansi(const wchar_t *pszCode,char *pszOut)
{
	int nLength;
	nLength=WideCharToMultiByte(CP_ACP,0,pszCode,-1,NULL,0,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,pszCode,-1,pszOut,nLength,NULL,NULL);
	return pszOut;
}
char* unicode_to_ansi(const wchar_t *pszCode,char **pszOut)
{
	int nLength;
	nLength=WideCharToMultiByte(CP_ACP,0,pszCode,-1,NULL,0,NULL,NULL);
	*pszOut=(char*)malloc(nLength);
	unicode_to_ansi(pszCode,*pszOut);
	return *pszOut;
}
char* unicode_to_utf8(const wchar_t *pszCode,char *pszOut)
{
	int nLength;
	nLength=WideCharToMultiByte(CP_UTF8,0,pszCode,-1,NULL,0,NULL,NULL);
	WideCharToMultiByte(CP_UTF8,0,pszCode,-1,pszOut,nLength,NULL,NULL);
	return pszOut;
}
char* unicode_to_utf8(const wchar_t *pszCode,char **pszOut)
{
	int nLength;
	nLength=WideCharToMultiByte(CP_UTF8,0,pszCode,-1,NULL,0,NULL,NULL);
	*pszOut=(char*)malloc(nLength);
	unicode_to_utf8(pszCode,*pszOut);
	return *pszOut;
}
char* utf8_to_ansi(const char *pszCode,char *pszOut)
{
	int nLength;
	wchar_t *bstrWide;
	nLength=MultiByteToWideChar(CP_UTF8,0,pszCode,-1,NULL,NULL);
	bstrWide=SysAllocStringLen(NULL,nLength);
	MultiByteToWideChar(CP_UTF8,0,pszCode,-1,bstrWide,nLength);
	nLength=WideCharToMultiByte(CP_ACP,0,bstrWide,-1,NULL,0,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,bstrWide,-1,pszOut,nLength,NULL,NULL);
	SysFreeString(bstrWide);
	return pszOut;
}
char* utf8_to_ansi(const char *pszCode,char **pszOut)
{
	int nLength;
	wchar_t *bstrWide;
	nLength=MultiByteToWideChar(CP_UTF8,0,pszCode,-1,NULL,NULL);
	bstrWide=SysAllocStringLen(NULL,nLength);
	MultiByteToWideChar(CP_UTF8,0,pszCode,-1,bstrWide,nLength);
	nLength=WideCharToMultiByte(CP_ACP,0,bstrWide,-1,NULL,0,NULL,NULL);
	*pszOut=(char*)malloc(nLength);
	utf8_to_ansi(pszCode,*pszOut);
	SysFreeString(bstrWide);
	return *pszOut;
}
wchar_t* utf8_to_unicode(const char *pszCode,wchar_t *pszOut)
{
	int nLength;
	nLength=MultiByteToWideChar(CP_UTF8,0,pszCode,-1,NULL,NULL);
	MultiByteToWideChar(CP_UTF8,0,pszCode,-1,pszOut,nLength);
	return pszOut;
}
wchar_t* utf8_to_unicode(const char *pszCode,wchar_t **pszOut)
{
	int nLength;
	nLength=MultiByteToWideChar(CP_UTF8,0,pszCode,-1,NULL,NULL);
	*pszOut=SysAllocStringLen(NULL,nLength);
	utf8_to_unicode(pszCode,*pszOut);
	return *pszOut;
}
void strcpy(char *dest,const char *src,const char *until) // cf. sscanf(src,"%[^U]",dest);
{
	int i,ul=strlen(until);
	for(i=0;src[i];++i)
	{
		if(!strncmp(src+i,until,ul))
		{
			dest[i]=0;
			break;
		}
		dest[i]=src[i];
	}
}
char* strchg(char *dest,const char *from,const char *to,bool once=false)
{
	int i,dl=strlen(dest),fl=strlen(from),tl=strlen(to);
	char *ptr=dest;
	while(ptr=strstr(ptr,from))
	{
		memmove(ptr+tl,ptr+fl,dl-(ptr-dest)-fl+1);
		for(i=0;i<tl;++i)ptr[i]=to[i];
		dl=dl-fl+tl;
		ptr=ptr+tl;
		if(once)break;
	}
	return dest;
}
char* escape_windows(char *dest)
{
	int i,l=strlen(dest);
	char to[128][3]={0};
	to['\\'][0]=-95;
	to['\\'][1]=-84;
	to['/'][0]=-93;
	to['/'][1]=-81;
	to[':'][0]=-93;
	to[':'][1]=-70;
	to['*'][0]=-93;
	to['*'][1]=-86;
	to['?'][0]=-93;
	to['?'][1]=-65;
	to['\"'][0]=-93;
	to['\"'][1]=-94;
	to['<'][0]=-93;
	to['<'][1]=-68;
	to['>'][0]=-93;
	to['>'][1]=-66;
	to['|'][0]=-93;
	to['|'][1]=-4;
	for(i=0;i<l;++i)
	{
		if(dest[i]<0)
		{
			i++;
			continue;
		}
		if(to[dest[i]][0])
		{
			memmove(dest+i+2,dest+i+1,l-i);
			dest[i+1]=to[dest[i]][1];
			dest[i]=to[dest[i]][0];
			l++;
			i++;
		}
	}
	return dest;
}
char* unescape_html(char *dest,bool toUtf8=false)
{
	int i,dl=strlen(dest),fl,tl;
	wchar_t unicode[2]={0};
	char *ptr,entity[10],conv[10],from[10][10]={"&nbsp;","&quot;","&amp;","&lt;","&gt;"},to[10][10]={" ","\"","&","<",">"};
	ptr=dest;
	while(ptr=strstr(ptr,"&#x"))
	{
		strcpy(entity,ptr,";");
		fl=strlen(entity)+1;
		sscanf(entity+3,"%x",&unicode[0]);
		if(toUtf8)unicode_to_utf8(unicode,conv);
		else unicode_to_ansi(unicode,conv);
		tl=strlen(conv);
		memmove(ptr+tl,ptr+fl,dl-(ptr-dest)-fl+1);
		for(i=0;i<tl;++i)ptr[i]=conv[i];
		dl=dl-fl+tl;
		ptr=ptr+tl;
	}
	ptr=dest;
	while(ptr=strstr(ptr,"&#"))
	{
		strcpy(entity,ptr,";");
		fl=strlen(entity)+1;
		sscanf(entity+2,"%d",&unicode[0]);
		if(toUtf8)unicode_to_utf8(unicode,conv);
		else unicode_to_ansi(unicode,conv);
		tl=strlen(conv);
		memmove(ptr+tl,ptr+fl,dl-(ptr-dest)-fl+1);
		for(i=0;i<tl;++i)ptr[i]=conv[i];
		dl=dl-fl+tl;
		ptr=ptr+tl;
	}
	for(i=0;from[i][0];++i)strchg(dest,from[i],to[i]);
	return dest;
}
char* escape_url(char *dest)
{
	int i,l=strlen(dest),need[128]={0};
	char int2hex[17]="0123456789ABCDEF";
	need[' ']=1;
	need['\"']=1;
	need['#']=1;
	need['$']=1;
	need['%']=1;
	need['&']=1;
	need['\'']=1;
	need['+']=1;
	need[',']=1;
	need['/']=1;
	need[':']=1;
	need[';']=1;
	need['<']=1;
	need['=']=1;
	need['>']=1;
	need['?']=1;
	need['@']=1;
	need['[']=1;
	need['\\']=1;
	need[']']=1;
	need['^']=1;
	need['`']=1;
	need['{']=1;
	need['|']=1;
	need['}']=1;
	for(i=0;i<l;++i)
	{
		if(dest[i]<0||need[dest[i]])
		{
			memmove(dest+i+3,dest+i+1,l-i);
			int t=dest[i];
			if(t<0)t=t+256;
			dest[i]='%';
			dest[i+1]=int2hex[t/16];
			dest[i+2]=int2hex[t%16];
			l=l+2;
			i=i+2;
		}
	}
	return dest;
}
char* unescape_url(char *dest)
{
	int i,l=strlen(dest),hex2int[128];
	hex2int['0']=0;
	hex2int['1']=1;
	hex2int['2']=2;
	hex2int['3']=3;
	hex2int['4']=4;
	hex2int['5']=5;
	hex2int['6']=6;
	hex2int['7']=7;
	hex2int['8']=8;
	hex2int['9']=9;
	hex2int['a']=10;
	hex2int['b']=11;
	hex2int['c']=12;
	hex2int['d']=13;
	hex2int['e']=14;
	hex2int['f']=15;
	hex2int['A']=10;
	hex2int['B']=11;
	hex2int['C']=12;
	hex2int['D']=13;
	hex2int['E']=14;
	hex2int['F']=15;
	strchg(dest,"+"," ");
	for(i=0;i<l;++i)
	{
		if(dest[i]=='%'&&hex2int[dest[i+1]]>=0&&hex2int[dest[i+2]]>=0)
		{
			dest[i]=hex2int[dest[i+1]]*16+hex2int[dest[i+2]];
			memmove(dest+i+1,dest+i+3,strlen(dest)-i-2);
			l=l-2;
		}
	}
	return dest;
}
int getCount(const char *src,const char *str,bool duplicate=false)
{
	int i,sl=strlen(src),tl=strlen(str),ret=0;
	for(i=0;i<sl;++i)
	{
		if(!strncmp(src+i,str,tl))
		{
			ret++;
			if(!duplicate)i=i+tl-1;
		}
	}
	return ret;
}
int lastIndexOf(const char *src,const char *str)
{
	int sl=strlen(str);
	const char *t=src,*tt;
	while(tt=strstr(t,str))t=tt+sl;
	return t-sl-src;
}
#endif