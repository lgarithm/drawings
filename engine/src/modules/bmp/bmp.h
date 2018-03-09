/*
 * Author: lgarithm@gmail.com
 * bmp head
 */

#pragma once

#include <cstdio>

/* 2 bytes */
struct bmp_magic {
    unsigned char magic[2]; /* "BM" */
};

/* 3 * 4 = 12 bytes */
struct bmp_header {
    unsigned file_size;       // file size in Byte, w * h * 3 + 54D
    unsigned short _creater1; // 0
    unsigned short _creater2; // 0
    unsigned offset;          // offset to image data: 54D, 36H
};

/* 10 * 4 = 40 bytes */
struct bmp_info {
    unsigned header_size;   // info size in bytes, equals 40D, or 28H
    unsigned width;         // width in pixel
    unsigned height;        // height in pixel
    unsigned short nplanes; // number of color planes, 1
    unsigned short bitspp;  // bits per pixel, 24D, 18H
    unsigned compress_type; // compress type, default 0, (0-no, 1-, 2-, 3-)
    unsigned image_size;    // image size in Byte, w * h * 3
    unsigned hres;          // pixels per meter, 0
    unsigned vres;          // pixels per meter, 0
    unsigned ncolors;       // number of colors, 0
    unsigned nimpcolors;    // important colors, 0
};

/* 2 + 12 + 40 = 54 bytes */
struct bmp_head {
    bmp_magic magic;
    bmp_header header;
    bmp_info info;

    /* create a bmp head of an image which is
       w wide and h height */
    void init(unsigned width, unsigned height);

    /* write bmp head into binary stream */
    void write(FILE *) const;
};

void write_bmp_chunk(FILE *, const unsigned char *, int, int = 1);
void write_bmp_file(const bmp_head &, const unsigned char *, const char *);
void stream_bmp(const bmp_head &, const unsigned char *, int);
