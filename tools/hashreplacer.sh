#run gpp on the files in the included directory.
echo $1
pushd ./$1
pwd
#
files=$(ls ./mtmp/*.lua)
for ff in $files
do
	echo $ff
	fstem=$(basename $ff .lua)
	hashreplacer $ff 'g_mlcl.' gazzeter.txt '@' > "$fstem".lua
done
popd

