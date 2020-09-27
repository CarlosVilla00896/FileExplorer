#include "stdafx.h"
#include "SystemDrives.h"

SystemDrives::SystemDrives()
{
	_numberOfDrive = 0;
}

SystemDrives::~SystemDrives()
{
	delete(driveLetter);
	delete(volumeName);
	delete(driveType);
}

void SystemDrives::getSystemDrives()
{
	TCHAR str[STRING_SIZE]; //el buffer que se llena
	long temp = GetLogicalDriveStrings(STRING_SIZE, str); //Llena un buffer con strings que especifican los drives validos del sistema
	int i = 0;
	while (!(str[i] == '\0' && str[i + 1] == '\0')) // cuento los drives que se almacenaron en el buffer
	{
		if (str[i] == '\0')
			_numberOfDrive++;
		i++;
	}
	_numberOfDrive++;
	driveLetter = new TCHAR*[_numberOfDrive]; //instancio arreglos para almacenar nombres, volumen y tipo del drive
	volumeName = new TCHAR*[_numberOfDrive];
	driveType = new TCHAR*[_numberOfDrive];
	icon = new int[_numberOfDrive];
	for (int i = 0; i < _numberOfDrive; i++) //inicializo cada posicion del arreglo segun el string_size
	{
		driveLetter[i] = new TCHAR[STRING_SIZE];
		volumeName[i] = new TCHAR[STRING_SIZE];
		driveType[i] = new TCHAR[STRING_SIZE];
	}
	
	int index = 0, k;
	for (int j = 0; j < _numberOfDrive; j++)	
	{
		k = 0;
		while (str[index] != 0)					
		{
			driveLetter[j][k++] = str[index++]; //asigno el string en esa posicion de mi buffer a driveLetter
		}
		driveLetter[j][k] = '\0';
		index++;
	}

	int nType;
	for (int i = 0; i < _numberOfDrive; ++i) //uso un ciclo para verificar que tipo de drive son cada uno 
	{
		StrCpy(str, L"");
		nType = GetDriveType(driveLetter[i]); //me devuelve el tipo del drive que tengo segun su letra
		switch (nType)
		{
		case DRIVE_FIXED:
			StrCpy(driveType[i], L"Local Disk");
			break;
		case DRIVE_REMOVABLE:
			StrCpy(driveType[i], L"Removable Drive");
			break;
		case DRIVE_REMOTE:
			StrCpy(driveType[i], L"Network Drive");
			break;
		default:
			break;
		}

		StrCpy(volumeName[i], str);
		
		if (!StrCmp(volumeName[i], L"DATA"))
			icon[i] = IDI_DATA;
		else if (!StrCmp(volumeName[i], L"OS"))
			icon[i] = IDI_OS;

		StrCat(volumeName[i], driveLetter[i]);
	}
}