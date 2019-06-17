    .data
newline:.asciiz "\n"
    .text
    .globl main
    .ent main
main:
    subu    $sp, 16
    sw      $ra, 12($sp)
    li      $t0, 10
    li      $t1, 15
    li      $t2, 5
    add     $a0, $t0, $t1
    sub     $a0, $a0, $t2
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
