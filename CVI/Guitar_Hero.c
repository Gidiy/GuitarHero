#include "windows.h"
#include "toolbox.h"
#include <ansi_c.h>
#include <utility.h>
#include <cvirte.h>
#include <userint.h>
#include "bass.h"
#include "Guitar_Hero.h"

//panels
static int panelHandle,panelHandle2,panelHandle3,panelHandle4,panelHandle5,panelHandle6,panelHandle7,panelHandle8,panelHandle9;
//pics
int NOA_image,HARRY_image,STAY_image,KUPIDON_image,fireworks,inst,boy_background,girl_background,good,bad,ok;
//faces
int man,woman,gilad1,gilad2,anael1,anael2;
int BG_C=1,loop=0;//gender
int pic_size=100; //size of the arrows
//black arrows
int arrow_black_left_inside,arrow_black_right_inside,arrow_black_top_inside,arrow_black_down_inside,arrow_black_left_outside,arrow_black_right_outside,arrow_black_top_outside,arrow_black_down_outside;;
//yellow arrows
int arrow_yellow_left_inside,arrow_yellow_right_inside,arrow_yellow_top_inside,arrow_yellow_down_inside;
//blue arrows
int arrow_blue_left_inside,arrow_blue_right_inside,arrow_blue_top_inside,arrow_blue_down_inside;
//blue arrows
int arrow_red_left_inside,arrow_red_right_inside,arrow_red_top_inside,arrow_red_down_inside;
//canvas
int canvas_width,canvas_height,distance;
//arrow initial location
int y_a1=700,y_a2=700,y_a3=700,y_a4=700 ,x_a1=100,x_a2=300,x_a3=500,x_a4=700;
//record
int score=0,low_dis=10,mid_dis=5, high_dis=-5;
//name
char name[20];
//level in the future
int level,speed=1,level_val,level_lable;
//file-music
static FILE *fp;
double Seconds[10000];
int Larr[10000],Rarr[10000],Tarr[10000],Barr[10000];
int counter=0,mute=0;
char filenameNew[1000]="";
//file-scores
static FILE *scorFile;
//timer
int dt=1,clicks=0,runner=0,runnert_struct=0,clico=1500,deltaT=0;//clico=game length-2000
double tol;
//pushed
int pushed1=0,pushed2=0,pushed3=0,pushed4=0;
//table
int winnerTable;
//list of songs
int song_num=4;
int index_song;
char label[20];
// struct for every note
struct note    //הגדרת מבנה
{
	int y;
	int pu;//if pushed
	int visi;
};
// struct for every PLAYER
struct player    //הגדרת מבנה
{
	int POINTS;
	char player_name[30];
};
//style game - creative
int creative=0;
//structs
static struct note C[100],D[100],E[100],F[100]; //יצירת משתנה של מבנה
static struct player actors[5];
//runer for every note
int c_run=0,d_run=0,e_run=0,f_run=0;
//functions
void init();
void terminate();
void display_arrows(int left, int right, int top , int down);
void init_table();
void update_table(char player_new[],int player_score);
void stopallmusic();

//soundc files
HSTREAM NOA_KIREL_DIAMONDS;
HSTREAM HARRY_STYLE_AS_IT_WAS;
HSTREAM THE_KID_LAROI_STAY;
HSTREAM AGAM_KUPIDON;
HSTREAM BACKGROUND;
HSTREAM count_321;
HSTREAM clap;
HSTREAM wa;
HSTREAM goodpoints;
HSTREAM badpoints;
HSTREAM newSong;

void ReleaseMP3s(void)
{
	BASS_StreamFree(NOA_KIREL_DIAMONDS);
	BASS_StreamFree(HARRY_STYLE_AS_IT_WAS);
	BASS_StreamFree(THE_KID_LAROI_STAY);
	BASS_StreamFree(AGAM_KUPIDON);
	BASS_StreamFree(count_321);
	BASS_StreamFree(clap);
	BASS_StreamFree(wa);
	BASS_StreamFree(goodpoints);
	BASS_StreamFree(badpoints);
}

void InitMP3s(void)
{
	BASS_Init( -1,44100, 0,0,NULL);
	//soundc files
	NOA_KIREL_DIAMONDS=BASS_StreamCreateFile(FALSE,"songs/DIAMONDS.mp3",0,0,0);
	HARRY_STYLE_AS_IT_WAS=BASS_StreamCreateFile(FALSE,"songs/AS_IT_WAS.mp3",0,0,0);
	THE_KID_LAROI_STAY=BASS_StreamCreateFile(FALSE,"songs/STAY.mp3",0,0,0);
	AGAM_KUPIDON=BASS_StreamCreateFile(FALSE,"songs/KUPIDON.mp3",0,0,0);
	BACKGROUND=BASS_StreamCreateFile(FALSE,"songs/GTA.mp3",0,0,0);
	count_321=BASS_StreamCreateFile(FALSE,"songs/count.mp3",0,0,0);
	clap=BASS_StreamCreateFile(FALSE,"songs/clap.mp3",0,0,0);
	wa=BASS_StreamCreateFile(FALSE,"songs/wa.mp3",0,0,0);
	goodpoints=BASS_StreamCreateFile(FALSE,"songs/goodpoints.mp3",0,0,0);
	badpoints=BASS_StreamCreateFile(FALSE,"songs/badpoints.mp3",0,0,0);

	BASS_ChannelSetAttribute(NOA_KIREL_DIAMONDS, BASS_ATTRIB_VOL, 1.0);// volume
	BASS_ChannelSetAttribute(HARRY_STYLE_AS_IT_WAS, BASS_ATTRIB_VOL, 1.0);// volume
	BASS_ChannelSetAttribute(THE_KID_LAROI_STAY, BASS_ATTRIB_VOL, 5.0);// volume
	BASS_ChannelSetAttribute(AGAM_KUPIDON, BASS_ATTRIB_VOL, 1.0);// volume
	BASS_ChannelSetAttribute(BACKGROUND, BASS_ATTRIB_VOL, 1.0);// volume
	BASS_ChannelSetAttribute(count_321, BASS_ATTRIB_VOL, 1.0);// volume
	BASS_ChannelSetAttribute(clap, BASS_ATTRIB_VOL, 1.0);// volume
	BASS_ChannelSetAttribute(wa, BASS_ATTRIB_VOL, 1.0);// volume

	BASS_ChannelPlay(BACKGROUND,TRUE);

}

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Guitar_Hero.uir", PANEL)) < 0)
		return -1;
	if ((panelHandle2 = LoadPanel (0, "Guitar_Hero.uir", PANEL_MANU)) < 0)
		return -1;
	if ((panelHandle3 = LoadPanel (0, "Guitar_Hero.uir", HowToPLAY)) < 0)
		return -1;
	if ((panelHandle4 = LoadPanel (0, "Guitar_Hero.uir", StartType)) < 0)
		return -1;
	if ((panelHandle5 = LoadPanel (0, "Guitar_Hero.uir", MANURETURN)) < 0)
		return -1;
	if ((panelHandle6 = LoadPanel (0, "Guitar_Hero.uir", PANEL_2)) < 0)
		return -1;
	if ((panelHandle7 = LoadPanel (0, "Guitar_Hero.uir", ABOUT)) < 0)
		return -1;
	if ((panelHandle8 = LoadPanel (0, "Guitar_Hero.uir", PANEL_3)) < 0)
		return -1;
	if ((panelHandle9 = LoadPanel (0, "Guitar_Hero.uir", PANEL_4)) < 0)
		return -1;
	init();
	init_table();
	DisplayPanel (panelHandle9);
	Delay(5);
	InitMP3s();

	HidePanel (panelHandle9);
	DisplayPanel (panelHandle2);
	RunUserInterface ();
	terminate();
	ReleaseMP3s();
	return 0;
}

void init()
{
	//faces pics
	GetBitmapFromFile("pics/faces/woman.PNG",&woman);
	GetBitmapFromFile("pics/faces/man.PNG",&man);
	GetBitmapFromFile("pics/faces/gilad1.PNG",&gilad1);
	GetBitmapFromFile("pics/faces/gilad2.PNG",&gilad2);
	GetBitmapFromFile("pics/faces/anael1.PNG",&anael1);
	GetBitmapFromFile("pics/faces/anael2.PNG",&anael2);
	//background pics
	GetBitmapFromFile("pics/background/NOA.jpg",& NOA_image);
	GetBitmapFromFile("pics/background/HARRY.jpg",&HARRY_image);
	GetBitmapFromFile("pics/background/STAY.jpg",&STAY_image);
	GetBitmapFromFile("pics/background/KUPIDON.jpg",&KUPIDON_image);
	GetBitmapFromFile("pics/background/KUPIDON.jpg",&girl_background);
	GetBitmapFromFile("pics/background/guitar-hero-boy.PNG",&boy_background);
	GetBitmapFromFile("pics/background/guitar-hero-girl.PNG",&girl_background);
	//black arrows
	GetBitmapFromFile("pics/black_arrow_path/left_inside.PNG",&arrow_black_left_inside);
	GetBitmapFromFile("pics/black_arrow_path/right_inside.PNG",&arrow_black_right_inside);
	GetBitmapFromFile("pics/black_arrow_path/top_inside.PNG",&arrow_black_top_inside);
	GetBitmapFromFile("pics/black_arrow_path/down_inside.PNG",&arrow_black_down_inside);
	GetBitmapFromFile("pics/black_arrow_path/left_outside.PNG",&arrow_black_left_outside);
	GetBitmapFromFile("pics/black_arrow_path/right_outside.PNG",&arrow_black_right_outside);
	GetBitmapFromFile("pics/black_arrow_path/top_outside.PNG",&arrow_black_top_outside);
	GetBitmapFromFile("pics/black_arrow_path/down_outside.PNG",&arrow_black_down_outside);
	//yellow arrows
	GetBitmapFromFile("pics/yellow_arrow_path/left_inside.PNG",&arrow_yellow_left_inside);
	GetBitmapFromFile("pics/yellow_arrow_path/right_inside.PNG",&arrow_yellow_right_inside);
	GetBitmapFromFile("pics/yellow_arrow_path/top_inside.PNG",&arrow_yellow_top_inside);
	GetBitmapFromFile("pics/yellow_arrow_path/down_inside.PNG",&arrow_yellow_down_inside);
	//blue arrows
	GetBitmapFromFile("pics/blue_arrow_path/left_inside.PNG",&arrow_blue_left_inside);
	GetBitmapFromFile("pics/blue_arrow_path/right_inside.PNG",&arrow_blue_right_inside);
	GetBitmapFromFile("pics/blue_arrow_path/top_inside.PNG",&arrow_blue_top_inside);
	GetBitmapFromFile("pics/blue_arrow_path/down_inside.PNG",&arrow_blue_down_inside);
	//red arrows
	GetBitmapFromFile("pics/red_arrow_path/left_inside.PNG",&arrow_red_left_inside);
	GetBitmapFromFile("pics/red_arrow_path/right_inside.PNG",&arrow_red_right_inside);
	GetBitmapFromFile("pics/red_arrow_path/top_inside.PNG",&arrow_red_top_inside);
	GetBitmapFromFile("pics/red_arrow_path/down_inside.PNG",&arrow_red_down_inside);

	GetBitmapFromFile("pics/fireworks.PNG",&fireworks);
	GetBitmapFromFile("pics/+10.PNG",&good);
	GetBitmapFromFile("pics/minus5.PNG",&bad);
	GetBitmapFromFile("pics/+5.PNG",&ok);
	GetCtrlAttribute(panelHandle,PANEL_CANVAS,ATTR_WIDTH,&canvas_width);
	GetCtrlAttribute(panelHandle,PANEL_CANVAS,ATTR_HEIGHT,&canvas_height);

	//INSERT_SONGS_LIST
	InsertListItem (panelHandle2,PANEL_MANU_SONGS, 0, "DIAMONDS", 0);//same number for each song
	InsertListItem (panelHandle2,PANEL_MANU_SONGS, 1, "AS_IT_WAS", 1);//same number for each song
	InsertListItem (panelHandle2,PANEL_MANU_SONGS, 2, "STAY", 2);//same number for each song
	InsertListItem (panelHandle2,PANEL_MANU_SONGS, 3, "KUPIDON", 3);//same number for each song
	//labels in table score
	SetTableColumnAttribute (panelHandle6, PANEL_2_WINNERS, 1, ATTR_USE_LABEL_TEXT, 1);
	SetTableColumnAttribute (panelHandle6, PANEL_2_WINNERS, 1, ATTR_LABEL_TEXT, "NAME");
	SetTableColumnAttribute (panelHandle6, PANEL_2_WINNERS, 2, ATTR_USE_LABEL_TEXT, 1);
	SetTableColumnAttribute (panelHandle6, PANEL_2_WINNERS, 2, ATTR_LABEL_TEXT, "SCORE");
	//define table
	for(int v=1; v<6; v++)//only 5 winners
	{
		SetTableCellAttribute (panelHandle6 ,PANEL_2_WINNERS, MakePoint (2, v), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
		SetTableCellAttribute (panelHandle6, PANEL_2_WINNERS, MakePoint (1, v), ATTR_CELL_TYPE, VAL_CELL_STRING);
	}
}

void terminate()
{
	//discards panels
	DiscardPanel (panelHandle);
	DiscardPanel (panelHandle2);
	DiscardPanel (panelHandle3);
	DiscardPanel (panelHandle4);
	DiscardPanel (panelHandle5);
	DiscardPanel (panelHandle6);
	DiscardPanel (panelHandle7);
	DiscardPanel (panelHandle8);
	DiscardPanel (panelHandle9);
	//BACKGROUND PICS
	DiscardBitmap(NOA_image);
	DiscardBitmap(HARRY_image);
	DiscardBitmap(STAY_image);
	DiscardBitmap(KUPIDON_image);
	DiscardBitmap(girl_background);
	DiscardBitmap(boy_background);
	//black arrow
	DiscardBitmap(arrow_black_left_inside);
	DiscardBitmap(arrow_black_right_inside);
	DiscardBitmap(arrow_black_top_inside);
	DiscardBitmap(arrow_black_down_inside);
	DiscardBitmap(arrow_black_left_outside);
	DiscardBitmap(arrow_black_right_outside);
	DiscardBitmap(arrow_black_top_outside);
	DiscardBitmap(arrow_black_down_outside);
	//yellow arrow
	DiscardBitmap(arrow_yellow_left_inside);
	DiscardBitmap(arrow_yellow_right_inside);
	DiscardBitmap(arrow_yellow_top_inside);
	DiscardBitmap(arrow_yellow_down_inside);
	//blue arrow
	DiscardBitmap(arrow_blue_left_inside);
	DiscardBitmap(arrow_blue_right_inside);
	DiscardBitmap(arrow_blue_top_inside);
	DiscardBitmap(arrow_blue_down_inside);
	//red arrow
	DiscardBitmap(arrow_red_left_inside);
	DiscardBitmap(arrow_red_right_inside);
	DiscardBitmap(arrow_red_top_inside);
	DiscardBitmap(arrow_red_down_inside);
	
	DiscardBitmap(fireworks);
	DiscardBitmap(good);
	DiscardBitmap(bad);
	DiscardBitmap(ok);
	//faces
	DiscardBitmap(man);
	DiscardBitmap(woman);
	DiscardBitmap(gilad1);
	DiscardBitmap(gilad2);
	DiscardBitmap(anael1);
	DiscardBitmap(anael2);
}

int CVICALLBACK Exit (int panel, int event, void *callbackData,
					  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface(0);
			break;
	}
	return 0;
}


int CVICALLBACK Time (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	char message1[300]="כל הכבוד  ";
	char message2[300]=" הציון שלך הוא:  ";
	char score_str[300];

	switch (event)
	{
		case EVENT_TIMER_TICK:


			if(clicks%20==0)
			{
				if(BG_C==0)//gender
				{
					if(loop==1)
					{
						CanvasStartBatchDraw(panelHandle, PANEL_face);

						CanvasClear (panelHandle, PANEL_face, VAL_ENTIRE_OBJECT);

						CanvasDrawBitmap (panelHandle, PANEL_face,gilad1, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
						loop=0;
						CanvasEndBatchDraw(panelHandle, PANEL_face);
					}
					else
					{

						CanvasStartBatchDraw(panelHandle, PANEL_face);

						CanvasClear (panelHandle, PANEL_face, VAL_ENTIRE_OBJECT);

						CanvasDrawBitmap (panelHandle, PANEL_face,gilad2, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
						loop=1;
						CanvasEndBatchDraw(panelHandle, PANEL_face);
					}

				}
				else
				{

					if(loop==1)
					{
						CanvasStartBatchDraw(panelHandle, PANEL_face);

						CanvasClear (panelHandle, PANEL_face, VAL_ENTIRE_OBJECT);

						CanvasDrawBitmap (panelHandle, PANEL_face,anael1, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
						loop=0;
						CanvasEndBatchDraw(panelHandle, PANEL_face);
					}
					else
					{

						CanvasStartBatchDraw(panelHandle, PANEL_face);

						CanvasClear (panelHandle, PANEL_face, VAL_ENTIRE_OBJECT);

						CanvasDrawBitmap (panelHandle, PANEL_face,anael2, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
						loop=1;
						CanvasEndBatchDraw(panelHandle, PANEL_face);
					}
				}
			}

			SetCtrlAttribute (panelHandle, PANEL_arrow1, ATTR_CMD_BUTTON_COLOR, VAL_WHITE);
			SetCtrlAttribute (panelHandle, PANEL_arrow2, ATTR_CMD_BUTTON_COLOR, VAL_WHITE);
			SetCtrlAttribute (panelHandle, PANEL_arrow3, ATTR_CMD_BUTTON_COLOR, VAL_WHITE);
			SetCtrlAttribute (panelHandle, PANEL_arrow4, ATTR_CMD_BUTTON_COLOR, VAL_WHITE);

			if(creative==1)
			{
				if(deltaT>clicks)
					SetCtrlVal(panelHandle4,StartType_Stopper2,(deltaT-clicks));
				else
				{
					SetCtrlAttribute(panelHandle,PANEL_INSTRUMENT,ATTR_DIMMED,0);//unDimmed instrumen
					HidePanel(panelHandle4);
				}
			}
			else
				SetCtrlAttribute(panelHandle,PANEL_INSTRUMENT,ATTR_DIMMED,0);//unDimmed instrumen
			//stop The game
			if(clicks==clico)
			{
				strcat(message1, name);
				strcat(message1, message2);
				sprintf(score_str, "%d",score);
				strcat(message1, score_str);
				SetCtrlAttribute(panelHandle,PANEL_TIMER,ATTR_ENABLED,0);
				//end canvas
			CanvasStartBatchDraw(panelHandle, PANEL_CANVAS);
			CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
			CanvasEndBatchDraw(panelHandle, PANEL_CANVAS);
			//end canvas
				DisplayPanel(panelHandle5);
				if(creative==0)
					SetCtrlVal(panelHandle5,MANURETURN_TEXT,message1);
				else
					SetCtrlVal(panelHandle5,MANURETURN_TEXT,"יצרת משחק משלך! את.ה מוזמן.ת לשחק בו עכשיו");
				stopallmusic();
				BASS_ChannelPlay(clap,TRUE);
				//reset pushed of any arrow
				for(int k=0; k<c_run; k++)
				{
					C[k].pu = 0;
					C[k].visi=0;//visible
				}
				for(int k=0; k<d_run; k++)
					D[k].pu = 0;

				for(int k=0; k<e_run; k++)
					E[k].pu = 0;

				for(int k=0; k<f_run; k++)
					F[k].pu = 0;
			}
			CanvasStartBatchDraw(panelHandle, PANEL_CANVAS);

			CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
			//background pics
			if(strcmp(label,"DIAMONDS")==0)
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, NOA_image, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);	//display background pic
			if(strcmp(label, "AS_IT_WAS")==0)
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, HARRY_image, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);	//display background pic

			if(strcmp(label, "STAY")==0)
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, STAY_image, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);	//display background pic

			if(strcmp(label,  "KUPIDON")==0)
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, KUPIDON_image, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);	//display background pic
			//static black outside arrows
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, arrow_black_left_outside, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a1, pic_size, pic_size));	//display black arrow outside pic
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, arrow_black_top_outside, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a2, pic_size, pic_size));	//display black arrow outside pic
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, arrow_black_down_outside, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a3, pic_size, pic_size));	//display black arrow outside pic
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, arrow_black_right_outside, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a4, pic_size, pic_size));	//display black arrow outside pic
			//displays
			SetCtrlVal(panelHandle,PANEL_Clock,clico-clicks);
			SetCtrlVal(panelHandle,PANEL_Clock_2,c_run);
			SetCtrlVal(panelHandle,PANEL_Clock_3,d_run);
			SetCtrlVal(panelHandle,PANEL_Clock_4,e_run);
			SetCtrlVal(panelHandle,PANEL_Clock_5,f_run);
			
				
					
			//arrow color by level chosen
			switch (level_val)
			{
				case 1:
					display_arrows(arrow_blue_left_inside, arrow_blue_right_inside, arrow_blue_top_inside ,arrow_blue_down_inside);
					break;
				case 2:
					display_arrows(arrow_yellow_left_inside, arrow_yellow_right_inside, arrow_yellow_top_inside ,arrow_yellow_down_inside);
					break;
				case 3:
					display_arrows(arrow_red_left_inside, arrow_red_right_inside, arrow_red_top_inside ,arrow_red_down_inside);
					break;
			}
			CanvasEndBatchDraw(panelHandle, PANEL_CANVAS);
			//GetCtrlVal(panelHandle2,PANEL_MANU_CREATIVE,&creative);
			switch (creative)
			{
				case 1:
				{
					if((clicks-deltaT)>=0)//add only positive and zero seconds
					{
						fprintf(fp,"%lf,%d,%d,%d,%d\n" ,(double)(clicks-deltaT),pushed1,pushed2,pushed3,pushed4);//write to file with tolerance of waiting
						pushed1=0;
						pushed2=0;
						pushed3=0;
						pushed4=0;
					}
					break;
				}
			}
			clicks++;//every second


			break;
	}
	return 0;
}

int CVICALLBACK RUN (int panel, int control, int event,
					 void *callbackData, int eventData1, int eventData2)
{
	char line[30];

	switch (event)
	{
		case EVENT_COMMIT:
			//GetCtrlVal(panelHandle2,PANEL_MANU_BG,&BG_C);
			if(BG_C==0)//choose body
			{
				CanvasStartBatchDraw(panelHandle, PANEL_body);

				CanvasClear (panelHandle, PANEL_body, VAL_ENTIRE_OBJECT);
				CanvasDrawBitmap (panelHandle, PANEL_body,man, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			}
			else
			{
				CanvasStartBatchDraw(panelHandle, PANEL_body);

				CanvasClear (panelHandle, PANEL_body, VAL_ENTIRE_OBJECT);
				CanvasDrawBitmap (panelHandle, PANEL_body, woman, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			}
			GetCtrlVal(panelHandle2,PANEL_MANU_NAME,name);
			if(strlen(name) >0)
			{
				SetCtrlAttribute (panelHandle, PANEL_INSTRUMENT, ATTR_DIMMED, 1);//Dimmed instrument
				//GetCtrlVal(panelHandle2,PANEL_MANU_CREATIVE,&creative);
				//How TO Play AND stopper
				if(creative==1)
				{
					SetCtrlAttribute(panelHandle3,HowToPLAY_STRING,ATTR_LABEL_TEXT,"חוקי המשחק- מצב יצירה");
					SetCtrlVal(panelHandle3,HowToPLAY_STRING_2,"מומלץ לרווח בין החיצים");
				}
				else
				{
					SetCtrlAttribute(panelHandle3,HowToPLAY_STRING,ATTR_LABEL_TEXT,"חוקי המשחק");
					SetCtrlVal (panelHandle3, HowToPLAY_STRING_2,  "מדוייק 10 נק',ליד 5 נק', פספוס -5 נקודות");
				}

				SetCtrlAttribute(panelHandle3,HowToPLAY_STOPPER,ATTR_VISIBLE,1);
				SetCtrlAttribute(panelHandle3,HowToPLAY_STOPPER,ATTR_LABEL_VISIBLE,1);

				BASS_ChannelStop(BACKGROUND);

				BASS_ChannelPlay(count_321,TRUE);//countdown-start
				DisplayPanel (panelHandle3);
				for(int h=0; h<3; h++)
				{

					SetCtrlVal(panelHandle3,HowToPLAY_STOPPER,(3-h));
					Delay(1);
				}

				//SONGS LIST
				GetCtrlAttribute (panelHandle2, PANEL_MANU_SONGS, ATTR_CTRL_INDEX,&index_song );
				GetLabelFromIndex (panelHandle2, PANEL_MANU_SONGS, index_song, label);
				SetCtrlVal(panelHandle,PANEL_SONG_NAME,label);
				//option for any song in the list with full file name
				char s1[30]="songs/";
				strcat(s1, label);
				char txt[]=".txt";
				strcat(s1, txt);
				//creative mode
				switch (creative)
				{
					case 0:
					{
						SetCtrlAttribute(panelHandle,PANEL_RETURN_BOT,ATTR_LABEL_TEXT,"חזרה לתפריט");
						fp = fopen(s1,"r");//load song
						while(fgets(line,29,fp))
						{
							sscanf(line,"%lf,%d,%d,%d,%d",&Seconds[counter],&Larr[counter],&Rarr[counter],&Tarr[counter],&Barr[counter]);
							counter++;
						}
						fclose(fp);
						break;
					}
					case 1:
					{
						//write to file
						SetCtrlAttribute(panelHandle,PANEL_RETURN_BOT,ATTR_LABEL_TEXT,"שמירה");
						fp = fopen(s1,"w");//load song
					}
					break;
				}
				GetCtrlVal(panelHandle2,PANEL_MANU_RINGSLIDE,&level_val);


				switch (level_val)
				{
					case 1:
						level=3;
						SetCtrlVal(panelHandle,PANEL_LEVEL_NAME,"מתחיל");
						break;
					case 2:
						level=7;
						SetCtrlVal(panelHandle,PANEL_LEVEL_NAME,"מתקדם");
						break;
					case 3:
						level=15;
						SetCtrlVal(panelHandle,PANEL_LEVEL_NAME,"מומחה");
						break;
				}
				if(strcmp(label,"DIAMONDS")==0)
					BASS_ChannelPlay(NOA_KIREL_DIAMONDS,TRUE);
				else if(strcmp(label, "AS_IT_WAS")==0)
					BASS_ChannelPlay(HARRY_STYLE_AS_IT_WAS,TRUE);
				else if(strcmp(label, "STAY")==0)
					BASS_ChannelPlay(THE_KID_LAROI_STAY,TRUE);
				else if(strcmp(label,  "KUPIDON")==0)
					BASS_ChannelPlay(AGAM_KUPIDON,TRUE);
				else //new song
				{
					newSong=BASS_StreamCreateFile(FALSE,filenameNew,0,0,0);

					BASS_ChannelSetAttribute(newSong, BASS_ATTRIB_VOL, 1.0);// volume
					BASS_ChannelPlay(newSong,TRUE);
				}


				deltaT=(canvas_height*3/4)/(speed*level);
				//reset values
				c_run=0,d_run=0,e_run=0,f_run=0,dt=1,clicks=0,runner=0,runnert_struct=0,y_a1=700,y_a2=700,y_a3=700,y_a4=700 ,x_a1=100,x_a2=300,x_a3=500,x_a4=700,score=0;//start song from beggining
				SetCtrlVal(panelHandle,PANEL_SCORE,score);
				HidePanel(panelHandle3);
				SetCtrlVal(panelHandle3,HowToPLAY_STOPPER,3);
				//GetCtrlVal(panelHandle2,PANEL_MANU_NAME,name);
				DisplayPanel (panelHandle);
				if(creative==1)//creative mode
				{
					DisplayPanel (panelHandle4);
				}
				HidePanel(panelHandle2);
				SetCtrlVal(panelHandle,PANEL_NAME,name);
				SetCtrlAttribute(panelHandle,PANEL_TIMER,ATTR_ENABLED,1);//start time

			}
			else
			{					//no name insert
				SetCtrlAttribute (panelHandle2, PANEL_MANU_NAME, ATTR_TEXT_BGCOLOR, VAL_RED);
			}

	}
	return 0;
}

int CVICALLBACK EXIT (int panel, int event, void *callbackData,
					  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:
			break;
		case EVENT_LOST_FOCUS:
			break;
		case EVENT_CLOSE:
			QuitUserInterface(0);
			break;
	}
	return 0;
}

int CVICALLBACK Return (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute(panelHandle,PANEL_TIMER,ATTR_ENABLED,0);
			//GetCtrlVal(panelHandle2,PANEL_MANU_CREATIVE,&creative);
			switch (creative)
			{
				case 0:
				{
					GetCtrlVal(panelHandle2,PANEL_MANU_NAME,name);
					update_table(name,score);
					//reset pushed of any arrow
					for(int k=0; k<c_run; k++)
						C[k].pu = 0;
					for(int k=0; k<d_run; k++)
						D[k].pu = 0;

					for(int k=0; k<e_run; k++)
						E[k].pu = 0;

					for(int k=0; k<f_run; k++)
						F[k].pu = 0;


				}
				break;
				case 1:
					fclose(fp);//after save
					break;
			}
			DisplayPanel (panelHandle2);
			HidePanel(panelHandle);
			counter=0;//start from the beggining
			//STOP ALL MUSIC
			stopallmusic();

			if(mute==0)
			{
				BASS_ChannelPlay(BACKGROUND,TRUE);
			}
			break;
	}
	return 0;
}

int CVICALLBACK arrow1_run (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			switch (creative)
			{
				case 0:
				{
					SetCtrlAttribute (panelHandle, PANEL_arrow1, ATTR_CMD_BUTTON_COLOR, VAL_RED);
					

					// check every arrow in this arry with the distance and calculate score and update score
					for(int k=0; k<c_run; k++)
					{
						if(C[k].pu != 1)
						{
							distance=abs(C[k].y-(canvas_height/4));//outside arrow- 158, 1-> 131,140, upper side ->239,dowside->50
							if(distance>61 && distance<80)
							{
								score=score+high_dis;
								//SetCtrlVal(panelHandle,PANEL_DIS,"TOO MUCH");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, bad, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a1, pic_size, pic_size));	//display fireworks pic
								C[k].pu=1;//check once
								C[k].visi=1;//if 1 invisible
								BASS_ChannelPlay(badpoints,TRUE);
								Delay(0.02);//to be able see the fireworks
							}
							if(distance>41 && distance<60)
							{
								score=score+mid_dis;
								//	SetCtrlVal(panelHandle,PANEL_DIS,"MIDDLE");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, ok, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a1, pic_size, pic_size));	//display fireworks pic
								C[k].pu=1;//check once
								C[k].visi=1;//if 1 invisible
								BASS_ChannelPlay(goodpoints,TRUE);
								Delay(0.02);//to be able see the fireworks
							}
							if(distance>0 && distance<40)
							{
								score=score+low_dis;
								//SetCtrlVal(panelHandle,PANEL_DIS,"VERY CLOSE!");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, fireworks, VAL_ENTIRE_OBJECT, MakeRect ((canvas_height/4)-50, x_a1-50, pic_size+100, pic_size+100));	//display fireworks pic
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, good, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a1, pic_size, pic_size));	//display fireworks pic
								C[k].pu=1;//check once
								C[k].visi=1;//if 1 invisible
								Delay(0.02);//to be able see the fireworks
								BASS_ChannelPlay(goodpoints,TRUE);
							}
						}
					}
					SetCtrlVal(panelHandle,PANEL_SCORE,score);
				}
				break;
				case 1:
					pushed1=1;
					break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK arrow2_run (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			switch (creative)
			{
				case 0:
				{
					SetCtrlAttribute (panelHandle, PANEL_arrow2, ATTR_CMD_BUTTON_COLOR, VAL_BLUE);
					// check every arrow in this arry with the distance and calculate score and update score
					for(int k=0; k<d_run; k++)
					{
						if(D[k].pu != 1)
						{
							distance=abs(D[k].y-(canvas_height/4));
							if(distance>61 && distance<80)
							{
								score=score+high_dis;
								//SetCtrlVal(panelHandle,PANEL_DIS,"TOO MUCH");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, bad, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a2, pic_size, pic_size));	//display fireworks pic
								D[k].pu = 1;//check once
								D[k].visi=1;//if 1 invisible
								BASS_ChannelPlay(badpoints,TRUE);
								Delay(0.02);//to be able see the fireworks
							}
							if(distance>41 && distance<60)
							{
								score=score+mid_dis;
								//SetCtrlVal(panelHandle,PANEL_DIS,"MIDDLE");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, ok, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a2, pic_size, pic_size));	//display fireworks pic
								D[k].pu = 1;//check once
								D[k].visi=1;//if 1 invisible
								BASS_ChannelPlay(goodpoints,TRUE);
								Delay(0.02);//to be able see the fireworks
							}
							if(distance>0 && distance<40)
							{
								score=score+low_dis;
								//SetCtrlVal(panelHandle,PANEL_DIS,"VERY CLOSE!");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, fireworks, VAL_ENTIRE_OBJECT, MakeRect ((canvas_height/4)-50, x_a2-50, pic_size+100, pic_size+100));	//display black arrow outside pic
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, good, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a2, pic_size, pic_size));	//display fireworks pic
								D[k].pu = 1;//check once
								D[k].visi=1;//if 1 invisible
								Delay(0.02);//to be able see the fireworks
								BASS_ChannelPlay(goodpoints,TRUE);
							}
						}
					}
					SetCtrlVal(panelHandle,PANEL_SCORE,score);
				}
				break;
				case 1:
					pushed2=1;
					break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK arrow3_run (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			switch (creative)
			{
				case 0:
				{
					SetCtrlAttribute (panelHandle, PANEL_arrow3, ATTR_CMD_BUTTON_COLOR, VAL_GREEN);
					// check every arrow in this arry with the distance and calculate score and update score
					for(int k=0; k<e_run; k++) // check every arrow in this arry with the distance and calculate
					{
						if(E[k].pu != 1)
						{
							distance=abs(E[k].y-(canvas_height/4));
							if(distance>61 && distance<80)
							{
								score=score+high_dis;
								//SetCtrlVal(panelHandle,PANEL_DIS,"TOO MUCH");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, bad, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a3, pic_size, pic_size));	//display fireworks pic
								E[k].pu = 1;//check once
								E[k].visi=1;//if 1 invisible
								BASS_ChannelPlay(badpoints,TRUE);
								Delay(0.02);//to be able see the fireworks
							}
							if(distance>41 && distance<60)
							{
								score=score+mid_dis;
								SetCtrlVal(panelHandle,PANEL_DIS,"MIDDLE");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, ok, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a3, pic_size, pic_size));	//display fireworks pic
								E[k].pu = 1;//check once
								E[k].visi=1;//if 1 invisible
								BASS_ChannelPlay(goodpoints,TRUE);
								Delay(0.02);//to be able see the fireworks
							}
							if(distance>0 && distance<40)
							{
								score=score+low_dis;
								SetCtrlVal(panelHandle,PANEL_DIS,"VERY CLOSE!");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, fireworks, VAL_ENTIRE_OBJECT, MakeRect ((canvas_height/4)-50, x_a3-50, pic_size+100, pic_size+100));	//display black arrow outside pic
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, good, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a3, pic_size, pic_size));	//display fireworks pic
								E[k].pu = 1;//check once
								E[k].visi=1;//if 1 invisible
								Delay(0.02);//to be able see the fireworks
								BASS_ChannelPlay(goodpoints,TRUE);
							}
						}
					}
					SetCtrlVal(panelHandle,PANEL_SCORE,score);
				}
				break;
				case 1:
					pushed3=1;
					break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK arrow4_run (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			switch (creative)
			{
				case 0:
				{
					// check every arrow in this arry with the distance and calculate score and update score
					SetCtrlAttribute (panelHandle, PANEL_arrow4, ATTR_CMD_BUTTON_COLOR, VAL_YELLOW);
					for(int k=0; k<f_run; k++)
					{
						if(F[k].pu != 1)
						{
							distance=abs(F[k].y-(canvas_height/4));
							if(distance>61 && distance<80)
							{
								score=score+high_dis;
								SetCtrlVal(panelHandle,PANEL_DIS,"TOO MUCH");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, bad, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a4, pic_size, pic_size));	//display fireworks pic
								F[k].pu = 1;//check once
								F[k].visi=1;//if 1 invisible
								BASS_ChannelPlay(badpoints,TRUE);
								Delay(0.02);//to be able see the fireworks
							}
							if(distance>41 && distance<60)
							{
								score=score+mid_dis;
								SetCtrlVal(panelHandle,PANEL_DIS,"MIDDLE");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, ok, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a4, pic_size, pic_size));	//display fireworks pic
								F[k].pu = 1;//check once
								F[k].visi=1;//if 1 invisible
								BASS_ChannelPlay(goodpoints,TRUE);
								Delay(0.02);//to be able see the fireworks
							}
							if(distance>0 && distance<40)
							{
								score=score+low_dis;
								SetCtrlVal(panelHandle,PANEL_DIS,"VERY CLOSE!");
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, fireworks, VAL_ENTIRE_OBJECT, MakeRect ((canvas_height/4)-50, x_a4-50, pic_size+100, pic_size+100));	//display black arrow outside pic
								CanvasDrawBitmap (panelHandle, PANEL_CANVAS, good, VAL_ENTIRE_OBJECT, MakeRect (canvas_height/4, x_a4, pic_size, pic_size));	//display fireworks pic
								
								F[k].pu = 1;//check once
								F[k].visi=1;//if 1 invisible
								Delay(0.02);//to be able see the fireworks
								BASS_ChannelPlay(goodpoints,TRUE);
							}
						}
					}
					SetCtrlVal(panelHandle,PANEL_SCORE,score);
				}
				break;
				case 1:
					pushed4=1;
					break;
			}
			break;
	}
	return 0;

}

int CVICALLBACK EXIT1 (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			BASS_ChannelPlay(wa,TRUE);//funny voice
			Delay(1);
			QuitUserInterface(0);
			break;
	}
	return 0;
}


void display_arrows(int left, int right, int top , int down)
{
	switch (creative)
	{
		case 0:
		{
			if(Larr[clicks]==1)//CHECK WHO IS PUSHED AT THE SAME TIME OF TIMER
			{
				C[c_run].y=canvas_height;
				c_run++;
			}
			for(int j=0; j<c_run; j++)
			{
				if(C[j].visi==0)//invisible after push
				{
					CanvasDrawBitmap (panelHandle, PANEL_CANVAS, left, VAL_ENTIRE_OBJECT, MakeRect(C[j].y,x_a1,pic_size,pic_size));	//display inside left
					C[j].y-=speed*level;
				}
			}
			if(Rarr[clicks]==1)//CHECK WHO IS PUSHED AT THE SAME TIME OF TIMER
			{
				D[d_run].y=canvas_height;
				d_run++;
			}
			for(int j=0; j<d_run; j++)
			{
				if(D[j].visi==0)//invisible after push
				{
					CanvasDrawBitmap (panelHandle, PANEL_CANVAS, top, VAL_ENTIRE_OBJECT, MakeRect(D[j].y,x_a2,pic_size,pic_size));	//display inside top
					D[j].y-=speed*level;
				}
			}
			if(Tarr[clicks]==1)//CHECK WHO IS PUSHED AT THE SAME TIME OF TIMER
			{
				E[e_run].y=canvas_height;
				e_run++;
			}
			for(int j=0; j<e_run; j++)
			{
				if(E[j].visi==0)//invisible after push
				{
					CanvasDrawBitmap (panelHandle, PANEL_CANVAS, down, VAL_ENTIRE_OBJECT, MakeRect(E[j].y,x_a3,pic_size,pic_size));	//display inside dow
					E[j].y-=speed*level;
				}
			}
			if(Barr[clicks]==1)//CHECK WHO IS PUSHED AT THE SAME TIME OF TIMER
			{
				F[f_run].y=canvas_height;
				f_run++;
			}
			for(int j=0; j<f_run; j++)
			{
				if(F[j].visi==0)//invisible after push
				{
					CanvasDrawBitmap (panelHandle, PANEL_CANVAS, right, VAL_ENTIRE_OBJECT, MakeRect(F[j].y,x_a4,pic_size,pic_size));	//display inside right
					F[j].y-=speed*level;
				}
			}
			break;
		}
		case 1:
		{
			if(pushed1==1)//CHECK WHO IS PUSHED AT THE SAME TIME OF TIMER
			{
				C[c_run].y=canvas_height/4;
				c_run++;
			}
			for(int j=0; j<c_run; j++)
			{


				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, left, VAL_ENTIRE_OBJECT, MakeRect(C[j].y,x_a1,pic_size,pic_size));	//display inside left
				C[j].y-=speed*level;

			}
			if(pushed2==1)//CHECK WHO IS PUSHED AT THE SAME TIME OF TIMER
			{
				D[d_run].y=canvas_height/4;
				d_run++;
			}
			for(int j=0; j<d_run; j++)
			{
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, top, VAL_ENTIRE_OBJECT, MakeRect(D[j].y,x_a2,pic_size,pic_size));	//display inside top
				D[j].y-=speed*level;
			}
			if(pushed3==1)//CHECK WHO IS PUSHED AT THE SAME TIME OF TIMER
			{
				E[e_run].y=canvas_height/4;
				e_run++;
			}
			for(int j=0; j<e_run; j++)
			{
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, down, VAL_ENTIRE_OBJECT, MakeRect(E[j].y,x_a3,pic_size,pic_size));	//display inside dow
				E[j].y-=speed*level;
			}
			if(pushed4==1)//CHECK WHO IS PUSHED AT THE SAME TIME OF TIMER
			{
				F[f_run].y=canvas_height/4;
				f_run++;
			}
			for(int j=0; j<f_run; j++)
			{
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, right, VAL_ENTIRE_OBJECT, MakeRect(F[j].y,x_a4,pic_size,pic_size));	//display inside right
				F[j].y-=speed*level;
			}
		}
		break;
	}
}

void update_table(char player_new[],int player_score)//after win
{
	for(int l=0; l<5; l++) //check if score bigger than minimum- if true- insert and organize by score
	{
		if(actors[l].POINTS<player_score)
		{
			for(int n=3; n>=l; n--)
			{
				strcpy(actors[n+1].player_name,actors[n].player_name);
				actors[n+1].POINTS=actors[n].POINTS;
			}
			actors[l].POINTS=player_score;
			strcpy(actors[l].player_name,player_new);
			l=6;//skip the for
		}
	}

	//store data in file
	scorFile = fopen("Winners.txt","w");//load file to save new data
	for(int f=0; f<5; f++)
	{
		fprintf(scorFile,"%d,%s\n",actors[f].POINTS,actors[f].player_name);//write to file new data
	}
	fclose(scorFile);
	init_table();//updata data in table from new file
}
void init_table()
{
	char line1[30];
	int number=0;
	scorFile = fopen("Winners.txt","r");//load score file
	while(fgets(line1,29,scorFile))
	{
		sscanf(line1,"%d,%s",&actors[number].POINTS,actors[number].player_name);
		number++;
	}
	fclose(scorFile);
	//restore data in array from file

	//display table from file
	for(int c=1; c<6; c++)
	{
		SetTableCellVal (panelHandle6, PANEL_2_WINNERS, MakePoint (2, c), actors[c-1].POINTS);
		SetTableCellVal (panelHandle6, PANEL_2_WINNERS, MakePoint (1,c),actors[c-1].player_name);
	}
}

int CVICALLBACK Load (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	const char s[2] = "\\";//fine the last dir
	char *token;
	int status;
	char filename[1000]="";
	char filename2[1000]="";


	switch (event)
	{
		case EVENT_COMMIT:
			//extract file name and turn it into txt file
			status = FileSelectPopup ("\songs", "*.*", ".mp3", "Select new MP3 Song", VAL_LOAD_BUTTON, 0, 0, 1, 0, filename);
			strcpy(filenameNew,filename);
			token = strtok(filename, s);
			while( token != NULL )
			{
				strcpy(filename2,token);
				token = strtok(NULL, s);
			}
			strtok(filename2, ".");
			InsertListItem (panelHandle2,PANEL_MANU_SONGS, song_num, filename2, song_num);//same number for each song
			song_num++;
			MessagePopup ("אזהרה!!", "חובה ליצור משחק במצב יצירה לפני תחילת משחק");
			break;
	}
	return 0;
}

int CVICALLBACK about (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DisplayPanel(panelHandle7);
			break;
	}
	return 0;
}

void stopallmusic()
{
	BASS_ChannelStop(NOA_KIREL_DIAMONDS);
	BASS_ChannelStop(HARRY_STYLE_AS_IT_WAS);
	BASS_ChannelStop(THE_KID_LAROI_STAY);
	BASS_ChannelStop(AGAM_KUPIDON);
	BASS_ChannelStop(count_321);
	BASS_ChannelStop(clap);
	BASS_ChannelStop(BACKGROUND);
	BASS_ChannelStop(newSong);
}

int CVICALLBACK WINNERoP (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DisplayPanel(panelHandle6);
			break;
	}
	return 0;
}

int CVICALLBACK EXIT2 (int panel, int event, void *callbackData,
					   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel(panelHandle6);
			break;
	}
	return 0;
}

int CVICALLBACK changeins (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:



			if(inst == 1)
			{
				SetCtrlAttribute(panelHandle,PANEL_PICTURE,ATTR_VISIBLE,1);
				SetCtrlAttribute(panelHandle,PANEL_PICTURE_2,ATTR_VISIBLE,0);
				inst=0;
			}
			else
			{
				SetCtrlAttribute(panelHandle,PANEL_PICTURE,ATTR_VISIBLE,0);
				SetCtrlAttribute(panelHandle,PANEL_PICTURE_2,ATTR_VISIBLE,1);
				inst=1;
			}
			break;
	}
	return 0;
}


int CVICALLBACK STOP_MUSIC (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			if(mute==0)
			{
				stopallmusic();
				SetCtrlAttribute(panelHandle2,PANEL_MANU_STOP_MUS,ATTR_LABEL_TEXT,"הפעל מוזיקה");
				mute=1;
			}
			else
			{
				BASS_ChannelPlay(BACKGROUND,TRUE);
				SetCtrlAttribute(panelHandle2,PANEL_MANU_STOP_MUS,ATTR_LABEL_TEXT,"השתק מוזיקה");
				mute=0;
			}

			break;
	}
	return 0;
}

int CVICALLBACK changeGEN (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(BG_C==0)//BOY
			{
				SetCtrlAttribute(panelHandle2,PANEL_MANU_BG,ATTR_LABEL_TEXT,"בת");
				BG_C=1;//girl
				SetCtrlAttribute (panelHandle2, PANEL_MANU_PICTURE, ATTR_IMAGE_FILE, "pics/background/guitar-hero-girl.PNG");
			}
			else
			{
				SetCtrlAttribute(panelHandle2,PANEL_MANU_BG,ATTR_LABEL_TEXT,"בן");
				BG_C=0;
				SetCtrlAttribute (panelHandle2, PANEL_MANU_PICTURE, ATTR_IMAGE_FILE, "pics/background/guitar-hero-boy.PNG");
			}
			break;
	}
	return 0;
}

int CVICALLBACK ChangeMode (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(creative==0)//yes
			{
				SetCtrlAttribute(panelHandle2,PANEL_MANU_CREATIVE,ATTR_LABEL_TEXT,"יצירה");
				creative=1;//no
			}
			else
			{
				SetCtrlAttribute(panelHandle2,PANEL_MANU_CREATIVE,ATTR_LABEL_TEXT,"משחק");
				creative=0;
			}
			break;
	}
	return 0;
}

int CVICALLBACK exit1 (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(panelHandle7);
			break;
	}
	return 0;
}

int CVICALLBACK openpdf (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			OpenDocumentInDefaultViewer ("additional_doc.pdf", VAL_NO_ZOOM);
			break;
	}
	return 0;
}

int CVICALLBACK about2 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DisplayPanel(panelHandle8);
			break;
	}
	return 0;
}

int CVICALLBACK exit9 (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(panelHandle8);
			break;
	}
	return 0;
}

int CVICALLBACK DREWHITE (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			SetCtrlAttribute (panelHandle2, PANEL_MANU_NAME, ATTR_TEXT_BGCOLOR, VAL_WHITE);
		break;
	}
	return 0;
}

int CVICALLBACK openvideo (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			OpenDocumentInDefaultViewer ("guitarherovideo.MP4", VAL_NO_ZOOM);
			break;
	}
	return 0;
}
