

mac 下的iconv按照网上的例子不成功，一定是哪里调用错了。


为了解决 mac OX 开发下 ansi 和 Unicode 编码的转换问题，
搜到的一个 [github](www.github.com/exc-jdbi/base64)。

测试可以解决问题。

为什么需要转码，因为base64是针对ansi加解密的，unicode编码必须转换。

跨平台支持，C#版本和VB版本，[点击这里](www.github.com/exc-jdbi/base64)


```c

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

```












