/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  ABOUT                            1
#define  ABOUT_PICTURE                    2       /* control type: picture, callback function: (none) */
#define  ABOUT_COMMANDBUTTON_3            3       /* control type: command, callback function: exit1 */

#define  HowToPLAY                        2
#define  HowToPLAY_STOPPER                2       /* control type: numeric, callback function: (none) */
#define  HowToPLAY_STRING_2               3       /* control type: string, callback function: (none) */
#define  HowToPLAY_STRING                 4       /* control type: string, callback function: (none) */
#define  HowToPLAY_PICTURE                5       /* control type: picture, callback function: (none) */

#define  MANURETURN                       3
#define  MANURETURN_COMMANDBUTTON         2       /* control type: command, callback function: Return */
#define  MANURETURN_TEXT                  3       /* control type: string, callback function: (none) */

#define  PANEL                            4       /* callback function: Exit */
#define  PANEL_CANVAS                     2       /* control type: canvas, callback function: (none) */
#define  PANEL_arrow1                     3       /* control type: command, callback function: arrow1_run */
#define  PANEL_arrow2                     4       /* control type: command, callback function: arrow2_run */
#define  PANEL_arrow3                     5       /* control type: command, callback function: arrow3_run */
#define  PANEL_arrow4                     6       /* control type: command, callback function: arrow4_run */
#define  PANEL_NAME                       7       /* control type: string, callback function: (none) */
#define  PANEL_SCORE                      8       /* control type: numeric, callback function: (none) */
#define  PANEL_RETURN_BOT                 9       /* control type: command, callback function: Return */
#define  PANEL_SONG_NAME                  10      /* control type: string, callback function: (none) */
#define  PANEL_Clock_5                    11      /* control type: numeric, callback function: (none) */
#define  PANEL_Clock_4                    12      /* control type: numeric, callback function: (none) */
#define  PANEL_Clock_3                    13      /* control type: numeric, callback function: (none) */
#define  PANEL_Clock_2                    14      /* control type: numeric, callback function: (none) */
#define  PANEL_Clock                      15      /* control type: numeric, callback function: (none) */
#define  PANEL_DIS                        16      /* control type: string, callback function: (none) */
#define  PANEL_LEVEL_NAME                 17      /* control type: string, callback function: (none) */
#define  PANEL_TIMER                      18      /* control type: timer, callback function: Time */
#define  PANEL_PICTURE_2                  19      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE                    20      /* control type: picture, callback function: (none) */
#define  PANEL_INSTRUMENT                 21      /* control type: command, callback function: changeins */
#define  PANEL_body                       22      /* control type: canvas, callback function: (none) */
#define  PANEL_face                       23      /* control type: canvas, callback function: (none) */

#define  PANEL_2                          5       /* callback function: EXIT2 */
#define  PANEL_2_WINNERS                  2       /* control type: table, callback function: (none) */
#define  PANEL_2_PICTURE_3                3       /* control type: picture, callback function: (none) */

#define  PANEL_3                          6
#define  PANEL_3_COMMANDBUTTON_3          2       /* control type: command, callback function: exit9 */
#define  PANEL_3_PICTURE                  3       /* control type: picture, callback function: (none) */

#define  PANEL_4                          7
#define  PANEL_4_PICTURE                  2       /* control type: picture, callback function: (none) */

#define  PANEL_MANU                       8       /* callback function: EXIT */
#define  PANEL_MANU_NAME                  2       /* control type: string, callback function: DREWHITE */
#define  PANEL_MANU_CREATIVE              3       /* control type: command, callback function: ChangeMode */
#define  PANEL_MANU_BG                    4       /* control type: command, callback function: changeGEN */
#define  PANEL_MANU_STOP_MUS              5       /* control type: command, callback function: STOP_MUSIC */
#define  PANEL_MANU_RUN_BOT               6       /* control type: command, callback function: RUN */
#define  PANEL_MANU_RINGSLIDE             7       /* control type: slide, callback function: (none) */
#define  PANEL_MANU_SONGS                 8       /* control type: listBox, callback function: (none) */
#define  PANEL_MANU_COMMANDBUTTON_2       9       /* control type: command, callback function: EXIT1 */
#define  PANEL_MANU_COMMANDBUTTON_4       10      /* control type: command, callback function: openvideo */
#define  PANEL_MANU_COMMANDBUTTON_3       11      /* control type: command, callback function: openpdf */
#define  PANEL_MANU_ABOUTI_2              12      /* control type: command, callback function: about2 */
#define  PANEL_MANU_ABOUTI                13      /* control type: command, callback function: about */
#define  PANEL_MANU_WINNERSS              14      /* control type: command, callback function: WINNERoP */
#define  PANEL_MANU_LOAD                  15      /* control type: command, callback function: Load */
#define  PANEL_MANU_PICTURE               16      /* control type: pictButton, callback function: (none) */

#define  StartType                        9
#define  StartType_Stopper2               2       /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK about(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK about2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK arrow1_run(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK arrow2_run(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK arrow3_run(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK arrow4_run(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK changeGEN(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK changeins(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChangeMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DREWHITE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EXIT(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exit1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EXIT2(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exit9(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK openpdf(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK openvideo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Return(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RUN(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK STOP_MUSIC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Time(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WINNERoP(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif