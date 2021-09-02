#!/bin/bash
basenames=
dependencies=
for src in ${@:5}; do
    basenames+=" $(basename $src ".$2")"
done
for name in $basenames; do
    if [ -f "$3/$name.$4" -o $1 = "force" ]; then
        dependencies+=" $3/$name.$4"
    fi
done
echo $dependencies