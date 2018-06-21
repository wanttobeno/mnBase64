//
//  main.cpp
//  mnBase64
//
//  Created by Hi on 2018/6/21.
//  Copyright © 2018年 Hi. All rights reserved.
//

#include <iostream>

#include "myConvert.h"
#include "garbage.h"
#include "mnBase64.h"

#include <assert.h>


int base64Test1(){
    char cText[]="A Ansistring with special characters ¾½¼™Þ‰Æ€#èüä$!$£{°§1*-+±'?Øø}[»²³$£/&%ç¬›|‹¢@©®÷«]. ";
    wchar_t wcText[]=L"A Widestring with special characters 日本人, ไทย, Український, עברית, العربية, भारतीय,فارسی, русский, සිංහල, தமிழ். ";
    
    std::wstring ws;
    std::string s;
    for(int i=0;i<60;i++){
        ws+=wcText;
        s+=cText;
    }
    
    wchar_t *bufferW1=0,**pOutW1=&bufferW1;
    wchar_t *bufferW2=0,**pOutW2=&bufferW2;
    int iEncW=b64EncryptW(ws.c_str(),ws.length(),pOutW1,true);
    int iDecW=b64DecryptW(*pOutW1,iEncW,pOutW2,true);
    std::wstring wcDec(*pOutW2),wcEnc(*pOutW1);
    int nResutl = memcmp(ws.c_str(), bufferW2, ws.length());
    assert(nResutl == 0);
    
    
    
    
    char *bufferA1=0,**pOutA1=&bufferA1;
    char *bufferA2=0,**pOutA2=&bufferA2;
    int iEncA=b64EncryptA(s.c_str(),s.length(),pOutA1);
    int iDecA=b64DecryptA(*pOutA1,iEncA,pOutA2);
    std::string cDec(*pOutA2),cEnc(*pOutA1);
    int nResut2 = memcmp(s.c_str(), bufferA2, s.length());
    assert(nResut2 == 0);
    
    wchar_t *bufferW3=0,**pOutW3=&bufferW3;
    wchar_t *bufferW4=0,**pOutW4=&bufferW4;
    int iEncW2=b64EncryptW(ws.c_str(),ws.length(),pOutW3,true);
    int iDecW2=b64DecryptW(*pOutW3,iEncW2,pOutW4,true);
    std::wstring wcDec2(*pOutW4),wcEnc2(*pOutW3);
    int nResut3 = memcmp(ws.c_str(), bufferW4, ws.length());
    assert(nResut3 == 0);
    
    
    
    char *bufferA3=0,**pOutA3=&bufferA3;
    char *bufferA4=0,**pOutA4=&bufferA4;
    int iEncA2=b64EncryptA(s.c_str(),s.length(),pOutA3);
    int iDecA2=b64DecryptA(*pOutA3,iEncA2,pOutA4);
    std::string cDec2(*pOutA4),cEnc2(*pOutA3);
    int nResut4 = memcmp(s.c_str(), bufferA4, s.length());
    assert(nResut3 == 0);
    
    return 0;
}



int main(int argc, const char * argv[]) {
    // insert code here...
   
    char* szBuf = "abc中文123";
    myConvert convert;
    int nLen = strlen(szBuf);
    const wchar_t* ppOut;
    convert.ToUtf16(szBuf, nLen, &ppOut);
    
    // 转换结果失败！ "abc-\x87123"
    int nwLen = wcslen(ppOut);
    const char* pszBuf;
    convert.WString2String(ppOut, nwLen, &pszBuf);
    
    // 转换正常 abc中文123
    const char* pszUtf8;
    convert.ToUtf8(ppOut, nwLen, &pszUtf8);
    // 释放申请的内存
    Garbage::close();
    
    // base64 加解密测试
    base64Test1();
    // 释放申请的内存
    Garbage::close();
    return 0;
}
