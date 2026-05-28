func main()
  var before : int
  var a : array[10] of int
  var after : int
  var i : int

  before = 199;
  after  = 299;
  a[0]=5; a[1]=3; a[2]=8; a[3]=9; a[4]=7; 
  a[5]=3; a[6]=4; a[7]=6; a[8]=5; a[9]=8; 
  i = 0;
  while i < 10 do
    write "a["; write i; write "]=";
    write a[i]; write "\n";
    i = i + 1;
  endwhile
  write "a) a.max="; write a.max; write "\n";
  a[0] = a[0]*5;
  write "b) a.max="; write a.max; write "\n";
  a[9] = a[9] + a[0];
  write "c) a.max="; write a.max; write "\n";
endfunc
