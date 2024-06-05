source ./tester/echo/echo.sh

OUTFILE1=tester/vbash.txt
OUTFILE2=tester/vmini.txt
ERROR1=tester/berror.txt
ERROR2=tester/verror.txt
OUTPUT1=tester/bredir.txt
OUTPUT2=tester/vredir.txt



RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

i=0
es1=0
es2=0

LOG=tester/output_log.txt
ERROR_LOG=tester/error_log.txt
# LEAK_LOG="tester/leaks/leak_log$i.txt"

ECHO_FILES=tester/echo/
ECHO_I=0


error_log()
{
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

# exit_status()
# {
	
# }

tester()
{
	i=$((i+1))
	echo -e "\033[1m\033[37mtest $i: $@"
	# echo $@ "; exit" | ./Minishell >$OUTFILE1
	# echo $@ "; exit" | bash >$OUTFILE2
	echo -e $@ | bash >$OUTFILE1 2>$ERROR1
	es1=$?
	if test -f $OUTPUT1 ; then
		mv $OUTPUT1 $OUTFILE1
	fi
	echo -e $@ | valgrind --suppressions="read.supp" -s --log-file="tester/leaks/leak_log$i.txt" --leak-check=full --errors-for-leak-kinds=all --show-leak-kinds=all --trace-children=yes --track-fds=yes --error-exitcode=42 ./tester/Minishell >$OUTFILE2 2>$ERROR2
	es2=$?
	grep -v "$REM" $OUTFILE2 > tester/temp.txt
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
	# rm $OUTFILE1
	# rm $OUTFILE2
}
if test -f "tester/Minishell" ; then
	rm tester/Minishell
fi
# rm ./tester/Minishell >/dev/null
cp ./Minishell ./tester
if test -f $LOG ; then
	rm $LOG
fi
cp tester/read.supp ./
if test -f $ERROR_LOG ; then
	rm $ERROR_LOG
fi
# exit
echo '' | ./tester/Minishell >$OUTFILE2
REM=$(grep -m1 "" $OUTFILE2)
# exit
# REM=$(echo '' | ./tester/Minishell)
# printf "$REM\n"
rm tester/leaks/*.txt
rm tester/*.txt
rm tester/child_leak.txt
rm tester/child_leak2.txt
# exit
# clear_logs $i

# tester 'echo "> >> < ? [ ] | ; [ ] || && ( ) & # $ \ <<"'
# tester "echo '> >> < ? [ ] | ; [ ] || && ( ) & # $ \ <<'"
# tester 'echo "exit_code ->$? user ->$USER home -> $HOME"'
# tester 'echo "exit_code ->$? user"'

# tester "echo 'exit_code ->$? user ->$USER home -> $HOME'"

# exit
printf "\033[1m\033[36mSYNTAX TESTS\n"
tester '|'
tester '||'
tester '>'
tester '>>'
tester '>>>'
tester '<'
tester '<<'
tester '<<<'
tester 'echo hello >'
tester 'echo hello <'
tester 'echo hello |> ls'
tester 'echo hello >| ls'
tester 'echo hello > | ls'
tester 'echo hello | > ls'
tester 'echo hello |	> ls'
tester 'echo hello <> ls'
tester 'echo hello >< ls'
tester 'echo hello < > ls'
tester 'echo hello > < ls'
tester 'echo hello | "|"'
tester 'echo hello | "<"'
tester 'echo hello | ">"'

printf "\033[1m\033[36mECHO TESTS\n"
tester 'echo hello \n echo hello'
tester 'echo hello hello'
tester 'echo hello "hello hello"'
tester "echo hello 'hello hello'"
tester 'echo hello "hello hello" hello'
tester_echo 'echo -n hello "hello hello" hello'
# exit
tester_echo 'echo -n -n hello "hello hello" hello'
tester_echo 'echo -n -nm -n hello "hello hello" hello'
tester_echo 'echo -n -mn -n hello "hello hello" hello'
tester_echo 'echo -nnnnnnnnnnnn -n hello "hello hello" hello'

printf "\n\033[1m\033[36mPWD TESTS\n"
tester 'pwd'
tester 'pwd hello'

printf "\n\033[1m\033[36mCD TESTS\n"
tester 'cd'
tester 'cd ..\npwd'
tester 'cd $PWD\npwd'
tester 'cd ~\npwd'
tester 'cd ..\ncd -\npwd'
tester 'cd .. ..'
tester 'cd invalid'

printf "\n\033[1m\033[36mEXPORT TESTS\n"
# tester 'export var=5 \nexport'
export var="'hello'"
tester 'echo $var'
tester 'echo "$var"'
unset var
# exit
printf "\n\033[1m\033[36mUNSET TESTS\n"
# tester 'unset USER \nexport'

printf "\n\033[1m\033[36mENV TESTS\n"
# tester 'env'

printf "\n\033[1m\033[36mHEREDOC TESTS\n"
tester 'cat << end\nhere\nend'

printf "\n\033[1m\033[36m$ TESTS\n"
export var="ls"
tester '$var'
unset var
export var="ls "
tester '$var'
unset var
tester '$USER'
tester 'echo $'
tester 'echo "$"'
tester "echo '$'"
tester 'echo $ '
tester 'echo  $'
tester 'echo $$'
export var=hello
tester 'echo $var'
tester 'echo $ $'
tester 'echo $ $var'
tester 'echo $var$var'
tester 'echo $$$'
tester 'echo $ $$'
tester 'echo $ $var$'
tester 'echo $?'
tester 'echo $??'
tester 'echo $?$?'
tester 'echo $var$?'
tester 'echo $?$var'
tester 'echo ?'
tester 'echo $ ?'
tester 'echo $var?'
unset var


printf "\n\033[1m\033[36mEXIT TESTS\n"
tester 'exit 123'
tester 'exit 298'
tester 'exit +100'
tester 'exit "+100"'
tester 'exit +"100"'
tester 'exit -100'
tester 'exit "-100"'
tester 'exit -"100"'
tester 'exit hello'
tester 'exit 42 world'

printf "\n\033[1m\033[36mCMD TESTS\n"
tester 'ls'
tester 'sleep'

printf "\n\033[1m\033[36mCMD with flags TESTS\n"
tester 'ls -l'
tester 'sleep 1'
tester 'cat infile.txt'


printf "\n\033[1m\033[36mCMD with pipe TESTS\n"
tester 'ls | echo hello'
tester 'ls | pwd'
tester 'ls | exit 99'
tester 'ls | cat'
tester 'sleep 1 | ls -l'
tester 'ls -l | sleep 1'

printf "\n\033[1m\033[36mCMD with multiple pipe TESTS\n"
tester 'ls | cat -e | cat -e | cat -e'

printf "\n\033[1m\033[36mCMD with infile TESTS\n"
tester 'cat < infile.txt'
tester 'ls < infile.txt'

printf "\n\033[1m\033[36mCMD with multiple infile TESTS\n"
tester 'cat < infile.txt < out_new'
tester 'cat <out_new < infile.txt'

printf "\n\033[1m\033[36mCMD with outfile TESTS\n"
tester 'ls > tester/bredir.txt'

printf "\n\033[1m\033[36mCMD with multiple outfile TESTS\n"
tester 'ls > outfile > tester/bredir.txt'

# cat infile.txt
printf "\n\033[1m\033[36mCMD with infile outfile and pipe TESTS\n"
tester 'cat < infile.txt | cat -e'
tester 'cat < infile.txt | ls'
tester 'ls < infile.txt | cat -e'

printf "\n\033[1m\033[36mCMD with multiple infiles outfiles and pipes TESTS\n"
tester 'cat < infile.txt < out_new | cat -e | cat -e >outfile >tester/bredir.txt'
tester 'cat < infile.txt < out_new | ls | cat -e >outfile >tester/bredir.txt'
tester 'cat < out_new > tester/bredir.txt'

# rm $OUTFILE1
# rm $OUTFILE2
rm read.supp
printf $WHITE