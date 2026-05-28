func main()
  var a : array[10] of int
  var i,x : int

  i = 5; a[2] = 2222;
  while i > -5 do
    x = a[i];
    write "a["; write i;
    write "] ok";
    if i == 2 then write a[i]; endif
    write "\n";
    i = i - 1;
  endwhile
  write "bad message!"; write "\n";
endfunc
