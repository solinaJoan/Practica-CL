func main()
  var a : array[10] of int
  var i,x : int

  i = 5;
  while i < 10 do
    a[i] = i;
    write "a["; write i;
    write "]="; write a[i]; write "\n";
    i = i + 1;
  endwhile
  a[10] = 9999;
  write "bad message!"; write "\n";
endfunc
