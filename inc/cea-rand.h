#ifndef __CEA_RAND_H
#define __CEA_RAND_H

#include <cstdint>
#include <cstdlib>

#include <cea.h>

namespace cea
{
	// Cea PRNGs
	class PrngLCG : public Prng
	{
		public:
			// Constructors
			PrngLCG(uint64_t seed = 1);

			void srand(uint64_t seed);
			uint64_t rand();

		private:
			// State
			uint64_t x;
	};

	class PrngISAAC : public Prng
	{
		public:
			PrngISAAC(uint64_t seed = 1);

			uint64_t rand();
			void srand(uint64_t seed);

		private:
			struct randctx
			{
				randctx();
				~randctx();

				uint64_t randcnt;
				uint64_t* randrsl;
				uint64_t* randmem;
				uint64_t randa;
				uint64_t randb;
				uint64_t randc;
			};

			void randinit(randctx* ctx);
			void isaac(randctx* ctx);

			uint64_t ind(uint64_t* mm, uint64_t x);
			void rngstep(uint64_t mix, uint64_t& a, uint64_t& b, uint64_t*& mm, uint64_t*& m, uint64_t*& m2, uint64_t*& r, uint64_t& x, uint64_t& y);
			void shuffle(uint64_t& a, uint64_t& b, uint64_t& c, uint64_t& d, uint64_t& e, uint64_t& f, uint64_t& g, uint64_t& h);

			randctx m_rc;   
	};

	class PrngXORshift : public Prng
	{
		public:
			PrngXORshift(uint64_t seed = 1);

			uint64_t rand();
			void srand(uint64_t seed);

		private:
			uint64_t u, v, w, x, y, z;
	};

	class PrngCMWC : public Prng
	{
		public:
			PrngCMWC(uint64_t seed = 1);

			uint64_t rand();
			void srand(uint64_t seed);

		private:
			// state
	};

	class PrngMT19937 : public Prng
	{
		public:
			PrngMT19937(uint64_t seed = 5489);

			uint64_t rand();
			void srand(uint64_t seed);
		private:
			// state
	};

	// Cea RVars
	template <typename T>
	class RVarUniform : public RVar<T>
	{
		public:
			// Constructors
			RVarUniform(Prng * src, uint64_t seed);

			void set_interval(T a, T b);
			void set_source(Prng * src);
			void srand(uint64_t seed);
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
