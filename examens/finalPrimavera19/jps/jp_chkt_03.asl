func main()
  var Ai: array[10] of int
  var Af: array[10] of float
  var Ac: array[10] of char
  var Ab: array[10] of bool
  var i,k2 : int

  i = 0;
  while i < 10 do
    k2 = Ai.max*Af.max;
    if k2 > 'c' then
      write Ac.max < Ac[i]; write "\n";
    else
      if Ab.max then
        i = i + k2.max;
	i = Ab.max - i;
      endif
    endif
  endwhile
endfunc
