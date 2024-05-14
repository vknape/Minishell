#!/bin/sh
# source ./tester/utils.sh

OUTFILE1=tester/vbash
OUTFILE2=tester/vmini
OUTPUT1=tester/bredir
OUTPUT2=tester/vredir

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

LOG=tester/error_log
LEAK_LOG="leaks/leak_log$i"


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
	echo $@ | bash >$OUTFILE1
	es1=$?
	if test -f $OUTPUT1 ; then
		mv $OUTPUT1 $OUTFILE1
	fi
	echo $@ | ./tester/Minishell >$OUTFILE2
	es2=$?
	echo "$i." >> $LOG
	sed -i '1d' $OUTFILE2
	if test -f $OUTPUT1 ; then
		mv $OUTPUT1 $OUTFILE2
	fi
	# sed -i '1d' $OUTFILE2
	# gawk -i inplace 'NR>1' $OUTFILE2
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
	echo $@ | valgrind --log-file="tester/leaks/leak_log$i.txt" --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./tester/Minishell >$OUTFILE2
	es2=$?
	if [ $es2 -ne 42 ]; then
		printf "$BOLDGREEN MOK\n"
	else
		printf "$BOLDRED MKO\n"
	fi

}
if test -f "tester/Minishell"  ; then
	rm tester/Minishell
fi
# rm ./tester/Minishell
cp ./Minishell ./tester
if test -f $LOG ; then
	rm $LOG
fi
# exit
rm tester/leaks/*.txt
# exit
# clear_logs $i
printf "\033[1m\033[36mECHO TESTS\n"
tester 'echo hello'
tester 'echo hello hello'
tester 'echo hello "hello hello"'
tester 'echo hello "hello hello" hello'

printf "\n\033[1m\033[36mCD TESTS\n"


printf "\n\033[1m\033[36mPWD TESTS\n"
tester 'pwd'

printf "\n\033[1m\033[36mEXPORT TESTS\n"
tester 'export var=5'

printf "\n\033[1m\033[36mUNSET TESTS\n"

printf "\n\033[1m\033[36mENV TESTS\n"
# tester 'env'

printf "\n\033[1m\033[36mEXIT TESTS\n"

printf "\n\033[1m\033[36mCMD TESTS\n"
tester 'ls'
tester 'sleep'

printf "\n\033[1m\033[36mCMD with flags TESTS\n"
tester 'ls -l'
tester 'sleep 1'
tester 'cat infile.txt'

printf "\n\033[1m\033[36mCMD with pipe TESTS\n"
tester 'ls | echo'
tester 'ls | cat'
tester 'sleep 1 | ls -l'
tester 'ls -l | sleep 1'

printf "\n\033[1m\033[36mCMD with infile TESTS\n"
tester 'cat < infile.txt'
tester 'ls < infile.txt'

printf "\n\033[1m\033[36mCMD with outfile TESTS\n"
tester 'ls > tester/bredir'
exit

printf "\n\033[1m\033[36mCMD with infile outfile and pipe TESTS\n"
tester 'cat < infile.txt | cat -e'
tester 'cat < infile.txt | ls'
tester 'ls < infile.txt | cat -e'

# rm $OUTFILE1
# rm $OUTFILE2

printf $WHITE