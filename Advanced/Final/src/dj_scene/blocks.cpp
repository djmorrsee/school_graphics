#include "../dj.h"
#include "blocks.h"
#include <map>
#include <vector>

using std::vector;

block::block(int id) {
	block_id = id;
}

block::block(block *b) {
	block_id = b->GetID();
}

float block::GetID() {
	return float(block_id);
}
