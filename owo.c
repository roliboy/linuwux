#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

//TODO: rules to ignore '%l' and similar things
//TODO: ignore binary data on write

//stolen from stackoverflow
//blame the paramagnetic croissant if something goes wrong
void strreplace(char *target, const char *needle, const char *replacement) {
    char buffer[strlen(target) + 8];
    buffer[0] = 0;
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);

    while (1) {
        const char *p = strstr(tmp, needle);

        // walked past last occurrence of needle; copy remaining part
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }

        // copy part before needle
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;

        // copy replacement string
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;

        // adjust pointers, move on
        tmp = p + needle_len;
    }

    // write altered string back to target
    strcpy(target, buffer);
}

//TODO: capitalization
void owoify(char* owo, const char* uwu) {
    strcpy(owo, uwu);
    strreplace(owo, "r", "w");
    strreplace(owo, "R", "W");
    strreplace(owo, "l", "w");
    strreplace(owo, "L", "W");
    strreplace(owo, "?", "OwO");
    strreplace(owo, "!", "UwU");
    strreplace(owo, "na", "nya");
    strreplace(owo, "ne", "nye");
    strreplace(owo, "ni", "nyi");
    strreplace(owo, "no", "nyo");
    strreplace(owo, "nu", "nyu");
    strreplace(owo, "ma", "mya");
    strreplace(owo, "me", "mye");
    strreplace(owo, "mi", "myi");
    strreplace(owo, "mo", "myo");
    strreplace(owo, "mu", "myu");
    strreplace(owo, "ove", "uv");
    strreplace(owo, "th", "ff");
    strreplace(owo, "not", "nowt");
    strreplace(owo, " you ", " uwu ");
    strreplace(owo, "are", "awe");
}

ssize_t write (int filedes, const void *buffer, size_t size) {
    ssize_t (*libc_write)(int filedes, const void *buffer, size_t size) = dlsym(RTLD_NEXT, "write");
    char owo_buffer[2 * strlen(buffer)];
    owoify(owo_buffer, buffer);
    libc_write(filedes, owo_buffer, strlen(owo_buffer));
    return size;
}

int puts(const char *s) {
    int (*libc_puts)(const char *s) = dlsym(RTLD_NEXT, "puts");
    char owo_s[2 * strlen(s)];
    owoify(owo_s, s);
    libc_puts(owo_s);
    return strlen(s);
}

int printf(const char *template, ...) {
    int (*libc_vprintf)(const char *template, va_list ap) = dlsym(RTLD_NEXT, "vprintf");
    va_list ap;
    va_start(ap, template);
    //TODO: check argument sizes
    char owo_template[2 * strlen(template)];
    owoify(owo_template, template);
    int printed = libc_vprintf(owo_template, ap);
    va_end (ap);
    return printed;
}

int fputs(const char *s, FILE *stream) {
    int (*libc_fputs)(const char *s, FILE *stream) = dlsym(RTLD_NEXT, "fputs");
    char owo_s[2 * strlen(s)];
    owoify(owo_s, s);
    libc_fputs(owo_s, stream);
    return strlen(s);
}

int fprintf(FILE *stream, const char *template, ...) {
    int (*libc_vfprintf)(FILE *stream, const char *template, va_list ap) = dlsym(RTLD_NEXT, "vfprintf");
    va_list ap;
    va_start(ap, template);
    //TODO: check argument sizes
    char owo_template[2 * strlen(template)];
    owoify(owo_template, template);
//    int printed = libc_vfprintf(stream, owo_template, ap);
    int printed = libc_vfprintf(stream, template, ap);
    va_end(ap);
    return printed;
}

size_t fwrite(const void *data, size_t size, size_t count, FILE *stream) {
    ssize_t (*libc_fwrite)(const void *data, size_t size, size_t count, FILE *stream) = dlsym(RTLD_NEXT, "fwrite");

    //TODO: this
    /*char owo_buffer[2 * strlen(data)];
    owoify(owo_buffer, data);

    owo_buffer[0] = 'O';
    owo_buffer[1] = 'w';
    owo_buffer[2] = 'O';*/


    libc_fwrite(data, size, count, stream);
    return count;
}


//	asprintf:	 	Dynamic Output
//	fprintf:	 	Formatted Output Functions
//	fputc:	 	Simple Output
//	fputc_unlocked:	 	Simple Output
//	fputs:	 	Simple Output
//	fputs_unlocked:	 	Simple Output
//	fputwc:	 	Simple Output
//	fputwc_unlocked:	 	Simple Output
//	fputws:	 	Simple Output
//	fputws_unlocked:	 	Simple Output
//	fread:	 	Block Input/Output
//	fread_unlocked:	 	Block Input/Output
//	fwprintf:	 	Formatted Output Functions
//	fwrite:	 	Block Input/Output
//	fwrite_unlocked:	 	Block Input/Output
//	obstack_object_size:	 	Status of an Obstack
//	obstack_printf:	 	Dynamic Output
//	obstack_vprintf:	 	Variable Arguments Output
//	printf:	 	Formatted Output Functions
//	putc:	 	Simple Output
//	putchar:	 	Simple Output
//	putchar_unlocked:	 	Simple Output
//	putc_unlocked:	 	Simple Output
//	puts:	 	Simple Output
//	putw:	 	Simple Output
//	putwc:	 	Simple Output
//	putwchar:	 	Simple Output
//	putwchar_unlocked:	 	Simple Output
//	putwc_unlocked:	 	Simple Output
//	snprintf:	 	Formatted Output Functions
//	sprintf:	 	Formatted Output Functions
//	swprintf:	 	Formatted Output Functions
//	vasprintf:	 	Variable Arguments Output
//	vfprintf:	 	Variable Arguments Output
//	vfwprintf:	 	Variable Arguments Output
//	vprintf:	 	Variable Arguments Output
//	vsnprintf:	 	Variable Arguments Output
//	vsprintf:	 	Variable Arguments Output
//	vswprintf:	 	Variable Arguments Output
//	vwprintf:	 	Variable Arguments Output
//	wprintf:	 	Formatted Output Functions
//
//	aio_write:	 	Asynchronous Reads/Writes
//	aio_write64:	 	Asynchronous Reads/Writes
//  lio_listio:	 	Asynchronous Reads/Writes
//	lio_listio64:	 	Asynchronous Reads/Writes
//	pwrite:	 	I/O Primitives
//	pwrite64:	 	I/O Primitives
//	pwritev:	 	Scatter-Gather
//	pwritev2:	 	Scatter-Gather
//	pwritev64:	 	Scatter-Gather
//	pwritev64v2:	 	Scatter-Gather
//	write:	 	I/O Primitives
//	writev:	 	Scatter-Gather
//
