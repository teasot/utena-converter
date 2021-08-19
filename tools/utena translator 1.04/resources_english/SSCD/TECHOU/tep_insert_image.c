#include <stdio.h>
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

void insert_image(uint8_t *image, uint8_t *input, uint32_t *palette, int width, int height, int insert_x, int insert_y, int insert_width, int insert_height)
{
	int image_size = width*height;
	int j = 0;
	
	for (int i = 0; i < image_size; i++)
	{
		int x, y;
		
		x = i % width;
		y = height - 1 - (i / width); // top-down y
		
		if (x >= insert_x && x < (insert_x+insert_width) && y >= insert_y && y < (insert_y+insert_height))
		{
			image[i] = input[j++];			
		}
	}
}

void do_insert_image(const char *inout, const char *input, int x, int y)
{
	int file_size_inout, file_size_in;
	uint8_t *buf_inout, *buf_in;
	BMP_Header *hdr_inout, *hdr_in;
	
	buf_inout = read_file(inout, &file_size_inout);
	if (!buf_inout)
		return;
		
	hdr_inout = (BMP_Header *)buf_inout;
		
	if (file_size_inout < sizeof(BMP_Header) || hdr_inout->magic != BMP_MAGIC)	
	{
		fprintf(stderr, "Invalid bmp image.\n");
		return;
	}
	
	if (hdr_inout->bpp != 8)
	{
		fprintf(stderr, "Not a 8 colours image.\n");
		return;
	}
	
	if (hdr_inout->height < 0)
	{
		fprintf(stderr, "Top-down bmp files not supported.\n");
		return;
	}
	
	if (hdr_inout->ncolors != 0 && hdr_inout->ncolors != 0x100)
	{
		fprintf(stderr, "All colors of the palette must be stored (damn photoshop)\n");
		return;
	}	
	
	buf_in = read_file(input, &file_size_in);
	if (!buf_in)
		return;
		
	hdr_in = (BMP_Header *)buf_in;
		
	if (file_size_in < sizeof(BMP_Header) || hdr_in->magic != BMP_MAGIC)	
	{
		fprintf(stderr, "Invalid bmp image.\n");
		return;
	}
	
	if (hdr_in->bpp != 8)
	{
		fprintf(stderr, "Not a 8 colours image.\n");
		return;
	}
	
	if (hdr_in->height < 0)
	{
		fprintf(stderr, "Top-down bmp files not supported.\n");
		return;
	}
	
	if (hdr_in->ncolors != 0 && hdr_in->ncolors != 0x100)
	{
		fprintf(stderr, "All colors of the palette must be stored (damn photoshop)\n");
		return;
	}	
	
	insert_image(buf_inout+hdr_inout->offset, buf_in+hdr_in->offset, (uint32_t *)(buf_inout+0x36), hdr_inout->width, hdr_inout->height, x, y, hdr_in->width, hdr_in->height);
	
	FILE *f = fopen(inout, "rb+");
	if (!f)
	{
		fprintf(stderr, "Cannot open %s\n", inout);
		return;
	}
	
	fseek(f, 0x436, SEEK_SET);
	fwrite(buf_inout+hdr_inout->offset, 1, hdr_inout->width*hdr_inout->height, f);
	fclose(f);
}

int main()
{
	do_insert_image("tep06_image1_joined.bmp", "tes06_00000E48_shadow.bmp", 8, 28);
	do_insert_image("tep06_image1_joined.bmp", "tes06_000027C8_shadow.bmp", 8, 84);
	return 0;
}