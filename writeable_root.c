#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INFO:
// authenticated-root, SIP and FileVault must be disabled
// program will create new directory ~/temp
// program will require your password
// use with caution!
int main(int argc, char *argv[]) {
	FILE *fpipe;
	if ((fpipe = (FILE*)popen("mount", "r")) == 0) {
		perror("ERROR: failed to execute command");
		exit(EXIT_FAILURE);
	}
	char c;
	char disk[32];
	unsigned int i = 0;
	while (fread(&c, sizeof(char), 1, fpipe)) {
		if (c == ' ') {
			disk[i-2] = '\0';
			break;
		}
		disk[i] = c;
		i++;
	}
	pclose(fpipe);
	
	system("mkdir ~/temp");
	char mount[72] = "sudo mount -o nobrowse -t apfs ";
	strncat(mount, disk, 32);
	strncat(mount, " ~/temp", 8);
	system(mount);
	printf("make changes in the set directory and exit the shell when you're done\n");
	printf("WARNING: system will reboot on exit\n");
	system("cd ~/temp && sudo `echo $SHELL`");
	system("sudo bless --folder ~/temp/System/Library/CoreServices --bootefi --create-snapshot");
	system("sudo reboot");
	
	return EXIT_SUCCESS;
}
