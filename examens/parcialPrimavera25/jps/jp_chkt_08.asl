func main()
  var a : array [10][10] of int
  var b,c : array [5] of int
  var p,q : array [6][7][8] of float
  var i,j,k: int

  i = 0;
  while i<6 do
     j = 0;
     while j<7 do
        p[i][j] = b;
        p[i+1][j-2] = b[1:8];
        q[i] = a[0:7][0:8];
	p[j] = a[1:3][2:5];
	
        q[i-1][j+2] = a[4:6][0:7];
	if j>a[2:4][k] or a[i][3:7][k]!=p[i][j][k+1] then
           c = p[i][1:6][1:3];
           k = a[5:2][j+1];
           b = a[i+1][2:6];
	else
	   b = p[8:12][k];
           b = a[9:11][3:6][i-1][0:4];
	   j = b[2:2][0];
	endif
     endwhile
  endwhile

  a[2][3][4] = b[4:5][k] > a[1][2][3] or b[1] < a[2][3];
  write p[i][0:3][j+1][0:4][0] == 'c';
endfunc
