#!/usr/bin/env python


from getpass import getuser
from socket import gethostname
from pathlib import Path
import subprocess, shlex
# import signal # Need this for blocking KeyboardInterrupt



class Shell:
    colors = {
        'RED':     '\x1b[31m',
        'GREEN':   '\x1b[32m',
        'BLUE':    '\x1b[34m',
        'YELLOW':  '\x1b[33m',
        'MAGENTA': '\x1b[35m',
        'CYAN':    '\x1b[36m',
        'RESET':   '\x1b[0m',
    }

    # @classmethod
    # def colorize(cls, color, string):
    #     pstring = f"{cls.colors[color]} + {string} + {cls.colors['RESET']}"
    #     print(pstring, end='')


    @classmethod
    def print_userhost(cls, username, hostname, current_directory):
        '''Print out the shell prompt.
        Keyword arguments:
        username -- currently logged in username
        hostname -- hostname of computer
        current_directory -- current working directory
        '''
        # cls.colorize(cls.colors['CYAN'], '[')
        # cls.colorize(cls.colors['BLUE'], username + '@' + hostname + ' ')
        # cls.colorize(cls.colors['GREEN'], current_directory)
        # cls.colorize(cls.colors['CYAN'], ']')
        # print(' %% ')
        print("{0}@{1} {2} %%".format(username, hostname, current_directory), end='')
    
    @classmethod
    def loop(cls):
        '''Event loop for the shell.'''
        status = True
        while status:
            user_id = getuser()
            hostname = gethostname()
            current_dir = Path.cwd()
            if current_dir == Path.home():
                cls.print_userhost(user_id, hostname, '~')
            else: cls.print_userhost(user_id, hostname, current_dir)
            
            command = input()
            args = shlex.split(command)
            try:
                p = subprocess.Popen(args)
            except Exception as e:
                pass

if __name__ == '__main__':
    Shell.loop()