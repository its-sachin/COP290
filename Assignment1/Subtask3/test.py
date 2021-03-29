from subprocess import Popen, PIPE

output = Popen(["python3","plots.py"],stdout=PIPE)
response = output.communicate()
print (response)