#ifndef __CEA_RAND_H
#define __CEA_RAND_H

#include <cstdint>
#include <cstdlib>

#include <cea.h>

namespace cea
{
	/*
	   Cea PRNGs
	   All PRNGs are inspired by the work of George Marsaglia
	   and the excellent advice in Numerical Recipes.
	*/

	/*
	   Generator formed from an XOR shift and an MLCG.
	   + Period: ~=1.8 x 10^19 
	   + Speed: Fast
	*/
	class PrngMLCGXORShift : public Prng
	{
		public:
			PrngMLCGXORShift (uint64_t seed = 1);

			uint64_t rand();
			void srand(uint64_t seed);
		private:
			// State
			uint64_t x;
	};

	/*
	   Generator combining an XOR shift with an MWC generator.
	   + Period: ~= 8.5 x 10^37
	   + Speed: Medium
	*/
	class PrngMWCXORShift : public Prng
	{
		public:
			PrngMWCXORShift(uint64_t seed = 1);

			void srand(uint64_t seed);
			uint64_t rand();

		private:
			uint64_t x, y;
	};

	/*
	   KISS generator formed from 2 XOR shifts,
	   an LCG and an MWC.
	   + Period: ~= 3.1 x 10^57
	   + Speed: Slow
	*/
	class PrngKISS : public Prng
	{
		public:
			PrngKISS(uint64_t seed = 1);

			uint64_t rand();
			void srand(uint64_t seed);

		private:
			// State
			uint64_t u, v, w;
	};

	// Cea RVars
	template <typename T>
	class RVarUniform : public RVar<T>
	{
		public:
			// Constructors
			RVarUniform(Prng * src, T a = 0, T b = 0);

			void set_interval(T a, T b);
			void set_source(Prng * src);
			T rand();

		private:
			// Bounds
			T lower;
			T upper;

			// PRNG
			Prng * source;
	};

	class RVarNormal : public RVar<double>
	{
		public:
			// Constructors
			RVarNormal(Prng * src, uint64_t seed);

			void set_source(Prng * src);
			void srand(uint64_t seed);
			double rand();

		private:
			// PRNG
			Prng * source;
	};

	class RVarLogNormal : public RVar<double>
	{
		public:
			// Constructors
			RVarLogNormal(Prng * src, uint64_t seed);

			void set_source(Prng * src);
			void srand(uint64_t seed);
			double rand();

		private:
			// PRNG
			Prng * source;
	};

	class RVarPoisson : public RVar<uint64_t>
	{
		public:
			// Constructors
			RVarPoisson(Prng * src, uint64_t seed);

			void set_source(Prng * src);
			void srand(uint64_t seed);
			uint64_t rand();

		private:
			// PRNG
			Prng * source;
	};
}

#endif // __CEA_RAND_H
