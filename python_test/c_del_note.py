#!/usr/bin/python
# !conding=utf8

import os
import re
import sys
for i in range(0, len(sys.argv)):
    print ("参数", i, sys.argv[i])
# 根目录
count=0
if len(sys.argv)!=2:
    print("请正确输入要操作的目录")
    exit()
else:
    dir = sys.argv[1]

g = os.walk(dir)
C_Rule = "(//.*)|(/\*[\s\S]*?\*/)"
def del_note(filename):
    global count
    code_file = open(filename,"r+")
    code_content = code_file.read()
    code_content = re.sub(C_Rule, "", code_content)
    code_content=code_content.splitlines(True)
    new_content=''
    for line in code_content:
        if re.match(r'^[ \t]*$',line)==None:
            new_content = new_content+line
        count=count+1
    code_file.seek(0,0)
    code_file.write(new_content)
    code_file.truncate()
    code_file.close()


for path, d, filelist in g:
    for filename in filelist:
        if re.match(".*\.(c|cpp|h)",filename)!=None:
         print(os.path.join(path, filename))
         del_note(os.path.join(path, filename))
print("总代码行数： %d"%count)
#
