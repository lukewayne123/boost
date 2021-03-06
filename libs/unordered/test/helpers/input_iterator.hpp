
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_UNORDERED_TEST_HELPERS_INPUT_ITERATOR_HEADER)
#define BOOST_UNORDERED_TEST_HELPERS_INPUT_ITERATOR_HEADER

#include <boost/config.hpp>
#include <boost/iterator.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace test
{
    template <class Iterator>
    struct proxy
    {
        typedef BOOST_DEDUCED_TYPENAME Iterator::value_type value_type;

        explicit proxy(value_type const& v) : v_(v) {}
        proxy(proxy const& x) : v_(x.v_) {}
        operator value_type const&() const { return v_; }
        
        value_type v_;
    private:
        proxy& operator=(proxy const&);
    };

    template <class Iterator>
    struct input_iterator_adaptor
        : public boost::iterator<
            std::input_iterator_tag,
            BOOST_DEDUCED_TYPENAME boost::iterator_value<Iterator>::type,
            std::ptrdiff_t,
            BOOST_DEDUCED_TYPENAME boost::iterator_pointer<Iterator>::type,
            proxy<Iterator>
        >
    {
        typedef BOOST_DEDUCED_TYPENAME boost::iterator_value<Iterator>::type
            value_type;
    
        input_iterator_adaptor()
            : base_() {}
        explicit input_iterator_adaptor(Iterator& it)
            : base_(&it) {}
        proxy<Iterator> operator*() const {
            return proxy<Iterator>(**base_);
        }
        value_type* operator->() const {
            return &**base_;
        }
        input_iterator_adaptor& operator++() {
            ++*base_; return *this;
        }
        //input_iterator_adaptor operator++(int) {
        //}
        bool operator==(input_iterator_adaptor const& x) const {
            return *base_ == *x.base_;
        }
        bool operator!=(input_iterator_adaptor const& x) const {
            return *base_ != *x.base_;
        }
    private:
        Iterator* base_;
    };

    template <class Iterator>
    input_iterator_adaptor<Iterator> input_iterator(Iterator& it)
    {
        return input_iterator_adaptor<Iterator>(it);
    }
}

#endif

