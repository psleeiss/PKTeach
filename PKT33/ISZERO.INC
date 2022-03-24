function iszero : boolean;

{ This function displays a popup-menu and querries the user to find out if }
{ the robot has been "zeroed".  If yes, the function returns a TRUE value. }
{ Otherwise it will return with a value of FALSE. }

var
  win           : WindowPtr;
  any_char      : boolean;

  begin

    New(win, InitCustom(4, 3, 76, 22, MenuColors, wBordered+wClear));
    win^.setcursor(cuhidden);
    win^.wFrame.AddHeader(' Is the Robot in the ''ZERO'' position ', heTC);
    win^.Draw;

    writeln;
    writeln;
    writeln( ' Before continuing, you need to confirm that the robot is in the ');
    writeln(' "zero" position.  That is, all of the arrows on the robot''s base  ');
    writeln('  and arm should be aligned.  If this is true, you may proceed.  ');
    writeln('  if this is not the case, then you will want to return to the ');
    writeln('  Main Menu and select the [M] option so that you can move the');
    writeln('  robot back to it''s "zero" position.');
    writeln;
    writeln;
    write('       Is the robot in the ZERO position?');


    any_char := yorn;
    if any_char = true
     then iszero := true
      else iszero := false;

    win^.Erase;
    dispose(win,done);

end;