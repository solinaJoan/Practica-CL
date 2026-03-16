func g() : bool
  return true;
endfunc

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
  var x,z : float
  var a,b : array [10] of char
  var p : bool
  i = 5;
  j = a[i] or b>0;
  z = i+j;
  // la funcio f retorna any:
  z = anycast<float>(f(i+1, z<22, a)) + 2;
  // la suma de any i float dona un float, que no es any:
  x = anycast<float>(f(j+2, z<50, b) + 5.2);
  // la funcio g no retorna any, i a[3] no es de tipus any:
  x = anycast<float>(g(23,2)) + anycast<int>(a[3]);

  if j>i or anycast<bool>(f(15, false, a)) and not b then
     a[3] = anycast<char>(f(j, j>=100, b));
     b = anycast<bool>(f(j, j>=100, b) and not p) or x!=2;
  endif
  f(5, true, b);
  write z;
endfunc
