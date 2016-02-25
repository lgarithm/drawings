#include "bmp.h"

#include <cassert>

int _pad(int w)
{
  int row = w * 3;
  int pad = 0;
  for (; (pad + row) % 4; ++pad);
  return pad;
}

void bmp_head::init(unsigned width, unsigned height)
{
  magic.magic[0] = 'B';
  magic.magic[1] = 'M';

  info.header_size = 40;
  info.width = width;
  info.height = height;
  info.nplanes = 1;
  info.bitspp = 3 * 8;
  info.compress_type = 0;
  info.image_size = (_pad(width) + width * 3) * height;
  info.hres = 0;
  info.vres = 0;
  info.ncolors = 0;
  info.nimpcolors = 0;

  header._creater1 = 0;
  header._creater2 = 0;
  header.offset = 54;
  header.file_size = info.image_size + header.offset;
}

void bmp_head::write(FILE* fp) const
{
  fwrite(&magic, 1, 2, fp);
  fwrite(&header, 4, 3, fp);
  fwrite(&info, 4, 10, fp);
}

void write_bmp_file(const bmp_head& head,
                    const unsigned char* buffer,
                    const char* filename)
{
  FILE* fp = fopen(filename, "wb");
  head.write(fp);
  unsigned char zeros[4] = {0, 0, 0, 0};
  int pad = _pad(head.info.width);
  for (int i=0; i < head.info.height; ++i) {
    fwrite(buffer, 3, head.info.width, fp);
    fwrite(zeros, pad, 1, fp);
    buffer += head.info.width * 3;
  }
  size_t t = ftell(fp);
  assert(head.header.file_size == t);
  fclose(fp);
}
