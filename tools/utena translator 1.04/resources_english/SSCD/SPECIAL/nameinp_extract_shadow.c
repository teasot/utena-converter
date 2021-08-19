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

void extract_shadow(uint8_t *base, uint8_t *yes_no_flat, uint8_t *shadow, uint8_t *yes_no_out, int width, int height, int y)
{
	for (int i = width*y; i < (width*(y+height)); i++)
	{
		uint32_t rgb_flat;
		uint8_t rf, gf, bf, rb, gb, bb;
		int j = i - (width*y);
				
		rf = yes_no_flat[j*3+2];
		gf = yes_no_flat[j*3+1];
		bf = yes_no_flat[j*3];		
		rgb_flat = (rf << 16) | (gf << 8) | bf;
		
		rb = base[i*3+2];
		gb = base[i*3+1];
		bb = base[i*3];		
		
		if (rgb_flat == 0) // assume black = transparent
		{
			shadow[j*3+2] = rb;
			shadow[j*3+1] = gb;
			shadow[j*3] = bb;
		}
		else
		{
			yes_no_out[j*3+2] = rb;
			yes_no_out[j*3+1] = gb;
			yes_no_out[j*3] = bb;
		}
	}	
}

void unify_slash(uint8_t *yn_in, uint8_t *yn_inout, int width, int height, int y, int x, int len)
{
	for (int i = y*width; i < (width*(y+height)); i++)
	{
		int j = i - (width*y);
		int thisX = i % width;
		
		if (thisX >= x && thisX < (x+len))
		{
			memcpy(yn_inout+j*3, yn_in+i*3, 3);
		}
	}
}

void do_extract_shadow(const char *base, const char *yn, const char *shadow, const char *yn_out, int y)
{
	int file_size_base, file_size_yn;
	uint8_t *buf_base, *buf_yn;
	BMP_Header *hdr, *hdr2;
	
	uint8_t *buf_shadow, *buf_yn_out;
	
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
	
	buf_yn = read_file(yn, &file_size_yn);
	if (!buf_yn)
		return;
		
	hdr2 = (BMP_Header *)buf_yn;
		
	if (file_size_yn < sizeof(BMP_Header) || hdr2->magic != BMP_MAGIC)	
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
	
	buf_shadow = malloc(hdr2->width*hdr2->height*3);
	memset(buf_shadow, 0, hdr2->width*hdr2->height*3);
	
	buf_yn_out = malloc(hdr2->width*hdr2->height*3);
	memset(buf_yn_out, 0, hdr2->width*hdr2->height*3);
	
	extract_shadow(buf_base+hdr->offset, buf_yn+hdr2->offset, buf_shadow, buf_yn_out, hdr2->width, hdr2->height, y);
	
	FILE *f;
	
	f = fopen(shadow, "wb");
	if (!f)
	{
		fprintf(stderr, "Cannot open/create %s\n", shadow);
		return;
	}
	
	fwrite(buf_yn, 1, 0x36, f);
	fwrite(buf_shadow, 1, hdr2->width*hdr2->height*3, f);
	fclose(f);
	
	f = fopen(yn_out, "wb");
	if (!f)
	{
		fprintf(stderr, "Cannot open/create %s\n", yn_out);
		return;
	}
	
	fwrite(buf_yn, 1, 0x36, f);
	fwrite(buf_yn_out, 1, hdr2->width*hdr2->height*3, f);
	fclose(f);
}

void do_unify_slash(const char *in, const char *inout, int y, int x, int len)
{
	int file_size_in, file_size_inout;
	uint8_t *buf_in, *buf_inout;
	BMP_Header *hdr, *hdr2;
	
	buf_in = read_file(in, &file_size_in);
	if (!buf_in)
		return;
		
	hdr = (BMP_Header *)buf_in;
		
	if (file_size_in < sizeof(BMP_Header) || hdr->magic != BMP_MAGIC)	
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
	
	buf_inout = read_file(inout, &file_size_inout);
	if (!buf_inout)
		return;
		
	hdr2 = (BMP_Header *)buf_inout;
		
	if (file_size_inout < sizeof(BMP_Header) || hdr2->magic != BMP_MAGIC)	
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
		fprintf(stderr, "Both images should have same width and height.\n");
		return;
	}
	
	unify_slash(buf_in+hdr->offset, buf_inout+hdr2->offset, hdr2->width, hdr2->height, y, x, len);
	
	FILE *f;
	
	f = fopen(inout, "wb");
	if (!f)
	{
		fprintf(stderr, "Cannot open/create %s\n", inout);
		return;
	}
	
	fwrite(buf_inout, 1, file_size_inout, f);
	fclose(f);
}

int main()
{
	do_extract_shadow("nameinp_temp_shadow.bmp", "yn_flat.bmp", "shadow.bmp", "yn_out.bmp", 8);
	do_extract_shadow("nameinp_temp_shadow2.bmp", "yn_flat2.bmp", "shadow2.bmp", "yn_out2.bmp", 8);
	do_unify_slash("nameinp_temp_shadow.bmp", "yn_out2.bmp", 8, 30, 9);
	
	return 0;
}