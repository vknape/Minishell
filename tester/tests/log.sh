
# echo 4
# exit
# error_log()
# {
# 	echo 3
# }
error_log()
{
	if [ $# -eq 0 ]; then
		exit
	fi
	if [ $@ -eq 1 ]; then
		echo "Bash output is:	" >> $LOG
		cat $OUTFILE1 >> $LOG
		echo "Your output is:	" >> $LOG
		cat $OUTFILE2 >> $LOG
	fi
	if [ $@ -eq 2 ]; then
		echo "Bash exit status is: $es1" >> $LOG
		echo "Your exit status is: $es2" >> $LOG
	fi
	if [ $@ -eq 3 ]; then
		echo "Bash error is:	" >> $ERROR_LOG
		cat $ERROR1 >> $ERROR_LOG
		echo "Your error is:	" >> $ERROR_LOG
		cat $ERROR2 >> $ERROR_LOG
	fi
	
}