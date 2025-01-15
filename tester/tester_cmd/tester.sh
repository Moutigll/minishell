#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
RESET='\033[0m'

total_tests=0
passed_tests=0

run_test() {
	local description="$1"
	local command="$2"

	total_tests=$((total_tests + 1))

	echo -e "${YELLOW}Test (${total_tests}): ${description}${RESET}"
	echo -e "Command: ${BLUE}${command}${RESET}"

	(echo "${command}" | ./minishell > tmp_out_raw.txt 2> tmp_err.txt) 2>/dev/null
	sed '1d;$d' tmp_out_raw.txt > tmp_out.txt
	local actual_output
	actual_output=$(<tmp_out.txt)

	echo "${command}" | /bin/bash > tmp_out_bash.txt 2> /dev/null
	local bash_output
	bash_output=$(<tmp_out_bash.txt)

	if [ "${actual_output}" == "${bash_output}" ]; then
		echo -e "${GREEN}✓ Success: Output matches${RESET}"
		passed_tests=$((passed_tests + 1))
	else
		echo -e "${RED}✗ Failed: Output mismatch${RESET}"
		echo -e "Expected output:\n${BLUE}${bash_output}${RESET}"
		echo -e "Actual output:\n${RED}${actual_output}${RESET}"
	fi

	if [ -s tmp_err.txt ]; then
		echo -e "${BLUE}Standard Error:${RESET}"
		cat tmp_err.txt
	fi
	echo -e "${RESET}"
}



echo -e "${YELLOW}Starting Shell Tests...${RESET}\n"

run_test "Simple echo" "echo 'Hello, World!'"
run_test "Afficher date" "date"
run_test "Simple ls" "ls"
run_test "Redirection de stdin" "cat < /etc/hostname"
run_test "Commande avec pipe simple" "ls | wc -l"
run_test "Commande avec pipe et grep" "cat /etc/passwd | grep root"
run_test "Commande avec pipe et redirection" "ls | tee tmp_ls | wc -l"
run_test "Commande avec plusieurs pipes" "cat /etc/passwd | grep bin | cut -d':' -f1 | sort"
run_test "Lister fichiers cachés" "ls -a | grep '^\.'"
run_test "Afficher le type de fichiers" "file /etc/passwd"
run_test "Utiliser find pour chercher un fichier" "find . -name '*.sh'"
run_test "Echo avec redirection" "echo 'abc' > tmp"


rm -f tmp_out_raw.txt tmp_out.txt tmp_err.txt tmp_out_bash.txt tmp_out_bash_filtered.txt tmp_file tmp_date tmp_ls

echo -e "${GREEN}Tests completed: ${passed_tests}/${total_tests} passed.${RESET}"
