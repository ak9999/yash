#!/usr/bin/env python


from cmd import Cmd
from getpass import getuser
from socket import gethostname
from pathlib import Path
import subprocess, shlex
import os
import sys

class Shell(Cmd):
    def __init__(self):
        super(Shell, self).__init__()
        self.prompt = self.preloop()


    def Prompt(self, username, hostname, cwd):
        '''Print out the shell prompt.
        Keyword arguments:
        username -- currently logged in username
        hostname -- hostname of computer
        cwd -- current working directory
        '''
        return f'[{username}@{hostname}:{cwd}] % '
    

    def preloop(self):
        username = getuser()
        hostname = gethostname()
        current_working_directory = Path.cwd()
        if current_working_directory == Path.home():
            return self.Prompt(username, hostname, '~')
        else:
            return self.Prompt(username, hostname, current_working_directory)
    

    def postloop(self):
        cwd = None
        if Path.cwd() == Path.home():
            cwd = '~'
        else: cwd = Path.cwd()
        self.prompt = self.Prompt(getuser(), gethostname(), cwd)
    

    def default(self, line):
        command = shlex.split(line)
        try:
            subprocess.Popen(command)
        except EOFError:
            exit()
        except Exception as e:
            print(e)

    
    def emptyline(self): pass
    

    def do_cd(self, path=None):
        if not path:
            if sys.platform == 'win32':
                print(Path.cwd())
            else:
                os.chdir(Path.home())
        else:
            path = Path(path)
            os.chdir(path)
    

    def do_pwd(self, *args):
        print(Path.cwd())
    

    def do_exit(self, *args):
        exit()


if __name__ == '__main__':
    Shell().cmdloop()