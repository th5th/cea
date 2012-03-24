// Fully templated edition.
// TODO Allow variable number of children independent of parents.
#ifndef CEA_XO_2POINT_HPP
#define CEA_XO_2POINT_HPP

template <template <class U1, class U2 = std::allocator<U1> > class COuter,
         template <class V1, class V2 = std::allocator<V1> > class CInner,
         typename T>
class op_xo_2point
{
    public:
        // Constructors
        op_xo_2point(rvar<unsigned int> * src, unsigned int n_xo_ps)
            : source(src), num_xo_points(n_xo_ps) { }

        void operator()(pop<COuter,CInner,T>& p)
        {
            // Needed in call to do_xo:
            genome_length = p.begin()->size();

            // Parents are guaranteed unchanged later.
            std::vector<const_genome_pointer> parents;
            std::vector<genome_pointer> children;
            parents.reserve(p.size()/2);
            children.reserve(p.size()/2);

            // Need to figure out most efficient way to do this.......
            auto p_it = p.begin();
            for(; p_it != p.end(); ++p_it)
            {
                if(p_it->alive() == false)
                {
                    children.push_back(&(*p_it));
                }
                else
                {
                    parents.push_back(&(*p_it));
                }
            }

            auto child_it = children.begin();
            auto parent_it = parents.begin();
            for(; parent_it != parents.end() && child_it != children.end();
                parent_it+=2, child_it+=2)
            {
                do_xo(*parent_it, *(parent_it+1), *child_it, *(child_it+1));
            }
        }

    private:
        // Abbreviating typedefs.
        typedef typename pop<COuter,CInner,T>::const_pointer
            const_genome_pointer;
        typedef typename pop<COuter,CInner,T>::pointer
            genome_pointer;

        rvar<unsigned int> * source;
        unsigned int num_xo_points;
        unsigned int genome_length;

        // Cross-over genomes pointed by p1 and p2 into genomes
        // pointed by c1 and c2.
        void do_xo(const_genome_pointer p1, const_genome_pointer p2,
                genome_pointer c1, genome_pointer c2)
        {
            // Generate some points.
            std::vector<unsigned int> points(num_xo_points+2,0);
            for(unsigned int i = 1; i < num_xo_points+1; ++i)
            {
                points[i] = source->rand() % genome_length;
            }
            points[num_xo_points+1] = genome_length;

            // Sort and cull repeated els.
            std::sort(points.begin(), points.end());
            auto new_end_it = std::unique(points.begin(), points.end());
            points.resize(new_end_it - points.begin());

            // These loops ensure we have enough unique points.
            while(points.size() != num_xo_points+2)
            {
                while(points.size() < num_xo_points+2)
                {
                    points.push_back(source->rand() % genome_length);
                }
                // Sort and cull repeated els.
                std::sort(points.begin(), points.end());
                new_end_it = std::unique(points.begin(), points.end());
                points.resize(new_end_it - points.begin());
            }

            for(unsigned int i = 1; i < points.size(); ++i)
            {
                if(i&1)
                {
                    std::copy(p1->begin() + points[i-1],
                            p1->begin() + points[i],
                            c1->begin() + points[i-1]);
                    std::copy(p2->begin() + points[i-1],
                            p2->begin() + points[i],
                            c2->begin() + points[i-1]);
                }
                else
                {
                    std::copy(p2->begin() + points[i-1],
                            p2->begin() + points[i],
                            c1->begin() + points[i-1]);
                    std::copy(p1->begin() + points[i-1],
                            p1->begin() + points[i],
                            c2->begin() + points[i-1]);
                }
            }

            // Set flags
            c1->alive(true); c1->evald(false);
            c2->alive(true); c2->evald(false);

            return;
        }
};

#endif // CEA_XO_2POINT_HPP
