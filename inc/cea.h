#ifndef __CEA_H
#define __CEA_H

#include <list>
#include <vector>
#include <cstdint>

namespace cea
{
	// Data structures.
	template <typename T>
	class Genome
	{
		public:
			Genome();
			Genome(int size);

			unsigned int size() { return genes.size(); };
			void resize(unsigned int size) { genes.resize(size); };
			typename std::list<T>::iterator begin() { return genes.begin(); };
			typename std::list<T>::iterator end() { return genes.end(); };

			double get_fitness() { return fitness; };
			void set_fitness(double f) { fitness = f; };
			bool is_avail() { return avail; };
			void set_avail(bool a) { avail = a; };

		private:
			double fitness;
			bool avail;
			std::list<T> genes;
	};

	template <typename T>
	class Pop
	{
		public:
			Pop(int p_s, int g_s);

			unsigned int size() { return pop.size(); };
			void resize(unsigned int size) { pop.resize(size); };
			typename std::vector< Genome<T> >::iterator begin() { return pop.begin(); };
			typename std::vector< Genome<T> >::iterator end() { return pop.end(); };
			// May want to add direct random access - []?

		private:
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
			void apply_to(Pop<T>& p);

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
			virtual T rand() = 0;
	};
}

#endif // __CEA_H
