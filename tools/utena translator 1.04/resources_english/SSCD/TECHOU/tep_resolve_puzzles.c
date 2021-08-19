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

// Join four 8-bit images on the X axis
// It is assumed that all of them have same palette
void join_images4(uint8_t *image1, uint8_t *image2, uint8_t *image3, uint8_t *image4, uint32_t *palette, uint8_t *output_image, int width1, int width2, int width3, int width4, int height)
{
	int out_width = (width1+width2+width3+width4);
	int image_size =  out_width * height;
	
	for (int i = 0; i < image_size; i++)
	{
		int x = i % out_width;
		int y = i / out_width; // down-top y
		//uint32_t rgb;
		uint8_t idx;
		
		/*if (((y*out_width) + x) != i)
		{
			fprintf(stderr, "Mehhh\n");
		}*/
		
		if (x < width1)
		{
			int thisX = x;			
			idx = image1[(y*width1)+thisX];
		}
		else if (x < (width1+width2))
		{
			int thisX = (x-width1);			
			idx = image2[(y*width2)+thisX];
		}
		else if (x < (width1+width2+width3))
		{			
			int thisX = (x-width1-width2);			
			idx = image3[(y*width3)+thisX];
		}
		else
		{
			int thisX = (x-width1-width2-width3);			
			idx = image4[(y*width4)+thisX];
		}
		
		output_image[i] = idx;
	}
}

void do_join_images4(const char *image1, const char *image2, const char *image3, const char *image4, const char *output)
{
	int file_size1, file_size2, file_size3, file_size4;
	uint8_t *buf1, *buf2, *buf3, *buf4;
	BMP_Header *hdr1, *hdr2, *hdr3, *hdr4;
	
	uint8_t *output_buf;
	
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
	
	if (hdr1->ncolors != 0 && hdr1->ncolors != 0x100)
	{
		fprintf(stderr, "All colors of the palette must be stored (damn photoshop)\n");
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
	
	if (hdr2->ncolors != 0 && hdr2->ncolors != 0x100)
	{
		fprintf(stderr, "All colors of the palette must be stored (damn photoshop)\n");
		return;
	}
	
	buf3 = read_file(image3, &file_size3);
	if (!buf3)
		return;
		
	hdr3 = (BMP_Header *)buf3;
		
	if (file_size3 < sizeof(BMP_Header) || hdr3->magic != BMP_MAGIC)	
	{
		fprintf(stderr, "Invalid bmp image.\n");
		return;
	}
	
	if (hdr3->bpp != 8)
	{
		fprintf(stderr, "Not a 8 colours image.\n");
		return;
	}
	
	if (hdr3->height < 0)
	{
		fprintf(stderr, "Top-down bmp files not supported.\n");
		return;
	}
	
	if (hdr3->ncolors != 0 && hdr3->ncolors != 0x100)
	{
		fprintf(stderr, "All colors of the palette must be stored (damn photoshop)\n");
		return;
	}
	
	buf4 = read_file(image4, &file_size4);
	if (!buf4)
		return;
		
	hdr4 = (BMP_Header *)buf4;
		
	if (file_size4 < sizeof(BMP_Header) || hdr4->magic != BMP_MAGIC)	
	{
		fprintf(stderr, "Invalid bmp image.\n");
		return;
	}
	
	if (hdr4->bpp != 8)
	{
		fprintf(stderr, "Not a 8 colours image.\n");
		return;
	}
	
	if (hdr4->height < 0)
	{
		fprintf(stderr, "Top-down bmp files not supported.\n");
		return;
	}
	
	if (hdr4->ncolors != 0 && hdr4->ncolors != 0x100)
	{
		fprintf(stderr, "All colors of the palette must be stored (damn photoshop)\n");
		return;
	}
	
	if (hdr1->height != hdr2->height || hdr1->height != hdr3->height || hdr1->height != hdr4->height)
	{
		fprintf(stderr, "The four images should have same height.\n");
		return;
	}
	
	if (memcmp(buf1+0x36, buf2+0x36, 0x400) != 0 || memcmp(buf1+0x36, buf3+0x36, 0x400) != 0 || memcmp(buf1+0x36, buf4+0x36, 0x400) != 0)
	{
		fprintf(stderr, "The palette must be identical!.\n");
		return;
	}
	
	int output_size = (hdr1->width+hdr2->width+hdr3->width+hdr4->width) * hdr1->height;
	output_buf = malloc(output_size);
	
	join_images4(buf1+hdr1->offset, buf2+hdr2->offset, buf3+hdr3->offset, buf4+hdr4->offset, (uint32_t *)(buf1+0x36), output_buf, hdr1->width, hdr2->width, hdr3->width, hdr4->width, hdr1->height);
	
	FILE *f = fopen(output, "wb");
	if (!f)
	{
		fprintf(stderr, "Cannot open/creat %s\n", output);
		return;
	}
	
	BMP_Header out_hdr;
	
	memcpy(&out_hdr, hdr1, sizeof(BMP_Header));
	
	out_hdr.magic = BMP_MAGIC;
	out_hdr.file_size = 0x36 + 0x400 + output_size;
	out_hdr.width = (hdr1->width+hdr2->width+hdr3->width+hdr4->width);
	out_hdr.image_size = output_size;
		
	fwrite(&out_hdr, 1, 0x36, f);
	fwrite(buf1+0x36, 1, 0x400, f);
	fwrite(output_buf, 1, output_size, f);
	fclose(f);
}

void resolve_all_tep_puzzles(char *image_directory, char *output_directory)
{
	for (int i = 0; i <= 26; i++)
	{
		char ifile1[1024], ifile2[1024], ifile3[1024], ifile4[1024];
		char ofile[1024];
		
		snprintf(ifile1, sizeof(ifile1), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x3C);
		snprintf(ifile2, sizeof(ifile2), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x1C4C);
		snprintf(ifile3, sizeof(ifile3), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x385C);
		snprintf(ifile4, sizeof(ifile4), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x546c);
		snprintf(ofile, sizeof(ofile), "%s/tep%02d_image1_joined.bmp", output_directory, i);
		do_join_images4(ifile1, ifile2, ifile3, ifile4, ofile);
		
		snprintf(ifile1, sizeof(ifile1), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x707C);
		snprintf(ifile2, sizeof(ifile2), "%s/TEP%02d_%08X.bmp", image_directory, i, 0x8C8C);
		snprintf(ifile3, sizeof(ifile3), "%s/TEP%02d_%08X.bmp", image_directory, i, 0xA89C);
		snprintf(ifile4, sizeof(ifile4), "%s/TEP%02d_%08X.bmp", image_directory, i, 0xC4AC);
		snprintf(ofile, sizeof(ofile), "%s/tep%02d_image2_joined.bmp", output_directory, i);
		do_join_images4(ifile1, ifile2, ifile3, ifile4, ofile);
	}
}

int main()
{
	resolve_all_tep_puzzles("C:/msys/home/MUU/utena/utena_images/SSCD/TECHOU", ".");
	return 0;
}