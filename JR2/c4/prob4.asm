        .data
newline:.asciiz "\n"
hoge:   .word  1 4 1 4 2 1 3 5
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
#--関数calc1-------------------------------------------------
calc1:  li      $t0, 1          #factorial
        move    $t1, $a0        #i

k3:     ble     $t1, $zero, k4  #forにおけるi>0
        mul     $t0,$t0,$t1     #factorial *= i
        sub     $t1, 1          #i--

k4:     move    $v0, $t0        #戻り値を専用レジスタに格納
        jr      $ra             #親に帰る

#--関数calc2-------------------------------------------------
calc2:  li      $t0, 0          #sum
        li      $t1, 1          #i

k5:     bgt     $t1,$a0,k6      #forにおけるi<=a
        add     $t0,$t0,1       #sum += 1
        add     $t1, 1          #i++

k6:     move    $v0, $t0        #戻り値を専用レジスタに格納
        jr      $ra             #親に帰る

#--関数func--------------------------------------------------
func:   move    $s7, $ra        #戻り番地の保存

        div     $a0, 2          #条件分岐の準備
        mflo    $t0

        beq     $t0,$zero,toc1  #条件分岐

        jal     calc2           #calc2呼び出し
        j       rtmain

toc1:   jal     calc1           #calc1呼び出し

rtmain: move    $ra, $s7        #戻り番地を保存先から復元する
        jr      $ra             #親に帰る

#--関数print-------------------------------------------------
print:  li      $v0, 1          #整数を出力する命令
        syscall                 #$a0の値を画面に表示

        la      $a0, newline    #$a0にnewlineで定義された文字列をコピー
        li      $v0, 4          #文字列を出力する命令
        syscall                 #改行を画面に表示

        jr      $ra
