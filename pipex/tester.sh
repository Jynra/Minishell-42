#!/bin/bash

# ======== CONFIGURATION ========
PIPEX_PATH="./pipex"
TEST_DIR="./test"
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
BLUE="\033[0;34m"
RESET="\033[0m"

# ======== SETUP ========
# Create test directory
mkdir -p $TEST_DIR

# Create test files
echo "Hello world" > $TEST_DIR/infile.txt
echo "This is a test" >> $TEST_DIR/infile.txt
echo "Testing pipex" >> $TEST_DIR/infile.txt
echo "Another test line" >> $TEST_DIR/infile.txt

echo "Line 1" > $TEST_DIR/infile2.txt
echo "Line 2" >> $TEST_DIR/infile2.txt
echo "Line 3" >> $TEST_DIR/infile2.txt
echo "test Line 4" >> $TEST_DIR/infile2.txt
echo "test Line 5" >> $TEST_DIR/infile2.txt

# Function to print header
print_header() {
    echo -e "\n${BLUE}===============================================${RESET}"
    echo -e "${BLUE}   $1${RESET}"
    echo -e "${BLUE}===============================================${RESET}\n"
}

# Function to print test result
print_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✓ PASS: $2${RESET}"
    else
        echo -e "${RED}✗ FAIL: $2${RESET}"
    fi
}

# Function to compare output
compare_output() {
    local expected="$1"
    local actual="$2"
    local test_name="$3"
    
    if [ "$expected" = "$actual" ]; then
        print_result 0 "$test_name - Output matches"
    else
        print_result 1 "$test_name - Output doesn't match"
        echo -e "${YELLOW}Expected: '$expected'${RESET}"
        echo -e "${YELLOW}Actual  : '$actual'${RESET}"
    fi
}

# ======== TESTS ========
print_header "BASIC FUNCTIONALITY TESTS"

# Test 1: Basic pipe functionality
echo -e "${YELLOW}Test 1: Basic pipe functionality${RESET}"
$PIPEX_PATH $TEST_DIR/infile.txt "grep test" "wc -l" $TEST_DIR/outfile1.txt 2>/dev/null
RETURN_CODE=$?
print_result $RETURN_CODE "Program execution"

# Compare with actual bash command
EXPECTED=$(grep test < $TEST_DIR/infile.txt | wc -l)
ACTUAL=$(cat $TEST_DIR/outfile1.txt)
compare_output "$EXPECTED" "$ACTUAL" "Basic pipe"

# Test 2: Case-insensitive grep
echo -e "\n${YELLOW}Test 2: Case-insensitive grep${RESET}"
$PIPEX_PATH $TEST_DIR/infile.txt "grep -i TEST" "wc -w" $TEST_DIR/outfile2.txt 2>/dev/null
RETURN_CODE=$?
print_result $RETURN_CODE "Program execution"

# Compare with actual bash command
EXPECTED=$(grep -i TEST < $TEST_DIR/infile.txt | wc -w)
ACTUAL=$(cat $TEST_DIR/outfile2.txt)
compare_output "$EXPECTED" "$ACTUAL" "Case-insensitive grep"

print_header "MULTIPLE PIPES BONUS TESTS"

# Test 3: Three commands
echo -e "${YELLOW}Test 3: Three commands${RESET}"
$PIPEX_PATH $TEST_DIR/infile2.txt "grep test" "wc -l" "cat -e" $TEST_DIR/outfile3.txt 2>/dev/null
RETURN_CODE=$?
print_result $RETURN_CODE "Program execution"

# Compare with actual bash command
EXPECTED=$(grep test < $TEST_DIR/infile2.txt | wc -l | cat -e)
ACTUAL=$(cat $TEST_DIR/outfile3.txt)
compare_output "$EXPECTED" "$ACTUAL" "Three commands"

# Test 4: Four commands
echo -e "\n${YELLOW}Test 4: Four commands${RESET}"
$PIPEX_PATH $TEST_DIR/infile2.txt "cat" "grep test" "wc -l" "cat -e" $TEST_DIR/outfile4.txt 2>/dev/null
RETURN_CODE=$?
print_result $RETURN_CODE "Program execution"

# Compare with actual bash command
EXPECTED=$(cat < $TEST_DIR/infile2.txt | grep test | wc -l | cat -e)
ACTUAL=$(cat $TEST_DIR/outfile4.txt)
compare_output "$EXPECTED" "$ACTUAL" "Four commands"

print_header "HEREDOC BONUS TESTS"

# Test 5: Heredoc functionality
echo -e "\n${YELLOW}Test 5: Heredoc functionality${RESET}"

# Créer un fichier temporaire pour tester heredoc
echo "This is a test line with the word test" > $TEST_DIR/heredoc_temp.txt
echo "Another line with test word" >> $TEST_DIR/heredoc_temp.txt
echo "Nothing should match here" >> $TEST_DIR/heredoc_temp.txt
echo "EOF" >> $TEST_DIR/heredoc_temp.txt

# Exécuter pipex avec heredoc en utilisant le fichier temporaire
$PIPEX_PATH here_doc EOF "grep test" "wc -l" $TEST_DIR/pipex_heredoc.txt < $TEST_DIR/heredoc_temp.txt 2>/dev/null
RETURN_CODE=$?
print_result $RETURN_CODE "Program execution"

# Créer la sortie attendue
grep test << EOF | wc -l > $TEST_DIR/bash_heredoc.txt
This is a test line with the word test
Another line with test word
Nothing should match here
EOF

# Comparer les sorties
EXPECTED=$(cat $TEST_DIR/bash_heredoc.txt)
ACTUAL=$(cat $TEST_DIR/pipex_heredoc.txt)
compare_output "$EXPECTED" "$ACTUAL" "Heredoc functionality"

# Test 6: Heredoc append mode
echo -e "\n${YELLOW}Test 6: Heredoc append mode${RESET}"
echo "Previous content" > $TEST_DIR/append_test.txt

# Créer un fichier temporaire pour tester heredoc
echo "This should not match" > $TEST_DIR/heredoc_temp2.txt
echo "EOF" >> $TEST_DIR/heredoc_temp2.txt

# Exécuter pipex avec heredoc en mode append
$PIPEX_PATH here_doc EOF "grep nothing" "wc -l" $TEST_DIR/append_test.txt < $TEST_DIR/heredoc_temp2.txt 2>/dev/null
RETURN_CODE=$?
print_result $RETURN_CODE "Program execution"

# Créer la sortie attendue
echo "Previous content" > $TEST_DIR/expected_append.txt
grep nothing << EOF | wc -l >> $TEST_DIR/expected_append.txt
This should not match
EOF

# Comparer les sorties
EXPECTED=$(cat $TEST_DIR/expected_append.txt)
ACTUAL=$(cat $TEST_DIR/append_test.txt)
compare_output "$EXPECTED" "$ACTUAL" "Heredoc append mode"

print_header "ERROR HANDLING TESTS"

# Test 7: Non-existent input file
echo -e "${YELLOW}Test 7: Non-existent input file${RESET}"
$PIPEX_PATH $TEST_DIR/nonexistent.txt "cat" "wc -l" $TEST_DIR/outfile7.txt 2>&1 | grep -i "Cannot open infile" > /dev/null
RETURN_CODE=$?
print_result $RETURN_CODE "Non-existent input file (should display error)"

# Test 8: Invalid command
echo -e "\n${YELLOW}Test 8: Invalid command${RESET}"
$PIPEX_PATH $TEST_DIR/infile.txt "invalidcommand" "wc -l" $TEST_DIR/outfile8.txt 2>&1 | grep -i "Command not found" > /dev/null
RETURN_CODE=$?
print_result $RETURN_CODE "Invalid command (should display error)"

# ======== CLEANUP ========
print_header "CLEANUP"
echo -e "Removing test files and directory..."
rm -rf $TEST_DIR
echo -e "${GREEN}All tests completed!${RESET}"