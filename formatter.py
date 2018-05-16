import os

extensions = (".c", ".h")

for root, dirs, files in os.walk(os.getcwd()):
    for file in files:
        if file.endswith(extensions):
            os.system("clang-format -i -style=file " + root + "/" + file)