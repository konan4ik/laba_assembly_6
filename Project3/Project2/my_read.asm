.686
.model flat, C
option casemap: none
includelib kernel32.lib
include E:\masm32\include\windows.inc
include E:\masm32\include\kernel32.inc

.stack

.data
hndlFile DWORD 0
nbyteread DWORD 0
numbytes DWORD 512
soob DWORD 0

.code

my_read Proc
; пролог, сохраняем base pointer, на основе его
; расчитывается параметр в стеке
push ebp
mov ebp, esp
push ebx
mov eax,[ebp+8]
mov ebx,[ebp+12]
mov ecx,[ebp+16]
mov numbytes, ecx

mov soob, ebx
;push eax

invoke CreateFile, eax, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0

mov hndlFile, eax

invoke ReadFile, hndlFile, ebx, numbytes, ADDR nbyteread, 0

invoke CloseHandle, hndlFile
pop ebx
mov esp,ebp
pop ebp
ret
my_read ENDP

end