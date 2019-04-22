#!/bin/bash
while true; do
    ./gen > gen.in
    ./sol <gen.in >sol.out
    ./dp <gen.in >dp.out
    if diff sol.out dp.out; then
        printf "AC\n"
    else
        printf "Wa\n"
        exit 0
    fi
done

// sh duipai.sh
