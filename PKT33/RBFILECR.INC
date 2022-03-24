function rbfilecr( filename : string) : integer;

{ This function creates a BTRIEVE file to hold the robot commands.   }
{ This function returns as its value the BTRIEVE return code.        }

var
  myfile : record
             part1 : btrv_file;
             key2  : btrv_key;
             key3  : btrv_key;
           end;

  a_topic : std_topic;

begin
  myfile.part1.rec_len          := sizeof(pk_type);
  myfile.part1.page_size        := 512;  { Multiple of 512 }
  myfile.part1.num_of_indexes   := 3;
  myfile.part1.not_used[1]      := 0;
  myfile.part1.not_used[2]      := 0;
  myfile.part1.file_flags       := 0;
  myfile.part1.resrv_word       := 0;
  myfile.part1.allocation       := 0;

  myfile.part1.key_specs.key_pos     := 1;
  myfile.part1.key_specs.key_len     := 16;
  myfile.part1.key_specs.key_flags   := 258;    { Modifiable key,extended type }
  myfile.part1.key_specs.not_used[1] := 0;
  myfile.part1.key_specs.not_used[2] := 0;
  myfile.part1.key_specs.extended_key_type := 1; { integer extended type }
  myfile.part1.key_specs.null_val       := 0;
  myfile.part1.key_specs.resrv_words[1] := 0;
  myfile.part1.key_specs.resrv_words[2] := 0;

  myfile.key2.key_pos     := 17;
  myfile.key2.key_len     := 16;
  myfile.key2.key_flags   := 258;    { Extended type, modifiable }
  myfile.key2.not_used[1] := 0;
  myfile.key2.not_used[2] := 0;
  myfile.key2.extended_key_type := 1;   { Integer extended type }
  myfile.key2.null_val       := 0;
  myfile.key2.resrv_words[1] := 0;
  myfile.key2.resrv_words[2] := 0;

  myfile.key3.key_pos     := 13;
  myfile.key3.key_len     := 16;
  myfile.key3.key_flags   := 258;    { Extended type, modifiable }
  myfile.key3.not_used[1] := 0;
  myfile.key3.not_used[2] := 0;
  myfile.key3.extended_key_type := 1;   { Integer extended type }
  myfile.key3.null_val       := 0;
  myfile.key3.resrv_words[1] := 0;
  myfile.key3.resrv_words[2] := 0;

  { Attempt to create the file }
  btrv_data_len := sizeof(myfile);
  fillchar(btrv_pos_block,128,' ');
  btrv_rc := btrv(btrv_create,btrv_pos_block,myfile,btrv_data_len,
                      filename[1],0);

  topicfcr := btrv_rc;

end;

