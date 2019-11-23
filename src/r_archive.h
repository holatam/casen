#include <Rcpp.h>

#define class class_name
#define private private_ptr
#include <R_ext/Connections.h>
#undef class
#undef private

#if R_CONNECTIONS_VERSION != 1
#error "Missing or unsupported connection API in R"
#endif

#undef Realloc
// Also need to undefine the Free macro
#undef Free

#include <archive.h>
#include <archive_entry.h>

#undef TRUE
#undef FALSE
#include <R_ext/Boolean.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

#define R_EOF -1

#define FILTER_MAX 8

typedef struct {
  char* archive_filename;
  size_t archive_filename_size;
  int format;
  char* filename;
  size_t filename_size;
  char* buf;
  char* cur;
  archive* ar;
  archive_entry* entry;
  int last_response;
  int has_more;
  size_t limit;
  size_t size;
  int filters[FILTER_MAX];
} rchive;

size_t pop(void* target, size_t max, rchive* r);

size_t push(rchive* r);

#if ARCHIVE_VERSION_NUMBER < 3000004
int archive_write_add_filter(struct archive* a, int code);
#endif
