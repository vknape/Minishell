tester_echo()
{
	if [ $# -eq 0 ]; then
		exit
	fi
	test_main $@
	sed -i	'1d' $OUTFILE2
	sed -i "s@$REM@""@g" $OUTFILE2
	compare_main ''
}