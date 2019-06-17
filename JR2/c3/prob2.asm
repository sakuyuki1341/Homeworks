    .data
newline:.asciiz "\n"        #改行を画面に表示するおまじない
    .text
    .globl main
    .ent main
main:
    subu    $sp, 16
    sw      $ra, 12($sp)
    li      $t0, 9
    li      $t1, 2
    div     $t0, $t1

    mflo    $a0
    li      $v0, 1          #整数を出力する命令
    syscall                 #$a0の値を画面に表示

    la      $a0, newline    #$a0にnewlineで定義された文字列をコピー
    li      $v0, 4          #文字列を出力する命令
    syscall                 #改行を画面に表示

    mfhi    $a0
    li      $v0, 1
    syscall

    la      $a0, newline
    li      $v0, 4
    syscall

    move    $v0, $zero
    lw      $ra, 12($sp)
    addu    $sp, 16
    jr      $ra
    .end
