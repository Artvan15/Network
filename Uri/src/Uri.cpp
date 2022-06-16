#include "Uri/Uri.hpp"


namespace Uri
{
    struct Uri::Impl
    {

    };

    Uri::Uri()
        : pImpl_(std::make_unique<Impl>()) {}
    
    Uri::~Uri() = default;

}
