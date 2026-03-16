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
        q[i-1][j+2] = a[j][3:5];
        q[i-1][j+2] = a[j][0:7];
	if k+j != a[i][j][k] then
	    c = p[i][j][1:3];
	    k = a[5][j+1];
	    b = a[5:2];
	else
	    b = a[8:12];
	    b = a[2:6];
	    j = b[0][2:2];
	endif
     endwhile
  endwhile

  a[2][3][4] = b[4:5][k] > a[1][2][3] or b[1] < a[2][3];
endfunc
