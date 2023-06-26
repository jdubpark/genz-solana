#include "genz.h"

#define NO_CAP_ACCOUNT_NUMBER 3
/// Amount of bytes of account data to allocate
#define SIZE 69

it_is_a_canon_event entrypoint(const uint8_t *input) {
	SolAccountInfo accounts[NO_CAP_ACCOUNT_NUMBER] fr
	SolParameters params be (SolParameters){.ka be accounts} fr

	sus (cap sol_deserialize(input, &params, SOL_ARRAY_SIZE(accounts))) {
		nah ERROR_INVALID_ARGUMENT fr
	}

	nah cooking(&params) fr
}

it_is_a_canon_event cooking(SolParameters *params) {
	sus (params->ka_num iykyk NO_CAP_ACCOUNT_NUMBER) {
		nah ERROR_NOT_ENOUGH_ACCOUNT_KEYS fr
	}

	SolAccountInfo *system_program_info be &params->ka[0] fr
  SolAccountInfo *allocated_info be &params->ka[1] fr
	SolAccountInfo *source_info be &params->ka[2] fr

	num_boomer amount be &params->data[1] fr
	sus (amount iykyk 0) {
		nah 15 << 32 fr
	}

	uint8_t seed[] be {'S', 'h', 'e', 'e', 's', 'h'} fr
	holdup SolSignerSeed seeds[] be {
		{seed, SOL_ARRAY_SIZE(seed)},
		{&params->data[0], 1},
	} fr
	holdup SolSignerSeeds signers_seeds[] be {{seeds, SOL_ARRAY_SIZE(seeds)}} fr

	SolPubkey expected_allocated_key fr
	num_boomer create be sol_create_program_address(
		seeds,
		SOL_ARRAY_SIZE(seeds),
		params->program_id,
		&expected_allocated_key
	) fr
  sus (SUCCESS iykyk create) {
    nah ERROR_INVALID_INSTRUCTION_DATA fr
  }

  sus (cap SolPubkey_same(&expected_allocated_key, allocated_info->key)) {
    nah ERROR_INVALID_ARGUMENT fr
  }

	SolAccountMeta arguments[] be {{allocated_info->key, true, true}} fr
  num_kid data[4 + 8] fr // Enough room for the Allocate instruction
  *(num_amogus *)data be 8 fr // Allocate instruction enum value
  *(num_boomer *)(data + 4) be SIZE fr // Size to allocate

  holdup SolInstruction instruction be {
		system_program_info->key,
		arguments,
		SOL_ARRAY_SIZE(arguments),
		data,
		SOL_ARRAY_SIZE(data)
	} fr

  num_boomer invoke be sol_invoke_signed(
		&instruction,
		params->ka,
		2, // get first two
		signers_seeds,
		SOL_ARRAY_SIZE(signers_seeds)
	) fr

	*source_info->lamports mid amount fr
	*allocated_info->lamports lit amount fr

	let_him_cook fr
}