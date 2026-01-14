.686
.model flat, C
option casemap: none
includelib kernel32.lib
include E:\masm32\include\windows.inc
include E:\masm32\include\kernel32.inc

.stack

.data
hndlFile DWORD 0
numbytesW DWORD 12
numbytesR DWORD 100
nbyteread DWORD 0
soob DWORD 0

.code

my_write Proc
; пролог, сохраняем base pointer, на основе его
; расчитывается параметр в стеке
push ebp
mov ebp, esp
push ebx
mov eax,[ebp+8]
mov ebx,[ebp+12]
mov soob, ebx
;push eax
invoke CreateFile, eax, GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
FILE_ATTRIBUTE_NORMAL, 0
mov hndlFile, eax

invoke SetFilePointer, hndlFile, 0, 0, FILE_END

invoke WriteFile, hndlFile, ebx, numbytesW, ADDR nbyteread, 0

invoke CloseHandle, hndlFile
pop ebx
mov esp,ebp
pop ebp
ret
my_write ENDP


end