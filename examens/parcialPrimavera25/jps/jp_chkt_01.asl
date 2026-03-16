func f(a:int, b:bool, x:array[10] of char) : any
  if a > 10 then
     return b or not x[1];
  else if not b then
          return x[a];
       else
          return a*2.0;
       endif
  endif
endfunc

func main()
  var i,j : int
  var z : float
  var a,b : array [10] of char

  i = 5;
  j = a[i] or b>0;
  z = i+j;
  // f retorna un tipus any, i sense fer anycast la suma dona error:
  z = f(i+1, z<22, a) + 2;

  // tampoc es fa cast del resultat de f:
  if j>i or f(15, false, a) and not b then
     // assignacio sense cast:
     a[3] = f(j, j>=100, b);
  endif
  f(5, true, b);
  write z;
endfunc
