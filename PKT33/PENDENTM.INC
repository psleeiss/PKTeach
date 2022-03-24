function pendentmode : boolean;

 var
   answer : boolean;
   win    : windowptr;

  begin
    hidemouse;
    New(win, InitCustom(3, 16, 39, 20, MenuColors, wBordered+wClear));
    win^.setcursor(cuhidden);
    win^.wFrame.AddHeader(' Press Left(Y) or Right(N) ', heBC);
    if not win^.IsActive then
    win^.Draw;

    gotoxy(4,2);
    write('Use the mouse as a pendent ?');
    answer := yorn;

    win^.Erase;
    dispose(win,done);

    if answer = true
     then pendentmode := true
       else pendentmode := false;

  end;

