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

void merge_images(uint8_t *pixels, uint8_t *pixels_other, int width, int height, int y)
{
	for (int i = width*y; i < (width*(y+height)); i++)
	{
		uint32_t rgb;
		uint8_t r, g, b;
		int j = i - (width*y);
		
		r = pixels_other[j*3+2];
		g = pixels_other[j*3+1];
		b = pixels_other[j*3];
		
		rgb = (r << 16) | (g << 8) | b;
		
		if (rgb == 0) // assume black = transparent
		{
			// Nothing, it is transparent
		}
		else
		{
			pixels[i*3+2] = r;
			pixels[i*3+1] = g;
			pixels[i*3] = b;
		}
	}
}

void do_merge_images(const char *base, const char *other, const char *out, int y)
{
	int file_size_base, file_size_other;
	uint8_t *buf_base, *buf_other;
	BMP_Header *hdr, *hdr2;
	
	buf_base = read_file(base, &file_size_base);
	if (!buf_base)
		return;
		
	hdr = (BMP_Header *)buf_base;
		
	if (file_size_base < sizeof(BMP_Header) || hdr->magic != BMP_MAGIC)	
	{
		fprintf(stderr, "Invalid bmp image.\n");
		return;
	}
	
	if (hdr->bpp != 24)
	{
		fprintf(stderr, "Not a 24 colours image.\n");
		return;
	}
	
	if (hdr->height < 0)
	{
		fprintf(stderr, "Top-down bmp files not supported.\n");
		return;
	}
	
	buf_other = read_file(other, &file_size_other);
	if (!buf_other)
		return;
		
	hdr2 = (BMP_Header *)buf_other;
		
	if (file_size_other < sizeof(BMP_Header) || hdr2->magic != BMP_MAGIC)	
	{
		fprintf(stderr, "Invalid bmp image.\n");
		return;
	}
	
	if (hdr2->bpp != 24)
	{
		fprintf(stderr, "Not a 24 colours image.\n");
		return;
	}
	
	if (hdr2->height < 0)
	{
		fprintf(stderr, "Top-down bmp files not supported.\n");
		return;
	}
	
	if (hdr->width != hdr2->width)
	{
		fprintf(stderr, "Both images should have same width.\n");
		return;
	}
	
	merge_images(buf_base+hdr->offset, buf_other+hdr2->offset, hdr2->width, hdr2->height, y);
	
	FILE *f = fopen(out, "wb");
	if (!f)
	{
		fprintf(stderr, "Cannot open/creat %s\n", out);
		return;
	}
	
	fwrite(buf_base, 1, file_size_base, f);
	fclose(f);
}

int main()
{
	do_merge_images("savep_00000028_clear_24.bmp", "shadow.bmp", "savep_00000028_24.bmp", 8);
	return 0;
}