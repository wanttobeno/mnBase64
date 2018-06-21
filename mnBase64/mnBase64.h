/*
 * Copyright � exc-jdbi 2016
 *
 * � mnBase64 2016
 *
 * mnBase64 - www.github.com/exc-jdbi/base64
 *
 * mnBase64 is Free and Opensource Software
*/

#pragma once
#ifndef __MY_BASE64_DLL_H__
#define __MY_BASE64_DLL_H__

#ifdef WINNT
#define EXP32  extern "C" __declspec(dllexport)
#else
#define EXP32
#define _stdcall
#endif

//Widestrings
EXP32 int b64_EncryptW(const wchar_t *const plain,const int iLen,wchar_t **ppOut,bool _utf8=true);
EXP32 int _stdcall b64EncryptW(const wchar_t *const plain,const int iLen,wchar_t **ppOut,bool _utf8=true);

EXP32 int b64_DecryptW(const wchar_t *const cipher,const int iLen,wchar_t **ppOut,bool _utf8=true);
EXP32 int _stdcall b64DecryptW(const wchar_t *const cipher,const int iLen,wchar_t **ppOut,bool _utf8=true);

//Ansistrings
EXP32 int b64_EncryptA(const char *const plain,const int iLen,char **ppOut);
EXP32 int _stdcall b64EncryptA(const char *const plain,const int iLen,char **ppOut);

EXP32 int b64_DecryptA(const char *const cipher,const int iLen,char **ppOut);
EXP32 int _stdcall b64DecryptA(const char *const cipher,const int iLen,char **ppOut);

//Garbage
EXP32 bool start_Garbage();
EXP32 bool _stdcall startGarbage();

EXP32 bool close_Garbage();
EXP32 bool _stdcall closeGarbage();
#endif
