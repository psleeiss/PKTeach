unit everobj;    { Version 1.1   2/27/91 }

{$A-,B-,D-,E-,F+,I+,L-,N-,O-,R-,S-,V-}

{ This unit defines the everlock object for use in copy-protected programs }

interface

const
  verify_drive_only                            = 0;
  verify_name_drive                            = 1;
  verify_name_evserial_drive                   = 2;
  verify_name_evserial_progserial_drive        = 3;
  verify_name_drive_incexe                     = 11;
  verify_name_evserial_drive_incexe            = 12;
  verify_name_evserial_progserial_drive_incexe = 13;

  no_execute_cost                              = 0;

  EVCHK_memory_needed                          = 16400;
  not_enough_memory_error                      = -9999;
  invalid_scb_error                            = 7240;
  passed_protection_check                      = 0;

  my_evserial                                  = 013552;

type

  string15 = string[15];

  protection_mode_type = (protected_program,unprotected_program);

  { The SCB_block is the pascal definition of the structure required by }
  { Aztec software's EVERLOCK program (especially EVCHK.OBJ).           }
  SCB_block_ptr = ^SCB_block;
  SCB_block = record
    id                     : array[1..4] of char;
    ret_code               : integer;
    function_code          : byte;  { Specify level of security check }
    check_drive            : char;  { Drive to check }
    protect_type           : char;  { Protection type }
    prog_name              : array[1..13] of char;  { ASCIIZ format }
    serial_num             : longint;
    everlock_serial_number : longint;
    execute_count_left     : integer;
    execute_days_left      : integer;
    execute_expire_date    : array[1..9] of char;  { ASCIIZ string }
    reserved_1             : char;
    current_install_count  : byte;
    max_install_count      : byte;
    reserved_2             : array[1..7] of char;
    ptr_file_path          : array[1..11] of char; { Directory for ptr file }
    reserved_3             : array[1..10] of char;
    ptr_offset             : word;    { 16K buffer pointer offest }
    ptr_segment            : word;    { 16k buffer pointer segment address }
    ptr_use_flag           : char;    { Use buffer flag.  Must be "Y" or "N" }
    reserved_4             : char;
   end;

  { Your basic everlock object }
  everlock_obj = object
    SCB_ptr         : SCB_block_ptr;
    protection_mode : protection_mode_type;

    { Methods for this madness }
    constructor init(in_protection_mode        : protection_mode_type;
                     in_prog_name              : string15);
    destructor  done;
    procedure   set_check_type(in_func_code : byte);
    procedure   set_protection_mode(in_protection_mode : protection_mode_type);
    procedure   set_check_drive( in_drive   : char);
    function    get_serial_number           : longint;
    function    get_current_install_count   : byte;
    function    get_last_result             : integer;
    function    get_protection_mode         : protection_mode_type;
    function    check_copy_protection       : integer;
  end;

var
  everlock : everlock_obj;  { A ready-to-use everlock object }

implementation

{ Set ID String plus serial number for non-copy protected versions }
const
  my_id_string_var                 : string[13] = 'Snuggle Bunny';
  non_copy_protected_serial_number : longint    = 1000000123;


{ Define the EVCHK object file }
procedure evchk(sibptr : pointer); {external;}
begin
end;
procedure _evchk(sibptr : pointer); {external;}
begin
end;
{.$L evchk.obj}

constructor everlock_obj.init(in_protection_mode : protection_mode_type;
                              in_prog_name       : string15);
var
  count : integer;
begin
  protection_mode := in_protection_mode;
  if protection_mode = unprotected_program
  then begin
    scb_ptr := nil;
    exit;
  end;

  new(SCB_ptr);

  with scb_ptr^
  do begin
    id[1]                  := 'A';
    id[2]                  := 'Z';
    id[3]                  := 'E';
    id[4]                  := 'V';
    ret_code               := invalid_scb_error;
    function_code          := verify_name_evserial_drive;
    check_drive            := '@';    { Current drive }
    protect_type           := 'P';    { I don't know what this is! }

    { Transfer program name to character array }
    if length(in_prog_name) < sizeof(prog_name)
    then for count := 1 to length(in_prog_name) + 1
         do if count = length(in_prog_name) + 1
            then prog_name[count] := #0
            else prog_name[count] := upcase(in_prog_name[count]);

    serial_num             := 0;
    everlock_serial_number := my_evserial;
    execute_count_left     := no_execute_cost;
    execute_days_left      := 0;
    ptr_file_path [1]      := '\';
    ptr_file_path [2]      := #0;
    ptr_offset             := 0;
    ptr_segment            := 0;
    ptr_use_flag           := 'Y';
  end;
end;

destructor everlock_obj.done;
begin
  if protection_mode = unprotected_program
  then exit;
  dispose(scb_ptr);
end;

{ This procedure sets the type of protection check to be made }
procedure everlock_obj.set_check_type(in_func_code : byte);
begin
  scb_ptr^.function_code := in_func_code;
end;

{ This procedure sets the protection mode (protected or unprotected program }
procedure everlock_obj.set_protection_mode(in_protection_mode : protection_mode_type);
begin
  protection_mode:= in_protection_mode;
end;

{ Sets the drive to check for protection on.  "@" means current drive }
procedure everlock_obj.set_check_drive(in_drive : char);
begin
  scb_ptr^.check_drive := in_drive;
end;

function everlock_obj.get_serial_number : longint;
begin
  if protection_mode= protected_program
  then get_serial_number := scb_ptr^.serial_num
  else get_serial_number := non_copy_protected_serial_number;
end;

function everlock_obj.get_current_install_count : byte;
begin
  if protection_mode = protected_program
  then get_current_install_count := scb_ptr^.current_install_count
  else get_current_install_count := 255;
end;

{ Returns the last return code generated by a call to check_copy_protection }
function everlock_obj.get_last_result : integer;
begin
  get_last_result := scb_ptr^.ret_code;
end;

function everlock_obj.get_protection_mode : protection_mode_type;
begin
  get_protection_mode := protection_mode;
end;

{ This function calls the EVCHK external (assembly) program to check }
{ copy protection.  Note that there is much "bookkeeping" that must  }
{ be done before the actual call to EVCHK.  This includes the set up }
{ of a 16K block of memory for EVCHK's private use. If there is not  }
{ enough memory to create the the work block, the function returns   }
{ NOT_ENOUGH_MEMORY_ERROR.                                           }
function everlock_obj.check_copy_protection : integer;
var
  work_space : pointer;
begin
  { Exit if this is an unprotected copy }
  if protection_mode = unprotected_program
  then begin
    check_copy_protection := passed_protection_check;
    scb_ptr^.ret_code     := passed_protection_check;
    exit;
  end;

  { Check for enough memory }
  if maxavail < evchk_memory_needed
  then begin
    check_copy_protection := not_enough_memory_error;
    scb_ptr^.ret_code     := not_enough_memory_error;
    exit;
  end;

  { Tell EVCHK where the memory is that it can use }
  getmem(work_space,evchk_memory_needed);
  scb_ptr^.ptr_offset  := ofs(work_space^);
  scb_ptr^.ptr_segment := seg(work_space^);

  { Call EVCHK }
  evchk(scb_ptr);

  freemem(work_space,evchk_memory_needed);

  check_copy_protection := scb_ptr^.ret_code;
end;

begin
end.