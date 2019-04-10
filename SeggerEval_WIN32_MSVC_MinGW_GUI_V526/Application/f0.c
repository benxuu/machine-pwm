#include "DIALOG.h"

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
#define ID_TEXT_5            (GUI_ID_USER + 0x0F)
#define ID_TEXT_6            (GUI_ID_USER + 0x10)
#define ID_TEXT_7            (GUI_ID_USER + 0x11)
#define ID_TEXT_8            (GUI_ID_USER + 0x12)

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "PWMControl", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "tb_dianya", ID_EDIT_0, 130, 270, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "tb_dianliu", ID_EDIT_1, 130, 320, 80, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "voltage", ID_TEXT_0, 36, 275, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "current", ID_TEXT_1, 34, 319, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 380, 270, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 380, 320, 80, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "pulse width", ID_TEXT_2, 291, 326, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "frequency", ID_TEXT_3, 291, 267, 80, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "START", ID_BUTTON_0, 543, 187, 80, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "STOP", ID_BUTTON_1, 655, 189, 80, 30, 0, 0x0, 0 },
  { GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 0, 1, 500, 240, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 0, 431, 780, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 528, 49, 101, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "lbrv", ID_TEXT_6, 631, 47, 80, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_7, 523, 96, 90, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "lbrc", ID_TEXT_8, 625, 92, 80, 20, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

extern WM_HWIN hPage[4];

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
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
    //
    // Initialization of 'tb_dianya'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'tb_dianliu'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'voltage'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'current'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'pulse width'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'frequency'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'START'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, GUI_FONT_13_1);
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
    TEXT_SetText(hItem, "Real Voltage:");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'lbrv'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetText(hItem, "5.00");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetText(hItem, "Real Current:");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'lbrc'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetText(hItem, "2.00");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_EDIT_0: // Notifications sent by 'tb_dianya'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:

        // USER START (Optionally insert code for reacting on notification message)
        // USER END
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
        //WM_SetStayOnTop(hPage[1], 0);


        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
           WM_ShowWindow(hPage[1]);
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
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
          WM_ShowWindow(hPage[1]);
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

        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
         WM_ShowWindow(hPage[1]);

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

        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
          WM_HideWindow(hPage[1]);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
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


static void _cbBackGround(WM_MESSAGE* pMsg) {	//桌面背景的回调函数
	switch (pMsg->MsgId)
	{
	case WM_PAINT:	//窗口重绘消息,这个比较难说明白,反正在Framewin或Window窗体之中我们一般是用控
					//件,如果要在Framewin或Window窗体之中显示文字或绘制直线、矩形、圆等在这里实现
		GUI_SetBkColor(GUI_RED);				//设置背景颜色
		GUI_Clear();							//清屏
		break;
	default: WM_DefaultProc(pMsg); break;
	}
}

WM_HWIN CreatePWMControl(WM_HWIN hParent);
WM_HWIN CreatePWMControl(WM_HWIN hParent) {
	WM_HWIN hWin;
	WM_SetCallback(WM_HBKWIN, _cbBackGround);	//设置桌面背景的回调函数
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, hParent, 0, 0);
	return hWin;
}

//WM_HWIN CreatePWMControl(WM_HWIN hParent);
//WM_HWIN CreatePWMControl(WM_HWIN hParent) {
//  WM_HWIN hWin;
//WM_SetCallback(WM_HBKWIN, _cbBackGround);	//设置桌面背景的回调函数
//  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
//  return hWin;
//}
