func main()
  var a : array[10] of int
  var i,x : int

  i = 5;
  while i < 10 do
    x = a[i];
    write "a["; write i;
    write "] ok"; write "\n";
    i = i + 1;
  endwhile
  write a[10];
  write "bad message!"; write "\n";
endfunc
