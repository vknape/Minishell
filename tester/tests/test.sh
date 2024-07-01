source ./tester/tests/main.sh
source ./tester/tests/log.sh

tester()
{
	if [ $# -eq 0 ]; then
		exit
	fi
	test_main $@
	grep -v "$REM" $OUTFILE2 > tester/temp.txt
	mv tester/temp.txt $OUTFILE2
	grep -v ">" $OUTFILE2 > tester/temp.txt
	mv tester/temp.txt $OUTFILE2
	# grep -v ">" $OUTFILE2 > tester/temp.txt
	# mv tester/temp.txt $OUTFILE2
	# grep -v "> end" $OUTFILE2 > tester/temp.txt
	# mv tester/temp.txt $OUTFILE2
	# sed -i "s@$REM@""@g"
	# sed -i	'1d' $OUTFILE2
	# grep . $OUTFILE2 > tester/temp.txt && mv tester/temp.txt $OUTFILE2
	# cat $OUTFILE2 > tester/temp.txt
	# REM=$(grep -m1 "" $OUTFILE2)
	# grep -m1 "" $OUTFILE2 > tester/temp1.txt
	# awk -v pat="$REM" '/$0~pat/' $OUTFILE2 > tester/temp.txt 
	# gawk -i inplace -v pat="$REM" 'pat' $OUTFILE2 > tester/temp.txt
	compare_main ''
}
