#include <type_traits>
#include <string>
#include <iostream>
#include <sstream>

#include <Cea/Core>
#include <Cea/Random>

using namespace cea;

// Histogram data class.
template <typename T, typename Enable = void>
class Histogram;

template <typename T>
class Histogram <T, typename std::enable_if< std::is_arithmetic<T>::value >::type>
{
    public:
        Histogram(T s, T p, T e)
        {
            config_bins(s, p, e);
            // Format defaults.
            l_space = 5;
            width = 150;
            mark = '#';
        }

        void config_bins(T s, T p, T e)
        {
            // Check polarity of start and end.
            if(s+p > e)
            {
                throw("Bad start, pitch or end value.");
            }
            
            // Check that start + n*pitch = end.
            int n = static_cast<int>((e-s)/p);
            if(n*p!= e-s)
            {
                throw("Pitch value does not give integer number of bins.");
            }

            start = s; pitch = p; end = e;
            bins.clear();
            n_vals = 0;
            bins.resize(n);
        }

        void config_format(int l, int w, char m, bool ll)
        {
            l_space = l;
            mark = m;
            width = w;
            long_label = ll;
        }

        void add(T val)
        {
            // Add val to the histogram.
            unsigned int i = std::floor((val - start) / pitch);
            if(i < bins.size())
            {
                ++n_vals;
                ++bins[i];
            }
            else
            {
                std::cout << "Val out of bin range." << std::endl;
            }
        }

        void print() const
        {
            // Print the histogram.
            for(unsigned int i = 0; i < bins.size(); ++i)
            {
                std::stringstream label(std::stringstream::out);
                label << i;
                std::cout << make_rowstart(label.str());
                std::cout << make_bar(i);
                std::cout << std::endl;
            }
            std::cout << make_axis() << std::endl;
        }

    private:
        // Drawing helpers.
        std::string make_rowstart(std::string const& label) const
        {
            std::stringstream ss(std::stringstream::out);
            ss.width(l_space);
            ss << label;
            ss << "|";
            return ss.str();
        }

        std::string make_bar(int i) const
        {
            // Draw a bar.
            double temp = static_cast<double>(bins[i]) / static_cast<double>(n_vals);
            int length = static_cast<int>(std::floor(temp*width + 0.5));
            std::string bar(length, mark);
            return bar;
        }

        std::string make_axis() const
        {
            // Draw axis at bottoms.
            std::string axis(l_space, ' ');
            axis += "|";
            std::string axis_line(width/10 - 1, '-');
            for(unsigned int i = 0; i < 4; ++i)
            {
                axis += axis_line;
                axis += "|";
            }
            
            return axis;
        }

        T start, pitch, end;
        int l_space, width;
        char mark;
        bool long_label;
        std::vector<int> bins;
        int n_vals;
};

bool test_rvarnormal()
{
    PrngKISS p;
    RVarNormal<int32_t> r(&p, 0, 3);

    Histogram<int32_t> h(-15, 1, 15);
    //h.config_format(12, 100, '*', true);

    for(unsigned int i = 0; i < 100000; ++i)
        h.add(r.rand());

    //h.print();

    bool test_failed = false;
    return test_failed;
}
