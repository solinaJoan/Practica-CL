#! /bin/bash

#################################################
#
#  Segon examen parcial de CL 
# 
#  Script de verificacio de jocs de proves 
#
#  Us:  ./avalua.sh
#
#  Executa els jocs de proves dels directoris
#  ../jps
#
#  El resultat de l'script es una llista de quins 
#  jocs de proves se superen i quins no
#
#  Els resultats d'aquest script son orientatius, 
#  i no suposen cap compromís respecte a la qualificacio 
#  final de l'examen.
#
#################################################

BASEDIR=$(readlink -f `dirname $0`)
JPDIR=../jps

# build interpreter
make pristine
make antlr
make

# executar gramatica sobre els jps
rm -f $JPDIR/*.student.*

echo "==============================="
echo ""
echo "     Exercici ASL. Typecheck"
echo ""
for jp in $JPDIR/jp*_chkt_*.asl; do
    f=`basename $jp .asl`

    # Exectute test suite
    $BASEDIR/asl $jp |& egrep "^L" >& $JPDIR/$f.student.err

    # compare produced errors with expected errors
    if (diff -q -s $JPDIR/$f.err $JPDIR/$f.student.err &>/dev/null ); then err="OK"
    else err="NO"
    fi

    echo -e "$f:\t$err"
done

echo "==============================="
echo ""
echo "     Exercici ASL. CodeGen"
echo ""
for jp in $JPDIR/jp*_genc_*.asl; do
    f=`basename $jp .asl`

    # exectute test suite
    $BASEDIR/asl $jp >& $JPDIR/$f.student.t
    $BASEDIR/../tvm/tvm $JPDIR/$f.student.t < $JPDIR/$f.in >& $JPDIR/$f.student.out

    # compare produced output with expected output
    if ( ! test -f $JPDIR/$f.out || ! test -s $JPDIR/$f.out); then out="-"
    elif ( diff -q -s $JPDIR/$f.out $JPDIR/$f.student.out &>/dev/null ); then out="OK"
    else out="NO"
    fi

    echo -e "$f:\t$out"
done

echo "==============================="

