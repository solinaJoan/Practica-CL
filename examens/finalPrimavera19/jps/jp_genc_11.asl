func init(aI : array[10] of int,
          k : int)
  var i : int

  i = 0;
  while i < 10 do
    aI[i] = i*i + k; i = i + 1;
  endwhile
endfunc

func f(a : array[10] of int)
  var i,x : int

  i = 0;
  while i < 15 do
    x = a[i+1];
    write "a["; write i+1;
    write "]="; write x; write "\n";
    i = i + 1;
  endwhile
  write "bad message!"; write "\n";
endfunc

func main()
  var b,c: array[10] of int

  init(b, 5);
  c = b;
  f(c);
endfunc
