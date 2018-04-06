#include "demo/UserPhoto.h"

UserPhoto::UserPhoto(const char* filename,TApplication* app,const char* n, TWidget* obj)
	:TWindow(filename,app,n,obj)
{
    close_btn = new TPushButton(750,20,new TImage("1:/tgui_pic/check2_sel.png"),NULL,NULL, this);
    left_btn = new TPushButton(30,447,new TImage("1:/tgui_pic/button.png"),new TImage("1:/tgui_pic/button_sel.png"),"上一个", this);
    right_btn = new TPushButton(680,447,new TImage("1:/tgui_pic/button.png"),new TImage("1:/tgui_pic/button_sel.png"),"下一个", this);
    title_label = new TLabel(0,0,GUI_WIDTH,20,"PICTURE浏览器",this,ALIGN_CENTER,true,WHITE,BLACK);
	

    close_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserPhoto::closePhoto));
    left_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserPhoto::prevPhoto));
    right_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserPhoto::nextPhoto));

    startStat = false;

    fileNum = 0;
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
    if(startStat)
        showAll();
    
    picIndex ++;
    if(picIndex >= fileNum)
        picIndex = 0;
    TImageBox imgbox(0,0,(uint16)GUI_WIDTH,(uint16)GUI_HIGH,(const char* )fileName[picIndex],NULL,this,false);
    startStat = true;
}

void UserPhoto::prevPhoto()
{
	if(startStat)
        showAll();
    picIndex --;
    if(picIndex < 0)
        picIndex = fileNum - 1;
    TImageBox  imgbox(0,0,(uint16)GUI_WIDTH,(uint16)GUI_HIGH,(const char* )fileName[picIndex],NULL,this,false);
   startStat = true;
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
        int j=0;
        while (f_readdir(&dirs, &finfo) == FR_OK) 
        {
            if(!finfo.fname[0]) 
                break;
            if(finfo.fname[0]=='.' || (finfo.fname[0]=='.' && finfo.fname[1]=='.'))
                continue;

            
            fileName[fileNum][j] = 0;
            do
            {
                j++;
                fileName[fileNum][j] = 0;
            }
            while(fileName[fileNum][j] != '\0');
           
            if(fileNum<32)
            strcpy((char*)fileName[fileNum],path);
            strcat((char*)fileName[fileNum],"/");
            strcat((char*)fileName[fileNum],(*finfo.lfname ? finfo.lfname : finfo.fname));
            //printf("\r\nfilename = %s\r\n",(char*)fileName[fileNum]);
            fileNum++;
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
    f_closedir(&dirs);
}



void UserPhoto::show()
{
	refresh();
}


