/**
* This file is part of Ehnd.
*
* Ehnd is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* The Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Ehnd is distributed in the hope that it will be useful,
*
* But WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Ehnd.
*
*   If not, see <http://www.gnu.org/licenses/>.
*
**/

#include "stdafx.h"
#include "Ehnd.h"
#include "MinHook.h"
#include "J2K_Functions.hpp"

lua_State *L = NULL;

MESSAGEBOXW fpMessageBoxW = NULL;
char *space = NULL;
void AssignFreeSpace()
{

}
using RETN = void(*)();
RETN fpReturn = NULL;
LPBYTE lpfnRetn_A1;
LPBYTE lpfnRetn_A2;
LPBYTE lpfnRetn_A3;
LPBYTE lpfnRetn_B1;

LPBYTE lpfnRetn_C_Begin;

LPVOID fpPatch_Org_B1;

LPVOID fpPatch_Org_C1A_1;
LPVOID fpPatch_Org_C1A_2;
LPVOID fpPatch_Org_C1B_1;
LPVOID fpPatch_Org_C1C_1;
LPVOID fpPatch_Org_C1D_1;
LPVOID fpPatch_Org_C1D_2;
LPVOID fpPatch_Org_C1E_1;
LPVOID fpPatch_Org_C1E_2;
LPVOID fpPatch_Org_C1E_3;
LPVOID fpPatch_Org_C1E_4;
LPVOID fpPatch_Org_C1E_5;
LPVOID fpPatch_Org_C1E_6;
LPVOID fpPatch_Org_C1E_7;
LPVOID fpPatch_Org_C1E_8;
LPVOID fpPatch_Org_C1E_9;
LPVOID fpPatch_Org_C1F_1;
LPVOID fpPatch_Org_C1F_2;
LPVOID fpPatch_Org_C1F_3;
LPVOID fpPatch_Org_C1F_4;
LPVOID fpPatch_Org_C1F_5;
LPVOID fpPatch_Org_C1F_6;
LPVOID fpPatch_Org_C1F_7;
LPVOID fpPatch_Org_C1G_1;
LPVOID fpPatch_Org_C1G_2;
LPVOID fpPatch_Org_C1G_3;
LPVOID fpPatch_Org_C1G_4;
LPVOID fpPatch_Org_C2_1;
LPVOID fpPatch_Org_C2_2;
LPVOID fpPatch_Org_C2_3;
LPVOID fpPatch_Org_C2_4;
LPVOID fpPatch_Org_C2_5;
LPVOID fpPatch_Org_C2_6;
LPVOID fpPatch_Org_C3A_1;
LPVOID fpPatch_Org_C3A_2;
LPVOID fpPatch_Org_C3B_1;
LPVOID fpPatch_Org_C3C_2;
LPVOID fpPatch_Org_C3D_1;
LPVOID fpPatch_Org_C3D_2;
LPVOID fpPatch_Org_C4A_1;
LPVOID fpPatch_Org_C4B_1;
LPVOID fpPatch_Org_C4C_1;
LPVOID fpPatch_Org_C4C_2;
LPVOID fpPatch_Org_C5_1;
LPVOID fpPatch_Org_C6_1;
LPVOID fpPatch_Org_C6_2;
LPVOID fpPatch_Org_C7_1;
LPVOID fpPatch_Org_C8_1;
LPVOID fpPatch_Org_C8_2;
LPVOID fpPatch_Org_C8_3;
LPVOID fpPatch_Org_C8_4;
LPVOID fpPatch_Org_C9;
LPVOID fpPatch_Org_C10;
LPVOID fpPatch_Org_C11;
void DetourInitializeEx(char *a, char *b)
{

}

char *assign_memory(char *str)
{
	return new char[strlen(str) + 1];
}
void destroy_memory(char *str)
{
	return delete[] str;
}

// fix buffer overflow (process routine)
__declspec(naked) void Patch_A1()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [ESP + 0x20]
		CMP EAX, 0x0E
		JNE TEnd

		PUSH EBP
		CALL assign_memory
		ADD ESP, 0x04
		MOV DWORD PTR DS : [ESP + 0x2C], EAX

		MOV EDX, DWORD PTR SS : [ESP + 0x2C]
		PUSH EBP
		PUSH EDX

		CALL EDI

		TEnd:
		JMP lpfnRetn_A1
	}
}
__declspec(naked) void Patch_A2()
{
	__asm
	{
		ADD ESP, 4
		MOV EAX, DWORD PTR SS : [ESP + 0x2C]
		JMP lpfnRetn_A2
	}
}
__declspec(naked) void Patch_A3()
{
	__asm
	{
		PUSH DWORD PTR SS: [ESP + 0x2C]
		CALL destroy_memory
		ADD ESP, 4

		PUSH 0x0F
		PUSH EBP
		JMP lpfnRetn_A3
	}
}

// fix buffer overflow (translate-after routine)
char *Patch_B1a(char *p1, char *p2, int n)
{
	static int _size = 0;
	static char *_mem = NULL;

	//int len = strlen(p1 + 0x98); // existing stored string
	int len2 = strlen(*(char **)(p1 + 0x20)); // store string
	int total_size = 0x120 + (len2) * 2;

	delete[] _mem;
	_size = total_size;
	_mem = new char[total_size];
	memcpy(_mem, p1, 0x120);

	return _mem;
}
__declspec(naked) void Patch_B1()
{
	__asm
	{
		PUSH DWORD PTR SS:[ESP+0x08]
		PUSH DWORD PTR SS:[ESP+0x08]
		PUSH ECX
		CALL Patch_B1a // temporary memory allocate
		ADD ESP, 0x0C
		MOV ECX, EAX
		
		JMP fpPatch_Org_B1
	}
}

__declspec(naked) void Patch_C_Begin()
{
	// ECX+0xC4에 input data가 저장되어 있음.
	// 이 데이터의 길이를 기반으로 임시 공간을 만들고
	// 모든 접근을 그쪽으로 우회

	// SE Handler ESP+0x103C 주소를 이용해 저장

	__asm
	{
		PUSH -1
		MOV EAX, DWORD PTR DS:[ECX+0xC4]
		
		// shield
		PUSH ECX

		PUSH EAX // input data
		CALL assign_memory
		ADD ESP, 0x04

		// sheield
		POP ECX

		PUSH EAX
		MOV EAX, DWORD PTR FS:[0]
		JMP lpfnRetn_C_Begin;
	}
}
__declspec(naked) void Patch_C1(char chr)
{
	__asm
	{
		PUSH EAX
		PUSH ECX
		MOV CL, BYTE PTR SS : [ESP + 0x0C]
		MOV EAX, DWORD PTR SS : [ESP + 0x104C]
		MOV BYTE PTR SS:[EAX+ESI], CL
		POP ECX
		POP EAX
		RETN
	}
}

// MOV BYTE PTR SS:[ESP+ESI+0x38], 0x00
__declspec(naked) void Patch_C1A_1()
{
	__asm
	{
		PUSH 0x00
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1A_1
		ADD DWORD PTR SS:[ESP], 0x05
		RETN
	}
}
__declspec(naked) void Patch_C1A_2()
{
	__asm
	{
		PUSH EAX
		MOV EAX, DWORD PTR SS : [ESP + 0x1040]
		MOV BYTE PTR SS : [EAX + ESI], 0x00
		POP EAX
		PUSH fpPatch_Org_C1A_2
		ADD DWORD PTR SS:[ESP], 0x05
		RETN
	}
}

// MOV BYTE PTR SS:[ESP+ESI+0x0x38], 0x41
__declspec(naked) void Patch_C1B_1()
{
	__asm
	{
		PUSH 0x41
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1B_1
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}

// MOV BYTE PTR SS:[ESP+ESI+0x38], 0x5B
__declspec(naked) void Patch_C1C_1()
{
	__asm
	{
		PUSH 0x5B
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1C_1
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}

// MOV BYTE PTR SS:[ESP+ESI+0x38], 0x81
__declspec(naked) void Patch_C1D_1()
{
	__asm
	{
		PUSH 0x81
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1D_1
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
__declspec(naked) void Patch_C1D_2()
{
	__asm
	{
		PUSH 0x81
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1D_2
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}

// MOV BYTE PTR SS:[ESP+ESI+0x38], AL
__declspec(naked) void Patch_C1E_1()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1E_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1E_2()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1E_2
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1E_3()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1E_3
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1E_4()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1E_4
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1E_5()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1E_5
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1E_6()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1E_6
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1E_7()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1E_7
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1E_8()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1E_8
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1E_9()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1E_9
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}

// MOV BYTE PTR SS:[ESP+ESI+0x38], CL
__declspec(naked) void Patch_C1F_1()
{
	__asm
	{
		PUSH ECX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1F_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1F_2()
{
	__asm
	{
		PUSH ECX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1F_2
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1F_3()
{
	__asm
	{
		PUSH ECX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1F_3
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1F_4()
{
	__asm
	{
		PUSH ECX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1F_4
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1F_5()
{
	__asm
	{
		PUSH ECX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1F_5
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1F_6()
{
	__asm
	{
		PUSH ECX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1F_6
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1F_7()
{
	__asm
	{
		PUSH ECX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1F_7
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}

// MOV BYTE PTR SS:[ESP+ESI+0x38], CL
__declspec(naked) void Patch_C1G_1()
{
	__asm
	{
		PUSH EDX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1G_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1G_2()
{
	__asm
	{
		PUSH EDX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1G_2
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1G_3()
{
	__asm
	{
		PUSH EDX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1G_3
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C1G_4()
{
	__asm
	{
		PUSH EDX
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1G_4
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}

// MOV BYTE PTR SS:[ESP+ESI+0x3C], 0x00
__declspec(naked) void Patch_C2(char chr)
{
	__asm
	{
		PUSH EAX
		PUSH ECX
		MOV CL, BYTE PTR SS : [ESP + 0x0C]
		MOV EAX, DWORD PTR SS : [ESP + 0x104C + 0x04]
		MOV BYTE PTR SS : [EAX + ESI], CL
		POP ECX
		POP EAX
		RETN
	}
}
__declspec(naked) void Patch_C2_1()
{
	__asm
	{
		PUSH 0
		CALL Patch_C2
		ADD ESP, 0x04
		PUSH fpPatch_Org_C2_1
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
__declspec(naked) void Patch_C2_2()
{
	__asm
	{
		PUSH 0
		CALL Patch_C2
		ADD ESP, 0x04
		PUSH fpPatch_Org_C2_2
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
__declspec(naked) void Patch_C2_3()
{
	__asm
	{
		PUSH 0
		CALL Patch_C2
		ADD ESP, 0x04
		PUSH fpPatch_Org_C2_3
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
__declspec(naked) void Patch_C2_4()
{
	__asm
	{
		PUSH 0
		CALL Patch_C2
		ADD ESP, 0x04
		PUSH fpPatch_Org_C2_4
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
__declspec(naked) void Patch_C2_5()
{
	__asm
	{
		PUSH 0
		CALL Patch_C2
		ADD ESP, 0x04
		PUSH fpPatch_Org_C2_5
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
__declspec(naked) void Patch_C2_6()
{
	__asm
	{
		PUSH 0
		CALL Patch_C2
		ADD ESP, 0x04
		PUSH fpPatch_Org_C2_6
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}

__declspec(naked) void Patch_C3(char chr)
{
	__asm
	{
		PUSH EAX
		PUSH ECX
		MOV CL, BYTE PTR SS : [ESP + 0x0C]
		MOV EAX, DWORD PTR SS : [ESP + 0x104C]
		MOV BYTE PTR SS : [EAX], CL
		POP ECX
		POP EAX
		RETN
	}
}
// MOV BYTE PTR SS:[ESP+0x38], 0x81
__declspec(naked) void Patch_C3A_1()
{
	__asm
	{
		PUSH 0x81
		CALL Patch_C3
		ADD ESP, 0x04
		PUSH fpPatch_Org_C3A_1
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
__declspec(naked) void Patch_C3A_2()
{
	__asm
	{
		PUSH 0x81
		CALL Patch_C3
		ADD ESP, 0x04
		PUSH fpPatch_Org_C3A_2
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
// MOV BYTE PTR SS:[ESP+0x38], AL
__declspec(naked) void Patch_C3B_1()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C3
		ADD ESP, 0x04
		PUSH fpPatch_Org_C3B_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
// MOV BYTE PTR SS:[ESP+0x38], CL
__declspec(naked) void Patch_C3C_2()
{
	__asm
	{
		PUSH ECX
		CALL Patch_C3
		ADD ESP, 0x04
		PUSH fpPatch_Org_C3C_2
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
// MOV BYTE PTR SS:[ESP+0x38], DL
__declspec(naked) void Patch_C3D_1()
{
	__asm
	{
		PUSH EDX
		CALL Patch_C3
		ADD ESP, 0x04
		PUSH fpPatch_Org_C3D_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C3D_2()
{
	__asm
	{
		PUSH EDX
		CALL Patch_C3
		ADD ESP, 0x04
		PUSH fpPatch_Org_C3D_2
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}

__declspec(naked) void Patch_C4(char chr)
{
	__asm
	{
		PUSH EAX
		PUSH ECX
		MOV CL, BYTE PTR SS : [ESP + 0x0C]
		MOV EAX, DWORD PTR SS : [ESP + 0x104C]
		MOV BYTE PTR SS : [EAX + 0x01], CL
		POP ECX
		POP EAX
		RETN
	}
}
// MOV BYTE PTR SS:[ESP+0x39], 0x41
__declspec(naked) void Patch_C4A_1()
{
	__asm
	{
		PUSH 0x41
		CALL Patch_C4
		ADD ESP, 0x04
		PUSH fpPatch_Org_C4A_1
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
// MOV BYTE PTR SS:[ESP+0x39], 0x76
__declspec(naked) void Patch_C4B_1()
{
	__asm
	{
		PUSH 0x76
		CALL Patch_C4
		ADD ESP, 0x04
		PUSH fpPatch_Org_C4B_1
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
// MOV BYTE PTR SS:[ESP+0x39], AL
__declspec(naked) void Patch_C4C_1()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C4
		ADD ESP, 0x04
		PUSH fpPatch_Org_C4C_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C4C_2()
{
	__asm
	{
		PUSH EAX
		CALL Patch_C4
		ADD ESP, 0x04
		PUSH fpPatch_Org_C4C_2
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}

// MOV AL,BYTE PTR SS:[ESP+0x38]
__declspec(naked) void Patch_C5()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [ESP + 0x1040]
		MOV AL, BYTE PTR DS : [EAX]
		RETN
	}
}
__declspec(naked) void Patch_C5_1()
{
	__asm
	{
		CALL Patch_C5
		PUSH fpPatch_Org_C5_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}

// LEA EAX,DWORD PTR SS:[ESP+38]
__declspec(naked) void Patch_C6()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [ESP + 0x1040]
		RETN
	}
}
__declspec(naked) void Patch_C6_1()
{
	__asm
	{
		CALL Patch_C6
		PUSH fpPatch_Org_C6_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C6_2()
{
	__asm
	{
		CALL Patch_C6
		PUSH fpPatch_Org_C6_2
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}

// LEA ECX,DWORD PTR SS:[ESP+38]
__declspec(naked) void Patch_C7()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [ESP + 0x1040]
		RETN
	}
}
__declspec(naked) void Patch_C7_1()
{
	__asm
	{
		CALL Patch_C7
		PUSH fpPatch_Org_C7_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}

// LEA EDX,DWORD PTR SS:[ESP+38]
__declspec(naked) void Patch_C8()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [ESP + 0x1040]
		RETN
	}
}
__declspec(naked) void Patch_C8_1()
{
	__asm
	{
		CALL Patch_C8
		PUSH fpPatch_Org_C8_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C8_2()
{
	__asm
	{
		CALL Patch_C8
		PUSH fpPatch_Org_C8_2
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C8_3()
{
	__asm
	{
		CALL Patch_C8
		PUSH fpPatch_Org_C8_3
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
__declspec(naked) void Patch_C8_4()
{
	__asm
	{
		CALL Patch_C8
		PUSH fpPatch_Org_C8_4
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
// LEA ECX,DWORD PTR SS:[ESP+38]
// MOV BYTE PTR SS:[ESP+ESI+38],AL
__declspec(naked) void Patch_C9()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [ESP + 0x103C]
		MOV BYTE PTR SS:[ECX+ESI], AL

		PUSH fpPatch_Org_C9
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
// LEA ECX,DWORD PTR SS:[ESP+38]
// MOV BYTE PTR SS:[ESP+ESI+38],0
__declspec(naked) void Patch_C10()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [ESP + 0x103C]
		MOV BYTE PTR SS : [ECX + ESI], 0x00

		PUSH fpPatch_Org_C10
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
// MOV BYTE PTR SS:[ESP+38],CL
// MOV BYTE PTR SS:[ESP+39],AL
__declspec(naked) void Patch_C11()
{
	__asm
	{
		PUSH EDX
		MOV EDX, DWORD PTR SS : [ESP + 0x1040]
		MOV BYTE PTR DS:[EDX], CL
		MOV BYTE PTR DS:[EDX+1], AL
		POP EDX

		PUSH fpPatch_Org_C11
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}



__declspec(naked) void Patch_C_End()
{
	__asm
	{
		PUSH DWORD PTR SS:[ESP-0x08]
		CALL destroy_memory
		ADD ESP, 0x04
		RETN
	}
}

bool EH_UpdateCheck()
{
	return true;
}

bool EH_InitLua()
{
	// Create lua state
	L = luaL_newstate();
	luaL_openlibs(L);
	
	// opens the basic, table, I/O, string, math library
	luaopen_base(L);
	luaopen_table(L);
	luaopen_table(L);
	luaopen_io(L);
	luaopen_string(L);
	luaopen_math(L);
	return true;
}

bool EH_UninitLua()
{
	lua_close(L);
	return true;
}

bool EH_InstallHook(char *libPath)
{
	// Initialize Lua
	EH_InitLua();

	// Update Check
	EH_UpdateCheck();

	// Initialize minhook
	MH_Initialize();

	HINSTANCE hDLL;
	
	// Load J2KEngine.dlx
	if ((hDLL = LoadLibraryA(libPath)) == NULL)
	{
		MessageBox(0, fmt::format(L"LoadLibrary to J2KEngine.dlx Failed: {0}", libPath).c_str(), L"Error", MB_ICONERROR);
		return false;
	}

	// Declare eztrans function tables
	std::list<std::pair<char *, LPVOID>> fpTable =
	{
		{ "J2K_Initialize", &fpJ2KInitialize },
		{ "J2K_InitializeEx", &fpJ2KInitializeEx },
		{ "J2K_FreeMem", &fpJ2KFreeMem },
		{ "J2K_GetPriorDict", &fpJ2KGetPriorDict },
		{ "J2K_GetProperty", &fpJ2KGetProperty },
		{ "J2K_ReloadUserDict", &fpJ2KReloadUserDict },
		{ "J2K_SetDelJPN", &fpJ2KSetDelJPN },
		{ "J2K_SetField", &fpJ2KSetField },
		{ "J2K_SetHnj2han", &fpJ2KSetHnj2han },
		{ "J2K_SetJWin", &fpJ2KSetJWin },
		{ "J2K_SetPriorDict", &fpJ2KSetPriorDict },
		{ "J2K_SetProperty", &fpJ2KSetProperty },
		{ "J2K_StopTranslation", &fpJ2KStopTranslation },
		{ "J2K_Terminate", &fpJ2KTerminate },
		{ "J2K_TranslateChat", &fpJ2KTranslateChat },
		{ "J2K_TranslateFM", &fpJ2KTranslateFM },
		{ "J2K_TranslateMM", &fpJ2KTranslateMM },
		{ "J2K_TranslateMMEx", &fpJ2KTranslateMMEx },
		{ "J2K_TranslateMMNT", &fpJ2KTranslateMMNT },
		{ "?GetJ2KMainDir@@YA?AVCString@@XZ", &fpJ2KGetJ2KMainDir },
	};
	for (auto &p : fpTable)
	{
		if ((*reinterpret_cast<LPVOID *>(p.second) =
			reinterpret_cast<LPVOID>(
				GetProcAddress(hDLL, p.first)
				)) == NULL)
		{
			MessageBoxA(0, fmt::format("Load Failed - {0}", p.first).c_str(), "Hook Error", MB_ICONERROR);
			return false;
		}
	}
	
	g_bInit = true;

	// fix to function (hook)
	([] {
		// 101D66B0   > \6A FF               PUSH -1
		// 101D66B2   .  68 6A5B1F10         PUSH J2KEngin.101F5B6A                   ;  SE handler installation
		// 101D66B7   .  64:A1 00000000      MOV EAX,DWORD PTR FS:[0]
		// 101D66BD   .  50                  PUSH EAX
		// 101D66BE   .  64:8925 00000000    MOV DWORD PTR FS:[0],ESP
		// 101D66C5      81EC 1C010000       SUB ESP,11C
		// 101D66CB   .  53                  PUSH EBX
		// 101D66CC   .  55                  PUSH EBP
		// 101D66CD   .  56                  PUSH ESI
		// 101D66CE   .  57                  PUSH EDI
		// 101D66CF   .  8BD9                MOV EBX,ECX
		// 101D66D1   .  6A 30               PUSH 30

		// 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 81 EC 1C 01 00 00

		// +0x248 | LEA EDX,DWORD PTR SS:[ESP+2C] // CALL EDI (lstrcpyA)
		// +0x263 | ADD ESP,4; MOV ESI, EBP // LEA EAX,DWORD PTR SS:[ESP+2C]
		// +0x2A1 | PUSH 0x0F; PUSH EBP; MOV ECX, EBX
		WORD ptn[] = { 0x6A, 0xFF, 0x68, -1, -1, -1, -1, 0x64, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x50, 0x64, 0x89, 0x25, 0x00, 0x00, 0x00, 0x00, 0x81, 0xEC, 0x1C, 0x01, 0x00, 0x00 };
		LPBYTE addr = NULL;
		if (search_ptn(ptn, _countof(ptn), &addr, g_szDLLName) == 1)
		{
			if (MH_CreateHook(addr + 0x248, Patch_A1, NULL) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x263, Patch_A2, NULL) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x2A1, Patch_A3, NULL) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			lpfnRetn_A1 = addr + 0x248 + 0x08;
			lpfnRetn_A2 = addr + 0x263 + 0x09;
			lpfnRetn_A3 = addr + 0x2A1 + 0x05;
			MH_EnableHook(addr + 0x248);
			MH_EnableHook(addr + 0x263);
			MH_EnableHook(addr + 0x2A1);
			//MH_EnableHook(addr + 0x268);
			//MH_EnableHook(addr + 0x6E0);
		}
	}());

	// crash fix #2 (translated after)
	([] {
		//101C73C0    6A FF           PUSH - 1
		//101C73C2    68 0E6C1F10     PUSH J2KEngin.101F6C0E
		//101C73C7    64:A1 00000000  MOV EAX, DWORD PTR FS : [0]
		//101C73CD    50              PUSH EAX
		//101C73CE    64 : 8925 0000000>MOV DWORD PTR FS : [0], ESP
		//101C73D5    81EC 18020000   SUB ESP, 218
		//101C73DB    53              PUSH EBX
		//101C73DC    55              PUSH EBP
		//101C73DD    56              PUSH ESI
		//101C73DE    57              PUSH EDI
		//101C73DF    8BF1            MOV ESI, ECX
		//101C73E1    8BBC24 38020000 MOV EDI, DWORD PTR SS : [ESP + 238]
		//101C73E8    33ED            XOR EBP, EBP
		//101C73EA    3BFD            CMP EDI, EBP
		//101C73EC    89AC24 30020000 MOV DWORD PTR SS : [ESP + 230], EBP
		//101C73F3    0F84 710D0000   JE J2KEngin.101C816A
		//101C73F9    E8 FBACE3FF     CALL J2KEngin.100020F9
		//101C73FE    83F8 FF         CMP EAX, -1
		//101C7401    75 06           JNZ SHORT J2KEngin.101C7409
		//101C7403    89AE 94000000   MOV DWORD PTR DS : [ESI + 94], EBP
		//101C7409    83FF 0A         CMP EDI, 0A
		//101C740C    7D 3C           JGE SHORT J2KEngin.101C744A
		//101C740E    8BCE            MOV ECX, ESI
		//101C7410    E8 D6ABE3FF     CALL J2KEngin.10001FEB
		//101C7415    83F8 FF         CMP EAX, -1
		//101C7418    75 30           JNZ SHORT J2KEngin.101C744A
		//101C741A    81C6 98000000   ADD ESI, 98
		//101C7420    68 2CEE2910     PUSH J2KEngin.1029EE2C; ASCII "<???:Word도치 실패>"
		//101C7425    56              PUSH ESI
		//101C7426    FF15 B4152A10   CALL DWORD PTR DS : [<&KERNEL32.lstrcpyA>]; KERNEL32.lstrcpyA
		//101C742C    8D8C24 3C020000 LEA ECX, DWORD PTR SS : [ESP + 23C]
		//101C7433    C78424 30020000>MOV DWORD PTR SS : [ESP + 230], -1
		//101C743E    E8 0DB60200     CALL <JMP.&MFC42.#800>

		// 6A FF 68 ?? ?? ?? ?? 64 A1 ?? ?? ?? ?? 50 64 89 25 00 00 00 00 81 EC 18 02 00 00

		WORD ptn[] = { 0x6A, 0xFF, 0x68, -1, -1, -1, -1, 0x64, 0xA1, -1, -1, -1, -1, 0x50, 0x64, 0x89, 0x25, 0x00, 0x00, 0x00, 0x00, 0x81, 0xEC, 0x18, 0x02, 0x00, 0x00 };
		LPBYTE addr = NULL;
		if (search_ptn(ptn, _countof(ptn), &addr, g_szDLLName) == 1)
		{
			if (MH_CreateHook(addr, Patch_B1, &fpPatch_Org_B1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			//MH_EnableHook(addr);
		}
	}());


	// crash fix #3 (tokenize)
	([] {
		//101D5590    6A FF           PUSH - 1
		//101D5592    64:A1 00000000  MOV EAX, DWORD PTR FS : [0]
		//101D5598    68 4D6D1F10     PUSH J2KEngin.101F6D4D
		//101D559D    50              PUSH EAX
		//101D559E    B8 28100000     MOV EAX, 1028
		//101D55A3    64 : 8925 0000000>MOV DWORD PTR FS : [0], ESP
		//101D55AA    E8 A1DA0100     CALL J2KEngin.101F3050
		//101D55AF    53              PUSH EBX
		//101D55B0    55              PUSH EBP
		//101D55B1    56              PUSH ESI
		//101D55B2    8DB1 C4000000   LEA ESI, DWORD PTR DS : [ECX + C4]
		//101D55B8    57              PUSH EDI
		//101D55B9    894C24 18       MOV DWORD PTR SS : [ESP + 18], ECX
		//101D55BD    8B3E            MOV EDI, DWORD PTR DS : [ESI]
		//101D55BF    8B47 F8         MOV EAX, DWORD PTR DS : [EDI - 8]
		//101D55C2    85C0            TEST EAX, EAX
		//101D55C4    0F84 EE0C0000   JE J2KEngin.101D62B8
		//101D55CA    E8 0121E3FF     CALL J2KEngin.100076D0
		//101D55CF    85C0            TEST EAX, EAX
		//101D55D1    74 19           JE SHORT J2KEngin.101D55EC
		//101D55D3    8B06            MOV EAX, DWORD PTR DS : [ESI]
		//101D55D5    8B40 F8         MOV EAX, DWORD PTR DS : [EAX - 8]
		//101D55D8    85C0            TEST EAX, EAX
		//101D55DA    7E 10           JLE SHORT J2KEngin.101D55EC
		//101D55DC    F64438 FF 80    TEST BYTE PTR DS : [EAX + EDI - 1], 80
		//101D55E1    75 09           JNZ SHORT J2KEngin.101D55EC
		//101D55E3    56              PUSH ESI
		//101D55E4    E8 0A12E3FF     CALL J2KEngin.100067F3
		//101D55E9    83C4 04         ADD ESP, 4
		//101D55EC    8B1E            MOV EBX, DWORD PTR DS : [ESI]
		//101D55EE    83CD FF         OR EBP, FFFFFFFF
		//101D55F1    8D4C24 20       LEA ECX, DWORD PTR SS : [ESP + 20]
		//101D55F5    895C24 34       MOV DWORD PTR SS : [ESP + 34], EBX
		//101D55F9    896C24 10       MOV DWORD PTR SS : [ESP + 10], EBP
		//101D55FD    33F6            XOR ESI, ESI
		//101D55FF    E8 46D40100     CALL <JMP.&MFC42.#540>
		//101D5604    8D4C24 24       LEA ECX, DWORD PTR SS : [ESP + 24]
		//101D5608    89B424 40100000 MOV DWORD PTR SS : [ESP + 1040], ESI
		//101D560F    E8 36D40100     CALL <JMP.&MFC42.#540>
		//101D5614    33C0            XOR EAX, EAX
		//101D5616    C78424 40100000>MOV DWORD PTR SS : [ESP + 1040], 1
		//101D5621    894424 2C       MOV DWORD PTR SS : [ESP + 2C], EAX
		//101D5625    894424 30       MOV DWORD PTR SS : [ESP + 30], EAX
		//101D5629    894424 14       MOV DWORD PTR SS : [ESP + 14], EAX
		//101D562D    8A03            MOV AL, BYTE PTR DS : [EBX]
		//101D562F    84C0            TEST AL, AL
		//101D5631    0F84 8D0B0000   JE J2KEngin.101D61C4
		//101D5637    8A03            MOV AL, BYTE PTR DS : [EBX]
		//101D5639    8B3D 84192A10   MOV EDI, DWORD PTR DS : [<&MSVCRT.isalpha>]; msvcrt.isalpha
		//101D563F    3C 3C           CMP AL, 3C
		//101D5641    75 22           JNZ SHORT J2KEngin.101D5665

		// 6A FF 64 A1 00 00 00 00 68 ?? ?? ?? ?? 50 B8 28 10 00 00

		// +0x00  : Function Begin
		// +0xD40 : Function End (RETN)

		// #1A -- MOV BYTE PTR SS:[ESP+ESI+38],0
		// +0x524
		// +0xC43

		// #1B -- MOV BYTE PTR SS:[ESP+ESI+38],41
		// +0xB20

		// #1C -- MOV BYTE PTR SS:[ESP+ESI+38],5B
		// +0x9E2

		// #1D -- MOV BYTE PTR SS:[ESP+ESI+38],81
		// +0x9D8
		// +0xB11

		// #1E -- MOV BYTE PTR SS:[ESP+ESI+38],AL
		// +0x395
		// +0x436
		// +0x448
		// +0x475
		// +0x4A7
		// +0x503
		// +0x7AE
		// +0x897
		// +0x970

		// #1F -- MOV BYTE PTR SS:[ESP+ESI+38],CL
		// +0x390
		// +0x415
		// +0x778
		// +0x7C5
		// +0x7FD
		// +0x866
		// +0xAA2

		// #1G -- MOV BYTE PTR SS:[ESP+ESI+38],DL
		// +0x41D
		// +0x469
		// +0x78F
		// +0x7E3

		// #2 -- MOV BYTE PTR SS:[ESP+ESI+3C],0
		// +0x3B7
		// +0xB44
		// +0xBC4
		// +0xAB5
		// +0x8B5
		// +0x9FD

		// #3A -- MOV BYTE PTR SS:[ESP+38],81
		// +0x5B0
		// +0x5CE

		// #3B -- MOV BYTE PTR SS:[ESP+38],AL
		// +0x632

		// #3C -- MOV BYTE PTR SS:[ESP+38],CL
		// +0x921

		// #3D -- MOV BYTE PTR SS:[ESP+38],DL
		// +0x60C
		// +0xA6D

		// #4A -- MOV BYTE PTR SS:[ESP+39],41
		// +0x5D7

		// #4B -- MOV BYTE PTR SS:[ESP+39],76
		// +0x5B9

		// #4C -- MOV BYTE PTR SS:[ESP+39],AL
		// +0x5FA
		// +0x613

		// #5 -- MOV AL,BYTE PTR SS:[ESP+38]
		// +0xC34

		// #6 -- LEA EAX,DWORD PTR SS:[ESP+38]
		// +0x9F4
		// +0xC45

		// #7 -- LEA ECX,DWORD PTR SS:[ESP+38]
		// +0xB33

		// #8 -- LEA EDX,DWORD PTR SS:[ESP+38]
		// +0x3AE
		// +0x8A8
		// +0xAAC
		// +0xBB3

		// #9 -- LEA ECX,DWORD PTR SS:[ESP+38]
		//    -- MOV BYTE PTR SS:[ESP+ESI+38],AL
		// +0x970

		// #10 -- LEA ECX,DWORD PTR SS:[ESP+38]
		//     -- MOV BYTE PTR SS:[ESP+ESI+38],0
		// +0x51F

		// #11 -- MOV BYTE PTR SS:[ESP+38],CL
		//     -- MOV BYTE PTR SS:[ESP+39],AL
		// +0x5FA


		WORD ptn[] = { 0x6A, 0xFF, 0x64, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x68, -1, -1, -1, -1, 0x50, 0xB8, 0x28, 0x10, 0x00, 0x00 };
		LPBYTE addr = NULL;
		if (search_ptn(ptn, _countof(ptn), &addr, g_szDLLName) == 1)
		{
			// Begin/End
			if (MH_CreateHook(addr, Patch_C_Begin, NULL) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0xD40, Patch_C_End, NULL) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #1A -- MOV BYTE PTR SS:[ESP+ESI+38],0
			/*if (MH_CreateHook(addr + 0x51F, Patch_C1A_1, &fpPatch_Org_C1A_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}*/
			if (MH_CreateHook(addr + 0xC3E, Patch_C1A_2, &fpPatch_Org_C1A_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #1B -- MOV BYTE PTR SS:[ESP+ESI+38],41
			if (MH_CreateHook(addr + 0xB20, Patch_C1B_1, &fpPatch_Org_C1B_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #1C -- MOV BYTE PTR SS:[ESP+ESI+38],5B
			if (MH_CreateHook(addr + 0x9E2, Patch_C1C_1, &fpPatch_Org_C1C_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #1D -- MOV BYTE PTR SS:[ESP+ESI+38],81
			if (MH_CreateHook(addr + 0x9D8, Patch_C1D_1, &fpPatch_Org_C1D_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0xB11, Patch_C1D_2, &fpPatch_Org_C1D_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #1E -- MOV BYTE PTR SS:[ESP+ESI+38],AL
			if (MH_CreateHook(addr + 0x395, Patch_C1E_1, &fpPatch_Org_C1E_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x436, Patch_C1E_2, &fpPatch_Org_C1E_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x448, Patch_C1E_3, &fpPatch_Org_C1E_3) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x475, Patch_C1E_4, &fpPatch_Org_C1E_4) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x4A7, Patch_C1E_5, &fpPatch_Org_C1E_5) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x503, Patch_C1E_6, &fpPatch_Org_C1E_6) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x7AE, Patch_C1E_7, &fpPatch_Org_C1E_7) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x897, Patch_C1E_8, &fpPatch_Org_C1E_8) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			/*if (MH_CreateHook(addr + 0x970, Patch_C1E_9, &fpPatch_Org_C1E_9) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}*/

			// #1F -- MOV BYTE PTR SS:[ESP+ESI+38],CL
			if (MH_CreateHook(addr + 0x390, Patch_C1F_1, &fpPatch_Org_C1F_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x415, Patch_C1F_2, &fpPatch_Org_C1F_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x778, Patch_C1F_3, &fpPatch_Org_C1F_3) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x7C5, Patch_C1F_4, &fpPatch_Org_C1F_4) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x7FD, Patch_C1F_5, &fpPatch_Org_C1F_5) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x866, Patch_C1F_6, &fpPatch_Org_C1F_6) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0xAA2, Patch_C1F_7, &fpPatch_Org_C1F_7) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #1G -- MOV BYTE PTR SS:[ESP+ESI+38],DL
			if (MH_CreateHook(addr + 0x41D, Patch_C1G_1, &fpPatch_Org_C1G_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x469, Patch_C1G_2, &fpPatch_Org_C1G_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x78F, Patch_C1G_3, &fpPatch_Org_C1G_3) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x7E3, Patch_C1G_4, &fpPatch_Org_C1G_4) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #2 -- MOV BYTE PTR SS:[ESP+ESI+3C],0
			if (MH_CreateHook(addr + 0x3B7, Patch_C2_1, &fpPatch_Org_C2_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0xB44, Patch_C2_2, &fpPatch_Org_C2_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0xBC4, Patch_C2_3, &fpPatch_Org_C2_3) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0xAB5, Patch_C2_4, &fpPatch_Org_C2_4) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x8B5, Patch_C2_5, &fpPatch_Org_C2_5) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x9FD, Patch_C2_6, &fpPatch_Org_C2_6) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #3A -- MOV BYTE PTR SS:[ESP+38],81
			if (MH_CreateHook(addr + 0x5B0, Patch_C3A_1, &fpPatch_Org_C3A_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x5CE, Patch_C3A_1, &fpPatch_Org_C3A_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #3B -- MOV BYTE PTR SS:[ESP+38],AL
			if (MH_CreateHook(addr + 0x632, Patch_C3B_1, &fpPatch_Org_C3B_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #3C -- MOV BYTE PTR SS:[ESP+38],CL
			if (MH_CreateHook(addr + 0x921, Patch_C3C_2, &fpPatch_Org_C3C_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #3D -- MOV BYTE PTR SS:[ESP+38],DL
			if (MH_CreateHook(addr + 0x60C, Patch_C3D_1, &fpPatch_Org_C3D_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0xA6D, Patch_C3D_2, &fpPatch_Org_C3D_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #4A -- MOV BYTE PTR SS:[ESP+39],41
			if (MH_CreateHook(addr + 0x5D7, Patch_C4A_1, &fpPatch_Org_C4A_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #4B -- MOV BYTE PTR SS:[ESP+39],76
			if (MH_CreateHook(addr + 0x5B9, Patch_C4B_1, &fpPatch_Org_C4B_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #4C -- MOV BYTE PTR SS:[ESP+39],AL
			if (MH_CreateHook(addr + 0x613, Patch_C4C_2, &fpPatch_Org_C4C_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #5 -- MOV AL,BYTE PTR SS:[ESP+38]
			if (MH_CreateHook(addr + 0xC34, Patch_C5_1, &fpPatch_Org_C5_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #6 -- LEA EAX,DWORD PTR SS:[ESP+38]
			if (MH_CreateHook(addr + 0x9F4, Patch_C6_1, &fpPatch_Org_C6_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0xC45, Patch_C6_2, &fpPatch_Org_C6_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #7 -- LEA ECX,DWORD PTR SS:[ESP+38]
			if (MH_CreateHook(addr + 0xB33, Patch_C7_1, &fpPatch_Org_C7_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #8 -- LEA EDX,DWORD PTR SS:[ESP+38]
			if (MH_CreateHook(addr + 0x3AE, Patch_C8_1, &fpPatch_Org_C8_1) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x8A8, Patch_C8_2, &fpPatch_Org_C8_2) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			if (MH_CreateHook(addr + 0xAAC, Patch_C8_3, &fpPatch_Org_C8_3) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0xBB3, Patch_C8_4, &fpPatch_Org_C8_4) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #9
			if (MH_CreateHook(addr + 0x970, Patch_C9, &fpPatch_Org_C9) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #10
			if (MH_CreateHook(addr + 0x51F, Patch_C10, &fpPatch_Org_C10) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// #11
			if (MH_CreateHook(addr + 0x5FA, Patch_C11, &fpPatch_Org_C11) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}

			// Begin/End
			lpfnRetn_C_Begin = addr + 0x0D;
			MH_EnableHook(addr);
			MH_EnableHook(addr + 0xD40);

			// #1A -- MOV BYTE PTR SS:[ESP+ESI+38],0
			MH_EnableHook(addr + 0x51F);
			MH_EnableHook(addr + 0xC3E);

			// #1B -- MOV BYTE PTR SS:[ESP+ESI+38],41
			MH_EnableHook(addr + 0xB20);

			// #1C -- MOV BYTE PTR SS:[ESP+ESI+38],5B
			MH_EnableHook(addr + 0x9E2);

			// #1D -- MOV BYTE PTR SS:[ESP+ESI+38],81
			MH_EnableHook(addr + 0x9D8);
			MH_EnableHook(addr + 0xB11);

			// #1E -- MOV BYTE PTR SS:[ESP+ESI+38],AL
			MH_EnableHook(addr + 0x395);
			MH_EnableHook(addr + 0x436);
			MH_EnableHook(addr + 0x448);
			MH_EnableHook(addr + 0x475);
			MH_EnableHook(addr + 0x4A7);
			MH_EnableHook(addr + 0x503);
			MH_EnableHook(addr + 0x7AE);
			MH_EnableHook(addr + 0x897);
			MH_EnableHook(addr + 0x970);

			// #1F -- MOV BYTE PTR SS:[ESP+ESI+38],CL
			MH_EnableHook(addr + 0x390);
			MH_EnableHook(addr + 0x415);
			MH_EnableHook(addr + 0x778);
			MH_EnableHook(addr + 0x7C5);
			MH_EnableHook(addr + 0x7FD);
			MH_EnableHook(addr + 0x866);
			MH_EnableHook(addr + 0xAA2);

			// #1G -- MOV BYTE PTR SS:[ESP+ESI+38],DL
			MH_EnableHook(addr + 0x41D);
			MH_EnableHook(addr + 0x469);
			MH_EnableHook(addr + 0x78F);
			MH_EnableHook(addr + 0x7E3);

			// #2 -- MOV BYTE PTR SS:[ESP+ESI+3C],0
			MH_EnableHook(addr + 0x3B7);
			MH_EnableHook(addr + 0xB44);
			MH_EnableHook(addr + 0xBC4);
			MH_EnableHook(addr + 0xAB5);
			MH_EnableHook(addr + 0x8B5);
			MH_EnableHook(addr + 0x9FD);

			// #3A -- MOV BYTE PTR SS:[ESP+38],81
			MH_EnableHook(addr + 0x5B0);
			MH_EnableHook(addr + 0x5CE);

			// #3B -- MOV BYTE PTR SS:[ESP+38],AL
			MH_EnableHook(addr + 0x632);

			// #3C -- MOV BYTE PTR SS:[ESP+38],CL
			MH_EnableHook(addr + 0x921);

			// #3D -- MOV BYTE PTR SS:[ESP+38],DL
			MH_EnableHook(addr + 0x60C);
			MH_EnableHook(addr + 0xA6D);

			// #4A -- MOV BYTE PTR SS:[ESP+39],41
			MH_EnableHook(addr + 0x5D7);

			// #4B -- MOV BYTE PTR SS:[ESP+39],76
			MH_EnableHook(addr + 0x5B9);

			// #4C -- MOV BYTE PTR SS:[ESP+39],AL
			MH_EnableHook(addr + 0x5FA);
			MH_EnableHook(addr + 0x613);

			// #5 -- MOV AL,BYTE PTR SS:[ESP+38]
			MH_EnableHook(addr + 0xC34);

			// #6 -- LEA EAX,DWORD PTR SS:[ESP+38]
			MH_EnableHook(addr + 0x9F4);
			MH_EnableHook(addr + 0xC45);

			// #7 -- LEA ECX,DWORD PTR SS:[ESP+38]
			MH_EnableHook(addr + 0xB33);

			// #8 -- LEA EDX,DWORD PTR SS:[ESP+38]
			MH_EnableHook(addr + 0x3AE);
			MH_EnableHook(addr + 0x8A8);
			MH_EnableHook(addr + 0xAAC);
			MH_EnableHook(addr + 0xBB3);

			// #9
			MH_EnableHook(addr + 0x970);

			// #10
			MH_EnableHook(addr + 0x51F);

			// #11
			MH_EnableHook(addr + 0x5FA);

		}
	}());

	
	return true;
}

bool EH_UninstallHook()
{
	EH_UninitLua();
	MH_Uninitialize();
	return true;
}

// 내보낸 변수의 예제입니다.
EHND_API int nEhnd=0;

// 내보낸 함수의 예제입니다.
EHND_API int fnEhnd(void)
{
    return 42;
}

// 내보낸 클래스의 생성자입니다.
// 클래스 정의를 보려면 Ehnd.h를 참조하십시오.
CEhnd::CEhnd()
{
    return;
}
