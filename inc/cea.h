#ifndef __CEA_H
#define __CEA_H

#include <cstdint>

namespace cea
{
	class Popn
	{
		// empty
	};

	class Operator
	{
		public:
			virtual void apply_to(Popn pop) = 0;
	};

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
