procedure prodinf;

{ This procedure displays the product information screen }
{ Procedure was updated to OOP 6/9/90 by Robert Soule    }

var
  win      : WindowPtr;
  any_char : word;
  WinOpts  : Longint;

begin
  HideMouse;
  WinOpts := wBordered+wClear;
  ClrScr;
  New(win, InitCustom(2, 2, 79, 23, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Product Information ', heTC);
  win^.wFrame.AddHeader(' Press any Key or Mouse Button to Continue ', heBC);
  win^.Draw;


  { Display the product information }
  writeln;
  writeln('          "PK-TEACH" is a software product designed to be used with the ');
  writeln('          Marcraft Pro-Arm Educational Robot.  For information on how to');
  writeln('          order copies of the PK-TEACH software, or for information on');
  writeln('          how to order the Marcraft Pro-Arm Robot, or for technical ');
  writeln('          information on the Marcraft Pro-Arm Robot, contact');
  writeln;
  writeln;
  writeln('                    MARCRAFT INTERNATIONAL CORPORATION');
  writeln('                         100 North Morain Street');
  writeln('                       Kennewick, Washington 99336');
  writeln('                              (509) 783-7359');
  writeln;
  writeln;
  writeln('          "PK-TEACH" is another fine software product written and owned by ');
  writeln;
  writeln;
  writeln('                         PK Technologies, Inc.');
  writeln('                         44567 Pine Tree Drive');
  writeln('                         Plymouth, Michigan  48170');
  writeln('                         Phone : (313) 451-0970');
  writeln('                         Fax : (313) 451-2051');
  any_char := ReadKeyOrButton;

  win^.Erase;
  dispose(win,done);

end;
