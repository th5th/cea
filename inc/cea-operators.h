#ifndef __CEA_OP_H
#define __CEA_OP_H

namespace cea
{
	// Initialisers
	class OpInitRand : public Operator
	{
		public:
			// Constructors
			OpInitRand();
			OpInitRand(RVar * rv);

			void apply_to(Popn pop);

		private:
			// Various
	};

	class OpInitDeterm : public Operator
	{
		public:
			// Constructors

			void apply_to(Popn pop);

		private:
			// Various
	};

	// Selectors
	class OpSelTournament : public Operator
	{
		public:
			// Constructors

			void apply_to(Popn pop);

		private:
			// Various
	};

	class OpSelRoulette : public Operator
	{
		public:
			// Constructors

			void apply_to(Popn pop);

		private:
			// Various
	};

	class OpSelTruncation : public Operator
	{
		public:
			// Constructors

			void apply_to(Popn pop);

		private:
			// Various
	};

	// Crossovers
	class OpXoKpoint : public Operator
	{
		public:
			// Constructors

			void apply_to(Popn pop);

		private:
			// Various
	};

	class OpXoProportionate : public Operator
	{
		public:
			// Constructors

			void apply_to(Popn pop);

		private:
			// Various
	};

	// Mutators
	class OpMutOffset : public Operator
	{
		public:
			// Constructors

			void apply_to(Popn pop);

		private:
			// Various
	};

	class OpMutGeneShuffle : public Operator
	{
		public:
			// Constructors

			void apply_to(Popn pop);

		private:
			// Various
	};

	// Terminators
	class OpTermFixedTime : public Operator
	{
		public:
			// Constructors

			void apply_to(Popn pop);

		private:
			// Various
	};

	class OpTermFitnessThresh : public Operator
	{
		public:
			// Constructors

			void apply_to(Popn pop);

		private:
			// Various
	};
}

#endif // __CEA_OP_H
