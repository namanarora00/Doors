typedef unsigned int uint32;

// represents the stack when an isr handler is called by  isr_common_stub
typedef struct registers_t
{
    uint32 ds;                                     // data segment selector
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha
    uint32 int_no, err_code;                       // error code and num pushed in this order
    uint32 eip, cs, eflags, useresp, ss;           //Pushed by processor

} registers_t;
