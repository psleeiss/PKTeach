procedure title;

{ Display the title screen }
const
  pk_version = 'version 3.3';

var
  any_key        : word;
  serial_num_str : string[20];
  dv, dm         : integer;
  ErrorCode      : integer;

begin
  dv := detect;
  if MouseInstalled then
    EnableEventHandling;
  { Convert serial number into a string we can display }
  str(everlock.get_serial_number,serial_num_str);

  initgraph(dv, dm, '');
  ErrorCode := GraphResult;
  if ErrorCode = grOk then
  begin
    setgraphmode(getmaxmode);
    SetBkColor(Blue);
    SetColor(Yellow);
    if dv > graph.cga
    then begin
      SetTextStyle(TriplexFont, Horizdir, 4);
      SetTextJustify(CenterText,TopText);
      SetUserCharSize(2,1,2,1);
      OutTextXY(Succ(GetMaxX) div 2,(GetMaxY div 2) - 180,'Marcraft');
      OutTextXY(Succ(GetMaxX) div 2,(GetMaxY div 2) - 125,'International');
      SetUserCharSize(1,1,1,1);
      OutTextXY(Succ(GetMaxX) div 2,(GetMaxY div 2) - 25,'Presents');
      SetColor(White);
      OutTextXY(Succ(GetMaxX) div 2,(GetMaxY div 2) + 50,
                'PK-TEACH ('+pk_version+')');
      SetColor(Yellow);
      SetTextStyle(SmallFont, Horizdir, 4);
      OutTextXY(Succ(GetMaxX) div 2,(GetMaxY div 2) + 120,
                'Copyright (C) 1991 by Inspired Software Solutions, Inc');
      OutTextXY(Succ(GetmaxX) div 2,(GetMaxY div 2) + 135,
                'All Rights Reserved');
      setusercharsize(5,4,5,4);
      OutTextXY(Succ(getmaxX) div 2,(GetMaxY div 2) + 160,
                'Serial # PKT'+serial_num_str);
    end
    else begin
      SetTextStyle(TriplexFont, Horizdir, 4);
      SetTextJustify(CenterText,TopText);
      SetUserCharSize(1,1,1,1);
      OutTextXY(Succ(GetMaxX) div 2,(GetMaxY div 2) - 100,'Marcraft');
      OutTextXY(Succ(GetMaxX) div 2,(GetMaxY div 2) - 70,'International');
      SetUserCharSize(1,2,1,2);
      OutTextXY(Succ(GetMaxX) div 2,(GetMaxY div 2) - 25,'Presents');
      SetColor(White);
      setusercharsize(1,1,1,1);
      OutTextXY(Succ(GetMaxX) div 2,(GetMaxY div 2) + 0,
                'PK-TEACH ('+pk_version+')');
      SetColor(Yellow);
      SetTextStyle(SmallFont, Horizdir, 4);
      OutTextXY(Succ(GetMaxX) div 2,(GetMaxY div 2) + 50,
                'Copyright (C) 1991 by Inspired Software Solutions, Inc');
      OutTextXY(Succ(GetmaxX) div 2,(GetMaxY div 2) + 70,
                'All Rights Reserved');
      OutTextXY(Succ(getmaxX) div 2,(GetMaxY div 2) + 90,
                'Serial # PKT'+serial_num_str);
    end;

    HiddenCursor;
    any_key := ReadKeyOrButton;

    CloseGraph;
    NormalCursor;
  end
  else
    title2;
end;


