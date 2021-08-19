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

#define NUM_REPLACE1	83

uint32_t in_replace1[NUM_REPLACE1] =
{
	0x202020, 0x484000, 0x282008, 0x383008,
	0x302808, 0x403800, 0x483800, 0x403000,
	0x403810, 0x484018, 0x403808, 0x181810,
	0x101008, 0x181818, 0x201008, 0x181808,
	0x181000, 0x202010, 0x281010, 0x202018,
	0x383000, 0x202008, 0x282010, 0x383010,
	0x282818, 0x303018, 0x302818, 0x201818,
	0x302800, 0x483808, 0x302810, 0x382800,
	0x101010, 0x202000, 0x181008, 0x282018,
	0x282000, 0x181800, 0x181010, 0x381810,
	0x301810, 0x402018, 0xD8A090, 0xD8A898, 
	0xD09880, 0xD08878, 0x301010, 0xD09080,
	0xD09078, 0x502018, 0x402010, 0xC07050,
	0xC87058, 0xC06850, 0x904030, 0x904830,
	0x603020, 0xC88068, 0xA85038, 0x281008,
	0xD08870, 0xC06040, 0x804028, 0x703828,
	0xC87858, 0xC87868, 0x984830, 0x482018,
	0xB05038, 0xA04830, 0xD08070, 0xD89888, 
	0x502818, 0xB85838, 0xB05838, 0xC06848,
	0x582810, 0x884028, 0x582818, 0x703820,
	0x783828, 0x683020, 0x803828,
};

uint32_t out_replace1[NUM_REPLACE1] =
{
	0x808080, 0xF8D800, 0xB89810, 0x988848,
	0x605840, 0xF0B800, 0xE0B808, 0xE0B810,
	0xF8D800, 0xE0B808, 0xD8A800, 0xE0B000,
	0x707070, 0x808080, 0x706008, 0x484840,
	0x706008, 0x605840, 0xB89810, 0xB89810,
	0xA88810, 0x989058, 0xC8A820, 0x807010,
	0x988848, 0x707060, 0x605840, 0x404040,
	0x706018, 0xA88810, 0x706018, 0xB09830,
	0xA88810, 0x807010, 0x886800, 0x886800,
	0x706008, 0xD8A800, 0x484008, 0x787878,
	0x787878, 0x787878, 0xF8D808, 0xF8D808,
	0xF8D000, 0xE0C040, 0x787878, 0xF8D010,
	0xF8D010, 0xB89810, 0x807010, 0xD8B020,
	0xD0A808, 0xF8D800, 0xA88820, 0xB89810,
	0x705810, 0xE0C040, 0xF8D800, 0xB89810,
	0xD0A808, 0xF8E000, 0xE8B800, 0xE0B808,
	0xB8A848, 0xB8A848, 0x584820, 0x705810,
	0xE8C018, 0x807010, 0xF8D800, 0xF8D808,
	0x705810, 0xF0C000, 0xF8D000, 0xA88810,
	0xD0A808, 0xF8D000, 0xD0A808, 0x787878,
	0xF0C818, 0xE0C040, 0xB8A848,
};

/////////////////////


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

uint8_t find_colour_index(uint32_t rgb, uint32_t *palette)
{
	for (int i = 0; i < 256; i++)
	{
		if ((rgb&0xFFFFFF) == (palette[i] & 0xFFFFFF))
		{
			return i;
		}
	}
	
	fprintf(stderr, "Couldn't find colour index.\n");
	return 0;
}

void replace_image1(uint32_t *palette, uint8_t *pixels, unsigned int width, unsigned int height)
{
	//int image_size = width*height;
	int count = 0;
	
	for (int i = width*24; i < (width*(24+14)); i++)
	{
		uint32_t rgb = palette[pixels[i]] & 0xFFFFFF;
		
		for (int j = 0; j < NUM_REPLACE1; j++)
		{
			if (rgb == in_replace1[j])
			{
				rgb = out_replace1[j];
				pixels[i] = find_colour_index(rgb, palette);
				count++;
				break;
			}
		}
	}
	
	printf("%d pixels replaced.\n", count);
}

void clear_image1(const char *file, const char *out)
{
	int file_size;
	uint8_t *buf;
	BMP_Header *hdr;
	
	buf = read_file(file, &file_size);
	if (!buf)
		return;
		
	hdr = (BMP_Header *)buf;
		
	if (file_size < sizeof(BMP_Header) || hdr->magic != BMP_MAGIC)	
	{
		fprintf(stderr, "Invalid bmp image.\n");
		return;
	}
	
	if (hdr->bpp != 8)
	{
		fprintf(stderr, "Not a 8 colours image.\n");
		return;
	}
	
	if (hdr->height < 0)
	{
		fprintf(stderr, "Top-down bmp files not supported.\n");
		return;
	}
	
	replace_image1((uint32_t *)(buf+0x36), buf+hdr->offset, hdr->width, hdr->height);
	
	FILE *f = fopen(out, "wb");
	if (!f)
	{
		fprintf(stderr, "Cannot open/creat %s\n", out);
		return;
	}
	
	fwrite(buf, 1, file_size, f);
	fclose(f);
}

int main()
{
	// SAVEP_00000028.bmp is the version with the hai/iie shadow cleared
	clear_image1("SAVEP_00000028.bmp", "nameinp_clear_auto.bmp");
	
	return 0;
}