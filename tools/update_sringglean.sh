STRINGGLEANLOC=$1
if [ -z $STRINGGLEANLOC ]; then
    STRINGGLEANLOC=../stringglean/bin
    STRINGGLEANTOOLS=../stringglean/tools
fi
cp ${STRINGGLEANLOC}/stringglean /usr/local/bin/stringglean
cp ${STRINGGLEANLOC}/hashreplacer /usr/local/bin/hashreplacer
cp ${STRINGGLEANLOC}/clear_empty_lines /usr/local/bin/clear_empty_lines
DIR=./tools
if [ -d "$DIR" ]; then
    echo "$DIR directory exists"
else
    mkdir $DIR
fi
cp ${STRINGGLEANTOOLS}/*.sh ./tools/
