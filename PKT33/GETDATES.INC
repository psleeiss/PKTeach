procedure getdates( var year_str        : string;
                    var month_str       : string;
                    var day_str         : string;
                    var day_of_week_str : string);

{ This procedure returns the date as strings instead of words (Pascal GETDATE) }

var
  year           : word;
  month          : word;
  day            : word;
  day_of_week    : word;

begin

  { Get the system date }
  getdate(year,month,day,day_of_week);

  { Get the string for Year }
  str(year:4,year_str);

  { Get the string for the month }
  case month of
    1 : month_str := 'January';
    2 : month_str := 'February';
    3 : month_str := 'March';
    4 : month_str := 'April';
    5 : month_str := 'May';
    6 : month_str := 'June';
    7 : month_str := 'July';
    8 : month_str := 'August';
    9 : month_str := 'September';
    10: month_str := 'October';
    11: month_str := 'November';
    12: month_str := 'December';
    else month_str := 'Month error!!!';
  end;  { Case Statement }

  { Get the string for the day }
  str(day,day_str);
  if day < 10
  then day_str := '0' + day_str;

  { Get the string for day of week }
  case day_of_week of
    0: day_of_week_str := 'Sunday';
    1: day_of_week_str := 'Monday';
    2: day_of_week_str := 'Tuesday';
    3: day_of_week_str := 'Wednsday';
    4: day_of_week_str := 'Thursday';
    5: day_of_week_str := 'Friday';
    6: day_of_week_str := 'Saturday';
    else day_of_week_str := 'Day-of-week error!!!';
  end;   { Case statement }


end;