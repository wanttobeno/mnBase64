//
//  myConvert.cpp
//  mnBase64
//
//  Created by Hi on 2018/6/21.
//  Copyright © 2018年 Hi. All rights reserved.
//

#include "myConvert.h"
#include <iostream>
#include "garbage.h"


inline bool checkLen(char const *ch,int const &iLen){
    if((ch)&&(iLen>0)){if(iLen<=(int)std::strlen(ch))return true;}
    return false;
}

inline bool checkLen(unsigned int const &x,unsigned int const &y,unsigned int const &z){
    if (x+y>=z)return false;
    return true;
}

inline bool checkLen(wchar_t const *wch,int const &iLen){
    if((wch) && (iLen>0)){if(iLen<=(int)std::wcslen(wch))return true;}
    return false;
}

inline bool isBase64(unsigned char c) {
    return (isalnum(c)||(c==43)||(c==47));
};

myConvert::myConvert()
{
}

myConvert::~myConvert()
{
}

//myConvert::myConvert(const myConvert &obj)
//{
//}

//myConvert::myConvert(const myConvert &obj){}

int myConvert::pUtf8ToUnicode(const char *const cUtf8,const int &iLen,const wchar_t **ppOut){
    int ret=-1;
    try{
        if(checkLen(cUtf8,iLen)&&(ppOut)){
            unsigned char ch=0;
            unsigned int offset=0,ui=0;
            
            wchar_t *pOut=new wchar_t[iLen+20];
            wmemset(pOut,0,iLen+20);
            Garbage::setNews(pOut);
            
            for(int i=0;i<iLen;i++){
                ch=(unsigned int)cUtf8[i+offset];
                if(ch<0xC0){
                    ui=cUtf8[i+offset];
                }else if(ch<0xE0){
                    if(!checkLen(i,offset,iLen))return false;
                    ui=(cUtf8[i+offset++]&0x1f)<<6;
                    ui|=(cUtf8[i+offset]&0x3f);
                }else if(ch<0xF0){
                    if(!checkLen(i,offset,iLen))return false;
                    ui=(cUtf8[i+offset++]&0x0f)<<12;
                    ui|=(cUtf8[i+offset++]&0x3f)<<6;
                    ui|=(cUtf8[i+offset]& 0x3f);
                }else if(ch<0xF8){
                    if(!checkLen(i,offset,iLen))return false;
                    ui=(cUtf8[i+offset++]&0x07)<<18;
                    ui|=(cUtf8[i+offset++]&0x3f)<<12;
                    ui|=(cUtf8[i+offset++]&0x3f)<<6;
                    ui|=(cUtf8[i+offset]&0x3f);
                }else if(ch<0xFC){
                    if(!checkLen(i,offset,iLen))return false;
                    ui=(cUtf8[i+offset++]&0x03)<<24;
                    ui|=(cUtf8[i+offset++]&0x3f)<<18;
                    ui|=(cUtf8[i+offset++]&0x3f)<<12;
                    ui|=(cUtf8[i+offset++]&0x3f)<<6;
                    ui|=(cUtf8[i+offset]&0x3f);
                }else {
                    if(!checkLen(i,offset,iLen))return false;
                    ui= (cUtf8[i+offset++]&0x01)<<30;
                    ui|=(cUtf8[i+offset++]&0x3f)<<24;
                    ui|=(cUtf8[i+offset++]&0x3f)<<18;
                    ui|=(cUtf8[i+offset++]&0x3f)<<12;
                    ui|=(cUtf8[i+offset++]&0x3f)<<6;
                    ui|=(cUtf8[i+offset]&0x3f);
                }
                pOut[i]=ui;
            }
            if(std::wcslen(pOut)>0){
                *ppOut=pOut;
                ret=std::wcslen(pOut);
            }
        }
        return ret;
    }
    catch(std::exception &ex){
        std::cout<<"pConvert::pUtf8ToUnicode: "<<ex.what()<<std::endl;
        return ret;
    }
}

int myConvert::pUnicodeToUtf8(const std::vector<unsigned int> &vuiUnicode,const char **ppOut){
    int ret=-1;
    try{
        if((vuiUnicode.size()>0)&&(ppOut)){
            unsigned int offset=0,uni=0;
            
            char *pOut=new char[vuiUnicode.size()*5];
            memset(pOut,0,vuiUnicode.size()*5);
            Garbage::setNews(pOut);
            
            for(unsigned int i=0;i<vuiUnicode.size();i++){
                uni=vuiUnicode[i];
                if (uni<0x80) {
                    pOut[i+offset]=uni;
                }else if(uni<0x800){
                    pOut[i+offset++]=(((uni>>6)&0x1f)|0xc0);
                    pOut[i+offset]=((uni&0x3f)|0x80);
                }else if(uni<0x10000){
                    pOut[i+offset++]=(((uni>>12)&0x0f)|0xe0);
                    pOut[i+offset++]=(((uni>>6)&0x3f)|0x80);
                    pOut[i+offset]=((uni&0x3f)|0x80);
                }else if(uni<0x200000){
                    pOut[i+offset++]=(((uni>>18)&0x07)|0xf0);
                    pOut[i+offset++]=(((uni>>12)&0x3f)|0x80);
                    pOut[i+offset++]=(((uni>>6)&0x3f)|0x80);
                    pOut[i+offset]=((uni&0x3f)|0x80);
                }else if(uni<0x4000000) {
                    pOut[i+offset++]=(((uni>>24)& 0x03)|0xf8);
                    pOut[i+offset++]=(((uni>>18)& 0x3f)|0x80);
                    pOut[i+offset++]=(((uni>>12)& 0x3f)|0x80);
                    pOut[i+offset++]=(((uni>>6)& 0x3f)|0x80);
                    pOut[i+offset]=((uni&0x3f)|0x80);
                }else {
                    pOut[i+offset++]=(((uni>>30)&0x01)|0xfc);
                    pOut[i+offset++]=(((uni>>24)&0x3f)|0x80);
                    pOut[i+offset++]=(((uni>>18)&0x3f)|0x80);
                    pOut[i+offset++]=(((uni>>12)&0x3f)|0x80);
                    pOut[i+offset++]=(((uni>>6) &0x3f)|0x80);
                    pOut[i+offset]=((uni&0x3f)|0x80);
                }
            }
            *ppOut=pOut;
            ret=vuiUnicode.size()+offset;
        }
        return ret;
    }
    catch(std::exception &ex){
        std::cout<<"pConvert::pUnicodeToUtf8: "<<ex.what()<<std::endl;
        return ret;
    }
}

int myConvert::pToUtf8(const wchar_t *const wsStr,const int &iLen,const char **ppOut){
    int ret=-1;
    try{
        if((checkLen(wsStr,iLen))&&(ppOut)){
            std::vector<unsigned int>vuiUnicode(iLen);
            for(int i=0;i<iLen;i++){
                vuiUnicode[i]=wsStr[i];
            }
            const char *buffer=0,**pOut=&buffer;
            int iL=pUnicodeToUtf8(vuiUnicode,pOut);
            if(iL>0){
                *ppOut=*pOut;
                ret=iL;
            }
        }
        return ret;
    }
    catch(std::exception &ex){
        std::cout<<"pConvert::pToUtf8: "<<ex.what()<<std::endl;
        return ret;
    }
}

int myConvert::pToUtf16(const char *const cStr,const int &iLen,const wchar_t **ppOut){
    int ret=-1;
    try{
        if((checkLen(cStr,iLen))&&(ppOut)){
            std::vector<unsigned int>vuiUnicode(iLen);
            const wchar_t *buffer=0,**pOut=&buffer;
            int iL=pUtf8ToUnicode(cStr,iLen,pOut);
            if(iL>0){
                *ppOut=*pOut;
                ret=iL;
            }
        }
        return ret;
    }
    catch(std::exception &ex){
        std::cout<<"pConvert::pToUtf16: "<<ex.what()<<std::endl;
        return ret;
    }
}

int myConvert::pWString2String(const wchar_t *const wcStr,const int &iLen,const char **ppOut){
    int ret=-1;
    try{
        if((checkLen(wcStr,iLen))&&(ppOut)){
            std::vector<unsigned int>vuiUnicode(iLen);
            for(int i=0;i<iLen;i++){
                vuiUnicode[i]=wcStr[i];
            }
            char *pOut=new char[vuiUnicode.size()+1];
            memset(pOut,0,vuiUnicode.size()+1);
            Garbage::setNews(pOut);
            
            for(unsigned int i=0;i<vuiUnicode.size();i++){
                pOut[i]=vuiUnicode[i];
            }
            if(vuiUnicode.size()>0){
                *ppOut=pOut;
                ret=vuiUnicode.size();
            }
        }
        return ret;
    }
    catch(std::exception &ex){
        std::cout<<"pConvert::pWString2String: "<<ex.what()<<std::endl;
        return ret;
    }
}
int myConvert::pString2WString(const char *const cStr,const int &iLen,const wchar_t **ppOut){
    int ret=-1;
    try{
        if((checkLen(cStr,iLen))&&(ppOut)){
            unsigned char uChar=0;
            std::vector<unsigned int>vuiUnicode(iLen);
            for(int i=0;i<iLen;i++){
                uChar=cStr[i];
                vuiUnicode[i]=(unsigned int)uChar;
            }
            wchar_t *pOut=new wchar_t[vuiUnicode.size()+1];
            wmemset(pOut,0,vuiUnicode.size()+1);
            Garbage::setNews(pOut);
            
            for(unsigned int i=0;i<vuiUnicode.size();i++){
                pOut[i]=vuiUnicode[i];
            }
            if(vuiUnicode.size()>0){
                *ppOut=pOut;
                ret=vuiUnicode.size();
            }
        }
        return ret;
    }
    catch(std::exception &ex){
        std::cout<<"pConvert::pString2WString: "<<ex.what()<<std::endl;
        return ret;
    }
}
int myConvert::ToUtf8(const wchar_t *const buffer,const int &iLen,const char **ppOut){
    return pToUtf8(buffer,iLen,ppOut);
}
int myConvert::ToUtf16(const char *const buffer,const int &iLen,const wchar_t **ppOut){
    return pToUtf16(buffer,iLen,ppOut);
}
int myConvert::WString2String(const wchar_t *const ws,const int &iLen,const char **ppOut){
    return pWString2String(ws,iLen,ppOut);
}
int myConvert::String2WString(const char *const c,const int &iLen,const wchar_t **ppOut){
    return pString2WString(c,iLen,ppOut);
}
