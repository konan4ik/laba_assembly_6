#include <iostream>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <winioctl.h>

#define wszDrive L"\\\\.\\PhysicalDrive0"

extern "C" {
	void my_read(char* x, unsigned char* y, int z);
	void my_write(char* x, const char* y, int z);
}

// получение размера в секторе диска с помощью DeviceIoControl
BOOL GetDriveGeometry(LPWSTR wszPath, DISK_GEOMETRY* pdg)
{
	HANDLE hDevice = INVALID_HANDLE_VALUE;  // handle to the drive to be examined 
	BOOL bResult = FALSE;                 // results flag
	DWORD junk = 0;                     // discard results

	hDevice = CreateFileW(wszPath,          // drive to open
		0,                // no access to the drive
		FILE_SHARE_READ | // share mode
		FILE_SHARE_WRITE,
		NULL,             // default security attributes
		OPEN_EXISTING,    // disposition
		0,                // file attributes
		NULL);            // do not copy file attributes

	if (hDevice == INVALID_HANDLE_VALUE)    // cannot open the drive
	{
		return (FALSE);
	}

	bResult = DeviceIoControl(hDevice,                       // device to be queried
		IOCTL_DISK_GET_DRIVE_GEOMETRY, // operation to perform
		NULL, 0,                       // no input buffer
		pdg, sizeof(*pdg),            // output buffer
		&junk,                         // # bytes returned
		(LPOVERLAPPED)NULL);          // synchronous I/O

	CloseHandle(hDevice);

	return (bResult);
}

int main()
{
	char diskname[51] = "\\\\.\\PhysicalDrive0";
	char filename[52] = "C:\\Users\\nikita\\Desktop\\laba_assembly_6\\lba0-1.txt";

	DISK_GEOMETRY pdg = { 0 }; 
	BOOL bResult = FALSE;      

	bResult = GetDriveGeometry((LPWSTR)wszDrive, &pdg);

	int s1 = 0;

	s1 = pdg.BytesPerSector;
	
	unsigned char x[1760 * 2] = " ";

	my_read(diskname, x, s1 * 2);
	std::string str;
	char buf[32];

	for (int i = 0; i < s1*2; i++) {
		if (i % 16 == 0) {
			sprintf_s(buf, sizeof(buf), "\n%04X: ", i);
			str += buf;
		}
		sprintf_s(buf, sizeof(buf), "%02X ", x[i]);
		str += buf;
	}

	const char* c_str_ptr = str.c_str();
	my_write(filename, c_str_ptr, str.size());

	my_read(filename, x, str.size());
	printf("%s", x);

}
