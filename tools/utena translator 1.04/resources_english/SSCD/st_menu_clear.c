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

#define NUM_REPLACE1	218

uint32_t in_replace1[NUM_REPLACE1] =
{
	0x98B8C8, 0xB8C8D0, 0x90A8C0, 0xD8E0E8,
	0x587890, 0xF8F8F8, 0xD0D8E0, 0xB0C0D0,
	0x7898B8, 0xE8F0F0,	0xC0D0D8, 0xC8D0D8,
	0xE8E8F0, 0xF0F0F8, 0xE0E0E8, 0xD0D8D8,
	0xB0C8D0, 0xD8D8E0, 0xA8B0C0, 0x98A8B8,
	0xE0E8F0, 0xE0E0E0, 0x607080, 0x586870,
	0x788898, 0x6888A8, 0x88A8B0, 0xA8B8C8,
	0x88A0B0, 0x90A0A8, 0xA0A8B0, 0xA0A8A8,
	0xB8C0C8, 0x082838, 0x304860, 0x001820,
	0x607888, 0xB0B8C0, 0x486068, 0x486070,
	0x204060, 0x103048, 0x183848, 0x183048,
	0x103040, 0x002840, 0x102028, 0x184058,
	0x708088, 0x305068,	0x102838, 0x184868,
	0x285070, 0x203848, 0x9098A0, 0x708090,
	0x909898, 0x081820, 0x081828, 0x90A8B0,
	0x384050, 0x102030, 0x8890A0, 0x808898,
	0xA0B0C0, 0xA0B0B8, 0xC0C8C8, 0xB8C0C0,
	0x687888, 0xD0D0D8, 0x082038, 0x102830,
	0xA8B0B0, 0x081020, 0x788890, 0x606878,
	0x102840, 0xB0B0B8, 0x082840, 0x082028,
	0x183850, 0x9098A8, 0x385060, 0x808088,
	0x485050, 0x707888, 0x80A0B8, 0x607078,
	0x808890, 0x082030, 0x606870, 0xC0C8D0,
	0x202838, 0x183038, 0x083048, 0xA8B8C0,
	0x182838, 0x204058, 0x98A8B0, 0x203040,
	0xB8C0D0, 0x385878,	0x184860, 0xC8D8E0,
	0x688898, 0x184060, 0x204860, 0x8098B0,
	0x184860, 0xA0B8C8, 0x304050, 0xA8C0D0,
	0x183040, 0x182840, 0x98B0C0, 0x405870,
	0x6890B0, 0x7098B0, 0x103848, 0x88A8B8,
	0x104058, 0x104060, 0x809098, 0x103858,
	0x184060, 0x103850, 0x204050, 0x183858,
	0x205070, 0x204868, 0x98B0C8, 0x185070,
	0x88A8C0, 0x7898B0, 0x203038, 0x284868,
	0x90B0C0, 0x203840, 0xA8B0B8, 0x284860,
	0xA0A8B8, 0x506878, 0x607890, 0x8898A0,
	0x486878, 0x506880, 0x182830, 0x507088,
	0x6088A8, 0x788088, 0xA0B8C0, 0x284050,
	0x586068, 0xB8C8D8, 0xA0A0A8, 0x90A8B8,
	0x406078, 0x90A0B0, 0x081018, 0x283848,
	0xC8C8D0, 0xC0C0C8, 0x284858, 0x485868,
	0xB0C0C8, 0xE0E8E8, 0x587888, 0x083850,
	0x7090A8, 0x688090, 0x607880, 0x506070,
	0x305870, 0x384858, 0xA8B8D0, 0xC0D0E0,
	0x7890A0, 0x586070, 0x8090A0, 0x203850,
	0x285060, 0x205068, 0x687880, 0x202830,
	0x001018, 0x587088, 0x88A0B8, 0x6888A0,
	0x001828, 0x485860, 0x506068, 0x707880,
	0x487090, 0x6890A8, 0x5888A0, 0xC8D0D0,
	0x485060, 0xC0C8D8, 0x083050, 0x002030,
	0x5880A0, 0x588098, 0x98A0B0, 0x8898A8,
	0x7088A0, 0x4880A0, 0x608098, 0x407088,
	0x587898, 0x285068, 0x285878, 0x205860,
	0x507890, 0x105070, 0x205860, 0x305878,
	0x4878A0, 0x507898,
};

uint32_t out_replace1[NUM_REPLACE1] =
{
	0x206088, 0x286088, 0x407098, 0x206088,
	0x286080, 0x286090,	0x306890, 0x286890,
	0x205888, 0x286090,	0x407090, 0x286090,
	0x286090, 0x306890, 0x286090, 0x306890,
	0x286890, 0x286088, 0x206088, 0x286090,
	0x286090, 0x306890, 0x206088, 0x286090,
	0x206088, 0x306890, 0x205888, 0x286088,
	0x205888, 0x206088, 0x286088, 0x306890,
	0x286088, 0x286090, 0x286088, 0x286090,
	0x286088, 0x286090, 0x286088, 0x206088,
	0x205078, 0x286088, 0x185880, 0x286090,
	0x206088, 0x286088, 0x206088, 0x286088,
	0x286088, 0x286090, 0x286088, 0x206088,
	0x206088, 0x285078, 0x286088, 0x286090,
	0x286088, 0x286090, 0x286088, 0x286088,
	0x306890, 0x185880, 0x206088, 0x286088,
	0x286088, 0x306890, 0x387090, 0x286088,
	0x306890, 0x387098, 0x205078, 0x105078,
	0x307098, 0x306890, 0x306890, 0x286088,
	0x205078, 0x307098, 0x286088, 0x286088,
	0x205078, 0x286090, 0x286090, 0x306890,
	0x286088, 0x307098, 0x4078A0, 0x205078,
	0x386888, 0x286088, 0x185880, 0x286090,
	0x286090, 0x205078, 0x105080, 0x206088,
	0x185880, 0x286088, 0x286088, 0x4078A0,
	0x306890, 0x307098, 0x085078, 0x306890,
	0x387090, 0x105080, 0x085078, 0x387098,
	0x307098, 0x387098, 0x105080, 0x4078A0,
	0x105080, 0x306890, 0x407090, 0x286088,
	0x286088, 0x4078A0, 0x085078, 0x407090,
	0x286088, 0x286088, 0x105080, 0x085078,
	0x306890, 0x185880, 0x286890, 0x407098,
	0x407098, 0x286090, 0x407098, 0x387098,
	0x387098, 0x205888, 0x306890, 0x185880,
	0x306890, 0x286088, 0x205078, 0x185078,
	0x306890, 0x286090, 0x185078, 0x306890,
	0x085078, 0x205878, 0x105078, 0x286088,
	0x286088, 0x206088, 0x487890, 0x185880,
	0x306890, 0x206088, 0x4078A0, 0x286088,
	0x185880, 0x286090, 0x386888, 0x306898,
	0x206088, 0x286090, 0x286090, 0x205078,
	0x306890, 0x407090, 0x185880, 0x306890,
	0x407090, 0x085078, 0x105080, 0x185880,
	0x205078, 0x185880, 0x205888, 0x185880,
	0x205078, 0x105080, 0x306890, 0x387098,
	0x185880, 0x286080, 0x286090, 0x306890,
	0x286088, 0x286080, 0x306890, 0x286090,
	0x105080, 0x286090, 0x286090, 0x306890,
	0x4078A0, 0x306890, 0x185880, 0x286090,
	0x286088, 0x286090, 0x387098, 0x205078,
	0x185880, 0x105078, 0x306890, 0x306890,
	0x306890, 0x085078, 0x205880, 0x387098,
	0x286890, 0x286088, 0x306890, 0x306890,
	0x387098, 0x105080, 0x306890, 0x286088,
	0x206088, 0x286080,
};

/////////////////////

#define NUM_REPLACE2	30

uint32_t in_replace2[NUM_REPLACE2] =
{
	0x001060, 0x000870, 0x000868, 0x000078,
	0x081858, 0x001850, 0x081850, 0x001068,
	0x102050, 0x081060, 0x082058, 0x000070,
	0x102858, 0x081860, 0x081068, 0x082050,
	0x102058, 0x082048, 0x081868, 0x102060,
	0x001058, 0x000878, 0x082060, 0x081070,
	0x102850, 0x182858, 0x002050, 0x002048,
	0x082850, 0x182850, 
};

uint32_t out_replace2[NUM_REPLACE2] =
{
	0x082840, 0x183048, 0x103048, 0x103040,
	0x082840, 0x103040, 0x103040, 0x103040,
	0x082840, 0x103040, 0x183048, 0x102840,
	0x082840, 0x183048, 0x102840, 0x082840,
	0x102848, 0x183048, 0x183848, 0x102840,
	0x103040, 0x183048, 0x103048, 0x183048,
	0x082840, 0x102840, 0x183048, 0x002838,
	0x082840, 0x103040,
};



////////////////////////

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

void replace_image1(uint8_t *pixels, unsigned int width, unsigned int height)
{
	int image_size = width*height;
	int count = 0;
	
	for (int i = width*4; i < (image_size - width*4); i++)
	{
		uint8_t r, g, b;
		uint32_t rgb;
		
		int row = i % width;
		
		if (row >= (width-2) || row <= 2)	
			continue;
		
		r = pixels[i*3+2];
		g = pixels[i*3+1];
		b = pixels[i*3];
		
		rgb = (r << 16) | (g << 8) | b;
		
		for (int j = 0; j < NUM_REPLACE1; j++)
		{
			if (rgb == in_replace1[j])
			{
				rgb = out_replace1[j];
				r = rgb >> 16;
				g = (rgb & 0xFF00) >> 8;
				b = rgb & 0xFF;
				
				pixels[i*3+2] = r;
				pixels[i*3+1] = g;
				pixels[i*3] = b;
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
	
	replace_image1(buf+hdr->offset, hdr->width, hdr->height);
	
	FILE *f = fopen(out, "wb");
	if (!f)
	{
		fprintf(stderr, "Cannot open/creat %s\n", out);
		return;
	}
	
	fwrite(buf, 1, file_size, f);
	fclose(f);
}

void replace_image2(uint8_t *pixels, unsigned int width, unsigned int height)
{
	int image_size = width*height;
	int count = 0;
	
	for (int i = width*4; i < (image_size - width*4); i++)
	{
		uint8_t r, g, b;
		uint32_t rgb;
		
		int row = i % width;
		
		if (row >= (width-2) || row <= 2)	
			continue;
		
		r = pixels[i*3+2];
		g = pixels[i*3+1];
		b = pixels[i*3];
		
		rgb = (r << 16) | (g << 8) | b;
		
		for (int j = 0; j < NUM_REPLACE2; j++)
		{
			if (rgb == in_replace2[j])
			{
				rgb = out_replace2[j];
				r = rgb >> 16;
				g = (rgb & 0xFF00) >> 8;
				b = rgb & 0xFF;
				
				pixels[i*3+2] = r;
				pixels[i*3+1] = g;
				pixels[i*3] = b;
				count++;
				break;
			}
		}
	}
	
	printf("%d pixels replaced.\n", count);
}

void clear_image2(const char *file, const char *out)
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
	
	replace_image2(buf+hdr->offset, hdr->width, hdr->height);
	
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
	//clear_image1("ST_MENU_0000AFB4.BMP", "clear1.bmp"); // This one needs a bit of hand-editing after automatic clear
	clear_image2("ST_MENU_0001A524.bmp", "clear2.bmp");
	return 0;
}