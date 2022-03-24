procedure PKTmenu;

{*** sample test code follows ***}

var
  Status : Word;
  M      : Menu;      {menu system}

begin
  ClrScr;

  Status := InitMenu(M);
  if Status <> 0 then begin
    WriteLn('Error initializing menu: ', Status);
    Halt(1);
  end;

  {$IFDEF UseMouse}
  if MouseInstalled then
    with MenuColors do begin
      {activate mouse cursor}
      SoftMouseCursor($0000, (ColorMono(MouseColor, MouseMono) shl 8)+
                             Byte(MouseChar));
      ShowMouse;
      {enable mouse support}
      MenuCommands.cpOptionsOn(cpEnableMouse);
    end;
  {$ENDIF}

  M.Draw;
  M.Process;
  {Skeleton for menu choice handling}
  if M.GetLastCommand = ccSelect then
    case M.MenuChoice of
      miWrite1        : ;
      miEdit2         : ;
      miRun3          : ;
      miDelete4       : ;
      miMove5         : ;
      miTranslate8    : ;
      miDirectory9    : ;
      miProduct10     : ;
      miExit7         : ;
    end;
  M.Erase;
  WriteLn('Item ', M.MenuChoice);
  WriteLn('Command ', M.GetLastCommand);
  M.Done;

  {$IFDEF UseMouse}
  HideMouse;
  {$ENDIF}
 end;