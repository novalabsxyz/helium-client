#include "helium_atom_api.h"
#include "helium_atom_api_info.h"
#include "crucible_interface.h"

size_t const schema_length_word_size = 2;
size_t const schema_tag_size = 2;
size_t const schema_max_size = 271;
size_t const schema_depth = 9;
struct schema_descriptor const * const schema_schema_descriptor = &schema_descriptor_helium_atom_api;
struct schema_info const * const schema_schema_info = &schema_info_helium_atom_api;
