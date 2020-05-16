STRINGGLEANLOC=$1
if [ -z $STRINGGLEANLOC ]; then
    STRINGGLEANLOC=../stringglean/bin
fi
cp ${STRINGGLEANLOC}/subofpub /usr/local/bin/subofpub
cp ${STRINGGLEANLOC}/stringglean /usr/local/bin/stringglean
cp ${STRINGGLEANLOC}/hashreplacer /usr/local/bin/hashreplacer
cp ${STRINGGLEANLOC}/clear_empty_lines /usr/local/bin/clear_empty_lines
DIR=./tools
if [ -d "$DIR" ]; then
    echo "$DIR directory exists"
else
    mkdir tools
fi
cp ${STRINGGLEANLOC}/tools/*.sh ./tools/
