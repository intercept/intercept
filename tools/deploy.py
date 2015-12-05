#!/usr/bin/env python3

import os
import sys
import shutil
import traceback
import subprocess as sp
from pygithub3 import Github


TRANSLATIONISSUE = 13
TRANSLATIONBODY = """## **SQF->C++ Conversion Coverage statistics**

{}
"""

REPOUSER = "NouberNou"
REPONAME = "intercept"
REPOPATH = "{}/{}".format(REPOUSER,REPONAME)


def update_coverage_statistics(token):
    diag = sp.check_output(["python3", "tools/conversion_coverage.py", "--markdown"])
    diag = str(diag, "utf-8")
    repo = Github(token).get_repo(REPOPATH)
    issue = repo.get_issue(TRANSLATIONISSUE)
    issue.edit(body=TRANSLATIONBODY.format(diag))


def main():
    print("Obtaining GH Token ")
    try:
        token = os.environ["GH_TOKEN"]
    except:
        print("Could not obtain token.")
        print(traceback.format_exc())
        return 1
    else:
        print("done.")

    print("\nUpdating coverage issue ...")
    try:
        update_coverage_statistics(token)
    except:
        print("Failed to update coverage issue.")
        print(traceback.format_exc())
        return 1
    else:
        print("done.")

    return 0

if __name__ == "__main__":
    sys.exit(main())
