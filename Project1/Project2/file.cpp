#include <iostream>
#include <stdio.h>
extern "C" {
	void my_write(char* x, char* y);
	void my_read(char* x, char* y);
}
int main()
{
	char x[300] = " ";
	char filename[51] = "C:\\Users\\nikita\\Desktop\\laba_assembly_6\\8_1.txt";
	char content[15] = "new_content\n";

	my_read(filename, x);
	printf("before: %s", x);

	my_write(filename, content);

	my_read(filename, x);
	printf("after: %s", x);

}
