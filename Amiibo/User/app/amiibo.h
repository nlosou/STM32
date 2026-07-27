#ifndef AMIIBO_H_
#define AMIIBO_H_


#include "NTAG21x.h"

typedef struct {
   NTAG21x_t *card_info;
}Amiibo_ctx_t;

#endif
