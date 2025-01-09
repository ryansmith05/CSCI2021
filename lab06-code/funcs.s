.text
.global my_max
.global my_pow

# Computes maximum of 2 arguments
# You can assume argument 1 (x) is in %edi
# You can assume argument 2 (y) is in %esi
# If you need to store temporary values, you may use the following registers:
#   %eax, %ecx, %edx, %esi, %edi, %r8d, %r9d, %r10d, %r11d
# DO NOT USE other registers. We will learn why soon.
my_max:
    cmpl %esi, %edi      
    jge .Lreturn_x       
    movl %esi, %eax      
    ret
.Lreturn_x:
    movl %edi, %eax      # Move x into %eax (return x)
    ret

# Computes base^exp
# You can assume argument 1 (base) is in %edi
# You can assume argument 2 (exp) is in %esi
# If you need to store temporary values, you may use the following registers:
#   %eax, %ecx, %edx, %esi, %edi, %r8d, %r9d, %r10d, %r11d
# DO NOT USE other registers. We will learn why soon.
my_pow:
    cmpl $1, %esi        
    jle .Ldone           
    movl %edi, %eax      
    movl $2, %ecx        
.Lloop:
    cmpl %esi, %ecx      
    jg .Ldone           
    imull %edi, %eax     
    incl %ecx            
    jmp .Lloop           
.Ldone:
    ret                  
