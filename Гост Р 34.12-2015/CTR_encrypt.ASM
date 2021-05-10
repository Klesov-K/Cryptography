format pe console
include 'win32ax.inc'

SEEK_SET equ 0  ; Относительно начала файлаб начало файла- позиция 0
SEEK_CUR equ 1  ;Относительно текущей позицииб > 0-впередб <0 назад
SEEK_END equ 2  ; Относительно конца файла(значение pos-отрицательное)
NULL     equ 0
EOF      equ -1
section '.data' data readable writable
        msgA db 'Hello,Reverse Engineer    ',0
        msgB db 'Enter string    ',0
        fbuf32          db 4 dup(0)
        fbuf64          db 4 dup(0)
        synchro_package db 0x12 ,0x34, 0x56, 0x78
        Init_Vector     db 8 dup(0)
        new_fbuf        db 8 dup(0)
        gamma           db 8 dup(0)
        length_buf_wr   dd 8

        buftobewritten  db 4 dup(0)
        handle          dd 0

        file_encrypted db 'C:\Fasm\fasmw17316\Text\decrypt.txt',0

        i dd ?
        j dd ?
        length dd ? ;длина сбокса
        N2 db 4 dup(0)
       ; key db '00001111222233334444555566667777',0
        key_step db '1234',0
        key0 db '9999',0
        key1 db '9999',0
        key2 db '9999',0
        key3 db '9999',0
        key4 db '9999',0
        key5 db '9999',0
        key6 db '9999',0
        key7 db '9999',0

        fbuf64_0 db '0'
        fbuf64_1 db '0'
        fbuf64_2 db '0'
        fbuf64_3 db '0'
        fbuf64_4 db '0'
        fbuf64_5 db '0'
        fbuf64_6 db '0'
        fbuf64_7 db '0'

         sbox db 0xc6, 0xc8, 0xc2 , 0xc3 , 0xc9 , 0xca , 0xc5 , 0xcc , 0xc1 ,0xce , 0xc4 ,0xc7 , 0xcb , 0xcd , 0xc0 , 0xcf ,\
                0x46, 0x48, 0x42 , 0x43 , 0x49 , 0x4a , 0x45 , 0x4c , 0x41 ,0x4e , 0x44 ,0x47 , 0x4b , 0x4d , 0x40 , 0x4f ,\
                0x66, 0x68, 0x62 , 0x63 , 0x69 , 0x6a , 0x65 , 0x6c , 0x61 ,0x6e , 0x64 ,0x67 , 0x6b , 0x6d , 0x60 , 0x6f ,\
                0x26, 0x28, 0x22 , 0x23 , 0x29 , 0x2a , 0x25 , 0x2c , 0x21 ,0x2e , 0x24 ,0x27 , 0x2b , 0x2d , 0x20 , 0x2f ,\
                0xa6, 0xa8, 0xa2 , 0xa3 , 0xa9 , 0xaa , 0xa5 , 0xac , 0xa1 ,0xae , 0xa4 ,0xa7 , 0xab , 0xad , 0xa0 , 0xaf ,\
                0x56, 0x58, 0x52 , 0x53 , 0x59 , 0x5a , 0x55 , 0x5c , 0x51 ,0x5e , 0x54 ,0x57 , 0x5b , 0x5d , 0x50 , 0x5f ,\
                0xb6, 0xb8, 0xb2 , 0xb3 , 0xb9 , 0xba , 0xb5 , 0xbc , 0xb1 ,0xbe , 0xb4 ,0xb7 , 0xbb , 0xbd , 0xb0 , 0xbf ,\
                0x96, 0x98, 0x92 , 0x93 , 0x99 , 0x9a , 0x95 , 0x9c , 0x91 ,0x9e , 0x94 ,0x97 , 0x9b , 0x9d , 0x90 , 0x9f ,\
                0xe6, 0xe8, 0xe2 , 0xe3 , 0xe9 , 0xea , 0xe5 , 0xec , 0xe1 ,0xee , 0xe4 ,0xe7 , 0xeb , 0xed , 0xe0 , 0xef ,\
                0x86, 0x88, 0x82 , 0x83 , 0x89 , 0x8a , 0x85 , 0x8c , 0x81 ,0x8e , 0x84 ,0x87 , 0x8b , 0x8d , 0x80 , 0x8f ,\
                0xd6, 0xd8, 0xd2 , 0xd3 , 0xd9 , 0xda , 0xd5 , 0xdc , 0xd1 ,0xde , 0xd4 ,0xd7 , 0xdb , 0xdd , 0xd0 , 0xdf ,\
                0x76, 0x78, 0x72 , 0x73 , 0x79 , 0x7a , 0x75 , 0x7c , 0x71 ,0x7e , 0x74 ,0x77 , 0x7b , 0x7d , 0x70 , 0x7f ,\
                0x06, 0x08, 0x02 , 0x03 , 0x09 , 0x0a , 0x05 , 0x0c , 0x01 ,0x0e , 0x04 ,0x07 , 0x0b , 0x0d , 0x00 , 0x0f ,\
                0x36, 0x38, 0x32 , 0x33 , 0x39 , 0x3a , 0x35 , 0x3c , 0x31 ,0x3e , 0x34 ,0x37 , 0x3b , 0x3d , 0x30 , 0x3f ,\
                0xf6, 0xf8, 0xf2 , 0xf3 , 0xf9 , 0xfa , 0xf5 , 0xfc , 0xf1 ,0xfe , 0xf4 ,0xf7 , 0xfb , 0xfd , 0xf0 , 0xff ,\
                0x16, 0x18, 0x12 , 0x13 , 0x19 , 0x1a , 0x15 , 0x1c , 0x11 ,0x1e , 0x14 ,0x17 , 0x1b , 0x1d , 0x10 , 0x1f ,\               ;2 блок
                0xbc, 0xb8, 0xb2 , 0xb1 , 0xbd , 0xb4 , 0xbf , 0xb6 , 0xb7 ,0xb0 , 0xba ,0xb5 , 0xb3 , 0xbe , 0xb9 , 0xbb ,\
                0x3c, 0x38, 0x32 , 0x31 , 0x3d , 0x34 , 0x3f , 0x36 , 0x37 ,0x30 , 0x3a ,0x35 , 0x33 , 0x3e , 0x39 , 0x3b ,\
                0x5c, 0x58, 0x52 , 0x51 , 0x5d , 0x54 , 0x5f , 0x56 , 0x57 ,0x50 , 0x5a ,0x55 , 0x53 , 0x5e , 0x59 , 0x5b ,\
                0x8c, 0x88, 0x82 , 0x81 , 0x8d , 0x84 , 0x8f , 0x86 , 0x87 ,0x80 , 0x8a ,0x85 , 0x83 , 0x8e , 0x89 , 0x8b ,\
                0x2c, 0x28, 0x22 , 0x21 , 0x2d , 0x24 , 0x2f , 0x26 , 0x27 ,0x20 , 0x2a ,0x25 , 0x23 , 0x2e , 0x29 , 0x2b ,\
                0xfc, 0xf8, 0xf2 , 0xf1 , 0xfd , 0xf4 , 0xff , 0xf6 , 0xf7 ,0xf0 , 0xfa ,0xf5 , 0xf3 , 0xfe , 0xf9 , 0xfb ,\
                0xac, 0xa8, 0xa2 , 0xa1 , 0xad , 0xa4 , 0xaf , 0xa6 , 0xa7 ,0xa0 , 0xaa ,0xa5 , 0xa3 , 0xae , 0xa9 , 0xab ,\
                0xdc, 0xd8, 0xd2 , 0xd1 , 0xdd , 0xd4 , 0xdf , 0xd6 , 0xd7 ,0xd0 , 0xda ,0xd5 , 0xd3 , 0xde , 0xd9 , 0xdb ,\
                0xec, 0xe8, 0xe2 , 0xe1 , 0xed , 0xe4 , 0xef , 0xe6 , 0xe7 ,0xe0 , 0xea ,0xe5 , 0xe3 , 0xee , 0xe9 , 0xeb ,\
                0x1c, 0x18, 0x12 , 0x11 , 0x1d , 0x14 , 0x1f , 0x16 , 0x17 ,0x10 , 0x1a ,0x15 , 0x13 , 0x1e , 0x19 , 0x1b ,\
                0x7c, 0x78, 0x72 , 0x71 , 0x7d , 0x74 , 0x7f , 0x76 , 0x77 ,0x70 , 0x7a ,0x75 , 0x73 , 0x7e , 0x79 , 0x7b ,\
                0x4c, 0x48, 0x42 , 0x41 , 0x4d , 0x44 , 0x4f , 0x46 , 0x47 ,0x40 , 0x4a ,0x45 , 0x43 , 0x4e , 0x49 , 0x4b ,\
                0xcc, 0xc8, 0xc2 , 0xc1 , 0xcd , 0xc4 , 0xcf , 0xc6 , 0xc7 ,0xc0 , 0xca ,0xc5 , 0xc3 , 0xce , 0xc9 , 0xcb ,\
                0x9c, 0x98, 0x92 , 0x91 , 0x9d , 0x94 , 0x9f , 0x96 , 0x97 ,0x90 , 0x9a ,0x95 , 0x93 , 0x9e , 0x99 , 0x9b ,\
                0x6c, 0x68, 0x62 , 0x61 , 0x6d , 0x64 , 0x6f , 0x66 , 0x67 ,0x60 , 0x6a ,0x65 , 0x63 , 0x6e , 0x69 , 0x6b ,\
                0x0c, 0x08, 0x02 , 0x01 , 0x0d , 0x04 , 0x0f , 0x06 , 0x07 ,0x00 , 0x0a ,0x05 , 0x03 , 0x0e , 0x09 , 0x0b ,\               ; 3 блок
                0x75, 0x7d, 0x7f,  0x76,  0x79,  0x72,  0x7c,  0x7a,  0x7b, 0x77,  0x78, 0x71,  0x74,  0x73,  0x7e,  0x70, \
                0xf5, 0xfd, 0xff,  0xf6,  0xf9,  0xf2,  0xfc,  0xfa,  0xfb, 0xf7,  0xf8, 0xf1,  0xf4,  0xf3,  0xfe,  0xf0, \
                0x55, 0x5d, 0x5f,  0x56,  0x59,  0x52,  0x5c,  0x5a,  0x5b, 0x57,  0x58, 0x51,  0x54,  0x53,  0x5e,  0x50, \
                0xa5, 0xad, 0xaf,  0xa6,  0xa9,  0xa2,  0xac,  0xaa,  0xab, 0xa7,  0xa8, 0xa1,  0xa4,  0xa3,  0xae,  0xa0, \
                0x85, 0x8d, 0x8f,  0x86,  0x89,  0x82,  0x8c,  0x8a,  0x8b, 0x87,  0x88, 0x81,  0x84,  0x83,  0x8e,  0x80, \
                0x15, 0x1d, 0x1f,  0x16,  0x19,  0x12,  0x1c,  0x1a,  0x1b, 0x17,  0x18, 0x11,  0x14,  0x13,  0x1e,  0x10, \
                0x65, 0x6d, 0x6f,  0x66,  0x69,  0x62,  0x6c,  0x6a,  0x6b, 0x67,  0x68, 0x61,  0x64,  0x63,  0x6e,  0x60, \
                0xd5, 0xdd, 0xdf,  0xd6,  0xd9,  0xd2,  0xdc,  0xda,  0xdb, 0xd7,  0xd8, 0xd1,  0xd4,  0xd3,  0xde,  0xd0, \
                0x05, 0x0d, 0x0f,  0x06,  0x09,  0x02,  0x0c,  0x0a,  0x0b, 0x07,  0x08, 0x01,  0x04,  0x03,  0x0e,  0x00, \
                0x95, 0x9d, 0x9f,  0x96,  0x99,  0x92,  0x9c,  0x9a,  0x9b, 0x97,  0x98, 0x91,  0x94,  0x93,  0x9e,  0x90, \
                0x35, 0x3d, 0x3f,  0x36,  0x39,  0x32,  0x3c,  0x3a,  0x3b, 0x37,  0x38, 0x31,  0x34,  0x33,  0x3e,  0x30, \
                0xe5, 0xed, 0xef,  0xe6,  0xe9,  0xe2,  0xec,  0xea,  0xeb, 0xe7,  0xe8, 0xe1,  0xe4,  0xe3,  0xee,  0xe0, \
                0xb5, 0xbd, 0xbf,  0xb6,  0xb9,  0xb2,  0xbc,  0xba,  0xbb, 0xb7,  0xb8, 0xb1,  0xb4,  0xb3,  0xbe,  0xb0, \
                0x45, 0x4d, 0x4f,  0x46,  0x49,  0x42,  0x4c,  0x4a,  0x4b, 0x47,  0x48, 0x41,  0x44,  0x43,  0x4e,  0x40, \
                0x25, 0x2d, 0x2f,  0x26,  0x29,  0x22,  0x2c,  0x2a,  0x2b, 0x27,  0x28, 0x21,  0x24,  0x23,  0x2e,  0x20, \
                0xc5, 0xcd, 0xcf,  0xc6,  0xc9,  0xc2,  0xcc,  0xca,  0xcb, 0xc7,  0xc8, 0xc1,  0xc4,  0xc3,  0xce,  0xc0, \              ; 4 блок
                0x81, 0x87, 0x8e,  0x8d,  0x80,  0x85,  0x88,  0x83,  0x84, 0x8f,  0x8a,  0x86,  0x89,  0x8c,  0x8b,  0x82,\
                0xe1, 0xe7, 0xee,  0xed,  0xe0,  0xe5,  0xe8,  0xe3,  0xe4, 0xef,  0xea,  0xe6,  0xe9,  0xec,  0xeb,  0xe2,\
                0x21, 0x27, 0x2e,  0x2d,  0x20,  0x25,  0x28,  0x23,  0x24, 0x2f,  0x2a,  0x26,  0x29,  0x2c,  0x2b,  0x22,\
                0x51, 0x57, 0x5e,  0x5d,  0x50,  0x55,  0x58,  0x53,  0x54, 0x5f,  0x5a,  0x56,  0x59,  0x5c,  0x5b,  0x52,\
                0x61, 0x67, 0x6e,  0x6d,  0x60,  0x65,  0x68,  0x63,  0x64, 0x6f,  0x6a,  0x66,  0x69,  0x6c,  0x6b,  0x62,\
                0x91, 0x97, 0x9e,  0x9d,  0x90,  0x95,  0x98,  0x93,  0x94, 0x9f,  0x9a,  0x96,  0x99,  0x9c,  0x9b,  0x92,\
                0x11, 0x17, 0x1e,  0x1d,  0x10,  0x15,  0x18,  0x13,  0x14, 0x1f,  0x1a,  0x16,  0x19,  0x1c,  0x1b,  0x12,\
                0xc1, 0xc7, 0xce,  0xcd,  0xc0,  0xc5,  0xc8,  0xc3,  0xc4, 0xcf,  0xca,  0xc6,  0xc9,  0xcc,  0xcb,  0xc2,\
                0xf1, 0xf7, 0xfe,  0xfd,  0xf0,  0xf5,  0xf8,  0xf3,  0xf4, 0xff,  0xfa,  0xf6,  0xf9,  0xfc,  0xfb,  0xf2,\
                0x41, 0x47, 0x4e,  0x4d,  0x40,  0x45,  0x48,  0x43,  0x44, 0x4f,  0x4a,  0x46,  0x49,  0x4c,  0x4b,  0x42,\
                0xb1, 0xb7, 0xbe,  0xbd,  0xb0,  0xb5,  0xb8,  0xb3,  0xb4, 0xbf,  0xba,  0xb6,  0xb9,  0xbc,  0xbb,  0xb2,\
                0x01, 0x07, 0x0e,  0x0d,  0x00,  0x05,  0x08,  0x03,  0x04, 0x0f,  0x0a,  0x06,  0x09,  0x0c,  0x0b,  0x02,\
                0xd1, 0xd7, 0xde,  0xdd,  0xd0,  0xd5,  0xd8,  0xd3,  0xd4, 0xdf,  0xda,  0xd6,  0xd9,  0xdc,  0xdb,  0xd2,\
                0xa1, 0xa7, 0xae,  0xad,  0xa0,  0xa5,  0xa8,  0xa3,  0xa4, 0xaf,  0xaa,  0xa6,  0xa9,  0xac,  0xab,  0xa2,\
                0x31, 0x37, 0x3e,  0x3d,  0x30,  0x35,  0x38,  0x33,  0x34, 0x3f,  0x3a,  0x36,  0x39,  0x3c,  0x3b,  0x32,\
                0x71, 0x77, 0x7e,  0x7d,  0x70,  0x75,  0x78,  0x73,  0x74, 0x7f,  0x7a,  0x76,  0x79,  0x7c,  0x7b,  0x72






        time_start  db 8 dup(0)
        time_end    db 8 dup(0)
        time        db 8 dup(0)


        argc        dd ?
        argv        dd ?
        env         dd ?
        fp          dd ?
        fp_k        dd ?
        fp_vector   dd ?
        flength     dd ?
        flength_key dd ?
        key         dd ?
        fbuf        dd ?
        msg         db  '%s %s%s',0
        newstr      db '',13,10,0
        msg_hello   db 'Full path to the file you entered',13,10,0
        errmsg      db "Error.",0



section '.code' code readable executable
entry start



;synchro_package_:

;               push ebp
;               mov ebp, esp

               ;  Вызовем функцию расписания ключей
;               cinvoke fopen,dword [esi+12],'rb'
;               test eax,eax
;               jz .err
;               mov [fp_vector],eax


                ;Устанавливаем указатель чтения-записи в конец файла

;                cinvoke fseek,[fp_vector],0,SEEK_END
;               .if eax <> 0
;                jmp .err
;               .endif

                ;Узнаем значение этого указателя, который равен размеру файла
;               cinvoke ftell, [fp_vector]
;               test eax,eax
;               jz .err
;               cmp eax,32
;               jne .err
              ; mov [flength_key], eax

              ;Запрашиваем динамическую память
               ; размером : длина файла + 1 бит
;               inc eax
;               cinvoke malloc,eax
;               jz .err
;               mov [key],eax  ;



               ;Возвращаем указатель чтения-записи в начало файла
;               cinvoke fseek,[fp_vector],0,SEEK_SET
;               test eax,eax
;               jnz .err



               ;Читаем весь файл в динамическую память
;               cinvoke fread,[synchro_package],1,4,[fp_vector]
;               cmp eax,32
;               jne .err

                ;Записываем 0 в конце строки для обозачения
                ;конца строки
;                mov eax, [synchro_package]
;                add eax, 32
;                mov byte [eax], 0


;                mov esp, ebp
;                pop ebp


;        ret

 inc_CTR:
                push ebp
                mov ebp, esp

                mov esi, Init_Vector
                add dword [esi+4], 1




                mov esp, ebp
                pop ebp

         ret

 init_vector:

                push ebp
                mov ebp, esp

                mov edx,synchro_package
                lea ebx, [edx]
                mov esi,Init_Vector
                mov ecx,4

             ;заполняем инициализирующий вектор байтами синхропосылки
            .init_vector_0_31:

                mov al,[ebx]
                mov byte [esi], al
                inc ebx
                inc esi
                Loop .init_vector_0_31


                mov ecx,4
            ;добиваем инициализирующий вектор нулями
            .init_vector_32_63:

                mov al,0
                mov byte [esi], al
                inc esi
                Loop .init_vector_32_63


                mov esp, ebp
                pop ebp

        ret

 gamma_:
                push ebp
                mov ebp, esp





                mov eax,Init_Vector
                lea esi,[eax]


     _Metka:
                mov ebx,fbuf32         ;зануляем fbuf32 и fbuf64

                push eax
                mov eax, 0
                mov [ebx], eax
                mov [ebx+4], eax
                pop eax



              ;  xor edx,edx
              ;  mov eax,edi
              ;  mov ecx,8
              ;  div ecx
              ;  cmp edx,0         ;длина строки должна быть 8 байт(64 бита)
              ;  jne start.err         ;нужно сделать дополнение до 64 бит

                mov ecx,4          ;ecx=4(32 бита)

             .L32:                  ;fbuf32=адрес 0-32 бит строки fbuf
                mov al,[esi]

                mov byte [ebx],al
                inc esi
                inc ebx
                Loop .L32


              ;  cinvoke printf,<' ; fbuf32 is : %s' >,fbuf32,<13,10,0>

                mov ecx,4       ;ecx=32 бита
                mov ebx,fbuf64

             .L64:                   ;fbuf64=адрес 32-64 бит строки fbuf

                mov al,[esi]

                mov byte [ebx],al
                inc esi
                inc ebx
                Loop .L64


             ;   cinvoke printf,<'  fbuf64 is : %s ;  ' >,fbuf64,<13,10,0>

                push key0
                call step              ;1
                add esp, 4

                push key1
                call step              ;2
                add esp, 4

                push key2
                call step              ;3
                add esp, 4

                push key3
                call step              ;4
                add esp, 4

                push key4
                call step              ;5
                add esp, 4

                push key5
                call step              ;6
                add esp, 4

                push key6
                call step              ;7
                add esp, 4

                push key7
                call step              ;8
                add esp, 4

                push key0
                call step              ;9
                add esp, 4

                push key1
                call step              ;10
                add esp, 4

                push key2
                call step              ;11
                add esp, 4

                push key3
                call step              ;12
                add esp, 4

                push key4
                call step              ;13
                add esp, 4

                push key5
                call step              ;14
                add esp, 4

                push key6
                call step              ;15
                add esp, 4

                push key7
                call step              ;16
                add esp, 4

                push key0
                call step              ;17
                add esp, 4

                push key1
                call step              ;18
                add esp, 4

                push key2
                call step              ;19
                add esp, 4

                push key3
                call step              ;20
                add esp, 4

                push key4
                call step              ;21
                add esp, 4

                push key5
                call step              ;22
                add esp, 4

                push key6
                call step              ;23
                add esp, 4

                push key7
                call step              ;24
                add esp, 4

                push key7
                call step              ;25
                add esp, 4

                push key6
                call step              ;26
                add esp, 4

                push key5
                call step              ;27
                add esp, 4

                push key4
                call step              ;28
                add esp, 4

                push key3
                call step              ;29
                add esp, 4

                push key2
                call step              ;30
                add esp, 4

                push key1
                call step              ;31
                add esp, 4

                push key0
                call last_step         ;32
                add esp, 4


                mov ecx,8
                mov esi,gamma
                mov ebx, new_fbuf
                lea edi, [ebx]

             ;запишем в перемнную gamma значения из new_fbuf
           .V:
                mov al,[edi]
                mov byte [esi], al
                inc esi
                inc edi
                Loop .V




                mov esp, ebp
                pop ebp
          ret



 gamma_xor_fbuf:


                 push ebp
                 mov ebp, esp




                 mov ecx, 8

                 cmp edi,8
                 jb .M
                 jmp .P
           .M:
                 mov ecx, edi
                ; mov ebx, 0
                ; push ebx

                ; push edi
                 mov ebx, 8
                 mov [ebp+8],ebx

           .P:
                 mov ebx, gamma
                 mov edx, fbuf32
                 lea esi,[ebx]

         .XOR:

                 mov al, [esi]
                 xor byte [edx], al
                 inc esi
                 inc edx
                 Loop .XOR




                 mov esp, ebp
                 pop ebp




           ret







 write_into_file:

                push ebp
                mov ebp, esp




                cinvoke fopen,file_encrypted,'a',0
                mov ebx, handle
                mov [ebx],eax

               ; cinvoke fwrite,buftobewritten,1,[length_buf_wr],[handle]
               ; cinvoke fwrite,new_fbuf,1,[length_buf_wr],[handle]
               ; mov ecx, [esp-4]
                cmp edi,8
                jb .P
                mov ecx,8
                jmp .M

             .P:
                mov ecx, edi

             .M:
                cinvoke fwrite,fbuf32,1,ecx,[handle]
              ;  cinvoke fwrite,buftobewritten,1,8,[handle]

                cinvoke fclose,[handle]


                mov esp, ebp
                pop ebp


        ret



 key_func:
                push ebp
                mov ebp, esp

                mov edx,[key]

                lea ebx, [edx]
                mov esi,key0
                mov ecx,4

            .Key0:
                mov al,[ebx]
                mov byte [esi], al
                inc ebx
                inc esi
                Loop .Key0

                mov esi,key1
                mov ecx,4

            .Key1:
                mov al,[ebx]
                mov byte [esi], al
                inc ebx
                inc esi
                Loop .Key1

                mov esi,key2
                mov ecx,4

            .Key2:
                mov al,[ebx]
                mov byte [esi], al
                inc ebx
                inc esi
                Loop .Key2

                mov esi,key3
                mov ecx,4

            .Key3:
                mov al,[ebx]
                mov byte [esi], al
                inc ebx
                inc esi
                Loop .Key3

                mov esi,key4
                mov ecx,4

            .Key4:
                mov al,[ebx]
                mov byte [esi], al
                inc ebx
                inc esi
                Loop .Key4

                mov esi,key5
                mov ecx,4

            .Key5:
                mov al,[ebx]
                mov byte [esi], al
                inc ebx
                inc esi
                Loop .Key5

                mov esi,key6
                mov ecx,4

            .Key6:
                mov al,[ebx]
                mov byte [esi], al
                inc ebx
                inc esi
                Loop .Key6

                mov esi,key7
                mov ecx,4

            .Key7:
                mov al,[ebx]
                mov byte [esi], al
                inc ebx
                inc esi
                Loop .Key7

                mov esp, ebp
                pop ebp


        ret



 step:
                push ebp
                mov ebp, esp

                mov esi, key_step
                mov edi,[esp+8]
                lea ebx, [edi]
                mov ecx,4
             .KS:
                mov al,[ebx]
                mov byte [esi],al
                inc esi
                inc ebx
                Loop .KS


                ;sub esp,8
                ; cinvoke printf,"key_step is:  %d  ",key_step,,<13,10,10>




                ;N2:=fbuf64
                mov eax,fbuf64
                mov ebx, [eax]
                mov ecx,N2
                mov [ecx],ebx
                ;fbuf64 add key mod 32 бит
                .add_key:
                        mov ebx, fbuf64
                        mov ecx, key_step

                        mov edx, [ecx]
                        mov eax, [ebx]
                        add eax, edx

                       ; mov ebx, fbuf64
                        mov [ebx], eax
                        ; fbuf64= N2 add key


                
                 mov ecx,0
                        lea esi, [fbuf64]
                        mov [length],256

             _Sbox:

                       ; mov [i], ecx

                       ; mov [j], [esi]
                        xor eax,eax
                        mov al,1
                        mul [length]
                        mul ecx
                        add al, byte[esi]
                        add eax,sbox

                        lea edi,[eax]
                        mov bl,[edi]
                        mov byte [esi], bl

                        inc esi
                        inc ecx

                       ;  xor ebx,ebx
                        ; mov bl,[esi]
                         ;cinvoke printf,<'Sbox[%d][%d]=   %d'>,ecx,esi,ebx,<13,10,0>

                        cmp ecx,4
                        jne _Sbox


              .sdvig:

                     ; mov eax,fbuf64
                     ; mov ebx,[eax]
                      rol dword [fbuf64],11




               op_4:     ;S=S+N1(fbuf64=fbuf64 xor fbuf32)

                      mov ebx,fbuf64
                      mov eax,[ebx]
                      mov ecx,fbuf32
                      mov edx, [ecx]
                      xor eax, edx
                      mov [ebx], eax

               op_5:

                      mov eax,N2
                      mov ecx,[eax]
                      mov ebx, fbuf32
                      mov [ebx], ecx




                                           ;N2:=S(fbuf64)


               op_6:
                    mov ecx,4
                    lea esi,[fbuf32]
                    mov ebx,new_fbuf         ;new_fbuf

                  _M1:

                       mov al, [esi]

                       mov byte [ebx],al
                       inc ebx
                       inc esi
                       Loop _M1


                   mov ecx,4
                   lea esi, [fbuf64]

                  _M2:

                       mov al, [esi]

                       mov byte [ebx],al
                       inc ebx
                       inc esi
                       Loop _M2




                _ret:

                     xor eax,eax
                     mov eax,new_fbuf




                mov esp,ebp
                pop ebp


   ret

last_step:
                push ebp
                mov ebp, esp


                mov esi, key_step
                mov edi,[esp+8]
                lea ebx, [edi]
                mov ecx,4
             .KS:
                mov al,[ebx]
                mov byte [esi],al
                inc esi
                inc ebx
                Loop .KS


                ;sub esp,8
               ; cinvoke printf,"key_step is:  %s  ",key_step,,<13,10,10>



                ;N2:=fbuf64
                mov eax,fbuf64
                mov ebx, [eax]
                mov ecx,N2
                mov [ecx],ebx
                ;fbuf64 add key mod 32 бит
                .add_key:
                        xor eax,eax
                        mov ebx, fbuf64
                        mov ecx, key_step

                        mov edx, [ecx]
                        mov eax, [ebx]
                        add eax, edx

                        mov ebx, fbuf64
                        mov [ebx], eax
                        ; fbuf32= N1 add key


                
               mov ecx,0
                        lea esi, [fbuf64]
                        mov [length],256

             .Sbox:

                       ; mov [i], ecx

                       ; mov [j], [esi]
                        xor eax,eax
                        mov al,1
                        mul [length]
                        mul ecx
                        add al, byte[esi]
                        add eax,sbox

                        lea edi,[eax]
                        mov bl,[edi]
                        mov byte [esi], bl

                        inc esi
                        inc ecx

                       ;  xor ebx,ebx
                        ; mov bl,[esi]
                         ;cinvoke printf,<'Sbox[%d][%d]=   %d'>,ecx,esi,ebx,<13,10,0>

                        cmp ecx,4
                        jne _Sbox


              .sdvig:

                     ; mov eax,fbuf32
                     ; mov ebx,[eax]
                      rol dword [fbuf64],11




               .op_4:     ;S=S+N2

                      mov ebx,fbuf64
                      mov eax,[ebx]
                      mov ecx,fbuf32
                      mov edx, [ecx]
                      xor eax, edx
                      mov [ebx], eax


               .op5:
                      mov eax, fbuf64       ; fbuf32:=S(fbuf64)
                      mov ebx, [eax]
                      mov ecx, fbuf32
                      mov [ecx], ebx

                      mov ecx, N2           ;fbuf64:=N2
                      mov ebx, [ecx]
                      mov [eax], ebx
               .op_6:
                    mov ecx,4
                    lea esi,[fbuf32]
                    mov ebx,new_fbuf         ;new_fbuf

                  .M1:

                       mov al, [esi]

                       mov byte [ebx],al
                       inc ebx
                       inc esi
                       Loop .M1


                   mov ecx,4
                   lea esi, [fbuf64]

                  .M2:

                       mov al, [esi]

                       mov byte [ebx],al
                       inc ebx
                       inc esi
                       Loop .M2




                .ret:

                     xor eax,eax
                     mov eax,new_fbuf




                mov esp,ebp
                pop ebp


   ret



        start:


                        mov esi,time_start
                        rdtsc
                        mov [esi],edx
                        mov[esi+4],eax
              ;инициализируем вектор = синхропосылка+0...0(32)
               call init_vector
              ; call key_func
              ;cinvoke printf,'key7 is : %s   ',key7,<13,10,0>


             ; cinvoke printf,'%s',<'Hello        ;',13,10,0>

              ;Получаем полный путь к программе и заданный ей параметр
              ; аналогично программе на С
              ; cinvoke __getmainargs,argc,argv,env,0
               push 0
               push env
               push argv
               push argc
               call [__getmainargs]

               cmp [argc],3
               jne .err
               mov esi,[argv]

;;;;;;;;;;;;;;;;;;;;;;;;;;KEY;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
              ; Вызовем функцию расписания ключей
               cinvoke fopen,dword [esi+8],'rb'
               test eax,eax
               jz .err
               mov [fp_k],eax


                ;Устанавливаем указатель чтения-записи в конец файла

                cinvoke fseek,[fp_k],0,SEEK_END
               .if eax <> 0
                jmp .err
               .endif

                ;Узнаем значение этого указателя, который равен размеру файла
               cinvoke ftell, [fp_k]
               test eax,eax
               jz .err
               cmp eax,32
               jne .err
               mov [flength_key], eax

              ;Запрашиваем динамическую память
               ; размером : длина файла + 1 бит
               inc eax
               cinvoke malloc,eax
               jz .err
               mov [key],eax  ;



               ;Возвращаем указатель чтения-записи в начало файла
               cinvoke fseek,[fp_k],0,SEEK_SET
               test eax,eax
               jnz .err



               ;Читаем весь файл в динамическую память
               cinvoke fread, [key],1,[flength_key],[fp_k]
               cmp eax,[flength_key]
               jne .err

                ;Записываем 0 в конце строки для обозачения
                ;конца строки
                mov eax, [key]
                add eax, [flength_key]
                mov byte [eax], 0




               ; call key_func

               ; invoke CharToOemA,dword [esi],dword [esi]
               ; invoke CharToOemA,dword [esi+4],dword [esi+4]

               ; Выводим имя программы с путем и параметр
              ; push newstr
              ; push dword [esi+4]
              ; push dword [esi]
              ; push msg
              ; call [printf]
             ; cinvoke printf,msg,dword [esi],dword [esi+4],dword [esi+8],<13,10,0>


 ;;;;;;;;;;;;;;;;;;;;;;;;;;Plain next;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
               ;Открываем заданный текстовый файл в режиме "чтение"
               ; и двоичный
               cinvoke fopen,dword [esi+4],'rb'
               test eax,eax
               jz .err
               mov [fp],eax


               ;Устанавливаем указатель чтения-записи в конец файла

                cinvoke fseek,[fp],0,SEEK_END
               .if eax <> 0
                jmp .err
               .endif


               ;Узнаем значение этого указателя, который равен размеру файла
               cinvoke ftell, [fp]
               test eax,eax
               jz .err
               mov [flength], eax

               ;Выводим длину файла
               ;cinvoke printf,'Length of file is: %d',eax,<13,10,0>


               ;Запрашиваем динамическую память
               ; размером : длина файла + 1 бит
               inc eax
               cinvoke malloc,eax
               jz .err
               mov [fbuf],eax  ;



               ;Возвращаем указатель чтения-записи в начало файла
               cinvoke fseek,[fp],0,SEEK_SET
               test eax,eax
               jnz .err



               ;Читаем весь файл в динамическую память
               cinvoke fread, [fbuf],1,[flength],[fp]
               cmp eax,[flength]
               jne .err

                ;Записываем 0 в конце строки для обозачения
                ;конца строки
                mov eax, [fbuf]
                add eax, [flength]
                mov byte [eax], 0

               ; Выводим файл на консоль
               cinvoke printf, [key],<13,10,0>
               cinvoke printf,';   Length of key you entered is %d     ',[flength_key],<13,10,0>


               call key_func
                ; TEST
;будем проверять делится ли длина текста нацело на 8,если -да,то переходим к N=N1+N2
;и вызову цикла шифрования
;////////////////////////////////////////////////////////////////////////////////////





                mov edi,[flength]  ; edi=длина fbuf
                mov eax,[fbuf]     ;  eax= указатель на [fbuf]
                lea esi,[eax]      ;  esi=адрес первого символа строки






     .Metka:
                push eax
                push ebx
                push edi
                push esi

                call gamma_

                pop esi
                pop edi
                pop ebx
                pop eax


                mov ebx,fbuf32         ;зануляем fbuf32 и fbuf64

                push eax
                mov eax, 0
                mov [ebx], eax
                mov [ebx+4], eax
                pop eax



           ;     xor edx,edx
           ;     mov eax,edi
           ;     mov ecx,8
           ;     div ecx
           ;     cmp edx,0         ;длина строки должна быть 8 байт(64 бита)
           ;     jne .err         ;нужно сделать дополнение до 64 бит

                mov ecx,4          ;ecx=4(32 бита)

             .L32:                  ;fbuf32=адрес 0-32 бит строки fbuf
                mov al,[esi]

                mov byte [ebx],al
                inc esi
                inc ebx
                Loop .L32


               ; cinvoke printf,<' ; fbuf32 is : %s' >,fbuf32,<13,10,0>

                mov ecx,4       ;ecx=32 бита
                mov ebx,fbuf64

             .L64:                   ;fbuf64=адрес 32-64 бит строки fbuf

                mov al,[esi]

                mov byte [ebx],al
                inc esi
                inc ebx
                Loop .L64


               ; cinvoke printf,<'  fbuf64 is : %s ;  ' >,fbuf64,<13,10,0>


               ;вызываем 32 шага шифрования
                push eax
                push ebx
                push esi
                push edi

                call gamma_xor_fbuf                 ;накладываем гамму на входной текст








                                              ;32 раунда шифрования





               ; push fbuf32
                call write_into_file
               ; add esp, 4

               ; cinvoke printf,new_fbuf,<13,10,10>  ; запись в выходной файл

                pop edi
                pop esi
                pop ebx
                pop eax

               ;проверка ,достигнут ли конец файла










                sub edi,8
                cmp edi,0
                je .Continue

                push eax
                push ebx
                push esi
                push edi
                ;увеличиваем счетчик

                call inc_CTR

                pop edi
                pop esi
                pop ebx
                pop eax
                jmp .Metka



;///////////////////////////////////////////////////////////////////////////////////////////

          .Continue:
               ;Закрываем файл
               cinvoke fclose, [fp]
               test eax,eax
               jnz .err









               ;Освобождаем динамическую память
               cinvoke free, [fbuf]

     ;time;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


      ;time;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


         .finish:
              ;  call [getch]


                 mov esi,time_end
                     rdtsc
                     mov [esi], edx
                     mov [esi+4],eax

              .time:
                    mov edi, time_start
                    ; mov ecx, time
                    sub edx,[edi]
                    sub eax, [edi+4]

                    mov ecx, time
                    mov [ecx],edx
                    mov [ecx+4], eax




                  cinvoke printf,"time:= %d ",eax,<13,10,0>













                push NULL
                call [ExitProcess]


        .err:
                push errmsg
                call [printf]
                jmp .finish



           ;  mov esp, ebp
           ;  pop ebp
      ; ret



section '.idata' import data readable
        library kernel, 'kernel32.dll',\
                msvcrt, 'msvcrt.dll',\
                user32,'user32.dll'

        import kernel,\
               ExitProcess, 'ExitProcess',\
               GetCommandLineA,'GetCommandLineA',\
               AllocConsole,'AllocConsole',\
               FreeConsole,'FreeConsole',\
               SetConsoleOutputCP,'SetConsoleOutputCP',\
               SetConsoleCP,'SetConsoleCP'


       import msvcrt,\
               __getmainargs,'__getmainargs',\
               fopen,'fopen',\
               fseek,'fseek',\
               ftell,'ftell',\
               malloc,'malloc',\
               free,'free',\
               fread,'fread',\
               fwrite,'fwrite',\
               fclose,'fclose',\
               printf,'printf',\
               getch,'_getch',\
               puts,'puts'

        import user32,\
        CharToOemA,'CharToOemA'