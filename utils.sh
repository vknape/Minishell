logs=$(ls -l leaks | wc -l)
logs=$((logs-1))

clear_logs()
{
	while [ $logs -gt 0 ]
	do
		rm leaks/*.txt
		logs=$((logs-1))
		echo $logs
	done

}