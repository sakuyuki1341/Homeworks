    .data
newline:.asciiz "\n"        #改行を画面に表示するおまじない
hoge:.word  1 4 1 4 2 1 3 5
bar:.word 0 0 0 0 0 0 0 0
    .text
    .align 2
    .globl main
    .ent main
main:
    subu    $sp, 16
    sw      $ra, 12($sp)

    la      $t0, hoge
    la      $t1, bar
    li      $t2, 0          #i
    li      $t3, 8          #定数
    li      $t4, 0          #sum

k1: bge     $t2, $t3, k2

    sll     $t5, $t2, 2
    add     $t6, $t5, $t1
    add     $t5, $t5, $t0
    lw      $t7, 0($t5)

    add     $t4, $t4, $t7

    sw      $t4, 0($t6)

    move    $a0, $t4

    li      $v0, 1          #整数を出力する命令
    syscall                 #$a0の値を画面に表示

    la      $a0, newline    #$a0にnewlineで定義された文字列をコピー
    li      $v0, 4          #文字列を出力する命令
    syscall                 #改行を画面に表示

    add     $t2, $t2, 1
    b       k1

k2: move    $v0, $zero
    lw      $ra, 12($sp)
    addu    $sp, 16
    jr      $ra

    .end
