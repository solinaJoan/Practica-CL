func f(a:int, b:bool, x:array[10] of char) : any
  if a > 10 then
     return b or not z;
  else if not b then
          return x[a];
       else
          return a*2.0 + (x!=1);
       endif
  endif
endfunc

func main()
  var i,j : int
  var x,z : float
  var a,b : array [10] of char
  var p : bool
  i = 5;
  j = a[i] or b>0;
  z = i+j;

  z = anycast<float>(f(i+1, z<22, a)) or not p;
  i = anycast<float>(f(j+2, z<50) + 5.2) + j/i;
  if j>i or anycast<int>(f(15, false, a)) and not b then
     b = anycast<char>(f(j, j>=100, b));
     a[3] = anycast<bool>(f(j, j>=100, b) and not p);
  endif
  f(5, true, b);
  write z;
endfunc
