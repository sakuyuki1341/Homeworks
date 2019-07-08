        .data
newline:.asciiz "\n"
        .text
        .globl  main
        .ent    main
main:
        subu    $sp, 16
        sw      $ra, 12($sp)
#ここまでおまじない-------------------------------------------------

        li      $v0, 5
        syscall                 #read_int
        move    $t0, $v0

        li      $t1, 1
        li      $t2, 1

k1:     beq     $t0, $t1, k2

        mult    $t2, $t0
        mflo    $t2

        sub     $t0, $t0, 1

        b       k1

k2:     move    $a0, $t2
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
