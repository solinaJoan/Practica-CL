
func ff(a: array[1] of int, c:array[2] of int)
    var i:int
    zip a and a into c;
    write "a:"; write a[0]; write "\n";
    write "c:"; write c[0];  
    write " "; write c[1]; write "\n";    
endfunc

func main()
  var i,j,n: int
  var x, y: float
  var A,B: array[1] of int
  var C: array[2] of int
  var X: array[1] of char
  var Y: array[1] of char
  var Z: array[2] of char

  read A[0]; read B[0];
  read X[0]; read Y[0];

  zip A and B into C;
  write "C:"; write C[0];
  write " "; write C[1]; write "\n";
  
  zip X and Y into Z;
  write "Z:"; write Z[0];
  write " "; write Z[1]; write "\n";
  
  ff(B,C);
  write "C2:"; write C[0];
  write " "; write C[1]; write "\n";
endfunc

