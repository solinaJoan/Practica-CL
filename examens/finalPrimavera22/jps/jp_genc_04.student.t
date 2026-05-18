function main
  vars
    a integer
    b integer
    A integer 2
    x float
    y float
  endvars

     %1 = 3
     %2 = float %1
     x = %2
     readi b
     %3 = b / b
     a = %3
     %5 = 0
     %6 = 8
     A[%5] = %6
     %8 = 1
     %9 = 9
     A[%8] = %9
     %12 = float a
     %11 = %12 *. x
     y = %11
  label while1 :
     %14 = 100
     %16 = float %14
     %15 = x <. %16
     ifFalse %15 goto endwhile1
     %17 = - b
     %19 = float %17
     %18 = %19 +. x
     %20 = 0
     %21 = A[%20]
     %22 = 2
     %23 = %21 / %22
     %24 = %23 * a
     %26 = float %24
     %25 = %18 <=. %26
     %25 = not %25
     ifFalse %25 goto else1
     %27 = 1
     %28 = A[%27]
     %29 = %28 - b
     %30 = float %29
     x = %30
     %31 = 1
     %32 = 1
     %33 = b + %32
     A[%31] = %33
     goto endif1
  label else1 :
     readf x
  label endif1 :
     writes "loop "
     %35 = 1
     %36 = A[%35]
     writei %36
     writes " "
     writef x
     writes "\n"
     goto while1
  label endwhile1 :
     %37 = 12
     %38 = b - %37
     writei %38
     writes "\n"
     %39 = 12
     %40 = b - %39
     %41 = 5
     %42 = %40 * %41
     a = %42
     writes "end "
     writef y
     writes "\n"
     return
endfunction


