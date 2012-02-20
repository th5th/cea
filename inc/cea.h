#ifndef __CEA_H
#define __CEA_H

#include <list>
#include <vector>
#include <cstdint>

namespace cea
{
	// Data structures.
	template <typename T>
	struct Genome
	{
		double fitness;
		bool avail;
		std::list<T> genes;
	};

	template <typename T>
	struct Pop
	{
		Pop(int p_s, int g_s)
		{
			pop_size = p_s;
			gno_size = g_s;

			pop.resize(p_s);
			typename std::vector< Genome<T> >::iterator it;
			for(it = pop.begin(); it != pop.end(); ++it)
				it->genes.resize(g_s);
		}

		// etc.
		~Pop()
		{
			// hold on...
		}

		int pop_size;
		int gno_size;
		std::vector< Genome<T> > pop;
	};

	// Operator classes.
	template <typename T>
	class OpPop
	{
		public:
			virtual void apply_to(Pop<T>& p) = 0;
	};

	template <typename T>
	class OpGenome : public OpPop<T>
	{
		public:
			void apply_to(Pop<T>& p)
			{
				typename std::vector< Genome<T> >::iterator it;
				for(it = p.pop.begin(); it != p.pop.end(); ++it)
					apply_tog(*it);
			}
		private:
			virtual void apply_tog(Genome<T>& g) = 0;
	};

	// Core algorithm class.
	template <typename T>
	class Cea
	{
		public:
			Cea();
			Cea(int n_i, int n_g);
			Cea(int n_i, int n_g, std::vector< OpPop<T>* > ops);
			~Cea();

			int get_pop_size();
			void set_pop_size(int p_s);

			int get_gno_size();
			void set_gno_size(int g_s);

			void add_op(OpPop<T>* op);
			void rm_last_op();
			void clear_pops();

			// Functions to set up output... Yawn.

			// The Big One.
			void run();

		private:
			std::vector< OpPop<T>* > operations;
			Pop<T> p;;


	};


	// Support classes to generate pseudo random numbers.
	class Prng
	{
		public:
			virtual void srand(uint64_t seed) = 0;
			virtual uint64_t rand() = 0;
	};

	template <typename T>
	class RVar
	{
		public:
			virtual void srand(uint64_t seed) = 0;
			virtual T rand() = 0;
	};
}

#endif // __CEA_H
