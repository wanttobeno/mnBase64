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
//#include <process.h>

#include "garbage.h"

namespace Garbage{
	class myGarbage{
	private:
		int iSize;
		std::vector<char*>vChar;
		std::vector<wchar_t*>vwChar;
	private:
		~myGarbage(){}		
		myGarbage(const myGarbage&){}
		//myGarbage& operator=(const myGarbage&){}
	private:
		static myGarbage *singleInstance;
	public:
		myGarbage();
	public:
		int getSize();
		bool setNew(char *c);
		bool setNew(wchar_t *wc);
		bool DeleteNews();
	public:
		inline bool destroyInstance();
		inline static myGarbage &getInstance();
	};
	myGarbage::myGarbage(){
		vChar.assign(0,0);
		vwChar.assign(0,0);
		iSize=0;
	}
	myGarbage* myGarbage::singleInstance=0;

	myGarbage& myGarbage::getInstance(){
		if(singleInstance==0)
			singleInstance=new myGarbage;
		return *singleInstance;
	}
	bool myGarbage::destroyInstance(){
		if (singleInstance!=0)
			delete singleInstance;
		singleInstance=0;
		if(singleInstance==0)return true;
		return false;
	}
	int myGarbage::getSize(){return iSize;}
	bool myGarbage::setNew(char *c){
		if(c){
			vChar.resize(vChar.size()+1);
			vChar[vChar.size()-1]=c;
			iSize++;
			return true;
		}
		return false;
	}
	bool myGarbage::setNew(wchar_t *wc){
		if(wc){
			vwChar.resize(vwChar.size()+1);
			vwChar[vwChar.size()-1]=wc;
			iSize++;
			return true;
		}
		return false;
	}
	bool myGarbage::DeleteNews(){
		if(vChar.size()>0){
			char *ptr=0;
			for(int i=0;vChar.size()>0;i++){
				ptr=(char*)vChar[vChar.size()-1];
				if(ptr){
					std::cout<<(void*)&(*vChar[vChar.size()-1])<<" delete ..."<<std::endl;
					try{
						delete [] ptr;ptr=0;
						vChar[vChar.size()-1]=0;
					}catch(std::exception &ex){
						std::cout<<"myGarbage::DeleteNews: "<<ex.what()<<std::endl;						
					}
				}
				vChar.resize(vChar.size()-1);
				iSize--;
			}
		}
		if(vwChar.size()>0){
			wchar_t *ptr=0;
			for(int i=0;vwChar.size()>0;i++){
				ptr=(wchar_t*)vwChar[vwChar.size()-1];
				if(ptr){
					std::cout<<(void*)&(*vwChar[vwChar.size()-1])<<" delete ..."<<std::endl;
					try{
						delete [] ptr;ptr=0;
						vwChar[vwChar.size()-1]=0;
					}catch(std::exception &ex){
						std::cout<<"myGarbage::DeleteNews: "<<ex.what()<<std::endl;						
					}
				}
				vwChar.resize(vwChar.size()-1);
				iSize--;
			}
		}
		return true;
	}
	
	bool start(){
		myGarbage &myG=myGarbage::getInstance();
		return true;
	}
	bool close(){
		bool ret=false;
		myGarbage &myG=myGarbage::getInstance();
		myG.DeleteNews();
		myG.destroyInstance();
		ret=true;
		return ret;
	}
	bool setNews(char *c){
		bool ret=false;		
		if(c){
			std::cout<<"SetNews "<<(void*)&(*c)<<std::endl;
			myGarbage &myG=myGarbage::getInstance();
			ret=myG.setNew(c);
		}
		return ret;
	}
	bool setNews(wchar_t *wc){
		bool ret=false;		
		if(wc){
			std::cout<<"SetNews "<<(void*)&(*wc)<<std::endl;
			myGarbage &myG=myGarbage::getInstance();
			ret=myG.setNew(wc);
		}
		return ret;
	}
}
