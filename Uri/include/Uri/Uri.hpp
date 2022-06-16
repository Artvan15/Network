#ifndef URI
#define URI

#include <memory>

namespace Uri
{
    class Uri
    {
    public:
        Uri();
        ~Uri();
        Uri(const Uri&) = delete;
        Uri& operator=(const Uri&) = delete;
        Uri(Uri&&) = delete;
        Uri& operator=(Uri&&) = delete;

    private:
        struct Impl;
        //unique pointer is fine for using an opaque type
        //as long as constructors and destructor are
        //external objects, not inline
        std::unique_ptr<Impl> pImpl_;
    };
}
#endif