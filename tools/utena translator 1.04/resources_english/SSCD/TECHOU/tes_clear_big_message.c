#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdint.h>

#  define __bswap_32(x) \
     (__extension__                                                           \
       ({ register unsigned int __v, __x = (x);                                \
          if (__builtin_constant_p (__x))                                      \
           __v = __bswap_constant_32 (__x);                                   \
          else                                                                 \
            __asm__ ("bswap %0" : "=r" (__v) : "0" (__x));                     \
          __v; }))

#define BMP_MAGIC 	0x4D42    // "BM" 
#define DC_MAGIC  	0x4344    // "DC"
#define PP_MAGIC  	0x5050	// "PP" 8 bits (256 col)
#define PP4_MAGIC	0x7070	// "pp" 4 bits (16 col)
#define MATO_MAGIC	0x6F74616D	// "mato"

#define COPY_BUF_SIZE	(16*1024*1024)

typedef struct 
{
	uint16_t magic; // 0
	uint32_t file_size; // 2
	uint16_t reserved1; // 6
	uint16_t reserved2; // 8
	uint32_t offset; // A
	uint32_t dib_hdr_size; // E
	uint32_t width; // 12
	int32_t height; // 16
	uint16_t bitplanes; // 1a
	uint16_t bpp; // 1c
	uint32_t compression; // 1e
	uint32_t image_size; // 22
	int32_t hres; // 26
	int32_t vres; // 2a
	uint32_t ncolors; // 2e
	uint32_t icolors; // 32
} __attribute__((packed)) BMP_Header; 

void *read_file(const char *file, int *psize)
{
	FILE *fd;
	int size;
	void *buf;
	
	fd = fopen(file, "rb");
	if (!fd)
	{
		fprintf(stderr, "Cannot open %s\n", file);
		return NULL;
	}
	
	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	
	buf = malloc(size);
	if (!buf)
	{
		fprintf(stderr, "Out of memory.\n");
		fclose(fd);
		return NULL;
	}
	
	if (fread(buf, 1, size, fd) != (size_t)size)
	{
		fprintf(stderr, "Error while reading %s\n", file);
		fclose(fd);
		return NULL;
	}
	
	fclose(fd);
	*psize = size;
	return buf;
}

uint32_t reds[] =
{
	0x803020, 0x803830, 0x884038,
	0x904030, 0x984038, 0x985850, 0x986860, 0x989898,
	0xA06060, 0xA07870, 0xA08078, 0xA08880, 0xA09088, 0xA0A0A0,
	0xB09888, 0xB0A8A0, 0xB0B0B0, 0xB8B8B8, 0xB8C8C0,
	0xC0C0C0, 0xC0A098, 0xC0B8B0, 0xC8C8C8,	
	0xD0D0D0,
};

#define N_REDS (sizeof(reds) / sizeof(uint32_t))

static uint8_t is_red(uint32_t rgb)
{	
	rgb = rgb & 0xFFFFFF;
	
	for (int i = 0; i < N_REDS; i++)
	{
		if (reds[i] == rgb)
			return 1;
	}
	
	return 0;
}

void clear_image(uint8_t *inout, uint8_t *input, uint32_t *palette, int width, int height)
{
	for (int i = 0; i < width*height; i++)
	{
		int x = i % width;
		int y = i / width;
		
		if (x >= 2 && x < (width-2) && y >= 2 && y < (height-2))
		{
			if (is_red(palette[inout[i]]) && !is_red(palette[input[i]]))
			{
				inout[i] = input[i];
			}
		}
	}
}

void do_clear_image(const char *image1, const char *image2, const char *output)
{
	int file_size1, file_size2;
	uint8_t *buf1, *buf2;
	BMP_Header *hdr1, *hdr2;
	
	buf1 = read_file(image1, &file_size1);
	if (!buf1)
		return;
		
	hdr1 = (BMP_Header *)buf1;
		
	if (file_size1 < sizeof(BMP_Header) || hdr1->magic != BMP_MAGIC)	
	{
		fprintf(stderr, "Invalid bmp image.\n");
		return;
	}
	
	if (hdr1->bpp != 8)
	{
		fprintf(stderr, "Not a 8 colours image.\n");
		return;
	}
	
	if (hdr1->height < 0)
	{
		fprintf(stderr, "Top-down bmp files not supported.\n");
		return;
	}
	
	buf2 = read_file(image2, &file_size2);
	if (!buf2)
		return;
		
	hdr2 = (BMP_Header *)buf2;
		
	if (file_size2 < sizeof(BMP_Header) || hdr2->magic != BMP_MAGIC)	
	{
		fprintf(stderr, "Invalid bmp image.\n");
		return;
	}
	
	if (hdr2->bpp != 8)
	{
		fprintf(stderr, "Not a 8 colours image.\n");
		return;
	}
	
	if (hdr2->height < 0)
	{
		fprintf(stderr, "Top-down bmp files not supported.\n");
		return;
	}
	
	if (hdr1->width != hdr2->width || hdr1->height != hdr2->height)
	{
		fprintf(stderr, "Both images should have same size.\n");
		return;
	}
	
	clear_image(buf1+hdr1->offset, buf2+hdr2->offset, (uint32_t *)(buf1+0x36), hdr1->width, hdr1->height);
	
	FILE *f = fopen(output, "wb");
	if (!f)
	{
		fprintf(stderr, "Cannot open/creat %s\n", output);
		return;
	}

	fwrite(buf1, 1, file_size1, f);
	fclose(f);
}

int main()
{
	do_clear_image("TES06_000304B8.bmp", "TES06_000336C8.bmp", "tes_big_message_clear_base.bmp");
	return 0;
}