func ff(a: array[10] of int, c:array[20] of float)
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
  var A: array[10] of int
  var B: array[15] of float
  var C: array[20] of float

  i=0;
  while i<15 do
     read B[i];
     if i<10 then read A[i]; endif
     i = i+1;
  endwhile

  zip A and B into C;
  write "C:"; i=0;
  while i<20 do
     write " "; write C[i]; i = i+1;
     if i==10 then write "\n  "; endif
  endwhile
  write "\n";

  ff(A,C);
  write "C2:"; i=0;
  while i<20 do
     write " "; write C[i]; i = i+1;
     if i==10 then write "\n   "; endif     
  endwhile
  write "\n";

endfunc
