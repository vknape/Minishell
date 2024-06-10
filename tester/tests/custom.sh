source ./tester/tests/main.sh
source ./tester/tests/log.sh
CUSTOM=0

tester_custom ()
{
	if [ $# -eq 0 ]; then
		exit
	fi
	CUSTOM=$((CUSTOM+1))
	test_main $@
	grep -v "$REM" $OUTFILE2 > tester/temp.txt
	mv tester/temp.txt $OUTFILE2
	if [ $CUSTOM -lt 4 ]; then
		echo hello > tester/temp.txt
		es1=127
		if diff $OUTFILE2 tester/temp.txt >/dev/null; then
			> $OUTFILE2
		fi
	fi
	if [ $CUSTOM -eq 4 ]; then
		es1=2
		> $OUTFILE1
	fi
	if [ $CUSTOM -eq 5 ]; then
		es1=0
		echo '$$' > $OUTFILE1
		# if diff $OUTFILE2 tester/temp.txt >/dev/null; then
		# 	echo '$$' > $OUTFILE1
		# fi
	fi
	if [ $CUSTOM -eq 6 ]; then
		es1=0
		echo '$$$' > $OUTFILE1
		# if diff $OUTFILE2 tester/temp.txt >/dev/null; then
		# 	echo '$$$' > $OUTFILE1
		# fi
	fi
	if [ $CUSTOM -eq 7 ]; then
		es1=0
		echo '$ $$' > $OUTFILE1
		# if diff $OUTFILE2 tester/temp.txt >/dev/null; then
		# 	echo '$ $$' > $OUTFILE1
		# fi
	fi
	if [ $CUSTOM -eq 8 ]; then
		es1=0
		echo '?' > $OUTFILE1
	fi
	if [ $CUSTOM -eq 9 ]; then
		es1=0
		echo '$ ?' > $OUTFILE1
	fi
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