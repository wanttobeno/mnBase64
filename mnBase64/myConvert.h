//
//  myConvert.hpp
//  mnBase64
//
//  Created by Hi on 2018/6/21.
//  Copyright © 2018年 Hi. All rights reserved.
//

#ifndef myConvert_hpp
#define myConvert_hpp

#include <stdio.h>
#include <vector>


class myConvert{
public:
    myConvert();
    ~myConvert();
private:
//    myConvert(const myConvert &obj);
#ifdef WINNT
    myConvert& operator=(const myConvert& data){}
#endif
private:
    int pUtf8ToUnicode(const char *const cUtf8,const int &iLen,const wchar_t **ppOut);
    int pUnicodeToUtf8(const std::vector<unsigned int> &vuiUnicode,const char **ppOut);
    
    int pToUtf8(const wchar_t *const buffer,const int &iLen,const char **ppOut);
    int pToUtf16(const char *const buffer,const int &iLen,const wchar_t **ppOut);
    
    int pWString2String(const wchar_t *const wcStr,const int &iLen,const char **ppOut);
    int pString2WString(const char *const cStr,const int &iLen,const wchar_t **ppOut);

public:
    int ToUtf8(const wchar_t *const buffer,const int &iLen,const char **ppOut);
    int ToUtf16(const char *const buffer,const int &iLen,const wchar_t **ppOut);
    
    int WString2String(const wchar_t *const ws,const int &iLen,const char **ppOut);
    int String2WString(const char *const c,const int &iLen,const wchar_t **ppOut);
};




#endif /* myConvert_hpp */
