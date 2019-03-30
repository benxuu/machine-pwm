/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2014  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.26 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIDEMO_Start.c
Purpose     : GUIDEMO initialization
----------------------------------------------------------------------
*/

#include "GUIDEMO.h"

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  #if GUI_WINSUPPORT
    WM_SetCreateFlags(WM_CF_MEMDEV);
  #endif
  WM_HWIN hNumPad;

  GUI_Init();

  #if GUI_WINSUPPORT
    WM_MULTIBUF_Enable(1);
  #endif
  //GUIDEMO_Main();
    CreatePWMControl(WM_HBKWIN); //创建窗体,父窗体是桌面背景

    WM_SetCallback(WM_HBKWIN, _cbDesktop);
  hNumPad = GUI_CreateDialogBox(_aDialogNumPad,
                                GUI_COUNTOF(_aDialogNumPad),
                                _cbDialogNumPad, WM_HBKWIN, 0, 0); /* Create the numpad dialog */
  WM_SetStayOnTop(hNumPad, 1);
    while(1) {
             GUI_ExecDialogBox(_aDialogUser,
                      GUI_COUNTOF(_aDialogUser),
                      _cbDialogUser, WM_HBKWIN, 0, 0);             /* Execute the user dialog */
            GUI_Delay(200);


    } //调用GUI_Delay函数延时20MS(最终目的是调用GUI_Exec()函数)


}

/*************************** End of file ****************************/

