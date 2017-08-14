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

#pragma once

char * assign_memory(char * str);
void destroy_memory(char * str);

void Patch_A1();
void Patch_A2();
void Patch_A3();

void Patch_C_Begin();
void Patch_C1(char chr);
void Patch_C1A_1();
void Patch_C1A_2();
void Patch_C1B_1();
void Patch_C1C_1();
void Patch_C1D_1();
void Patch_C1D_2();
void Patch_C1E_1();
void Patch_C1E_2();
void Patch_C1E_3();
void Patch_C1E_4();
void Patch_C1E_5();
void Patch_C1E_6();
void Patch_C1E_7();
void Patch_C1E_8();
void Patch_C1E_9();
void Patch_C1F_1();
void Patch_C1F_2();
void Patch_C1F_3();
void Patch_C1F_4();
void Patch_C1F_5();
void Patch_C1F_6();
void Patch_C1F_7();
void Patch_C1G_1();
void Patch_C1G_2();
void Patch_C1G_3();
void Patch_C1G_4();

void Patch_C2(char chr);
void Patch_C2_1();
void Patch_C2_2();
void Patch_C2_3();
void Patch_C2_4();
void Patch_C2_5();
void Patch_C2_6();

void Patch_C3(char chr);
void Patch_C3A_1();
void Patch_C3A_2();
void Patch_C3B_1();
void Patch_C3C_2();
void Patch_C3D_1();
void Patch_C3D_2();

void Patch_C4(char chr);
void Patch_C4A_1();
void Patch_C4B_1();
void Patch_C4C_1();
void Patch_C4C_2();

void Patch_C5();
void Patch_C5_1();

void Patch_C6();
void Patch_C6_1();
void Patch_C6_2();

void Patch_C7();
void Patch_C7_1();

void Patch_C8();
void Patch_C8_1();
void Patch_C8_2();
void Patch_C8_3();
void Patch_C8_4();

void Patch_C9();
void Patch_C10();
void Patch_C11();
void Patch_C_End();

bool EZTJ2K_FixHook(char *module_name);
