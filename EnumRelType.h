#pragma once

enum RT	// Relocation Type
{
	RT_IMM32 = 32,
	RT_IMM2x16,
	RT_IMM16 = 16,

	RT_IMM18 = 18,
	RT_IMM21 = 21,
	RT_IMM21_PC,
	RT_IMM24 = 24,
	RT_IMM24_PC,
	RT_IMM8 = 8,
	RT_IMM5 = 5
};