{$F+}
unit filing;

{ This unit is used to provide the filing system for the PKTEACH program }

interface
uses dos,OpString,opcrt,misc{,everlock};

{ Include file declares }
{$I robofile.inc}

var
  file_ascii : text;          { File for command translation }

  top_ptr    : pk_ptr;        { Variables to hold a single mem-res command }
  cur_ptr    : pk_ptr;


{ This procedure writes the memory_resident linked-list to the file }
procedure filestor( var the_file : pk_file);

{ This function loads a file of commands into memory. }
procedure fileld( var the_file : pk_file );

{ This procedure clears the memory-resident linked list of commands }
procedure lstclear;

{ This procedure deletes an item out of the memory-resident linked list }
procedure lstdel;

{ This procedure inserts a command into the command list. }
procedure lstins( temp_ptr : pk_ptr);

{ This function moves cur_ptr forward one command in the linked list.  If
{ we are at the end of the list (which includes having an empty list), then
{ the function will return a value of FALSE.  Otherwise, it returns TRUE. }
function lstnext : boolean;

{ This function is used to move the cur_ptr to the previous command in the
{ mem-resident linked list.  If the list is empty or if we are at the top
{ of the list, the function returns a value of FALSE.  Otherwise it will
{ return a value of TRUE.                                      }
function lstprev : boolean;

{ Function:         PKOPEN
{
{ Programmer:       Peter S. Lee                Date: Oct 18, 1988
{
{ Purpose:          To attempt to open a pk_data file.
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
function pkopen( var data_file : pk_file;
                     create    : boolean) : boolean;




implementation

{$I pkopen.inc}
{$I filebe.inc}
{$I filestor.inc}
{$I fileld.inc}
{$I lstclear.inc}
{$I lstdel.inc}
{$I lstins.inc}
{$I lstprev.inc}
{$I lstnext.inc}


begin
  cur_ptr := nil;
  top_ptr := nil;

end.