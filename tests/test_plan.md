NEWTON NTOITI
SCT212-0180/2024
the msh test plan and the results i got

testing environment is ubuntu linux ...compiler is GCC...compilation command is:gcc -Wall -Wextra -Werror -std=c11 msh.c -o msh while execution command is ./msh

T01:
Feature:           Prompt and input
Test input/action: Start ./msh and enter multiple commands
expected result:   Prompt appears and accepts successive input lines
actual result:     Prompt displayed and accepted multiple commands
status:             pass

T02:                  
Feature:              Blank input and parsing
Test input/action:    Enter blank lines, commands with multiple spaces and tabs
expected result:      Blank input is ignored; arguments are separated correctly
actual result:        Blank input and whitespace handling worked
status:               pass

T03:
Feature:              EOF handling
Test input/action:    press Ctrl+D
expected result:      Shell exits cleanly
actual result:        Shell exited cleanly
status:               pass

T04:
Feature:              External commands
Test input/action:   Run pwd, ls, echo hello
expected result:      Commands execute and display output
actual result:        Commands executed successfully
status:               pass

T05:
Feature:              Unknown command
Test input/action:    Run nosuchcommand
expected result:      Error is reported and status is 127
actual result:        Error reported; next prompt displayed msh[127]>
status:               pass

T06:
Feature:              Built-in help
Test input/action:    run help
expected result:      Help information is displayed
actual result:        Built-in command information displayed
status:               pass

T07:
Feature:              Change directory
Test input/action:     Run cd /tmp, pwd, then cd and pwd
expected result:        Directory changes; no-argument cd returns to HOME
actual result:         Both directory changes worked
status:               pass

T08:
Feature:               exit status
Test input/action:     Run true, false, and nosuchcommand
expected result:        Prompt displays 0, 1, and 127 respectively
actual result:         Observed msh[0]>, msh[1]>, and msh[127]>
status:                pass

T09:
Feature:               Background execution
Test input/action:     Run sleep 5 & followed by echo hello
expected result:        Shell immediately accepts another command
actual result:         PID displayed; echo hello ran while sleep continued
status:                pass

T10: 
Feature:              Zombie prevention
Test input/action:    Allow the background sleep 5 process to finish
expected result:      Completed child is reaped without blocking the shell
actual result:        Shell reported the completed background PID
status:               pass

T11:
Feature:                Basic output redirection
Test input/action:      Run echo hello world > output.txt, then cat output.txt
expected result:        Output is stored in the file
actual result:          File contained hello world
status:                 pass

T12:                    
Feature:                 File overwrite
Test input/action:       Write two different outputs to output.txt and read it
expected result:         Previous contents are replaced
actual result:           File contained only second version
status:                  pass

T13:
Feature:                 Redirect command output
Test input/action:       Run pwd > directory.txt and read the file
expected result:         Current directory is stored in the file
actual result:           Correct working directory was stored
status:                  pass

T14:
Feature:                 Empty output file
Test input/action:       Run echo -n > empty.txt
expected result:         An empty file is created
actual result:            File was created with zero bytes
status:                    pass

T15:
Feature:                 Background redirection
Test input/action:       Run sleep 3 > background.txt &
expected result:         Background command starts and output file is created
actual result:           PID displayed; process completed and was reaped
status:                  pass

T16:
Feature:                Invalid redirection
Test input/action:      Run echo hello >
expected result:        Error is displayed without crashing the shell
actual result:          Invalid redirection error displayed; shell remained operational
status:                 pass

T17:
Feature:                 Ctrl+C handling
Test input/action:        Run sleep 100 and press Ctrl+C
expected result:         Foreground process terminates; shell survives
actual result:           Shell returned with status 130
status:                  pass

T18:
Feature:                Shell recovery after signal
Test input/action:       After interrupting sleep, run echo shell is still alive
expected result:        Shell accepts and executes another command
actual result:          Message displayed successfully; prompt returned with status 0
status:                  pass



The tests covered input handling, argument parsing, process creation, command execution, built-in commands, exit-status reporting, background execution, output redirection, and signal handling.

The observed results demonstrate that all eight required implementation areas were exercised successfully.
