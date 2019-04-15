#include "DIALOG.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys.h"
#include "pwm.h"
#include "ppower.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0            (GUI_ID_USER + 0x00)
#define ID_EDIT_0            (GUI_ID_USER + 0x01)
#define ID_EDIT_1            (GUI_ID_USER + 0x02)
#define ID_TEXT_0            (GUI_ID_USER + 0x03)
#define ID_TEXT_1            (GUI_ID_USER + 0x04)
#define ID_EDIT_2            (GUI_ID_USER + 0x05)
#define ID_EDIT_3            (GUI_ID_USER + 0x06)
#define ID_TEXT_2            (GUI_ID_USER + 0x07)
#define ID_TEXT_3            (GUI_ID_USER + 0x08)
#define ID_BUTTON_0            (GUI_ID_USER + 0x09)
#define ID_BUTTON_1            (GUI_ID_USER + 0x0A)
#define ID_GRAPH_0            (GUI_ID_USER + 0x0B)
#define ID_TEXT_4            (GUI_ID_USER + 0x0C)
#define ID_TEXT_5            (GUI_ID_USER + 0x0D)
#define ID_TEXT_6            (GUI_ID_USER + 0x0E)
#define ID_TEXT_7            (GUI_ID_USER + 0x0F)
#define ID_TEXT_8            (GUI_ID_USER + 0x10)
#define ID_HEADER_0            (GUI_ID_USER + 0x11)
#define ID_TEXT_9            (GUI_ID_USER + 0x12)
#define ID_BUTTON_2            (GUI_ID_USER + 0x13)
#define ID_BUTTON_3            (GUI_ID_USER + 0x14)
#define ID_BUTTON_4            (GUI_ID_USER + 0x15)
#define ID_BUTTON_5            (GUI_ID_USER + 0x16)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
static WM_HWIN hNumPad;
static WM_HWIN hWin;
static GRAPH_DATA_Handle  pdataV;
static GRAPH_DATA_Handle  pdataC;
extern u16 setV,setC,rtV,rtC;//电压、电流的设置值，当前实际值；
extern u8  PWM_CD;// Õ¼¿Õ±È
extern u16 PWM_fq;	// ÆµÂÊ
char * uimsg; ;//界显示面消息
char buf[4];
 
//WM_HWIN hedit;

// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "PWMControl", ID_FRAMEWIN_0, -2, 1, 800, 480, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "tb_dianya", ID_EDIT_0, 110, 325, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "tb_dianliu", ID_EDIT_1, 110, 375, 80, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "V (10mV):", ID_TEXT_0, 20, 327, 85, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "I (10mA):", ID_TEXT_1, 26, 383, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 334, 324, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 335, 375, 80, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "W(%):", ID_TEXT_2, 276, 376, 64, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "F(KHz):", ID_TEXT_3, 276, 327, 63, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "START", ID_BUTTON_0, 540, 339, 90, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "STOP", ID_BUTTON_1, 669, 340, 90, 50, 0, 0x0, 0 },
  { GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 10, 56, 480, 240, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 0, 436, 780, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 507, 117, 162, 29, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "lbrv", ID_TEXT_6, 665, 117, 80, 25, 0, 0x64, 0 },//电压显示
  { TEXT_CreateIndirect, "Text", ID_TEXT_7, 513, 171, 137, 27, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "lbrc", ID_TEXT_8, 667, 174, 80, 20, 0, 0x64, 0 },//电流显示
  { HEADER_CreateIndirect, "Header", ID_HEADER_0, 0, 0, 793, 44, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_9, 0, 0, 792, 40, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "setV", ID_BUTTON_2, 202, 331, 50, 25, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "setC", ID_BUTTON_3, 203, 379, 50, 25, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "setF", ID_BUTTON_4, 425, 328, 50, 25, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "setW", ID_BUTTON_5, 427, 378, 50, 25, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

#define MAX_VALUE	125

//int i=0;
/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  char buffer[4];
  int     NCode;
  int     Id;
//  	short Val;
	GRAPH_SCALE_Handle hScaleV;
	GRAPH_SCALE_Handle hScaleH;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'PWMControl'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetText(hItem, "PWM Control Panel");
    FRAMEWIN_SetTitleHeight(hItem, 20);
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    FRAMEWIN_SetTextColor(hItem, 0x00000000);
    FRAMEWIN_SetFont(hItem, GUI_FONT_20_1);
    FRAMEWIN_SetTitleVis(hItem, 0);
    //
    // Initialization of 'tb_dianya'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'tb_dianliu'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'V (10mV):'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'I (10mA):'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'W(us):'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'F(Hz):'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'START'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
    //
    // Initialization of 'STOP'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetText(hItem, "Copyright: Anhui omach technology co. LTD, 2019-2029");
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_13B_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetText(hItem, "RT V (10mV):");
    TEXT_SetFont(hItem, GUI_FONT_24_1);
    TEXT_SetTextColor(hItem, GUI_GREEN);
    //
    // Initialization of 'lbrv'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetText(hItem, "5.00");
    TEXT_SetFont(hItem, GUI_FONT_24_1);
     TEXT_SetTextColor(hItem, GUI_GREEN);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetText(hItem, "RT C (10mA):");
    TEXT_SetFont(hItem, GUI_FONT_24_1);
    TEXT_SetTextColor(hItem, GUI_RED);
    //
    // Initialization of 'lbrc'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetText(hItem, "2.00");
    TEXT_SetFont(hItem, GUI_FONT_24_1);
     TEXT_SetTextColor(hItem, GUI_RED);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetText(hItem, "PWM Power Control");
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextColor(hItem, 0x00804000);
    //
    // Initialization of 'setV'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'setI'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'setF'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'setW'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    //
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
   hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		GRAPH_SetBorder(hItem, 40, 5, 5, 5);//边框
		GRAPH_SetGridVis(hItem, 1);//启用网格
		GRAPH_SetGridFixedX(hItem, 1);//固定方向网格
		GRAPH_SetGridDistY(hItem, 25);//网格间距
		GRAPH_SetGridDistX(hItem, 50);
		GRAPH_SetVSizeX(hItem, 400);//x范围
		GRAPH_SetVSizeY(hItem, 11);//y范围
		hScaleV = GRAPH_SCALE_Create(30, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 20);//创建和增加垂直范围尺度标签
		GRAPH_SCALE_SetTextColor(hScaleV, GUI_RED);									//设置标签字体颜色
		 GRAPH_SCALE_SetFactor(hScaleV,0.05);//像素到刻度的计算因子
		GRAPH_AttachScale(hItem, hScaleV);
													//将标签添加到垂直方向
		hScaleH = GRAPH_SCALE_Create(225, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 50);	//创建和增加水平范围尺度标签
		GRAPH_SCALE_SetTextColor(hScaleH, GUI_DARKGREEN);							//设置字体颜色
		GRAPH_AttachScale(hItem, hScaleH);											//添加到水平方向

		pdataC = GRAPH_DATA_YT_Create(GUI_RED, 500/*最大数据个数*/, 0, 0);		//创建一个数据曲线,可创建多个曲线
		GRAPH_AttachData(hItem, pdataC);	 //为绘图控件添加数据对象
		pdataV = GRAPH_DATA_YT_Create(GUI_GREEN, 500/*最大数据个数*/, 0, 0);		//创建一个数据曲线,可创建多个曲线
		GRAPH_AttachData(hItem, pdataV);	 //为绘图控件添加数据对象

		break;

case WM_TIMER://定时器消息(定时到时程序跑到这里)
		WM_RestartTimer(pMsg->Data.v, 500);
		//if(WM_IsCompletelyCovered(pMsg->hWin)) break;		//当切换到其他页面什么都不做

 
//设置实时电压、电流标签数据刷新
				sprintf(buf,  "%4d", rtC);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);				
       TEXT_SetText(hItem,  buf);

			sprintf(buf,  "%4d", rtV);
       hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6); 
			TEXT_SetText(hItem,  buf);

//设置实时电压、电流曲线数据刷新
		 GRAPH_DATA_YT_AddValue(pdataV, (I16)rtV);		//赋值到曲线
		 GRAPH_DATA_YT_AddValue(pdataC, (I16)rtC);		//赋值到曲线
		break;

  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;

    //先判断消息类型
  switch (NCode) {
    case WM_NOTIFICATION_CLICKED:
     // Pressed = 1;
     //弹出键盘
     if(Id<=ID_EDIT_3){
            WM_ShowWindow(hNumPad);
            WM_SetStayOnTop(hNumPad, 1);
						WM_BringToTop(hNumPad);
					}
     break;
    case WM_NOTIFICATION_RELEASED:
//      if ((Id >= GUI_ID_USER) && (Id <= (GUI_ID_USER + GUI_COUNTOF(_aDialogNumPad) - 1))) {
//        int Key;
//        if (Id < GUI_ID_USER + 11) {
//          char acBuffer[10];
//          BUTTON_GetText(pMsg->hWinSrc, acBuffer, sizeof(acBuffer)); /* Get the text of the button */
//          Key = acBuffer[0];
//        } else {
//          Key = _aKey[Id - GUI_ID_USER - 11];                        /* Get the text from the array */
//        }
//        GUI_SendKeyMsg(Key, Pressed);                                /* Send a key message to the focussed window */
//      }
      break;
    }
  //

    switch(Id) {
    case ID_EDIT_0: // Notifications sent by 'tb_dianya'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END

        //WM_BringToTop(hNumPad);


        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_1: // Notifications sent by 'tb_dianliu'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
         // WM_BringToTop(hNumPad);
         //WM_SetStayOnTop(hNumPad, 1);
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_2: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        //WM_SetStayOnTop(hNumPad, 1);
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_3: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        //WM_SetStayOnTop(hNumPad, 1);
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'START'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
			power_start();//开机，电源输出
 
        // USER END
 
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
 
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'STOP'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        	power_shutdown();//开机，电源输出
 
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
 
         
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_HEADER_0: // Notifications sent by 'Header'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'setV'设定电压
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
          hItem=WM_GetDialogItem(hWin,ID_EDIT_0);//获取设定电压值
					EDIT_GetText(hItem,buffer,4);        
						setV=atoi(buffer);
					power_setV(setV);
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)

        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
   case ID_BUTTON_3: // Notifications sent by 'setI'设定电流
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem=WM_GetDialogItem(hWin,ID_EDIT_1);//获取设定电压值
        EDIT_GetText(hItem,buffer,4);
        setC= atoi(buffer);
				power_setC(setC);
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)

        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
        case ID_BUTTON_4: // Notifications sent by 'setF'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem=WM_GetDialogItem(hWin,ID_EDIT_2);//获取设定频率值
        EDIT_GetText(hItem,buffer,4);
        PWM_fq= atoi(buffer);
				PWM_Init_fq(PWM_fq);
			
			
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)

        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
        case ID_BUTTON_5: // Notifications sent by 'setW'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem=WM_GetDialogItem(hWin,ID_EDIT_3);//获取设定占空比值
        EDIT_GetText(hItem,buffer,4);
        PWM_CD= atoi(buffer);
				PWM_SET_CD(PWM_CD);//设置占空比
			
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)

        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;

      // USER START (Optionally insert additional code for further notification handling)
      // USER END



  //    break;

    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreatePWMControl
*/
WM_HWIN CreatePWMControl(void);
WM_HWIN CreatePWMControl(void) {
  //WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  WM_CreateTimer(WM_GetClientWindow(hWin), 1, 300, 0); //创建一个软件定时器
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END


//
// Bitmap data for arrow keys
//
static GUI_CONST_STORAGE GUI_COLOR _aColorsArrow[] = {
  0xFFFFFF, 0x000000
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalArrow = {
  2,	/* number of entries */
  1, 	/* No transparency */
  &_aColorsArrow[0]
};

static GUI_CONST_STORAGE unsigned char _acArrowRight[] = {
  ____XX__, ________,
  ____XXXX, ________,
  XXXXXXXX, XX______,
  ____XXXX, ________,
  ____XX__, ________
};

static GUI_CONST_STORAGE unsigned char _acArrowLeft[] = {
  ____XX__, ________,
  __XXXX__, ________,
  XXXXXXXX, XX______,
  __XXXX__, ________,
  ____XX__, ________
};

static GUI_CONST_STORAGE GUI_BITMAP _bmArrowRight = {
  10,            /* XSize */
  5,             /* YSize */
  2,             /* BytesPerLine */
  1,             /* BitsPerPixel */
  _acArrowRight, /* Pointer to picture data (indices) */
  &_PalArrow     /* Pointer to palette */
};

static GUI_CONST_STORAGE GUI_BITMAP _bmArrowLeft = {
  10,            /* XSize */
  5,             /* YSize */
  2,             /* BytesPerLine */
  1,             /* BitsPerPixel */
  _acArrowLeft,  /* Pointer to picture data (indices) */
  &_PalArrow     /* Pointer to palette */
};
//
// Array of keys
//
static int _aKey[] = {GUI_KEY_DELETE, GUI_KEY_TAB, GUI_KEY_LEFT, GUI_KEY_RIGHT,GUI_KEY_BACKSPACE,GUI_KEY_ENTER};

//
// Dialog resource of numpad
//
static const GUI_WIDGET_CREATE_INFO _aDialogNumPad[] = {
//
//  Function                 Text      Id                 Px   Py   Dx   Dy
//
  { WINDOW_CreateIndirect,   0,        0,                225, 110,  125, 130},
  { BUTTON_CreateIndirect,   "7",      GUI_ID_USER +  7,   5,   5,  25,  20},
  { BUTTON_CreateIndirect,   "8",      GUI_ID_USER +  8,  35,   5,  25,  20},
  { BUTTON_CreateIndirect,   "9",      GUI_ID_USER +  9,  65,   5,  25,  20},
   { BUTTON_CreateIndirect,   "Bak",    GUI_ID_USER +  15,  95,   5,  25,  45},
  { BUTTON_CreateIndirect,   "4",      GUI_ID_USER +  4,   5,  30,  25,  20},
  { BUTTON_CreateIndirect,   "5",      GUI_ID_USER +  5,  35,  30,  25,  20},
  { BUTTON_CreateIndirect,   "6",      GUI_ID_USER +  6,  65,  30,  25,  20},
  { BUTTON_CreateIndirect,   "1",      GUI_ID_USER +  1,   5,  55,  25,  20},
  { BUTTON_CreateIndirect,   "2",      GUI_ID_USER +  2,  35,  55,  25,  20},
  { BUTTON_CreateIndirect,   "3",      GUI_ID_USER +  3,  65,  55,  25,  20},
  { BUTTON_CreateIndirect,   "0",      GUI_ID_USER +  0,   5,  80,  25,  20},
  { BUTTON_CreateIndirect,   ".",      GUI_ID_USER + 10,  35,  80,  25,  20},
  { BUTTON_CreateIndirect,   "Del",    GUI_ID_USER + 11,  65,  80,  25,  20},
  { BUTTON_CreateIndirect,   "Tab",    GUI_ID_USER + 12,   5, 105,  25,  20},
  { BUTTON_CreateIndirect,   0,        GUI_ID_USER + 13,  35, 105,  25,  20},
  { BUTTON_CreateIndirect,   0,        GUI_ID_USER + 14,  65, 105,  25,  20},

   { BUTTON_CreateIndirect,   "Ent",    GUI_ID_USER +  16,  95,   85,  25,  30},
   { BUTTON_CreateIndirect,   "ESC",    GUI_ID_USER +  17,  95,   50,  25,  30},
};

//
// Dialog resource of user dialog
//


//
// Title of sample
//
//static char _aTitle[] = {"WIDGET_NumPad"};


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbDialogNumPad
*
* Function description
*   Callback function of the numpad.
*/
static void _cbDialogNumPad(WM_MESSAGE * pMsg) {
  GUI_RECT r;
  unsigned i;
  int      NCode;
  unsigned Id;
  int      Pressed;
  WM_HWIN  hDlg;
  WM_HWIN  hItem;

  Pressed = 0;
  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    WM_GetClientRect(&r);
    GUI_SetColor(0x000000);
    GUI_DrawRect(r.x0, r.y0, r.x1, r.y1);          /* Draw rectangle around it */
    /* Draw the bright sides */
    GUI_SetColor(0xffffff);
    GUI_DrawHLine(r.y0 + 1, r.x0 + 1, r.x1 - 2);   /* Draw top line */
    GUI_DrawVLine(r.x0 + 1, r.y0 + 1, r.y1 - 2);
    /* Draw the dark sides */
    GUI_SetColor(0x555555);
    GUI_DrawHLine(r.y1-1, r.x0 + 1, r.x1 - 1);
    GUI_DrawVLine(r.x1-1, r.y0 + 1, r.y1 - 2);
    break;
  case WM_INIT_DIALOG:
    for (i = 0; i < GUI_COUNTOF(_aDialogNumPad) - 1; i++) {
      hItem = WM_GetDialogItem(hDlg, GUI_ID_USER + i);
      BUTTON_SetFocussable(hItem, 0);                       /* Set all buttons non focussable */
      switch (i) {
      case 13:
        BUTTON_SetBitmapEx(hItem, 0, &_bmArrowLeft, 7, 7);  /* Set bitmap for arrow left button (unpressed) */
        BUTTON_SetBitmapEx(hItem, 1, &_bmArrowLeft, 7, 7);  /* Set bitmap for arrow left button (pressed) */
        break;
      case 14:
        BUTTON_SetBitmapEx(hItem, 0, &_bmArrowRight, 7, 7); /* Set bitmap for arrow right button (unpressed) */
        BUTTON_SetBitmapEx(hItem, 1, &_bmArrowRight, 7, 7); /* Set bitmap for arrow right button (pressed) */
        break;
      }
    }
    WM_GetDialogItem(hDlg, GUI_ID_USER + 12);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
    NCode = pMsg->Data.v;                 /* Notification code */
    switch (NCode) {
    case WM_NOTIFICATION_CLICKED:
      Pressed = 1;
    case WM_NOTIFICATION_RELEASED:
        if(Id == GUI_ID_USER + 17){//hide the hnum，ESC
            WM_HideWindow(hNumPad);
            break;
        }
      if ((Id >= GUI_ID_USER) && (Id <= (GUI_ID_USER + GUI_COUNTOF(_aDialogNumPad) - 1))) {
        int Key;
        if (Id < GUI_ID_USER + 11) {
          char acBuffer[10];
          BUTTON_GetText(pMsg->hWinSrc, acBuffer, sizeof(acBuffer)); /* Get the text of the button */
          Key = acBuffer[0];
        } else {
          Key = _aKey[Id - GUI_ID_USER - 11];                        /* Get the text from the array */
        }
        GUI_SendKeyMsg(Key, Pressed);                                /* Send a key message to the focussed window */
      }
      break;
    }
  default:
    WM_DefaultProc(pMsg);
  }
}



/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/

void CreateUI(void){
hWin=CreatePWMControl();
hNumPad = GUI_CreateDialogBox(_aDialogNumPad,
                                GUI_COUNTOF(_aDialogNumPad),
                                _cbDialogNumPad, WM_HBKWIN, 300, 200); /* Create the numpad dialog */
 WM_HideWindow(hNumPad);

}

//void MainTask(void) {


//  GUI_Init();
//   GUI_SetBkColor(GUI_RED);
// // WM_SetCallback(WM_HBKWIN, _cbDesktop);

// // hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
//  hWin=CreatePWMControl();
//  hNumPad = GUI_CreateDialogBox(_aDialogNumPad,
//                                GUI_COUNTOF(_aDialogNumPad),
//                                _cbDialogNumPad, WM_HBKWIN, 300, 200); /* Create the numpad dialog */
// WM_HideWindow(hNumPad);
//  //WM_SetStayOnTop(hNumPad, 0);//0,clear setting，1，set keep on top
//  while (1) {
//       // GUI_ExecDialogBox(hWin);
////    GUI_ExecDialogBox(_aDialogCreate,
////                      GUI_COUNTOF(_aDialogCreate),
////                      _cbDialog, WM_HBKWIN, 0, 0);             /* Execute the user dialog */
//    GUI_Delay(50);
//  }
//}


