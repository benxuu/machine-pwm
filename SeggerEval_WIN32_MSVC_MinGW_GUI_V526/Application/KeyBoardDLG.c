/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.20                          *
*        Compiled Mar 19 2013, 15:01:00                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0   (GUI_ID_USER + 0x01)
#define ID_BUTTON_1   (GUI_ID_USER + 0x02)
#define ID_BUTTON_2   (GUI_ID_USER + 0x03)
#define ID_EDIT_0     (GUI_ID_USER + 0x04)
#define ID_BUTTON_3   (GUI_ID_USER + 0x06)
#define ID_BUTTON_4   (GUI_ID_USER + 0x07)
#define ID_BUTTON_5   (GUI_ID_USER + 0x08)
#define ID_BUTTON_6   (GUI_ID_USER + 0x09)
#define ID_BUTTON_7   (GUI_ID_USER + 0x0A)
#define ID_BUTTON_8   (GUI_ID_USER + 0x0B)
#define ID_BUTTON_9   (GUI_ID_USER + 0x0C)
#define ID_BUTTON_10  (GUI_ID_USER + 0x0D)
#define ID_BUTTON_11  (GUI_ID_USER + 0x0E)
#define ID_BUTTON_12  (GUI_ID_USER + 0x0F)
#define ID_BUTTON_13  (GUI_ID_USER + 0x10)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
	{ FRAMEWIN_CreateIndirect, "KeyBoard", ID_FRAMEWIN_0, 12, 9, 210, 300, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "abc",  ID_BUTTON_0, 75, 75, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "def",  ID_BUTTON_1, 140, 75, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "ghi",  ID_BUTTON_2, 10, 120, 50, 20, 0, 0x0, 0 },
	{ EDIT_CreateIndirect,   "Edit", ID_EDIT_0, 10, 25, 180, 20, 0, 0x64, 0 },
	{ BUTTON_CreateIndirect, "jkl",  ID_BUTTON_3, 75, 120, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "mno",  ID_BUTTON_4, 140, 120, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "pqrs", ID_BUTTON_5, 10, 170, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "tuv",  ID_BUTTON_6, 75, 170, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "wxyz", ID_BUTTON_7, 140, 170, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "1",    ID_BUTTON_8, 10, 75, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "123",  ID_BUTTON_9, 10, 220, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "0",    ID_BUTTON_10, 75, 220, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "A/a",  ID_BUTTON_11, 140, 220, 50, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "ok",   ID_BUTTON_12, 110, 255, 80, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "backspace", ID_BUTTON_13, 10, 255, 80, 20, 0, 0x0, 0 },
	// USER START (Optionally insert additional widgets)
	// USER END
};
/* 初始化输入字符数组 */
static   char charbuf[26]   = "abcdefghijklmnopqrstuvwxyz";
static   char CHARBUF[26]   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static   char numbuf[10]    = "1234567890";
static   int  keyboardflag  = 0;                                     /* 记录按键按下的次数 */
static   int  switch_flag   = 1;                                     /* 调节字母选择标志位，当第一次按按钮的时候置1，当确定输入值以后置0 */
static   int  keyboard_mode = 0;                                     /* 键盘模式调节：0为小写字母，1为大写字母，2为数字 */

WM_HWIN hedit;
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*
删除输入的字母
*/
void delete_word(){
	int     i = 0;
	char    buf[12];
	EDIT_GetText(hedit, buf, 12);
	while (buf[i] != '\0')
	{
		i++;
	}
	if (i <= 0)
	{
		i = 0;
		return;
	}
	buf[i - 1] = '\0';
	EDIT_SetText(hedit, buf);
}
/*
添加输入的字母
*/
void set_keyboard_input_word(int key){
	
	
	int     i = 0;
	char    buf[12];
	EDIT_GetText(hedit, buf, 12);
	while (buf[i] != '\0')
	{
		i++;
	}
	if (i == 10)
		return;
	if (switch_flag == 1){
		switch (keyboard_mode){
		case 0:
			buf[i] = charbuf[key - 1];
			break;
		case 1:
			buf[i] = CHARBUF[key - 1];
			break;
		case 2:
			buf[i] = numbuf[key - 1];
			break;
		default:
			break;
		}
	buf[i + 1] = '\0';
	EDIT_SetText(hedit, buf);
	switch_flag = 0;
	}
	else{
		i--;
		switch (keyboard_mode){
		case 0:
			buf[i] = charbuf[key - 1];
			break;
		case 1:
			buf[i] = CHARBUF[key - 1];
			break;
		case 2:
			buf[i] = numbuf[key - 1];
			break;
		default:
			break;
		}
		buf[i + 1] = '\0';
		EDIT_SetText(hedit, buf);
	}
}
/*小写字母模式 */
void m_charmode(WM_HWIN hwin){
	WM_HWIN but2 = WM_GetDialogItem(hwin, ID_BUTTON_0);
	WM_HWIN but3 = WM_GetDialogItem(hwin, ID_BUTTON_1);
	WM_HWIN but4 = WM_GetDialogItem(hwin, ID_BUTTON_2);
	WM_HWIN but5 = WM_GetDialogItem(hwin, ID_BUTTON_3);
	WM_HWIN but6 = WM_GetDialogItem(hwin, ID_BUTTON_4);
	WM_HWIN but7 = WM_GetDialogItem(hwin, ID_BUTTON_5);
	WM_HWIN but8 = WM_GetDialogItem(hwin, ID_BUTTON_6);
	WM_HWIN but9 = WM_GetDialogItem(hwin, ID_BUTTON_7);

	BUTTON_SetText(but2, "abc");
	BUTTON_SetText(but3, "def");
	BUTTON_SetText(but4, "ghi");
	BUTTON_SetText(but5, "jkl");
	BUTTON_SetText(but6, "mon");
	BUTTON_SetText(but7, "pqrs");
	BUTTON_SetText(but8, "tuv");
	BUTTON_SetText(but9, "wxyz");

}

/*大写字母模式 */
void b_charmode(WM_HWIN hwin){

	WM_HWIN but2 = WM_GetDialogItem(hwin, ID_BUTTON_0);
	WM_HWIN but3 = WM_GetDialogItem(hwin, ID_BUTTON_1);
	WM_HWIN but4 = WM_GetDialogItem(hwin, ID_BUTTON_2);
	WM_HWIN but5 = WM_GetDialogItem(hwin, ID_BUTTON_3);
	WM_HWIN but6 = WM_GetDialogItem(hwin, ID_BUTTON_4);
	WM_HWIN but7 = WM_GetDialogItem(hwin, ID_BUTTON_5);
	WM_HWIN but8 = WM_GetDialogItem(hwin, ID_BUTTON_6);
	WM_HWIN but9 = WM_GetDialogItem(hwin, ID_BUTTON_7);

	BUTTON_SetText(but2, "ABC");
	BUTTON_SetText(but3, "DEF");
	BUTTON_SetText(but4, "GHI");
	BUTTON_SetText(but5, "JKL");
	BUTTON_SetText(but6, "MNO");
	BUTTON_SetText(but7, "PQRS");
	BUTTON_SetText(but8, "TUV");
	BUTTON_SetText(but9, "WXYZ");
}

/*数字模式*/
void num_mode(WM_HWIN hwin){
	WM_HWIN but2 = WM_GetDialogItem(hwin, ID_BUTTON_0);
	WM_HWIN but3 = WM_GetDialogItem(hwin, ID_BUTTON_1);
	WM_HWIN but4 = WM_GetDialogItem(hwin, ID_BUTTON_2);
	WM_HWIN but5 = WM_GetDialogItem(hwin, ID_BUTTON_3);
	WM_HWIN but6 = WM_GetDialogItem(hwin, ID_BUTTON_4);
	WM_HWIN but7 = WM_GetDialogItem(hwin, ID_BUTTON_5);
	WM_HWIN but8 = WM_GetDialogItem(hwin, ID_BUTTON_6);
	WM_HWIN but9 = WM_GetDialogItem(hwin, ID_BUTTON_7);

	BUTTON_SetText(but2, "2");
	BUTTON_SetText(but3, "3");
	BUTTON_SetText(but4, "4");
	BUTTON_SetText(but5, "5");
	BUTTON_SetText(but6, "6");
	BUTTON_SetText(but7, "7");
	BUTTON_SetText(but8, "8");
	BUTTON_SetText(but9, "9");
}

/*
模式转换函数，转换键盘的输入模式
*/
void mode_change(WM_HWIN hwin){
	switch (keyboard_mode)
	{
	case 0:
		m_charmode(hwin);
		break;
	case 1:
		b_charmode(hwin);
		break;
	case 2:
		num_mode(hwin);
		break;
	default:
		break;
	}
}

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	int     i = 0;
	char    buf[12];
	int     beforeflag = 0;                                  /* 记录当一次keyboardflag的值 */
	int     NCode;
	int     Id;
	// USER START (Optionally insert additional variables)
	// USER END
	hedit = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_BUTTON_0: // Notifications sent by 'abc'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				//按键 2
				if (keyboard_mode != 2){
					/* 如果keyboardflag达到最大变量计数值则将其置为0*/
					if (keyboardflag == 3)
						keyboardflag = 0;

					/* 将keyboardflag变量自加1*/
					keyboardflag++;
					/*设置输入值 */
					set_keyboard_input_word(keyboardflag);

					/*如果0.5秒内keyboflag的值不变则输入值确定 */
					beforeflag = keyboardflag;
					GUI_Delay(500);
					if (beforeflag == keyboardflag)
					{
						switch_flag = 1;
						keyboardflag = 0;
					}
				}
				else{
					/*开启设置模式 */
					switch_flag = 1;
					set_keyboard_input_word(2);
					switch_flag = 0;
				}
				// USER START (Optionally insert code for reacting on notification message)
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
		case ID_BUTTON_1: // Notifications sent by 'def'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				if (keyboard_mode != 2){
					if (keyboardflag == 3)
						keyboardflag = 0;
					keyboardflag++;
					set_keyboard_input_word(keyboardflag + 3);
					beforeflag = keyboardflag;
					GUI_Delay(500);
					if (beforeflag == keyboardflag)
					{
						switch_flag = 1;
						keyboardflag = 0;
					}
				}
				else{
					/*开启设置模式 */
					switch_flag = 1;
					set_keyboard_input_word(3);
					switch_flag = 0;
				}
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_2: // Notifications sent by 'ghi'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				if (keyboard_mode != 2){
					if (keyboardflag == 3)
						keyboardflag = 0;
					keyboardflag++;
					set_keyboard_input_word(keyboardflag + 6);
					beforeflag = keyboardflag;
					GUI_Delay(500);
					if (beforeflag == keyboardflag)
					{
						switch_flag = 1;
						keyboardflag = 0;
					}
				}
				else
				{
					/*开启设置模式 */
					switch_flag = 1;
					set_keyboard_input_word(4);
					switch_flag = 0;
				}
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
		case ID_EDIT_0: // Notifications sent by 'Edit'
			switch (NCode) {
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
		case ID_BUTTON_3: // Notifications sent by 'jkl'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				if (keyboard_mode != 2){
					if (keyboardflag == 3)
						keyboardflag = 0;
					keyboardflag++;
					set_keyboard_input_word(keyboardflag + 9);
					beforeflag = keyboardflag;
					GUI_Delay(500);
					if (beforeflag == keyboardflag)
					{
						switch_flag = 1;
						keyboardflag = 0;
					}
				}
				else
				{
					/*开启设置模式 */
					switch_flag = 1;
					set_keyboard_input_word(5);
					switch_flag = 0;
				}
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
		case ID_BUTTON_4: // Notifications sent by 'mno'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				if (keyboard_mode != 2){
					if (keyboardflag == 3)
						keyboardflag = 0;
					keyboardflag++;
					set_keyboard_input_word(keyboardflag + 12);
					beforeflag = keyboardflag;
					GUI_Delay(500);
					if (beforeflag == keyboardflag)
					{
						switch_flag = 1;
						keyboardflag = 0;
					}
				}
				else
				{
					/*开启设置模式 */
					switch_flag = 1;
					set_keyboard_input_word(6);
					switch_flag = 0;
				}
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
		case ID_BUTTON_5: // Notifications sent by 'pqrs'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				if (keyboard_mode != 2){
					if (keyboardflag == 4)
						keyboardflag = 0;
					keyboardflag++;
					set_keyboard_input_word(keyboardflag + 15);
					beforeflag = keyboardflag;
					GUI_Delay(500);
					if (beforeflag == keyboardflag)
					{
						switch_flag = 1;
						keyboardflag = 0;
					}
				}
				else
				{
					/*开启设置模式 */
					switch_flag = 1;
					set_keyboard_input_word(7);
					switch_flag = 0;
				}
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
		case ID_BUTTON_6: // Notifications sent by 'tuv'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				if (keyboard_mode != 2){
					if (keyboardflag == 3)
						keyboardflag = 0;
					keyboardflag++;
					set_keyboard_input_word(keyboardflag + 19);
					beforeflag = keyboardflag;
					GUI_Delay(500);
					if (beforeflag == keyboardflag)
					{
						switch_flag = 1;
						keyboardflag = 0;
					}
				}
				else
				{
					/*开启设置模式 */
					switch_flag = 1;
					set_keyboard_input_word(8);
					switch_flag = 0;
				}
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
		case ID_BUTTON_7: // Notifications sent by 'wxyz'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				if (keyboard_mode != 2){
					if (keyboardflag == 4)
						keyboardflag = 0;
					keyboardflag++;
					set_keyboard_input_word(keyboardflag + 22);
					beforeflag = keyboardflag;
					GUI_Delay(500);
					if (beforeflag == keyboardflag)
					{
						switch_flag = 1;
						keyboardflag = 0;
					}
				}
				else
				{
					/*开启设置模式 */
					switch_flag = 1;
					set_keyboard_input_word(9);
					switch_flag = 0;
				}
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
		case ID_BUTTON_8: // Notifications sent by '1'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				/* 按键1 相应操作 */
				EDIT_GetText(hedit, buf, 12);

				/*获取显示字符的个数 */
				while (buf[i] != '\0')
				{
					i++;
				}
				/*如果大于等于10个字符则返回 */
				if (i >= 10)
				   return;
				/* 更新edit 显示 */
				buf[i] = '1';
				buf[i + 1] = '\0';
				EDIT_SetText(hedit, buf);
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
		case ID_BUTTON_9: // Notifications sent by '123'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				if (keyboard_mode != 2){
					keyboard_mode = 2;
					mode_change(pMsg->hWin);
				}
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
		case ID_BUTTON_10: // Notifications sent by '0'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				/*按键0相应操作 */
				EDIT_GetText(hedit, buf, 12);
				/* 获取显示的字符个数 */
				while (buf[i] != '\0')
				{
					i++;
				}
				/* 如果大于等于10个字符则返回 */
				if (i >= 10)
					return;
				buf[i] = '0';
				buf[i + 1] = '\0';
				EDIT_SetText(hedit, buf);
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
		case ID_BUTTON_11: // Notifications sent by 'A/a'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				if (keyboard_mode == 0)
					keyboard_mode = 1;
				else
					keyboard_mode = 0;

				mode_change(pMsg->hWin);
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
		case ID_BUTTON_12: // Notifications sent by 'ok'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
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
		case ID_BUTTON_13: // Notifications sent by 'backspace'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				/* 删除按键 */
				delete_word();

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
*       CreateKeyBoard
*/
WM_HWIN CreateKeyBoard(void);
WM_HWIN CreateKeyBoard(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
