func ff(a: array[10] of int, c:array[20] of int)
    zip a and a into c;
endfunc

func main()
  var i,j,n: int
  var x, y: float
  var A,B: array[10] of int
  var C: array[20] of int
  var X: array[10] of char
  var Y: array[4] of char
  var Z: array[8] of char

  zip A and C into B;
  zip A and B into C;
  zip A and X into B;
  zip Z and Y into X;
  zip X and Y into Z;
  ff(B,C);
  ff(Y,Z);
  ff(C,C);
endfunc

