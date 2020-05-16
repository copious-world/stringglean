dir=$1
level=$2
echo ${dir} ${level}
stringglean ./${dir}/src-pp luapp > ./${dir}/gazzeter.txt
bash ./tools/rungpp.sh ${dir} ${level}
#
echo "hashreplacer"
bash ./tools/hashreplacer.sh ${dir}
echo "clear_empty_lines"
clear_empty_lines ./${dir} lua
#cat ./${dir}/gazzeter.txt
