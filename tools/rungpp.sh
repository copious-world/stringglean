#run gpp on the files in the included directory.
echo $1
pushd ./$1
pwd
#
if [ -z $2 ]; then
	level=4
else
	level=$2
fi
#
files=$(ls ./src-pp/*.luapp)
mkdir ./mtmp
for ff in $files
do
	fstem=$(basename $ff .luapp)
	echo $level
	#
	gpp +n -DLOG_LEVEL=$level $ff > ./mtmp/"$fstem".lua
done
popd

