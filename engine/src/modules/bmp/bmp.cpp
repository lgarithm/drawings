#include "bmp.h"

#include <cassert>
#include <cstdio>

#include <unistd.h>

namespace {
  static const unsigned char zeros[4] = {0, 0, 0, 0};
}  // namespace

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

void write_bmp_chunk(FILE* fp, const unsigned char* buffer, int w, int n)
{
  const int pad = _pad(w);
  for (int i=0; i < n; ++i) {
    fwrite(buffer, 3, w, fp);
    fwrite(zeros, pad, 1, fp);
    buffer += w * 3;
  }
}

void write_bmp_file(const bmp_head& head,
                    const unsigned char* buffer,
                    const char* filename)
{
  FILE* fp = fopen(filename, "wb");
  head.write(fp);
  write_bmp_chunk(fp, buffer, head.info.width, head.info.height);
  size_t t = ftell(fp);
  assert(head.header.file_size == t);
  fclose(fp);
}

#define UNCHECK(expr) ({auto _ = expr;})

void stream_bmp(const bmp_head& head, const unsigned char* buffer, int fd)
{
  UNCHECK(write(fd, &head.magic, 2));
  UNCHECK(write(fd, &head.header, 12));
  UNCHECK(write(fd, &head.info, 40));

  const int dl = 3 * head.info.width;
  const int pad = _pad(head.info.width);
  for (int i=0; i < head.info.height; ++i) {
    UNCHECK(write(fd, buffer, dl));
    UNCHECK(write(fd, zeros, pad));
    buffer += dl;
  }
}
