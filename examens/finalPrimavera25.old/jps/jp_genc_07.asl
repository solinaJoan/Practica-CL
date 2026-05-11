func ff(a: array[10] of int, c:array[20] of int)
    var i:int
    zip a and a into c;
    write "a:"; i=0;
    while i<10 do
       write " "; write a[i]; i = i+1;
    endwhile
    write "\n";
    write "c:"; i=0;
    while i<20 do
       write " "; write c[i]; i = i+1;
       if i==10 then write "\n  "; endif
    endwhile
    write "\n";    
endfunc

func main()
  var i,j,n: int
  var x, y: float
  var A,B: array[10] of int
  var C: array[20] of int
  var X: array[10] of char
  var Y: array[4] of char
  var Z: array[8] of char

  i=0;
  while i<10 do
     read A[i]; read B[i]; read X[i];
     if i<4 then read Y[i]; endif
     i = i+1;
  endwhile

  zip A and B into C;
  write "C:"; i=0;
  while i<20 do
     write " "; write C[i]; i = i+1;
     if i==10 then write "\n  "; endif
  endwhile
  write "\n";    
  
  zip X and Y into Z;
  write "Z:"; i=0;
  while i<8 do
     write " "; write Z[i]; i = i+1;
  endwhile
  write "\n";
  
  ff(B,C);
  write "C2:"; i=0;
  while i<20 do
     write " "; write C[i]; i = i+1;
     if i==10 then write "\n   "; endif
  endwhile
  write "\n";    
endfunc

