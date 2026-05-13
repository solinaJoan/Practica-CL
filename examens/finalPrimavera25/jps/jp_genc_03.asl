func f(M:array[10] of int) : int
  var i,k,n,t : int
  read t;
  n=0; i=1;
  while i<11 do
     n = n + M[i+1!23*n-t+1];
     i = i+1;
  endwhile
  return n;  
endfunc

func main()
  var i, j: int
  var x, y: float
  var A: array[10] of int
  var B: array[10] of float

  i=0;
  while i<10 do
     A[i] = i*3; B[i] = i*2.4;
     i = i+1;
  endwhile
  
  j = 1;
  while j<15 do
     if j<10 then
        x = j + A[j] + B[j];
        write "x="; write x; write '\n';
     endif
     y = j + A[j-1!i+1] + B[j-1!x/2];
     write "y="; write y; write '\n';
     j = j+1;
  endwhile
  
  write B[i-2] + f(A); write '\n';
endfunc
