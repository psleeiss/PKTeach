function openfile( var data_file : file;
                       create    : boolean) : boolean;

{ Function:         OPENFILE
{
{ Programmer:       Peter S. Lee                Date: Oct 2, 1987
{
{ Purpose:          To attempt to open a data file.
{
{ Input Parameters:
{    data_file      This is a file variable for the file to be openned.
{
{    create         If this flag is set to TRUE and the data_file cannot be
{                   openned, then this procedure will attempt to create the
{                   file.
{
{ Output Parameters:
{    opendata       The value of the function is TRUE only if the file was
{                   successfully openned.
}

begin
  {$I-}  { Disable I/O checking }
  reset(data_file);
  {$I+}

  if ioresult = 0
  then openfile := true
  else begin
    if create = true
    then begin
      {$I-}
      rewrite(data_file);
      {$I+}

      if ioresult = 0
      then openfile := true
      else openfile := false;
    end

    else openfile := false;
  end;

end;