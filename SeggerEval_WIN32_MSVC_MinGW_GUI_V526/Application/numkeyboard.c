static void _cbDialogKeyboard(WM_MESSAGE * pMsg) {
  GUI_RECT r;
  unsigned i;
  int     NCode;
  unsigned Id;
  int     Pressed;
  WM_HWIN hItem;
  WM_HWIN hDlg;

    Pressed = 0;
    hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
        case WM_PAINT:
        WM_GetClientRect(&r);
        GUI_SetColor(0x000000);
        GUI_DrawRect(r.x0, r.y0, r.x1, r.y1);
        GUI_SetColor(0xffffff);
        GUI_DrawHLine(r.y0 + 1, r.x0 + 1, r.x1 - 2);
        GUI_DrawVLine(r.x0 + 1, r.y0 + 1, r.y1 - 2);
        GUI_SetColor(0x555555);
        GUI_DrawHLine(r.y1-1, r.x0 + 1, r.x1 - 1);
        GUI_DrawVLine(r.x1-1, r.y0 + 1, r.y1 - 2);
        break;

        case WM_INIT_DIALOG:
            for (i = 0; i < GUI_COUNTOF(_aDialogKeyboard) - 1; i++) {
                hItem = WM_GetDialogItem(hDlg, GUI_ID_USER + i);
                BUTTON_SetFocussable(hItem, 0);

    }
    WM_GetDialogItem(hDlg, GUI_ID_USER + 12);      //Ê²Ã´ÒâË¼
    break;
        case WM_NOTIFY_PARENT:
        Id  = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch (NCode) {
            case WM_NOTIFICATION_CLICKED:
                Pressed = 1;
            case WM_NOTIFICATION_RELEASED:
                if ((Id >= GUI_ID_USER) && (Id <= (GUI_ID_USER + GUI_COUNTOF(_aDialogKeyboard) - 2))) {
        int Key;
        if (Id < GUI_ID_USER + 11) {
          char acBuffer[10];
          BUTTON_GetText(pMsg->hWinSrc, acBuffer, sizeof(acBuffer)); /* Get the text of the button */
          Key = acBuffer[0];
        }
        if (Id == GUI_ID_USER + 11) {
            Key = GUI_KEY_DELETE;
        }
        if (Id == GUI_ID_USER + 12) {
            Key = GUI_KEY_TAB;
        }
        GUI_SendKeyMsg(Key, Pressed);
      }
      if (Id == GUI_ID_USER + 13){
          WM_DeleteWindow(hDlg);
      }
      break;
    }
  default:
    WM_DefaultProc(pMsg);
  }
}



static void _cbDialogPZT(WM_MESSAGE * pMsg)
{
    int     i;
    int     NCode;
    int     Id;
    WM_HWIN hDlg;
    WM_HWIN hItem;


    hDlg = pMsg->hWin;
  switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
    FRAMEWIN_SetFont(hDlg,&GUI_Font24B_ASCII);
    FRAMEWIN_SetTextAlign(hDlg,GUI_TA_VCENTER|GUI_TA_CENTER);
    FRAMEWIN_AddCloseButton(hDlg, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_AddMaxButton(hDlg, FRAMEWIN_BUTTON_RIGHT, 1);
    FRAMEWIN_AddMinButton(hDlg, FRAMEWIN_BUTTON_RIGHT, 2);
    FRAMEWIN_SetTitleHeight(hDlg,30);
    for (i = 14; i < 30; i++) {
            EDIT_EnableBlink(WM_GetDialogItem(hDlg, GUI_ID_USER + i), 500, 1);
            hItem = WM_GetDialogItem(hDlg, GUI_ID_USER + i);
            EDIT_SetText(hItem, "");
        }
        break;
    case WM_NOTIFY_PARENT:
       Id = WM_GetId(pMsg->hWinSrc);
       NCode = pMsg->Data.v;
    switch (NCode) {
        case WM_NOTIFICATION_RELEASED:
            if ((Id >= GUI_ID_USER + 14) && (Id <= GUI_ID_USER + 29))  {
                Keyboard();
            }
            if (Id == GUI_ID_OK){
                WM_DeleteWindow(hDlg);
            }
            break;
    }
    break;
   default:
       WM_DefaultProc(pMsg);
    }
}
