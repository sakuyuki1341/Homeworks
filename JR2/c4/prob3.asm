        .data
newline:.asciiz "\n"
hoge:.word  1 4 1 4 2 1 3 5
        .text
        .globl  main
        .ent    main
main:
        subu    $sp, 16
        sw      $ra, 12($sp)
#ここまでおまじない-------------------------------------------------
        li      $s0, 0          #ループ用のi
        li      $s1, 8          #ループ回数の最大数
        la      $s2, hoge
        li      $s3, 0          #sum
k1:     bge     $s0, $s1, k2

        sll     $s4, $s0, 2     #hoge読み込み準備
        add     $s4, $s4, $s2
        lw      $a0, 0($s4)

        jal     func
        add     $s3, $s3, $v0

        move    $a0, $s3
        jal     print

        add     $s0, $s0, 1

        b       k1

k2:     move    $v0, $zero
        lw      $ra, 12($sp)
        addu    $sp, 16
        jr      $ra

        .end

#ここからサブルーチン-----------------------------------------------
func:   move    $v0, $a0

        mult    $v0, $v0
        mfl0    $v0

        add     $v0, $v0, 1

        j       $ra

print:  li      $v0, 1          #整数を出力する命令
        syscall                 #$a0の値を画面に表示

        la      $a0, newline    #$a0にnewlineで定義された文字列をコピー
        li      $v0, 4          #文字列を出力する命令
        syscall                 #改行を画面に表示

        j       $ra
