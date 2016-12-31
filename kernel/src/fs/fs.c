#include "common.h"
#include <string.h>
#include <sys/ioctl.h>

typedef struct {
	char *name;
	uint32_t size;
	uint32_t disk_offset;
} file_info;

typedef struct {
	bool opened;
	uint32_t offset;
} Fstate;

enum {SEEK_SET, SEEK_CUR, SEEK_END};

/* This is the information about all files in disk. */
static const file_info file_table[] __attribute__((used)) = {
	{"1.rpg", 188864, 1048576}, {"2.rpg", 188864, 1237440},
	{"3.rpg", 188864, 1426304}, {"4.rpg", 188864, 1615168},
	{"5.rpg", 188864, 1804032}, {"abc.mkf", 1022564, 1992896},
	{"ball.mkf", 134704, 3015460}, {"data.mkf", 66418, 3150164},
	{"desc.dat", 16027, 3216582}, {"fbp.mkf", 1128064, 3232609},
	{"fire.mkf", 834728, 4360673}, {"f.mkf", 186966, 5195401},
	{"gop.mkf", 11530322, 5382367}, {"map.mkf", 1496578, 16912689},
	{"mgo.mkf", 1577442, 18409267}, {"m.msg", 188232, 19986709},
	{"mus.mkf", 331284, 20174941}, {"pat.mkf", 8488, 20506225},
	{"rgm.mkf", 453202, 20514713}, {"rng.mkf", 4546074, 20967915},
	{"sss.mkf", 557004, 25513989}, {"voc.mkf", 1997044, 26070993},
	{"wor16.asc", 5374, 28068037}, {"wor16.fon", 82306, 28073411},
	{"word.dat", 5650, 28155717},
};

static Fstate file_state[] __attribute__((used)) = {
	{false, 0}, {false, 0}, {false, 0}, {false, 0},
	{false, 0}, {false, 0}, {false, 0}, {false, 0},
	{false, 0}, {false, 0}, {false, 0}, {false, 0},
	{false, 0}, {false, 0}, {false, 0}, {false, 0},
	{false, 0}, {false, 0}, {false, 0}, {false, 0},
	{false, 0}, {false, 0}, {false, 0}, {false, 0},
	{false, 0},
};


#define NR_FILES (sizeof(file_table) / sizeof(file_table[0]))

int fs_ioctl(int fd, uint32_t request, void *p) {
	assert(request == TCGETS);
	return (fd >= 0 && fd <= 2 ? 0 : -1);
}

void ide_read(uint8_t *, uint32_t, uint32_t);
void ide_write(uint8_t *, uint32_t, uint32_t);
void serial_printc(char);

/* TODO: implement a simplified file system here. */


static Fstate files[NR_FILES+3];

int fs_open(const char* pathname,int flags);
int fs_read(int fd, void *buf, int len);
int fs_write(int fd, void *buf, int len);
int fs_lseek(int fd, int offset, int whence);
int fs_close(int fd);

int fs_open(const char *pathname,int flags){
	int i;
    for(i = 0; i < NR_FILES; i++){
		if(strcmp(pathname, file_table[i].name) == 0){
	    	files[i + 3].opened = true;
	    	files[i + 3].offset = 0;
	    	return i + 3;
		}
	}

    panic("fs_open shouldn't reach here, it means no match file");
	return -1;
}

int fs_read(int fd, void *buf, int len){
	assert(fd>=3 && fd<=NR_FILES+3);
	assert((files[fd].opened) && (files[fd].offset>=0));
	assert(buf && len);

	int ret = -1;
	int remain=file_table[fd-3].size - files[fd].offset;

	if(remain <= 0) return 0;
	else if(remain < len) ret=remain;
	else ret=len;

	ide_read(buf,file_table[fd-3].disk_offset+files[fd].offset,ret);
	files[fd].offset+=ret;

	return ret;
}

int fs_write(int fd, void *buf, int len) {
	assert(fd>=0 && fd<=NR_FILES+3);
	assert(buf && len);

	int ret=-1;
	if(fd==0){
		panic("fs_write receive fd==0");
	}
	else if((fd==1) || (fd==2)){
		ret=len;

		int i;
		for(i=0;i<ret;i++){
			serial_printc(*(char *)(buf+i));
		}
	}
	else{
		assert((files[fd].opened) && (files[fd].offset>=0));

		int remain=file_table[fd-3].size - files[fd].offset;

		if(remain <= 0) return 0;
		else if(remain < len) ret=remain;
		else ret=len;

		ide_write(buf,file_table[fd-3].disk_offset+files[fd].offset,ret);
		files[fd].offset+=ret;

	}
	return ret;

}

int fs_lseek(int fd, int offset, int whence){
	assert(fd>=3 && fd<=NR_FILES+3);
	assert((files[fd].opened) && (files[fd].offset>=0));

	int n_offset = -1;
	switch (whence) {
		case SEEK_SET: n_offset=offset;break;
		case SEEK_CUR: n_offset=files[fd].offset + offset;break;
		case SEEK_END: n_offset=file_table[fd-3].size+offset;break;
		default:assert(0);break;
	}

	if(n_offset>file_table[fd-3].size)
		n_offset=file_table[fd-3].size;

	files[fd].offset=n_offset;
	return n_offset;
}

int fs_close(int fd) {
	assert(fd >= 3 && fd<NR_FILES+3);
	files[fd].opened=false;
	return 0;
}
