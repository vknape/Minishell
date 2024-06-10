
source ./tester/tests/log.sh
# echo 3

# test ()
# {
# 	echo 2
# 	error_log
# }

test_main ()
{
	if [ $# -eq 0 ]; then
		exit
	fi
	i=$((i+1))
	echo -e "\033[1m\033[37mtest $i: $@"
	echo -e $@ | bash >$OUTFILE1 2>$ERROR1
	es1=$?
	if test -f $OUTPUT1 ; then
		mv $OUTPUT1 $OUTFILE1
	fi
	echo -e $@ | valgrind --suppressions="read.supp" -s --log-file="tester/leaks/leak_log$i.txt" --leak-check=full --errors-for-leak-kinds=all --show-leak-kinds=all --trace-children=yes --track-fds=yes --error-exitcode=42 ./tester/Minishell >$OUTFILE2 2>$ERROR2
	es2=$?
	echo "$i." >> $LOG
	echo "$i." >> $ERROR_LOG
	# grep -v "$REM" $OUTFILE2 > tester/temp.txt
	# mv tester/temp.txt $OUTFILE2
	# echo "$i." >> $LOG
	# echo "$i." >> $ERROR_LOG
	# if test -f $OUTPUT1 ; then
	# 	mv $OUTPUT1 $OUTFILE2
	# fi
	# if diff $OUTFILE1 $OUTFILE2 >/dev/null; then
	# 	printf "$BOLDGREEN output"
	# else
	# 	printf "$BOLDRED output"
	# 	error_log 1
	# fi
	# # printf $es1\n
	# # printf $es2\n
	# if [ $es1 -eq $es2 ]; then
	# 	printf "$BOLDGREEN exit"
	# else
	# 	printf "$BOLDRED exit"
	# 	error_log 2
	# fi
	# if diff $ERROR1 $ERROR2 >/dev/null; then
	# 	printf "$BOLDGREEN error"
	# else
	# 	printf "$BOLDRED error"
	# 	error_log 3
	# fi
	# #echo $@ | valgrind --suppressions="read.supp" -s --log-file="tester/leaks/leak_log$i.txt" --leak-check=full --errors-for-leak-kinds=all --show-leak-kinds=all --trace-children=yes --track-fds=yes --error-exitcode=42 ./tester/Minishell &>/dev/null
	# es2=$?
	# # printf "$es2\n"
	# grep "ERROR SUMMARY: " tester/leaks/leak_log$i.txt >tester/child_leak.txt

	# # CHILD_LEAK=$(awk '$4 != "0"' tester/child_leak.txt)
	# awk '$4 != "0" {print $4}' tester/child_leak.txt > tester/child_leak2.txt
	# # printf $CHILD_LEAK\n
	# CHILD_LEAK=0
	# # CHILD_LEAK_NUM=0
	# while read -r CHILD_LEAK_NUM
	# do
	# 	CHILD_LEAK=1
	# done < "tester/child_leak2.txt"
	# if [ $es2 -ne 42 ] && [ $CHILD_LEAK -eq 0 ]; then
	# 	printf "$BOLDGREEN MOK\n"
	# else
	# 	printf "$BOLDRED MKO\n"
	# fi
}

compare_main ()
{
	if test -f $OUTPUT1 ; then
		mv $OUTPUT1 $OUTFILE2
	fi
	if diff $OUTFILE1 $OUTFILE2 >/dev/null; then
		printf "$BOLDGREEN output"
		# error_log 1
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
	BERROR=0
	while read -r TEMP_NUM
	do
		BERROR=1
	done < $ERROR1
	VERROR=0
	while read -r TEMP_NUM
	do
		VERROR=1
	done < $ERROR1
	if diff $ERROR1 $ERROR2 >/dev/null; then
		printf "$BOLDGREEN error"
	elif [ $BERROR -eq $VERROR ]; then
		printf "$BOLDYELLOW error"
		error_log 3
	else
		printf "$BOLDRED error"
		error_log 3
	fi
	#echo $@ | valgrind --suppressions="read.supp" -s --log-file="tester/leaks/leak_log$i.txt" --leak-check=full --errors-for-leak-kinds=all --show-leak-kinds=all --trace-children=yes --track-fds=yes --error-exitcode=42 ./tester/Minishell &>/dev/null
	es2=$?
	# printf "$es2\n"
	grep "ERROR SUMMARY: " tester/leaks/leak_log$i.txt >tester/child_leak.txt

	# CHILD_LEAK=$(awk '$4 != "0"' tester/child_leak.txt)
	awk '$4 != "0" {print $4}' tester/child_leak.txt > tester/child_leak2.txt
	# printf $CHILD_LEAK\n
	CHILD_LEAK=0
	# CHILD_LEAK_NUM=0
	while read -r CHILD_LEAK_NUM
	do
		CHILD_LEAK=1
	done < "tester/child_leak2.txt"
	if [ $es2 -ne 42 ] && [ $CHILD_LEAK -eq 0 ]; then
		printf "$BOLDGREEN MOK\n"
	else
		printf "$BOLDRED MKO\n"
	fi
	rm $OUTFILE1
	rm $OUTFILE2
}