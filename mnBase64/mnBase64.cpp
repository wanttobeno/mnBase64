/*
 * Copyright © exc-jdbi 2016
 *
 * © mnBase64 2016
 *
 * mnBase64 - www.github.com/exc-jdbi/base64
 *
 * mnBase64 is Free and Opensource Software
*/

#include <vector>
#include <iostream>
#ifdef WINNNT
#include <Windows.h>
#endif


#include "garbage.h"
#include "myConvert.h"
#include "mnBase64.h"

#define rbyte(addr) (*(const unsigned char*)(addr))

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

inline void x2y(unsigned char *cX, unsigned char * cY) {
	cY[0]=(cX[0]&0xfc)>>2;
	cY[1]=((cX[0]&0x03)<<4)+((cX[1]&0xf0)>>4);
	cY[2]=((cX[1]&0x0f)<<2)+((cX[2]&0xc0)>>6);
	cY[3]=(cX[2]&0x3f);
};

inline void y2x(unsigned char *cY, unsigned char *cX) {
	cX[0]=(cY[0]<<2)+((cY[1]&0x30)>>4);
	cX[1]=((cY[1]&0xf)<<4)+((cY[2]&0x3c)>>2);
	cX[2]=((cY[2]&0x3)<<6)+cY[3];
};

inline unsigned char b64Lookup(char c) {
	if(c>=65&&c<=90)return c-65;
	if(c>=97&&c<=122)return c-71;
	if(c>=48&&c<=57)return c+4;
	if(c==43)return 62;
	if(c==47)return 63;
	return -1;
};

const char b64AlphaNummeric[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
								"abcdefghijklmnopqrstuvwxyz"
								"0123456789+/";

class myBase64{
private:
	myBase64(const myBase64 &obj);
#ifdef WINNT
	myBase64& operator=(const myBase64&){}
#endif //
private:
	int pEnc(const char *const plain,const int &iLen,const char **ppOut);
	int pDec(const char *const cipher,const int &iLen,const char **ppOut);

	int pEncrypt(const wchar_t *const plain,const int &iLen,const wchar_t **ppOut,const bool _utf8=true);
	int pDecrypt(const wchar_t *const cipher,const int &iLen,const wchar_t **ppOut,const bool _utf8=true);
	
	int pEncrypt(const char *const plain,const int &iLen,const char **ppOut);
	int pDecrypt(const char *const cipher,const int &iLen,const char **ppOut);
public:
	myBase64();
	~myBase64();
public:
	int Encrypt(const wchar_t *const plain,const int &iLen,const wchar_t **ppOut,const bool _utf8=true);
	int Decrypt(const wchar_t *const cipher,const int &iLen,const wchar_t **ppOut,const bool _utf8=true);

	int Encrypt(const char *const plain,const int &iLen,const char **ppOut);
	int Decrypt(const char *const cipher,const int &iLen,const char **ppOut);
};


/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */

myBase64::myBase64(){}
myBase64::~myBase64(){}
myBase64::myBase64(const myBase64 &obj){}
int myBase64::pEnc(const char *const plain,const int &iLen,const char **ppOut){
	int ret=-1;
	try{
		if((checkLen(plain,iLen))&&(ppOut)){						
			int i=0,j=0,offset=0;			
			unsigned char x[3]={0},y[4]={0};
			int iB64Len=((iLen+2-((iLen+2)%3))*2);

			char *pOut=new char[iB64Len];
			memset(pOut,0,iB64Len);
			Garbage::setNews(pOut);

			for(int ii=0;ii<iLen;ii++){
				x[i++]=plain[ii];
				if(i>=3){
					x2y(x,y);
					for(int jj=0;jj<4;jj++){
						pOut[offset++]=rbyte(&b64AlphaNummeric[y[jj]]);
					}
					i=0;
				}
			}
			if(i){
				for(j=i;j<3;j++){
					x[j]=0;
				}
			}
			x2y(x,y);
			for(j=0;j<i+1;j++){
				pOut[offset++]=rbyte(&b64AlphaNummeric[y[j]]);
			}
			while((i++<3)){
				pOut[offset++]=61;
			}
			pOut[offset]=0;
			if(std::strlen(pOut)>0){
				int iCorrectLen=((iLen+2-((iLen+2)%3))/3)*4;
				memset(&pOut[iCorrectLen],0,iB64Len-iCorrectLen);
				*ppOut=pOut;
				ret=iCorrectLen;
			}			
		}
		return ret;
		}
	catch(std::exception &ex){
		std::cout<<"pEnc::pDecrypt: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myBase64::pDec(const char *const cipher,const int &iLen,const char **ppOut){
	int ret=-1;
	try{
		if((checkLen(cipher,iLen))&&(ppOut)){
			int i=0,j=0,offset=0;			
			unsigned char x[3]={0},y[4]={0};
			int iPlainLen=iLen*3/2;

			char *pOut=new char[iPlainLen];
			memset(pOut,0,iPlainLen);	
			Garbage::setNews(pOut);

			for(int ii=0;ii<iLen;ii++){
				if(cipher[ii]==61)break;

				y[i++]=cipher[ii];
				if(i>=4){
					for(int jj=0;jj<4;jj++){
						y[jj]=b64Lookup(y[jj]);
					}
					y2x(y,x);
					for(int jj=0;jj<3;jj++){
						pOut[offset++]=x[jj];
					}
					i=0;
				}
			}
			if(i){
				for(j=i;j<4;j++){
					y[j]=0;
				}
				for(j=0;j<4;j++){
					y[j]=b64Lookup(y[j]);
				}
				y2x(y,x);
				for (j=0;j<i-1;j++){
					pOut[offset++]=x[j];
				}
			}
			pOut[offset]=0;
			if(std::strlen(pOut)){
				*ppOut=pOut;
				ret=offset;
			}
		}
		return ret;
		}
	catch(std::exception &ex){
		std::cout<<"pDec::pDecrypt: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myBase64::pEncrypt(const wchar_t *const plain,const int &iLen,const wchar_t **ppOut,const bool _utf8){
	int ret=-1;
	try{
		if((checkLen(plain,iLen))&&(ppOut)){
			int iL=0;
			myConvert con;
			
			const char *buffer1=0,**pConvert=&buffer1;
			if(!_utf8){
				iL=con.WString2String(plain,iLen,pConvert);
			}else{
				iL=con.ToUtf8(plain,iLen,pConvert);
			}
			if(iL>0){
				const char *buffer2=0,**pB64=&buffer2;
				int iB64=pEnc(*pConvert,iL,pB64);
				if(iB64){
					const wchar_t *buffer3=0,**pOut=&buffer3;
					int iConv=con.String2WString(*pB64,iB64,pOut);
					if(iConv){
						*ppOut=*pOut;
						ret=iConv;
					}
				}
			}	
		}		
		return ret;
		}
	catch(std::exception &ex){
		std::cout<<"myBase64_Unicode::pEncrypt: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myBase64::pDecrypt(const wchar_t *const cipher,const int &iLen,const wchar_t **ppOut,const bool _utf8){
	int ret=-1;
	try{
		if((checkLen(cipher,iLen))&&(ppOut)){
			int iL=0;
			myConvert con;

			const char *buffer1=0,**pConvert=&buffer1;
			iL=con.WString2String(cipher,iLen,pConvert);
			if(iL>0){
				const char *buffer2=0,**pCipher=&buffer2;
				int iCipher=pDec(*pConvert,iL,pCipher);
				if(iCipher){
					int iR=0;
					const wchar_t *buffer3=0,**pPlain=&buffer3;
					if(!_utf8){
						iR=con.String2WString(*pCipher,iCipher,pPlain);
					}else{
						iR=con.ToUtf16(*pCipher,iCipher,pPlain);
					}
					if(iR>0){
						*ppOut=*pPlain;
						ret=iR;
					}
				}
			}
			return ret;
		}
		return ret;
		}
	catch(std::exception &ex){
		std::cout<<"myBase64_Unicode::pDecrypt: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myBase64::pEncrypt(const char *const plain,const int &iLen,const char **ppOut){
	int ret=-1;
	try{
		if((checkLen(plain,iLen))&&(ppOut)){
			const char *buffer1=0,**pB64=&buffer1;
			int iB64=pEnc(plain,iLen,pB64);
			if(iB64>0){
				*ppOut=*pB64;
				ret=iB64;
			}
		}
		return ret;
		}
	catch(std::exception &ex){
		std::cout<<"myBase64_Ansi::pEncrypt: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myBase64::pDecrypt(const char *const cipher,const int &iLen,const char **ppOut){
	int ret=-1;
	try{
		if((checkLen(cipher,iLen))&&(ppOut)){			
			const char *buffer1=0,**pDecipher=&buffer1;
			int iDec=pDec(cipher,iLen,pDecipher);
			if(iDec>0){
				*ppOut=*pDecipher;
				ret=iDec;
			}
		}
		return ret;
		}
	catch(std::exception &ex){
		std::cout<<"myBase64_Ansi::pDecrypt: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myBase64::Encrypt(const wchar_t *const plain,const int &iLen,const wchar_t **ppOut,const bool _utf8){
	return pEncrypt(plain,iLen,ppOut,_utf8);
}
int myBase64::Decrypt(const wchar_t *const cipher,const int &iLen,const wchar_t **ppOut,const bool _utf8){
	return pDecrypt(cipher,iLen,ppOut,_utf8);
}
int myBase64::Encrypt(const char *const plain,const int &iLen,const char **ppOut){
	return pEncrypt(plain,iLen,ppOut);
}
int myBase64::Decrypt(const char *const cipher,const int &iLen,const char **ppOut){
	return pDecrypt(cipher,iLen,ppOut);
}
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
int b64_EncryptW(const wchar_t *const plain,const int iLen,wchar_t **ppOut,bool _utf8){
	return b64EncryptW(plain,iLen,ppOut,_utf8);
}
int _stdcall b64EncryptW(const wchar_t *const plain,const int iLen,wchar_t **ppOut,bool _utf8){
	myBase64 b64;
	return b64.Encrypt(plain,iLen,(const wchar_t**)ppOut,_utf8);
}
int b64_DecryptW(const wchar_t *const cipher,const int iLen,wchar_t **ppOut,bool _utf8){
	return b64DecryptW(cipher,iLen,ppOut,_utf8);
}
int _stdcall b64DecryptW(const wchar_t *const cipher,const int iLen,wchar_t **ppOut,bool _utf8){
	myBase64 b64;
	return b64.Decrypt(cipher,iLen,(const wchar_t**)ppOut,_utf8);
}
int b64_EncryptA(const char *const plain,const int iLen,char **ppOut){
	return b64EncryptA(plain,iLen,ppOut);
}
int _stdcall b64EncryptA(const char *const plain,const int iLen,char **ppOut){
	myBase64 b64;
	return b64.Encrypt(plain,iLen,(const char**)ppOut);
}
int b64_DecryptA(const char *const cipher,const int iLen,char **ppOut){
	return b64DecryptA(cipher,iLen,ppOut);
}
int _stdcall b64DecryptA(const char *const cipher,const int iLen,char **ppOut){
	myBase64 b64;
	return b64.Decrypt(cipher,iLen,(const char**)ppOut);
}
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
