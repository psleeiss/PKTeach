function opentext( var text_file : text;
                       create    : boolean) : boolean;

{ Function:         OPENTEXT
{
{ Programmer:       Peter S. Lee                Date: Oct 2, 1987
{
{ Purpose:          To attempt to open a text file.
{
{ Input Parameters:
{    text_file      This is a file variable for the file to be openned.
{
{    create         If this flag is set to TRUE and the text_file cannot be
{                   openned, then this procedure will attempt to create the
{                   file.
{
{ Output Parameters:
{    opendata       The value of the function is TRUE only if the file was
{                   successfully openned.
}

begin
  {$I-}  { Disable I/O checking }
  reset(text_file);
  {$I+}

  if ioresult = 0
  then opentext := true
  else begin
    if create = true
    then begin
      {$I-}
      rewrite(text_file);
      {$I+}

      if ioresult = 0
      then opentext := true
      else opentext := false;
    end

    else opentext := false;
  end;

end;