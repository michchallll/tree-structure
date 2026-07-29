#!/bin/bash

depth=$1
nodescount=$2

depthpadding=$( wc -c <<<"$depth" )
nodescountpadding=$( wc -c <<<"$nodescount" )

rootnode="NODE"

echo "create node $rootnode"

function childnode() {
    parent=$1
    child=$2
    echo "create node $child"
    echo "attach node $child under $parent"
}

function recursive_tree() {
    local currdepth=$1
    local node=$2

    if [ $currdepth -eq $depth ]; then
        return;
    fi
    local n=
    for n in $(seq 1 $nodescount); do
        local currdepthprint=$(printf "%0${depthpadding}d" $currdepth)
        local nprint=$(printf "%0${nodescountpadding}d" $n)
        local childname="${node}${currdepth}n${nprint}"
        childnode $node $childname
        local newdepth=$currdepth
        (( newdepth++ ))
        recursive_tree $newdepth $childname
    done
}

recursive_tree 0 "$rootnode"

echo "print tree"