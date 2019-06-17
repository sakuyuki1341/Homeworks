    .data
newline:.asciiz "\n"        #改行を画面に表示するおまじない
    .text
    .globl main
    .ent main
main:
    subu    $sp, 16
    sw      $ra, 12($sp)

    li      $v0, 5
    syscall                 #read_int
    move    $t0, $v0

    li      $v0, 5
    syscall                 #read_int
    move    $t1, $v0

    add     $a0, $t0, $t1

    li      $v0, 1          #整数を出力する命令
    syscall                 #$a0の値を画面に表示

    la      $a0, newline    #$a0にnewlineで定義された文字列をコピー
    li      $v0, 4          #文字列を出力する命令
    syscall                 #改行を画面に表示

    move    $v0, $zero
    lw      $ra, 12($sp)
    addu    $sp, 16
    jr      $ra
    .end
