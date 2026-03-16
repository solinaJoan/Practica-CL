func main()
  var a,b : array [10] of int
  var p,q : array [6][7][10] of float
  var x,y : array [6][7][10] of int
  var z : array [10][7][6] of int
  var t : array [6] of int
  var i,j,k: int

  i = 0;
  while i<6 do
     j = 0;
     while j<7 do
        a[i][j] = b;
        a[i][j][0] = b[3] + a[0][0][j]*4;
        b = a[i][j];
        k = 0;
        while k<10 do
           write a[i][j][k] or k!=5;
           write b[k] + 1;
           a[k] = b;
        endwhile
        a[i] = b[j] * b[i-1];
     endwhile
  endwhile

  a[2][3][4] = b[5] > a[1][2][3] or b[1]<a[2][3];
  a[2][6][7] = b[0] + a[1][2][3]/2;

  i = p[0][0][0] + 5;
  p[0][0][0] = '2';
  x[i][j] = y[j][i];
  x[i][j] = b;
  b = z[i][j];
  x[i][j] = t;
endfunc
