// SectionModifier.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <atlstr.h>

//#define FOR_EXE
//#define FOR_DLL
//#define FOR_AVIRA_EXE
#define FOR_01_TEST

#ifdef FOR_AVIRA_EXE
void ChangeName(int sectionNumber, char* name)
{
	CString newName(name);
	CString oldName(name);

	switch (sectionNumber)
	{
	case 0:
		newName = ".sdata";
		break;
	case 1:
		newName = ".rdata";
		break;
	case 2:
		newName = ".reloc";
		break;
	case 3:
		newName = ".idata";
		break;
	case 4:
		newName = ".pdata";
		break;
	case 5:
		newName = ".bss";
		break;
	case 6:
		newName = ".data";
		break;
	case 7:
		newName = ".ndata";
		break;
	default:
		newName.Format(".sec%d", sectionNumber);
		break;
	}

	for (int i = 0; i < 8; i++)
	{
		if (i < newName.GetLength())
			name[i] = newName[i];
		else
			name[i] = '\0';
	}
}
#endif

#ifdef FOR_EXE
void ChangeName(int sectionNumber, char* name)
{
	CString newName(name);
	CString oldName(name);

	switch (sectionNumber)
	{
	case 0:
		newName = ".idata";
		break;
	case 1:
		newName = ".rdata";
		break;
	case 2:
		newName = ".reloc";
		break;
	case 3:
		newName = ".pdata";
		break;
	case 4:
		newName = ".sdata";
		break;
	case 5:
		newName = ".bss";
		break;
	case 6:
		newName = ".data";
		break;
	case 7:
		newName = ".ndata";
		break;
	default:
		newName.Format(".sec%d", sectionNumber);
		break;
	}

	for (int i = 0; i < 8; i++)
	{
		if (i < newName.GetLength())
			name[i] = newName[i];
		else
			name[i] = '\0';
	}
}
#endif


#ifdef FOR_01_TEST
void ChangeName(int sectionNumber, char* name)
{
	CString newName(name);
	CString oldName(name);

	switch (sectionNumber)
	{
	case 0:
		newName = ".text";
		break;
	case 1:
		newName = ".rdata";
		break;
	case 2:
		newName = ".data";
		break;
	case 3:
		newName = ".qtmetad";
		break;
	case 4:
		newName = ".tls";
		break;
	case 5:
		newName = ".gfids";
		break;
	case 6:
		newName = "_RDATA";
		break;
	case 7:
		newName = ".rsrc";
		break;
	case 8:
		newName = ".reloc";
		break;
	default:
		newName = "";
		break;
	}

	for (int i = 0; i < 8; i++)
	{
		if (i < newName.GetLength())
			name[i] = newName[i];
		else
			name[i] = '\0';
	}
}
#endif


#ifdef FOR_AVIRA_DLL
void ChangeName(int sectionNumber, char* name)
{
	CString newName(name);
	CString oldName(name);

	switch (sectionNumber)
	{
	case 0:
		newName = ".sdata";
		break;
	case 1:
		newName = ".rdata";
		break;
	case 2:
		newName = ".reloc";
		break;
	case 3:
		newName = ".bss";
		break;
	case 4:
		newName = ".idata";
		break;
	case 5:
		newName = ".pdata";
		break;
	case 6:
		newName = ".data";
		break;
	case 7:
		newName = ".ndata";
		break;
	default:
		newName.Format(".sec%d", sectionNumber);
		break;
	}

	for (int i = 0; i < 8; i++)
	{
		if (i < newName.GetLength())
			name[i] = newName[i];
		else
			name[i] = '\0';
	}
}
#endif

#ifdef FOR_DLL
void ChangeName(int sectionNumber, char* name)
{
	CString newName(name);
	CString oldName(name);

	switch (sectionNumber)
	{
	case 0:
		newName = ".idata";
		break;
	case 1:
		newName = ".rdata";
		break;
	case 2:
		newName = ".reloc";
		break;
	case 3:
		newName = ".bss";
		break;
	case 4:
		newName = ".pdata";
		break;
	case 5:
		newName = ".sdata";
		break;
	case 6:
		newName = ".data";
		break;
	case 7:
		newName = ".ndata";
		break;
	default:
		newName.Format(".sec%d", sectionNumber);
		break;
	}

	for (int i = 0; i < 8; i++)
	{
		if (i < newName.GetLength())
			name[i] = newName[i];
		else
			name[i] = '\0';
	}
}
#endif




int main(int argc, TCHAR* argv[])
{
	if (argc < 2)
	{
		::MessageBox(NULL, "No arguments", "Error", MB_OK);
		return 0;
	}


	int i = 0;
	HANDLE hMapObject, hFile;            //File Mapping Object
	LPVOID lpBase;                      //Pointer to the base memory of mapped file
	PIMAGE_DOS_HEADER dosHeader;        //Pointer to DOS Header
	PIMAGE_NT_HEADERS ntHeader;         //Pointer to NT Header
	IMAGE_FILE_HEADER header;           //Pointer to image file header of NT Header 
	IMAGE_OPTIONAL_HEADER opHeader;     //Optional Header of PE files present in NT Header structure
	PIMAGE_SECTION_HEADER pSecHeader;   //Section Header or Section Table Header
	
	CString inputFile(argv[1]);
	CString outputFile(argv[1]);
	if (argc > 2)
	{
		outputFile = CString(argv[2]);
	}

	//Open the Exe File 
	hFile = CreateFile(inputFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{ 
		::MessageBox(NULL, "File not found", "Error", MB_OK);
		return 0;
	};

	DWORD dwFileZize = GetFileSize(hFile, NULL);
	byte* fileData = new byte[dwFileZize];

	DWORD dwRead;
	ReadFile(hFile, fileData, dwFileZize, &dwRead, NULL);


	//Mapping Given EXE file to Memory
	hMapObject = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	lpBase = MapViewOfFile(hMapObject, FILE_MAP_READ, 0, 0, 0);

	//Get the DOS Header Base 
	dosHeader = (PIMAGE_DOS_HEADER)lpBase;// 0x04000000
											//Check for Valid DOS file
	if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE)
	{


	}
	ntHeader = (PIMAGE_NT_HEADERS)((DWORD)(dosHeader)+(dosHeader->e_lfanew));
	if (ntHeader->Signature == IMAGE_NT_SIGNATURE) 
	{
		for (pSecHeader = IMAGE_FIRST_SECTION(ntHeader), i = 0; i < ntHeader->FileHeader.NumberOfSections; i++, pSecHeader++) 
		{
			DWORD offset = ((DWORD*)pSecHeader - (DWORD*)dosHeader) * sizeof(DWORD);

			DWORD* dw = (DWORD*)(fileData + offset);
			PIMAGE_SECTION_HEADER pFileSec = (PIMAGE_SECTION_HEADER)dw;

			ChangeName(i, (char*)pFileSec->Name);

			TCHAR sectionName[9] = { 0 };
			memcpy(sectionName, pSecHeader->Name, 8);
			CString str(sectionName);
		}
	}

	UnmapViewOfFile(lpBase);
	CloseHandle(hMapObject);
	CloseHandle(hFile);
	
	// write file 
	HANDLE hFile2 = ::CreateFile(outputFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile2 != INVALID_HANDLE_VALUE)
	{
		DWORD dwWritten = 0;
		WriteFile(hFile2, fileData, dwFileZize, &dwWritten, NULL);
		CloseHandle(hFile2);
	}
	else
	{
		::MessageBox(NULL, "Cant write file", "Error", MB_OK);
	}

	delete[] fileData;

    return 0;
}

