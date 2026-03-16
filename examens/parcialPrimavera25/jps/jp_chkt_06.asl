func main()
  var a : array [10] of int
  var b,c : array [5] of int
  var p,q : array [6][7][5] of float
  var i,j,k: int

  i = 0;
  while i<6 do
     j = 0;
     while j<7 do
        p[i][j] = b;
        q[i-1][j+2] = b[3:7];
	if i != b[2:6][j] then
	    k = a[5:2][j+1];
	    b = a[5:2];
	else
	    b = a[8:12];
	    b = a[2:2];
	    j = b[2:2][0];
	endif
     endwhile
  endwhile

  a[2][3][4] = b[4:5][k] > a[1][2][3] or b[1]<a[2][3];
endfunc
