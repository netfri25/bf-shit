#include <stdio.h>
#include <stdlib.h>

typedef enum {
	ADD,
	SUB,
	LEFT,
	RIGHT,
	BEGIN_LOOP,
	END_LOOP,
	READ,
	WRITE
} OP;

typedef struct {
	OP* data;
	size_t size;
} Program;

Program parse_file(FILE* ifile, size_t size) {
	Program program = {(OP*)malloc(size*sizeof(OP)),0};
	char c;
	while ((c = fgetc(ifile)) != (char)EOF) {
		switch (c) {
			break; case '+': program.data[program.size++] = ADD;
			break; case '-': program.data[program.size++] = SUB;
			break; case '<': program.data[program.size++] = LEFT;
			break; case '>': program.data[program.size++] = RIGHT;
			break; case '[': program.data[program.size++] = BEGIN_LOOP;
			break; case ']': program.data[program.size++] = END_LOOP;
			break; case ',': program.data[program.size++] = READ;
			break; case '.': program.data[program.size++] = WRITE;
			break; /* default: {
				fprintf(stderr,"Unknown character found: `%c`(%d)\n",
						c,(int)c);
				exit(1);
			} */
		}
	}
	return program;
}

void generate_code(Program program,FILE* ofile) {
	fprintf(ofile,"#include <stdio.h>\n#include <stdlib.h>\n");
	fprintf(ofile,"int main() {char* p=(char*)malloc(30000);");
	for (int i = 0; i < program.size; i++) {
		switch (program.data[i]) {
			break; case ADD:        fprintf(ofile,"(*p)++;");
			break; case SUB:        fprintf(ofile,"(*p)--;");
			break; case LEFT:       fprintf(ofile,"p--;");
			break; case RIGHT:		fprintf(ofile,"p++;");
			break; case BEGIN_LOOP: fprintf(ofile,"while(*p){");
			break; case END_LOOP:   fprintf(ofile,"}");
			break; case READ:       fprintf(ofile,"*p=getchar();");
			break; case WRITE:      fprintf(ofile,"putchar(*p);");
			break; default: {
				fprintf(stderr,"Unreachable\n");
				exit(1);
			}
		}
	}
	fprintf(ofile,"putchar(10);}\n"); return;
}

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr,"Input file was not provided.\n");
		exit(1);
	}
	
	if (argc < 2) {
		fprintf(stderr,"Output file was not provided.\n");
		exit(1);
	}

	const char* ipath = argv[2];
	FILE* ifile = fopen(ipath,"r");
	if (ifile == NULL) {
		fprintf(stderr,"Error while trying to read `%s`.\n",
				ipath);
		exit(1);
	}

	fseek(ifile, 0, SEEK_END);
	size_t ifilesize = ftell(ifile);
	rewind(ifile);
	if (ifilesize == 0) {
		fprintf(stderr, "Provided file is empty.\n");
		exit(1);
	}

	const char* opath = argv[1];
	FILE* ofile = fopen(opath,"w+");
	if (ofile == NULL) {
		fprintf(stderr,"Error while trying to open `%s`.\n", 
				opath);
		exit(1);
	}
	
	Program program = parse_file(ifile,ifilesize-1);
	generate_code(program,ofile);
	fclose(ifile);
	fclose(ofile);
	return 0;
}
