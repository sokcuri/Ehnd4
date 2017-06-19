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
#include "MinHook.h"
#include "CrashFix.h"

LPVOID fpPatch_Org_A1;
LPVOID fpPatch_Org_A2;
LPVOID fpPatch_Org_A3;
LPVOID fpPatch_Org_C_Begin;
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

char *assign_memory(char *str)
{
	return new char[strlen(str) + 1];
}
void destroy_memory(char *str)
{
	return delete[] str;
}

// fix buffer overflow (process routine)
NAKED void Patch_A1()
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
		PUSH 0
		PUSH EAX
		PUSH EDX

		MOV EAX, DWORD PTR DS : [fpPatch_Org_A1]
		ADD EAX, 0x05
		MOV EDX, DWORD PTR DS : [EAX + 1]
		ADD EAX, EDX
		ADD EAX, 0x08
		MOV DWORD PTR SS : [ESP + 0x08], EAX

		POP EDX
		POP EAX
		RETN
	}
}
NAKED void Patch_A2()
{
	__asm
	{
		ADD ESP, 4
		MOV EAX, DWORD PTR SS : [ESP + 0x2C]
		PUSH 0
		PUSH EAX
		PUSH EDX

		MOV EAX, DWORD PTR DS : [fpPatch_Org_A2]
		ADD EAX, 0x05
		MOV EDX, DWORD PTR DS : [EAX + 1]
		ADD EAX, EDX
		ADD EAX, 0x09
		MOV DWORD PTR SS : [ESP + 0x08], EAX

		POP EDX
		POP EAX
		RETN
	}
}
NAKED void Patch_A3()
{
	__asm
	{
		PUSH DWORD PTR SS : [ESP + 0x2C]
		CALL destroy_memory
		ADD ESP, 4
		JMP fpPatch_Org_A3
	}
}

NAKED void Patch_C_Begin()
{
	// ECX+0xC4에 input data가 저장되어 있음.
	// 이 데이터의 길이를 기반으로 임시 공간을 만들고
	// 모든 접근을 그쪽으로 우회

	// SE Handler ESP+0x103C 주소를 이용해 저장

	__asm
	{
		MOV EAX, DWORD PTR DS : [ECX + 0xC4]

		// shield
		PUSH ECX

		PUSH EAX // input data
		CALL assign_memory
		ADD ESP, 0x04

		// sheield
		POP ECX

		PUSH EAX
		MOV EAX, DWORD PTR FS : [0]
		PUSH fpPatch_Org_C_Begin
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
NAKED void Patch_C1(char chr)
{
	__asm
	{
		PUSH EAX
		PUSH ECX
		MOV CL, BYTE PTR SS : [ESP + 0x0C]
		MOV EAX, DWORD PTR SS : [ESP + 0x104C]
		MOV BYTE PTR SS : [EAX + ESI], CL
		POP ECX
		POP EAX
		RETN
	}
}

// MOV BYTE PTR SS:[ESP+ESI+0x38], 0x00
NAKED void Patch_C1A_1()
{
	__asm
	{
		PUSH 0x00
		CALL Patch_C1
		ADD ESP, 0x04
		PUSH fpPatch_Org_C1A_1
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}
NAKED void Patch_C1A_2()
{
	__asm
	{
		PUSH EAX
		MOV EAX, DWORD PTR SS : [ESP + 0x1040]
		MOV BYTE PTR SS : [EAX + ESI], 0x00
		POP EAX
		PUSH fpPatch_Org_C1A_2
		ADD DWORD PTR SS : [ESP], 0x05
		RETN
	}
}

// MOV BYTE PTR SS:[ESP+ESI+0x0x38], 0x41
NAKED void Patch_C1B_1()
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
NAKED void Patch_C1C_1()
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
NAKED void Patch_C1D_1()
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
NAKED void Patch_C1D_2()
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
NAKED void Patch_C1E_1()
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
NAKED void Patch_C1E_2()
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
NAKED void Patch_C1E_3()
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
NAKED void Patch_C1E_4()
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
NAKED void Patch_C1E_5()
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
NAKED void Patch_C1E_6()
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
NAKED void Patch_C1E_7()
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
NAKED void Patch_C1E_8()
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
NAKED void Patch_C1E_9()
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
NAKED void Patch_C1F_1()
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
NAKED void Patch_C1F_2()
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
NAKED void Patch_C1F_3()
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
NAKED void Patch_C1F_4()
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
NAKED void Patch_C1F_5()
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
NAKED void Patch_C1F_6()
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
NAKED void Patch_C1F_7()
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
NAKED void Patch_C1G_1()
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
NAKED void Patch_C1G_2()
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
NAKED void Patch_C1G_3()
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
NAKED void Patch_C1G_4()
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
NAKED void Patch_C2(char chr)
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
NAKED void Patch_C2_1()
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
NAKED void Patch_C2_2()
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
NAKED void Patch_C2_3()
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
NAKED void Patch_C2_4()
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
NAKED void Patch_C2_5()
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
NAKED void Patch_C2_6()
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

NAKED void Patch_C3(char chr)
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
NAKED void Patch_C3A_1()
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
NAKED void Patch_C3A_2()
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
NAKED void Patch_C3B_1()
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
NAKED void Patch_C3C_2()
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
NAKED void Patch_C3D_1()
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
NAKED void Patch_C3D_2()
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

NAKED void Patch_C4(char chr)
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
NAKED void Patch_C4A_1()
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
NAKED void Patch_C4B_1()
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
NAKED void Patch_C4C_1()
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
NAKED void Patch_C4C_2()
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
NAKED void Patch_C5()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [ESP + 0x1040]
		MOV AL, BYTE PTR DS : [EAX]
		RETN
	}
}
NAKED void Patch_C5_1()
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
NAKED void Patch_C6()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [ESP + 0x1040]
		RETN
	}
}
NAKED void Patch_C6_1()
{
	__asm
	{
		CALL Patch_C6
		PUSH fpPatch_Org_C6_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
NAKED void Patch_C6_2()
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
NAKED void Patch_C7()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [ESP + 0x1040]
		RETN
	}
}
NAKED void Patch_C7_1()
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
NAKED void Patch_C8()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [ESP + 0x1040]
		RETN
	}
}
NAKED void Patch_C8_1()
{
	__asm
	{
		CALL Patch_C8
		PUSH fpPatch_Org_C8_1
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
NAKED void Patch_C8_2()
{
	__asm
	{
		CALL Patch_C8
		PUSH fpPatch_Org_C8_2
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
NAKED void Patch_C8_3()
{
	__asm
	{
		CALL Patch_C8
		PUSH fpPatch_Org_C8_3
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
NAKED void Patch_C8_4()
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
NAKED void Patch_C9()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [ESP + 0x103C]
		MOV BYTE PTR SS : [ECX + ESI], AL

		PUSH fpPatch_Org_C9
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}
// LEA ECX,DWORD PTR SS:[ESP+38]
// MOV BYTE PTR SS:[ESP+ESI+38],0
NAKED void Patch_C10()
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
NAKED void Patch_C11()
{
	__asm
	{
		PUSH EDX
		MOV EDX, DWORD PTR SS : [ESP + 0x1040]
		MOV BYTE PTR DS : [EDX], CL
		MOV BYTE PTR DS : [EDX + 1], AL
		POP EDX

		PUSH fpPatch_Org_C11
		ADD DWORD PTR SS : [ESP], 0x04
		RETN
	}
}

NAKED void Patch_C_End()
{
	__asm
	{
		PUSH DWORD PTR SS : [ESP - 0x08]
		CALL destroy_memory
		ADD ESP, 0x04
		RETN
	}
}

bool CrashFixHook()
{

	// CrashFix -- Prevent to crash ezTransXP
	LPBYTE addr1, addr2;

	WORD ptn1[] = {										// 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 81 EC 1C 01 00 00
		0x6A, 0xFF,										// 101D66B0 | 6A FF               PUSH -1
		0x68, -1, -1, -1, -1,							// 101D66B2 | 68 6A5B1F10         PUSH J2KEngin.101F5B6A
		0x64, 0xA1, 0x00, 0x00, 0x00, 0x00,				// 101D66B7 | 64:A1 00000000      MOV EAX,DWORD PTR FS:[0]
		0x50,											// 101D66BD | 50                  PUSH EAX
		0x64, 0x89, 0x25, 0x00, 0x00, 0x00, 0x00,		// 101D66BE | 64:8925 00000000    MOV DWORD PTR FS:[0],ESP
		0x81, 0xEC, 0x1C, 0x01, 0x00, 0x00 };			// 101D66C5 | 81EC 1C010000       SUB ESP,11C

	WORD ptn2[] = {										// 6A FF 64 A1 00 00 00 00 68 ?? ?? ?? ?? 50 B8 28 10 00 00
		0x6A, 0xFF,										// 101D5590 | 6A FF               PUSH -1
		0x64, 0xA1, 0x00, 0x00, 0x00, 0x00,				// 101D5592 | 64:A1 00000000      MOV EAX, DWORD PTR FS : [0]
		0x68, -1, -1, -1, -1,							// 101D5598 | 68 4D6D1F10         PUSH J2KEngin.101F6D4D
		0x50,											// 101D559D | 50                  PUSH EAX
		0xB8, 0x28, 0x10, 0x00, 0x00 };					// 101D559E | B8 28100000         MOV EAX, 1028

	std::list<std::tuple<char *, WORD *, size_t, LPBYTE *>> patterns = {
		{ "CrashFix Pattern 1", ptn1, _countof(ptn1), &addr1 },
		{ "CrashFix Pattern 2", ptn2, _countof(ptn2), &addr2 }
	};
	for (const auto &p : patterns)
	{
		if (search_ptn(std::get<1>(p), std::get<2>(p), std::get<3>(p), g_szDLLName) != 1)
		{
			printf("Can't Found %s\n", std::get<0>(p));
			return false;
		}
	}

	std::list<std::tuple<char *, LPVOID, LPVOID, LPVOID *>> fpHookTable =
	{
		// #A
		{ "A_1", addr1 + 0x248, Patch_A1, &fpPatch_Org_A1 },		// +0x248 | LEA EDX,DWORD PTR SS : [ESP + 2C]	|| CALL EDI (lstrcpyA)
		{ "A_2", addr1 + 0x263, Patch_A2, &fpPatch_Org_A2 },		// +0x263 | ADD ESP,4; MOV ESI, EBP				|| LEA EAX,DWORD PTR SS:[ESP+2C]
		{ "A_3", addr1 + 0x2A1, Patch_A3, &fpPatch_Org_A3 },		// +0x2A1 | PUSH 0x0F; PUSH EBP; MOV ECX, EBX

																	// #C_Begin
		{ "C_Begin", addr2 + 0x08, Patch_C_Begin, &fpPatch_Org_C_Begin },

		// #C_End
		{ "C_End", addr2 + 0xD40, Patch_C_End, NULL },

		// #C1A -- MOV BYTE PTR SS:[ESP+ESI+38],0
		{ "C1A_2", addr2 + 0xC3E, Patch_C1A_2, &fpPatch_Org_C1A_2 },

		// #C1B -- MOV BYTE PTR SS:[ESP+ESI+38],41
		{ "C1B_1", addr2 + 0xB20, Patch_C1B_1, &fpPatch_Org_C1B_1 },

		// #C1C -- MOV BYTE PTR SS:[ESP+ESI+38],5B
		{ "C1C_1", addr2 + 0x9E2, Patch_C1C_1, &fpPatch_Org_C1C_1 },

		// #C1D -- MOV BYTE PTR SS:[ESP+ESI+38],81
		{ "C1D_1", addr2 + 0x9D8, Patch_C1D_1, &fpPatch_Org_C1D_1 },
		{ "C1D_2", addr2 + 0xB11, Patch_C1D_2, &fpPatch_Org_C1D_2 },

		// #C1E -- MOV BYTE PTR SS:[ESP+ESI+38],AL
		{ "C1E_1", addr2 + 0x395, Patch_C1E_1, &fpPatch_Org_C1E_1 },
		{ "C1E_2", addr2 + 0x436, Patch_C1E_2, &fpPatch_Org_C1E_2 },
		{ "C1E_3", addr2 + 0x448, Patch_C1E_3, &fpPatch_Org_C1E_3 },
		{ "C1E_4", addr2 + 0x475, Patch_C1E_4, &fpPatch_Org_C1E_4 },
		{ "C1E_5", addr2 + 0x4A7, Patch_C1E_5, &fpPatch_Org_C1E_5 },
		{ "C1E_6", addr2 + 0x503, Patch_C1E_6, &fpPatch_Org_C1E_6 },
		{ "C1E_7", addr2 + 0x7AE, Patch_C1E_7, &fpPatch_Org_C1E_7 },
		{ "C1E_8", addr2 + 0x897, Patch_C1E_8, &fpPatch_Org_C1E_8 },

		// #C1F -- MOV BYTE PTR SS:[ESP+ESI+38],CL
		{ "C1F_1", addr2 + 0x390, Patch_C1F_1, &fpPatch_Org_C1F_1 },
		{ "C1F_2", addr2 + 0x415, Patch_C1F_2, &fpPatch_Org_C1F_2 },
		{ "C1F_3", addr2 + 0x778, Patch_C1F_3, &fpPatch_Org_C1F_3 },
		{ "C1F_4", addr2 + 0x7C5, Patch_C1F_4, &fpPatch_Org_C1F_4 },
		{ "C1F_5", addr2 + 0x7FD, Patch_C1F_5, &fpPatch_Org_C1F_5 },
		{ "C1F_6", addr2 + 0x866, Patch_C1F_6, &fpPatch_Org_C1F_6 },
		{ "C1F_7", addr2 + 0xAA2, Patch_C1F_7, &fpPatch_Org_C1F_7 },

		// #C1G -- MOV BYTE PTR SS:[ESP+ESI+38],DL
		{ "C1G_1", addr2 + 0x41D, Patch_C1G_1, &fpPatch_Org_C1G_1 },
		{ "C1G_2", addr2 + 0x469, Patch_C1G_2, &fpPatch_Org_C1G_2 },
		{ "C1G_3", addr2 + 0x78F, Patch_C1G_3, &fpPatch_Org_C1G_3 },
		{ "C1G_4", addr2 + 0x7E3, Patch_C1G_4, &fpPatch_Org_C1G_4 },

		// #C2 -- MOV BYTE PTR SS:[ESP+ESI+3C],0
		{ "C2_1", addr2 + 0x3B7, Patch_C2_1, &fpPatch_Org_C2_1 },
		{ "C2_2", addr2 + 0xB44, Patch_C2_2, &fpPatch_Org_C2_2 },
		{ "C2_3", addr2 + 0xBC4, Patch_C2_3, &fpPatch_Org_C2_3 },
		{ "C2_4", addr2 + 0xAB5, Patch_C2_4, &fpPatch_Org_C2_4 },
		{ "C2_5", addr2 + 0x8B5, Patch_C2_5, &fpPatch_Org_C2_5 },
		{ "C2_6", addr2 + 0x9FD, Patch_C2_6, &fpPatch_Org_C2_6 },

		// #C3A -- MOV BYTE PTR SS:[ESP+38],81
		{ "C3A_1", addr2 + 0x5B0, Patch_C3A_1, &fpPatch_Org_C3A_1 },
		{ "C3A_2", addr2 + 0x5CE, Patch_C3A_2, &fpPatch_Org_C3A_2 },

		// #C3B -- MOV BYTE PTR SS:[ESP+38],AL
		{ "C3B_1", addr2 + 0x632, Patch_C3B_1, &fpPatch_Org_C3B_1 },

		// #C3C -- MOV BYTE PTR SS:[ESP+38],CL
		{ "C3C_2", addr2 + 0x921, Patch_C3C_2, &fpPatch_Org_C3C_2 },

		// #C3D -- MOV BYTE PTR SS:[ESP+38],DL
		{ "C3D_1", addr2 + 0x60C, Patch_C3D_1, &fpPatch_Org_C3D_1 },
		{ "C3D_2", addr2 + 0xA6D, Patch_C3D_2, &fpPatch_Org_C3D_2 },

		// #C4A -- MOV BYTE PTR SS:[ESP+39],41
		{ "C4A_1", addr2 + 0x5D7, Patch_C4A_1, &fpPatch_Org_C4A_1 },

		// #C4B -- MOV BYTE PTR SS:[ESP+39],76
		{ "C4B_1", addr2 + 0x5B9, Patch_C4B_1, &fpPatch_Org_C4B_1 },

		// #C4C -- MOV BYTE PTR SS:[ESP+39],AL
		{ "C4C_2", addr2 + 0x613, Patch_C4C_2, &fpPatch_Org_C4C_2 },

		// #C5 -- MOV AL,BYTE PTR SS:[ESP+38]
		{ "C5_1", addr2 + 0xC34, Patch_C5_1, &fpPatch_Org_C5_1 },

		// #C6 -- LEA EAX,DWORD PTR SS:[ESP+38
		{ "C6_1", addr2 + 0x9F4, Patch_C6_1, &fpPatch_Org_C6_1 },
		{ "C6_2", addr2 + 0xC45, Patch_C6_2, &fpPatch_Org_C6_2 },

		// #C7 -- LEA ECX,DWORD PTR SS:[ESP+38]
		{ "C7_1", addr2 + 0xB33, Patch_C7_1, &fpPatch_Org_C7_1 },

		// #C8 -- LEA EDX,DWORD PTR SS:[ESP+38]
		{ "C8_1", addr2 + 0x3AE, Patch_C8_1, &fpPatch_Org_C8_1 },
		{ "C8_2", addr2 + 0x8A8, Patch_C8_2, &fpPatch_Org_C8_2 },
		{ "C8_3", addr2 + 0xAAC, Patch_C8_3, &fpPatch_Org_C8_3 },
		{ "C8_4", addr2 + 0xBB3, Patch_C8_4, &fpPatch_Org_C8_4 },

		// #C9 -- LEA ECX,DWORD PTR SS:[ESP+38]
		//    -- MOV BYTE PTR SS:[ESP+ESI+38],AL
		{ "C9_1", addr2 + 0x970, Patch_C9, &fpPatch_Org_C9 },

		// #C10 -- LEA ECX,DWORD PTR SS:[ESP+38]
		//     -- MOV BYTE PTR SS:[ESP+ESI+38],0
		{ "C10_1", addr2 + 0x51F, Patch_C10, &fpPatch_Org_C10 },

		// #C11 -- MOV BYTE PTR SS:[ESP+38],CL
		//     -- MOV BYTE PTR SS:[ESP+39],AL
		{ "C11_1", addr2 + 0x5FA, Patch_C11, &fpPatch_Org_C11 },
	};

	bool patch_result = [fpHookTable]
	{
		for (const auto &tp : fpHookTable)
		{
			if (MH_CreateHook(std::get<1>(tp), std::get<2>(tp), std::get<3>(tp)) != MH_OK)
			{
				printf("CreateHook Failed: %s\n", std::get<0>(tp));
				return false;
			}
		}

		for (const auto &tp : fpHookTable)
		{
			if (MH_EnableHook(std::get<1>(tp)) != MH_OK)
			{
				printf("EnableHook Failed: %s\n", std::get<0>(tp));
				return false;
			}
		}
		return true;
	}();
	if (!patch_result)
	{
		MessageBox(0, L"Hook Failed", L"CrashFix", MB_ICONERROR);
		return false;
	}
	return true;
}