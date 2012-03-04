#ifndef __CEA_OP_H
#define __CEA_OP_H

#include <cea.h>
#include <deque>

namespace cea
{
	// Initialisers
	template <typename T>
	class OpInitRand : public OpGenome<T>
	{
		public:
			// Constructors
			OpInitRand(RVar<T> * src) { source = src; };

		private:
			RVar<T>* source;
			void apply_tog(Genome<T>& g);
	};

	template <typename T>
	class OpInitDeterm : public OpPop<T>
	{
		public:
			// Constructors

			void apply_to(Pop<T>& p);

		private:
			// Various
	};

	// Selectors
	template <typename T>
	class OpSelTournament : public OpPop<T>
	{
		public:
			// Constructors

			void apply_to(Pop<T>& p);

		private:
			// Various
	};

	template <typename T>
	class OpSelRoulette : public OpPop<T>
	{
		public:
			// Constructors

			void apply_to(Pop<T>& p);

		private:
			// Various
	};

	template <typename T>
	class OpSelTruncation : public OpPop<T>
	{
		public:
			// Constructors

			void apply_to(Pop<T>& p);

		private:
			// Various
	};

	// Crossovers
	template <typename T>
	class OpXoKpoint : public OpPop<T>
	{
		public:
			// Constructors
			OpXoKpoint(RVar<uint64_t> * src);

			void set_xop(int xop_i) { xop = xop_i; };
			void set_par(int par_i) { par = par_i; };

			void apply_to(Pop<T>& p);

		private:
			// Helper functions.
			void check_points(std::vector<uint64_t>& points, uint64_t s);
			void gen_points(std::vector<uint64_t>& points, uint64_t s);
			void do_xo(std::vector<uint64_t> points, std::deque< Genome<T>* >& p, std::deque< Genome<T>* >& c);

			RVar<uint64_t> * source;
			uint32_t xop;
			uint32_t par;
	};

	template <typename T>
	class OpXoProportionate : public OpPop<T>
	{
		public:
			// Constructors

			void apply_to(Pop<T>& p);

		private:
			// Various
	};

	// Mutators
	template <typename T>
	class OpMutOffset : public OpGenome<T>
	{
		public:
			// Constructors

		private:
			// Various
			void apply_tog(Pop<T>& p);
	};

	template <typename T>
	class OpMutGeneShuffle : public OpGenome<T>
	{
		public:
			// Constructors

		private:
			// Various
			void apply_tog(Pop<T>& p);
	};

	// Terminators
	template <typename T>
	class OpTermFixedTime : public OpPop<T>
	{
		public:
			// Constructors

			void apply_to(Pop<T>& p);

		private:
			// Various
	};

	template <typename T>
	class OpTermFitnessThresh : public OpPop<T>
	{
		public:
			// Constructors

			void apply_to(Pop<T>& p);

		private:
			// Various
	};
}

#endif // __CEA_OP_H
