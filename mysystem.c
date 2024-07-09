/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
int mysystem(char *command) {
  int status = 0;

  // ここにプログラムを書く

  pid_t pid;

  if (command == NULL) {
    return 1; // コマンドがNULLの場合、非ゼロを返す
  }

  pid = fork();
  if (pid < 0) {
    // forkに失敗
    perror("fork failed");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    // 子プロセス
    execl("/bin/sh", "sh", "-c", command, (char *) NULL);
    // execlが失敗した場合
    perror("execl failed");
    exit(EXIT_FAILURE);
  } else {
    // 親プロセス
    if (waitpid(pid, &status, 0) == -1) {
      // waitpidに失敗
      perror("waitpid failed");
      exit(EXIT_FAILURE);
    }
  }
  return status;
}

/* 実行例

ここに実行例を書く
% make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c

% ls -l
total 584
-rw-r--r--  1 murafuto  staff     143  7  9 10:00 Makefile
-rw-r--r--  1 murafuto  staff    2795  7  9 10:00 README.md
-rw-r--r--  1 murafuto  staff  238232  7  9 10:00 README.pdf
-rwxr-xr-x  1 murafuto  staff   33416  7  9 10:28 mysysmain
-rw-r--r--  1 murafuto  staff     925  7  9 10:00 mysysmain.c
-rw-r--r--  1 murafuto  staff    1025  7  9 10:28 mysystem.c
-rw-r--r--  1 murafuto  staff      90  7  9 10:00 mysystem.h

% ./mysysmain "ls -l"
mysystem:
total 584
-rw-r--r--  1 murafuto  staff     143  7  9 10:00 Makefile
-rw-r--r--  1 murafuto  staff    2795  7  9 10:00 README.md
-rw-r--r--  1 murafuto  staff  238232  7  9 10:00 README.pdf
-rwxr-xr-x  1 murafuto  staff   33416  7  9 10:28 mysysmain
-rw-r--r--  1 murafuto  staff     925  7  9 10:00 mysysmain.c
-rw-r--r--  1 murafuto  staff    1025  7  9 10:28 mysystem.c
-rw-r--r--  1 murafuto  staff      90  7  9 10:00 mysystem.h
retval = 00000000
system:
total 584
-rw-r--r--  1 murafuto  staff     143  7  9 10:00 Makefile
-rw-r--r--  1 murafuto  staff    2795  7  9 10:00 README.md
-rw-r--r--  1 murafuto  staff  238232  7  9 10:00 README.pdf
-rwxr-xr-x  1 murafuto  staff   33416  7  9 10:28 mysysmain
-rw-r--r--  1 murafuto  staff     925  7  9 10:00 mysysmain.c
-rw-r--r--  1 murafuto  staff    1025  7  9 10:28 mysystem.c
-rw-r--r--  1 murafuto  staff      90  7  9 10:00 mysystem.h
retval = 00000000

%./mysysmain
使い方 : ./mysysmain コマンド文字列

*/
