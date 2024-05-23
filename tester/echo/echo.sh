tester_echo()
{
	ECHO_I=$((ECHO_I+1))
	i=$((i+1))
	echo -e "\033[1m\033[37mtest $i: $@"
	# echo $@ "; exit" | ./Minishell >$OUTFILE1
	# echo $@ "; exit" | bash >$OUTFILE2
	echo -e $@ | bash >$OUTFILE1 2>$ERROR1
	es1=$?
	if test -f $OUTPUT1 ; then
		mv $OUTPUT1 $OUTFILE1
	fi
	echo -e $@ | ./tester/Minishell >$OUTFILE2 2>$ERROR2
	es2=$?
	# grep -v "$REM" $OUTFILE2 > tester/temp.txt
	# mv tester/temp.txt $OUTFILE2
	# sed -i "s@$REM@""@g"
	sed -i	'1d' $OUTFILE2
	sed -i "s@$REM@""@g" $OUTFILE2
	# grep . $OUTFILE2 > tester/temp.txt && mv tester/temp.txt $OUTFILE2
	# cat $OUTFILE2 > tester/temp.txt
	# REM=$(grep -m1 "" $OUTFILE2)
	# grep -m1 "" $OUTFILE2 > tester/temp1.txt
	# awk -v pat="$REM" '/$0~pat/' $OUTFILE2 > tester/temp.txt 
	# gawk -i inplace -v pat="$REM" 'pat' $OUTFILE2 > tester/temp.txt 
	echo "$i." >> $LOG
	echo "$i." >> $ERROR_LOG
	if test -f $OUTPUT1 ; then
		mv $OUTPUT1 $OUTFILE2
	fi
	if diff $OUTFILE1 $OUTFILE2 >/dev/null; then
		printf "$BOLDGREEN output"
	else
		printf "$BOLDRED output"
		error_log 1
	fi
	# printf $es1\n
	# printf $es2\n
	if [ $es1 -eq $es2 ]; then
		printf "$BOLDGREEN exit"
	else
		printf "$BOLDRED exit"
		error_log 2
	fi
	if diff $ERROR1 $ERROR2 >/dev/null; then
		printf "$BOLDGREEN error"
	else
		printf "$BOLDRED error"
		error_log 3
	fi
	echo $@ | valgrind --log-file="tester/leaks/leak_log$i.txt" --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./tester/Minishell &>/dev/null
	es2=$?
	if [ $es2 -ne 42 ]; then
		printf "$BOLDGREEN MOK\n"
	else
		printf "$BOLDRED MKO\n"
	fi
	# rm $OUTFILE1
	# rm $OUTFILE2
}