#include "demo/UserPhoto.h"

UserPhoto::UserPhoto(const char* filename,TApplication* app,const char* n, TWidget* obj)
	:TWindow(filename,app,n,obj)
{
    close_btn = new TPushButton(650,70,new TImage("1:/tgui_pic/check2_sel.png"),NULL,NULL, this);
    left_btn = new TPushButton(100,400,new TImage("1:/tgui_pic/button.png"),new TImage("1:/tgui_pic/button_sel.png"),"上一个", this);
    right_btn = new TPushButton(600,400,new TImage("1:/tgui_pic/button.png"),new TImage("1:/tgui_pic/button_sel.png"),"下一个", this);
	

    close_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserPhoto::closePhoto));
    left_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserPhoto::prevPhoto));
    right_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserPhoto::nextPhoto));


    picIndex = 0;
    finfo.lfname = lfnamebuff;
    finfo.lfsize = sizeof(lfnamebuff);
    scanfile("1:/picture");
    
 							    
}

UserPhoto::~UserPhoto()
{

}

void UserPhoto::nextPhoto() 
{
    TImageBox(0,0,(uint16)GUI_WIDTH,(uint16)GUI_HIGH,(const char* )fileName[picIndex],NULL,this,false);
    picIndex ++;
    if(picIndex >= fileNum)
        picIndex = 0;
}

void UserPhoto::prevPhoto()
{
    TImageBox(0,0,(uint16)GUI_WIDTH,(uint16)GUI_HIGH,(const char* )fileName[picIndex],NULL,this,false);
    picIndex --;
    if(picIndex < 0)
        picIndex = fileNum - 1;
}

void UserPhoto::closePhoto()
{
    slot_close();
}



void UserPhoto::scanfile(const char* path)
{
    DIR dirs;
    char curdirpath[_MAX_LFN],nextdirpath[_MAX_LFN];
    if (f_opendir(&dirs, path) == FR_OK) 
    {
        while (f_readdir(&dirs, &finfo) == FR_OK) 
        {
            if(!finfo.fname[0]) 
                break;
            if(finfo.fname[0]=='.' || (finfo.fname[0]=='.' && finfo.fname[1]=='.'))
                continue;
            
            
            if(fileNum<32)
            strcpy((char*)fileName[fileNum],path);
            strcat((char*)fileName[fileNum],"/");
            strcat((char*)fileName[fileNum++],(*finfo.lfname ? finfo.lfname : finfo.fname));
           //strncpy( ,(*finfo.lfname ? finfo.lfname : finfo.fname),32);
            f_getcwd(curdirpath,_MAX_LFN);
            if((finfo.fattrib&AM_DIR) == AM_DIR)
            {			
                f_getcwd(curdirpath,_MAX_LFN);
                strcpy(nextdirpath, curdirpath);
                strcat(nextdirpath,"/");
                strncat(nextdirpath, *finfo.lfname ? finfo.lfname : finfo.fname, 32);	
                
                f_chdir(nextdirpath);
                scanfile(nextdirpath);
                
                f_chdir(curdirpath);
            }
        }
    }
}



void UserPhoto::show()
{
	refresh();
}


