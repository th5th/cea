/*
   Robert J. Jenkins Jr.'s ISAAC random number generator.

   C++ originally by Quinn Tyler Jackson 1998.
 */

#include <cstdint>

#include <cea-rand.h>

namespace cea
{
	const uint64_t GOLDEN_RATIO = static_cast<uint64_t>(0x9e3779b97f4a7c13);
	const int ALPHA = 8;
	const int N = 1<<ALPHA;	
	
	PrngISAAC::PrngISAAC(uint64_t seed)
	{
		srand(seed);
	}

	void PrngISAAC::srand(uint64_t seed)
	{
		for(int i = 0; i < N; i++)
		{
			m_rc.randrsl[i] = 0;
		}

		// Seed with a simple LCG.
		PrngLCG seeder(seed);
		m_rc.randa = seeder.rand();
		m_rc.randb = seeder.rand();
		m_rc.randc = seeder.rand();

		randinit(&m_rc);
	}
	
	PrngISAAC::randctx::randctx()
	{
		randrsl = static_cast<uint64_t*>(new uint64_t[N]);
		randmem = static_cast<uint64_t*>(new uint64_t[N]);
	}

	PrngISAAC::randctx::~randctx()
	{
		delete[] randrsl;
		delete[] randmem;
	}

	uint64_t PrngISAAC::rand()
	{
		return (!m_rc.randcnt-- ? (isaac(&m_rc), m_rc.randcnt=(N-1), m_rc.randrsl[m_rc.randcnt]) : m_rc.randrsl[m_rc.randcnt]);
	}

	void PrngISAAC::randinit(randctx* ctx)
	{
		int i;
		uint64_t a,b,c,d,e,f,g,h;

		a = b = c = d = e = f = g = h = GOLDEN_RATIO;

		uint64_t* m = (ctx->randmem);
		uint64_t* r = (ctx->randrsl);

		// Scramble it.
		for(i=0; i < 4; ++i)         
		{
			shuffle(a,b,c,d,e,f,g,h);
		}

		// Initialize using the contents of r[] as the seed.

		for(i=0; i < N; i+=8)
		{
			a+=r[i  ]; b+=r[i+1]; c+=r[i+2]; d+=r[i+3];
			e+=r[i+4]; f+=r[i+5]; g+=r[i+6]; h+=r[i+7];

			shuffle(a,b,c,d,e,f,g,h);

			m[i  ]=a; m[i+1]=b; m[i+2]=c; m[i+3]=d;
			m[i+4]=e; m[i+5]=f; m[i+6]=g; m[i+7]=h;
		}           

		// Do a second pass to make all of the seed affect all of m.

		for(i=0; i < N; i += 8)
		{
			a+=m[i  ]; b+=m[i+1]; c+=m[i+2]; d+=m[i+3];
			e+=m[i+4]; f+=m[i+5]; g+=m[i+6]; h+=m[i+7];

			shuffle(a,b,c,d,e,f,g,h);

			m[i  ]=a; m[i+1]=b; m[i+2]=c; m[i+3]=d;
			m[i+4]=e; m[i+5]=f; m[i+6]=g; m[i+7]=h;
		}

		// Fill in first result set and set count.
		isaac(ctx);
		ctx->randcnt = N;
	}

	inline uint64_t PrngISAAC::ind(uint64_t* mm, uint64_t x)
	{
		return (*(uint64_t*)((uint8_t*)(mm) + ((x) & ((N-1)<<3))));
	}

	inline void PrngISAAC::rngstep(uint64_t mix, uint64_t& a, uint64_t& b, uint64_t*& mm, uint64_t*& m, uint64_t*& m2, uint64_t*& r, uint64_t& x, uint64_t& y)
	{
		x = *m;  
		a = (a^(mix)) + *(m2++); 
		*(m++) = y = ind(mm,x) + a + b; 
		*(r++) = b = ind(mm,y>>ALPHA) + x; 
	}

	void PrngISAAC::shuffle(uint64_t& a, uint64_t& b, uint64_t& c, uint64_t& d, uint64_t& e, uint64_t& f, uint64_t& g, uint64_t& h)
	{ 
		a-=e; f^=h>>9;  h+=a;
		b-=f; g^=a<<9;  a+=b;
		c-=g; h^=b>>23; b+=c;
		d-=h; a^=c<<15; c+=d;
		e-=a; b^=d>>14; d+=e;
		f-=b; c^=e<<20; e+=f;
		g-=c; d^=f>>17; f+=g;
		h-=d; e^=g<<14; g+=h;
	}

	void PrngISAAC::isaac(randctx* ctx)
	{
		uint64_t x,y;

		uint64_t* mm = ctx->randmem;
		uint64_t* r  = ctx->randrsl;

		uint64_t a = (ctx->randa);
		uint64_t b = (ctx->randb + (++ctx->randc));

		uint64_t* m    = mm; 
		uint64_t* m2   = (m+(N/2));
		uint64_t* mend = m2;

		for(; m<mend; )
		{
			rngstep(~(a^(a<<21)), a, b, mm, m, m2, r, x, y);
			rngstep(  a^(a>>5)  , a, b, mm, m, m2, r, x, y);
			rngstep(  a^(a<<12) , a, b, mm, m, m2, r, x, y);
			rngstep(  a^(a>>33) , a, b, mm, m, m2, r, x, y);
		}

		m2 = mm;

		for(; m2<mend; )
		{
			rngstep(~(a^(a<<21)), a, b, mm, m, m2, r, x, y);
			rngstep(  a^(a>>5)  , a, b, mm, m, m2, r, x, y);
			rngstep(  a^(a<<12) , a, b, mm, m, m2, r, x, y);
			rngstep(  a^(a>>33) , a, b, mm, m, m2, r, x, y);
		}

		ctx->randb = b;
		ctx->randa = a;
	}
}
