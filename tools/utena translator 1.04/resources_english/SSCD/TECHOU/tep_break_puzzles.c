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

void extract_image(uint8_t *image, uint8_t *output, uint32_t *palette, int width, int height, int extract_x, int extract_y, int extract_width, int extract_height)
{
	int image_size = width*height;
	int j = 0;
	
	for (int i = 0; i < image_size; i++)
	{
		int x, y;
		
		x = i % width;
		y = height - 1 - (i / width); // top-down y
		
		if (x >= extract_x && x < (extract_x+extract_width) && y >= extract_y && y < (extract_y+extract_height))
		{
			output[j++] = image[i];			
		}
	}
}

void do_extract_image(const char *image, const char *output, int x, int y, int width, int height)
{
	int file_size;
	uint8_t *buf;
	BMP_Header *hdr;
	
	uint8_t *output_buf;
	
	buf = read_file(image, &file_size);
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
	
	if (hdr->ncolors != 0 && hdr->ncolors != 0x100)
	{
		fprintf(stderr, "All colors of the palette must be stored (damn photoshop)\n");
		return;
	}	
	
	int output_size = width * height;
	output_buf = malloc(output_size);
	
	extract_image(buf+hdr->offset, output_buf, (uint32_t *)(buf+0x36), hdr->width, hdr->height, x, y, width, height);
	
	FILE *f = fopen(output, "wb");
	if (!f)
	{
		fprintf(stderr, "Cannot open/creat %s\n", output);
		return;
	}
	
	BMP_Header out_hdr;
	
	memcpy(&out_hdr, hdr, sizeof(BMP_Header));
	
	out_hdr.magic = BMP_MAGIC;
	out_hdr.file_size = 0x36 + 0x400 + output_size;
	out_hdr.width = width;
	out_hdr.height = height;
	out_hdr.image_size = output_size;
		
	fwrite(&out_hdr, 1, 0x36, f);
	fwrite(buf+0x36, 1, 0x400, f);
	fwrite(output_buf, 1, output_size, f);
	fclose(f);
}

void break_all_tep_puzzles(char *image_directory, char *input_directory)
{
	for (int i = 0; i <= 26; i++)
	{
		char ifile[1024];
		char ofile1[1024], ofile2[1024], ofile3[1024], ofile4[1024];
				
		snprintf(ifile, sizeof(ifile), "%s/tep%02d_image1_joined.bmp", input_directory, i);
		snprintf(ofile1, sizeof(ofile1), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x3C);
		snprintf(ofile2, sizeof(ofile2), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x1C4C);
		snprintf(ofile3, sizeof(ofile3), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x385C);
		snprintf(ofile4, sizeof(ofile4), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x546c);		
		
		do_extract_image(ifile, ofile1, 0, 0, 32, 208);
		do_extract_image(ifile, ofile2, 32, 0, 32, 208);
		do_extract_image(ifile, ofile3, 64, 0, 32, 208);
		do_extract_image(ifile, ofile4, 96, 0, 32, 208);
		
		snprintf(ifile, sizeof(ifile), "%s/tep%02d_image2_joined.bmp", input_directory, i);
		snprintf(ofile1, sizeof(ofile1), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x707C);
		snprintf(ofile2, sizeof(ofile2), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x8C8C);
		snprintf(ofile3, sizeof(ofile3), "%s/TEP%02d_%08X.bmp", image_directory, i, 0xA89C);
		snprintf(ofile4, sizeof(ofile4), "%s/TEP%02d_%08X.bmp", image_directory, i, 0xC4AC);		
		
		do_extract_image(ifile, ofile1, 0, 0, 32, 208);
		do_extract_image(ifile, ofile2, 32, 0, 32, 208);
		do_extract_image(ifile, ofile3, 64, 0, 32, 208);
		do_extract_image(ifile, ofile4, 96, 0, 32, 208);
	}
}

int main()
{
	break_all_tep_puzzles(".", ".");
	return 0;
}