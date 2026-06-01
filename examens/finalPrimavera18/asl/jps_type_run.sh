#!/usr/bin/env bash
set -e

if [ -z "$1" ]; then
    echo "Ús: $0 NUMERO_EXEMPLE (1-14)"
    exit 1
fi

if [ "$1" -lt 1 ] || [ "$1" -gt 14 ]; then
    echo "L'exemple ha d'estar entre 1 i 14"
    exit 1
fi

EX=$(printf "%02d" "$1")

make >/dev/null

./asl < ../jps/jp_chkt_${EX}.asl | diff -y - ../jps/jp_chkt_${EX}.err
