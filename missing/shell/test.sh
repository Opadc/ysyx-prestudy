#! /bin/bash

foo=bar
echo "$foo"
echo '$foo'

mcd () {
    mkdir -p "$1"
    cd "$1"
}

print_all_param () {
    echo "total $# params print"
    echo $@
    return 2
}
print_all_param "1" 2 "3"
echo "last command status: $?"
echo "current pid: $$"
echo "last param: $_"

echo "Starting program at $(date)"

echo "running program $0 with $# arguments with pid $$"

for file in "$@"; do
    grep foobar "$file" > /dev/null 2> /dev/null
    if [[ $? -ne 0 ]]; then
        echo "file $file does not have any foobar, add one"
        echo "# foobar" >> "$file"
    fi
done
